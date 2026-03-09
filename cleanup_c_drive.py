#!/usr/bin/env python3
"""
Safe C: drive cleanup helper for Windows.

Features:
- Find junk files by extension/name
- Find duplicate files by size + SHA256
- Dry-run by default (no file changes)
- Optional execution mode to move files into a quarantine folder or delete them
- Restore quarantined files from a previous CSV report
- CSV report output

Usage examples:
  python cleanup_c_drive.py
  python cleanup_c_drive.py --root C:\\ --apply
  python cleanup_c_drive.py --apply --junk-action quarantine --dedupe-action quarantine
  python cleanup_c_drive.py --apply --junk-action delete --dedupe-action delete
  python cleanup_c_drive.py --restore-from-report .\\cleanup_apply.csv
  python cleanup_c_drive.py --restore-from-report .\\cleanup_apply.csv --apply
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import os
import shutil
import sys
import time
from dataclasses import dataclass
from datetime import datetime
from typing import Dict, Iterable, List, Tuple


DEFAULT_EXCLUDED_DIRS = [
    "Windows",
    "Program Files",
    "Program Files (x86)",
    "ProgramData",
    "$Recycle.Bin",
    "System Volume Information",
    "Recovery",
    "PerfLogs",
]

DEFAULT_JUNK_EXTENSIONS = {
    ".tmp",
    ".temp",
    ".bak",
    ".old",
    ".log",
    ".dmp",
    ".chk",
    ".gid",
    ".etl",
    ".cache",
}

DEFAULT_JUNK_NAMES = {
    "thumbs.db",
    ".ds_store",
}


@dataclass
class Candidate:
    path: str
    size: int
    reason: str


@dataclass
class RestoreCandidate:
    source_path: str
    target_path: str
    category: str
    size: int


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Cleanup junk and duplicate files safely.")
    parser.add_argument("--root", default=r"C:\\", help="Scan root path. Default: C:\\")
    parser.add_argument(
        "--quarantine",
        default=os.path.join(os.path.expanduser("~"), "cleanup_quarantine"),
        help="Folder where files are moved when action is quarantine.",
    )
    parser.add_argument(
        "--junk-action",
        choices=["none", "quarantine", "delete"],
        default="quarantine",
        help="Action for junk files.",
    )
    parser.add_argument(
        "--dedupe-action",
        choices=["none", "quarantine", "delete"],
        default="quarantine",
        help="Action for duplicate files (keeps one file per duplicate group).",
    )
    parser.add_argument(
        "--min-duplicate-size",
        type=int,
        default=1,
        help="Ignore duplicate checks below this file size (bytes).",
    )
    parser.add_argument(
        "--report",
        default=f"cleanup_report_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv",
        help="Output CSV report path.",
    )
    parser.add_argument(
        "--restore-from-report",
        default="",
        help="Restore mode: read a previous cleanup report and move quarantined files back.",
    )
    parser.add_argument(
        "--apply",
        action="store_true",
        help="Actually perform actions. If omitted, runs in dry-run mode for cleanup/restore.",
    )
    parser.add_argument(
        "--follow-links",
        action="store_true",
        help="Follow symbolic links. Off by default.",
    )
    return parser.parse_args()


def normalize_path(path: str) -> str:
    return os.path.normcase(os.path.abspath(path))


def make_excluded_paths(root: str, extra_paths: Iterable[str]) -> List[str]:
    root_abs = os.path.abspath(root)
    excluded = [normalize_path(os.path.join(root_abs, item)) for item in DEFAULT_EXCLUDED_DIRS]
    excluded.extend(normalize_path(p) for p in extra_paths)
    return excluded


def is_within(path: str, prefixes: Iterable[str]) -> bool:
    path_n = normalize_path(path)
    for pref in prefixes:
        if path_n == pref or path_n.startswith(pref + os.sep):
            return True
    return False


def is_junk_file(filename: str) -> bool:
    lower = filename.lower()
    _, ext = os.path.splitext(lower)
    if lower in DEFAULT_JUNK_NAMES:
        return True
    if ext in DEFAULT_JUNK_EXTENSIONS:
        return True
    if lower.startswith("~$"):
        return True
    return False


def hash_file(path: str, chunk_size: int = 1024 * 1024) -> str | None:
    digest = hashlib.sha256()
    try:
        with open(path, "rb") as f:
            while True:
                data = f.read(chunk_size)
                if not data:
                    break
                digest.update(data)
        return digest.hexdigest()
    except OSError:
        return None


def safe_mtime(path: str) -> float:
    try:
        return os.path.getmtime(path)
    except OSError:
        return 0.0


def build_quarantine_target(quarantine_root: str, source_path: str) -> str:
    drive, tail = os.path.splitdrive(os.path.abspath(source_path))
    drive_folder = drive.replace(":", "") if drive else "no_drive"
    clean_tail = tail.lstrip("\\/")
    target = os.path.join(quarantine_root, drive_folder, clean_tail)
    if not os.path.exists(target):
        return target

    base, ext = os.path.splitext(target)
    index = 1
    while True:
        candidate = f"{base}_{index}{ext}"
        if not os.path.exists(candidate):
            return candidate
        index += 1


def scan_files(
    root: str,
    excluded_paths: List[str],
    follow_links: bool,
) -> Tuple[List[Candidate], Dict[int, List[str]], List[str], int]:
    junk_candidates: List[Candidate] = []
    size_buckets: Dict[int, List[str]] = {}
    skipped_paths: List[str] = []
    scanned_files = 0

    def onerror(err: OSError) -> None:
        if getattr(err, "filename", None):
            skipped_paths.append(err.filename)

    for dirpath, dirnames, filenames in os.walk(root, topdown=True, onerror=onerror, followlinks=follow_links):
        # Skip excluded directories early to reduce scan cost and risk.
        filtered_dirs = []
        for d in dirnames:
            full = os.path.join(dirpath, d)
            if not is_within(full, excluded_paths):
                filtered_dirs.append(d)
        dirnames[:] = filtered_dirs

        for name in filenames:
            full_path = os.path.join(dirpath, name)
            if is_within(full_path, excluded_paths):
                continue
            try:
                size = os.path.getsize(full_path)
            except OSError:
                skipped_paths.append(full_path)
                continue

            scanned_files += 1
            size_buckets.setdefault(size, []).append(full_path)

            if is_junk_file(name):
                junk_candidates.append(Candidate(full_path, size, "junk_pattern"))

            if scanned_files % 25000 == 0:
                print(f"[scan] scanned_files={scanned_files}", flush=True)

    return junk_candidates, size_buckets, skipped_paths, scanned_files


def find_duplicate_candidates(
    size_buckets: Dict[int, List[str]],
    min_duplicate_size: int,
) -> Tuple[List[Candidate], int]:
    hash_buckets: Dict[Tuple[int, str], List[str]] = {}
    compared_files = 0

    duplicate_sizes = [size for size, files in size_buckets.items() if size >= min_duplicate_size and len(files) > 1]
    duplicate_sizes.sort(reverse=True)

    for idx, size in enumerate(duplicate_sizes, start=1):
        files = size_buckets[size]
        for path in files:
            file_hash = hash_file(path)
            if file_hash is None:
                continue
            hash_buckets.setdefault((size, file_hash), []).append(path)
            compared_files += 1

        if idx % 200 == 0:
            print(f"[hash] size_groups_done={idx}/{len(duplicate_sizes)} compared_files={compared_files}", flush=True)

    duplicate_candidates: List[Candidate] = []
    duplicate_groups = 0
    for (size, _file_hash), files in hash_buckets.items():
        if len(files) <= 1:
            continue
        duplicate_groups += 1
        # Keep most recently modified file, process others.
        keep_path = max(files, key=safe_mtime)
        for p in files:
            if p == keep_path:
                continue
            duplicate_candidates.append(Candidate(p, size, "duplicate"))

    return duplicate_candidates, duplicate_groups


def ensure_parent(path: str) -> None:
    parent = os.path.dirname(path)
    if parent:
        os.makedirs(parent, exist_ok=True)


def extract_message_value(message: str, key: str) -> str | None:
    prefix = f"{key}="
    if not message.startswith(prefix):
        return None
    value = message[len(prefix) :].strip()
    if not value:
        return None
    # Keep compatibility with optional metadata in message, e.g. "moved_to=...;warning=...".
    return value.split(";", 1)[0].strip()


def move_with_fallback(source_path: str, target_path: str) -> Tuple[bool, str]:
    """
    Move file to target.
    If direct move fails, try copy+delete. In constrained environments delete may fail;
    in that case return success with a warning because target file is already restored/quarantined.
    """
    ensure_parent(target_path)
    try:
        os.replace(source_path, target_path)
        return True, "moved"
    except OSError as move_exc:
        try:
            shutil.copy2(source_path, target_path)
        except OSError as copy_exc:
            return False, f"move_failed={move_exc};copy_failed={copy_exc}"
        try:
            os.remove(source_path)
            return True, "copied_then_removed_source"
        except OSError as remove_exc:
            return True, f"copied_only;source_not_removed={remove_exc}"


def process_candidates(
    candidates: List[Candidate],
    action: str,
    dry_run: bool,
    quarantine_root: str,
    report_rows: List[List[str]],
    seen_paths: set,
) -> Tuple[int, int, int]:
    processed = 0
    failed = 0
    reclaimable_bytes = 0

    for item in candidates:
        if item.path in seen_paths:
            continue
        seen_paths.add(item.path)

        processed += 1
        reclaimable_bytes += item.size

        if action == "none":
            report_rows.append([item.reason, action, item.path, str(item.size), "skipped", "action=none"])
            continue

        if dry_run:
            report_rows.append([item.reason, action, item.path, str(item.size), "planned", "dry_run"])
            continue

        try:
            if action == "delete":
                os.remove(item.path)
                report_rows.append([item.reason, action, item.path, str(item.size), "ok", "deleted"])
            elif action == "quarantine":
                target = build_quarantine_target(quarantine_root, item.path)
                ok, move_msg = move_with_fallback(item.path, target)
                status = "ok" if ok else "failed"
                message = f"moved_to={target}" if ok else move_msg
                if ok and move_msg != "moved":
                    message = f"{message};warning={move_msg}"
                report_rows.append([item.reason, action, item.path, str(item.size), status, message])
                if not ok:
                    failed += 1
            else:
                report_rows.append([item.reason, action, item.path, str(item.size), "skipped", "unknown_action"])
        except OSError as exc:
            failed += 1
            report_rows.append([item.reason, action, item.path, str(item.size), "failed", str(exc)])

    return processed, failed, reclaimable_bytes


def load_restore_candidates(report_path: str) -> Tuple[List[RestoreCandidate], int]:
    candidates: List[RestoreCandidate] = []
    total_rows = 0
    seen_pairs = set()

    with open(report_path, "r", newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        required_columns = {"category", "action", "path", "size_bytes", "status", "message"}
        if reader.fieldnames is None or not required_columns.issubset(set(reader.fieldnames)):
            raise ValueError("invalid report format: required columns are missing")

        for row in reader:
            total_rows += 1
            action = (row.get("action") or "").strip().lower()
            status = (row.get("status") or "").strip().lower()
            message = (row.get("message") or "").strip()
            target_path = (row.get("path") or "").strip()
            category = (row.get("category") or "").strip() or "unknown"

            if action != "quarantine" or status != "ok":
                continue
            if not target_path:
                continue

            source_path = extract_message_value(message, "moved_to")
            if not source_path:
                continue

            try:
                size = int((row.get("size_bytes") or "0").strip())
            except ValueError:
                size = 0

            key = (normalize_path(source_path), normalize_path(target_path))
            if key in seen_pairs:
                continue
            seen_pairs.add(key)

            candidates.append(
                RestoreCandidate(
                    source_path=source_path,
                    target_path=target_path,
                    category=category,
                    size=max(0, size),
                )
            )

    return candidates, total_rows


def process_restore_candidates(
    candidates: List[RestoreCandidate],
    dry_run: bool,
    report_rows: List[List[str]],
) -> Tuple[int, int, int, int]:
    processed = 0
    restored = 0
    skipped = 0
    failed = 0

    for item in candidates:
        processed += 1

        if dry_run:
            report_rows.append(
                [
                    item.category,
                    "restore",
                    item.target_path,
                    str(item.size),
                    "planned",
                    f"from={item.source_path}",
                ]
            )
            continue

        if not os.path.exists(item.source_path):
            skipped += 1
            report_rows.append(
                [
                    item.category,
                    "restore",
                    item.target_path,
                    str(item.size),
                    "skipped",
                    f"source_missing={item.source_path}",
                ]
            )
            continue

        if os.path.exists(item.target_path):
            skipped += 1
            report_rows.append(
                [
                    item.category,
                    "restore",
                    item.target_path,
                    str(item.size),
                    "skipped",
                    "target_exists",
                ]
            )
            continue

        try:
            ok, move_msg = move_with_fallback(item.source_path, item.target_path)
            if ok:
                restored += 1
                message = f"restored_from={item.source_path}"
                if move_msg != "moved":
                    message = f"{message};warning={move_msg}"
                report_rows.append(
                    [
                        item.category,
                        "restore",
                        item.target_path,
                        str(item.size),
                        "ok",
                        message,
                    ]
                )
            else:
                failed += 1
                report_rows.append(
                    [
                        item.category,
                        "restore",
                        item.target_path,
                        str(item.size),
                        "failed",
                        move_msg,
                    ]
                )
        except OSError as exc:
            failed += 1
            report_rows.append(
                [
                    item.category,
                    "restore",
                    item.target_path,
                    str(item.size),
                    "failed",
                    str(exc),
                ]
            )

    return processed, restored, skipped, failed


def write_report(report_path: str, rows: List[List[str]], skipped_paths: List[str]) -> None:
    ensure_parent(os.path.abspath(report_path))
    with open(report_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["category", "action", "path", "size_bytes", "status", "message"])
        writer.writerows(rows)
        for skipped in skipped_paths:
            writer.writerow(["scan", "none", skipped, "0", "skipped", "scan_failed_or_no_permission"])


def human_bytes(size: int) -> str:
    units = ["B", "KB", "MB", "GB", "TB"]
    value = float(size)
    for unit in units:
        if value < 1024.0 or unit == units[-1]:
            return f"{value:.2f}{unit}"
        value /= 1024.0
    return f"{size}B"


def main() -> int:
    args = parse_args()
    dry_run = not args.apply

    if args.restore_from_report:
        restore_report_path = os.path.abspath(args.restore_from_report)
        output_report_path = os.path.abspath(args.report)
        if normalize_path(restore_report_path) == normalize_path(output_report_path):
            print("[error] --restore-from-report and --report must be different paths", file=sys.stderr)
            return 2
        if not os.path.exists(restore_report_path):
            print(f"[error] restore report not found: {restore_report_path}", file=sys.stderr)
            return 2

        print("[info] Restore start")
        print(f"[info] dry_run={dry_run}")
        print(f"[info] restore_from_report={restore_report_path}")
        print(f"[info] report={output_report_path}")

        start_time = time.time()
        try:
            restore_candidates, total_rows = load_restore_candidates(restore_report_path)
        except (OSError, ValueError) as exc:
            print(f"[error] failed to load restore report: {exc}", file=sys.stderr)
            return 2

        restore_rows: List[List[str]] = []
        processed, restored, skipped, failed = process_restore_candidates(
            candidates=restore_candidates,
            dry_run=dry_run,
            report_rows=restore_rows,
        )

        try:
            write_report(output_report_path, restore_rows, [])
        except OSError as exc:
            print(f"[error] failed to write report: {exc}", file=sys.stderr)
            return 2

        elapsed = time.time() - start_time
        print("[info] Restore finished")
        print(f"[summary] input_rows={total_rows}")
        print(f"[summary] restore_candidates={processed}")
        print(f"[summary] restored={restored}")
        print(f"[summary] skipped={skipped}")
        print(f"[summary] failed_actions={failed}")
        print(f"[summary] report={output_report_path}")
        print(f"[summary] elapsed_seconds={elapsed:.2f}")
        if dry_run:
            print("[next] Re-run with --apply to perform restore.")
        return 0

    root = os.path.abspath(args.root)
    if not os.path.exists(root):
        print(f"[error] root not found: {root}", file=sys.stderr)
        return 2

    quarantine_root = os.path.abspath(args.quarantine)
    excluded_paths = make_excluded_paths(root, [quarantine_root, os.path.abspath(args.report)])

    print("[info] Cleanup start")
    print(f"[info] root={root}")
    print(f"[info] dry_run={dry_run}")
    print(f"[info] junk_action={args.junk_action}")
    print(f"[info] dedupe_action={args.dedupe_action}")
    print(f"[info] report={os.path.abspath(args.report)}")
    if not dry_run and (args.junk_action == "quarantine" or args.dedupe_action == "quarantine"):
        print(f"[info] quarantine_root={quarantine_root}")

    start_time = time.time()

    junk_candidates, size_buckets, skipped_paths, scanned_files = scan_files(
        root=root,
        excluded_paths=excluded_paths,
        follow_links=args.follow_links,
    )

    duplicate_candidates, duplicate_groups = find_duplicate_candidates(
        size_buckets=size_buckets,
        min_duplicate_size=max(0, args.min_duplicate_size),
    )

    duplicate_paths = {x.path for x in duplicate_candidates}
    junk_candidates = [x for x in junk_candidates if x.path not in duplicate_paths]

    report_rows: List[List[str]] = []
    seen_paths: set = set()

    dup_processed, dup_failed, dup_reclaim = process_candidates(
        candidates=duplicate_candidates,
        action=args.dedupe_action,
        dry_run=dry_run,
        quarantine_root=quarantine_root,
        report_rows=report_rows,
        seen_paths=seen_paths,
    )

    junk_processed, junk_failed, junk_reclaim = process_candidates(
        candidates=junk_candidates,
        action=args.junk_action,
        dry_run=dry_run,
        quarantine_root=quarantine_root,
        report_rows=report_rows,
        seen_paths=seen_paths,
    )

    try:
        write_report(args.report, report_rows, skipped_paths)
    except OSError as exc:
        print(f"[error] failed to write report: {exc}", file=sys.stderr)
        return 2

    elapsed = time.time() - start_time
    total_reclaim = dup_reclaim + junk_reclaim
    total_failed = dup_failed + junk_failed

    print("[info] Cleanup finished")
    print(f"[summary] scanned_files={scanned_files}")
    print(f"[summary] duplicate_groups={duplicate_groups}")
    print(f"[summary] duplicate_candidates={dup_processed}")
    print(f"[summary] junk_candidates={junk_processed}")
    print(f"[summary] failed_actions={total_failed}")
    print(f"[summary] skipped_scan_paths={len(skipped_paths)}")
    print(f"[summary] reclaimable={human_bytes(total_reclaim)}")
    print(f"[summary] report={os.path.abspath(args.report)}")
    print(f"[summary] elapsed_seconds={elapsed:.2f}")
    if dry_run:
        print("[next] Re-run with --apply after reviewing report.")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
