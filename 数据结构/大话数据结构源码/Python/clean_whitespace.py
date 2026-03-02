import pathlib

def clean_file(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except UnicodeDecodeError:
        print(f"⚠️ 跳过非 UTF-8 文件: {file_path}")
        return
    except Exception as e:
        print(f"❌ 读取失败 {file_path}: {e}")
        return

    cleaned = []
    blank_count = 0

    for line in lines:
        stripped = line.rstrip()
        if stripped == '':
            blank_count += 1
            if blank_count == 1:
                cleaned.append('')
        else:
            blank_count = 0
            cleaned.append(stripped)

    try:
        with open(file_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write('\n'.join(cleaned))
            if cleaned and not cleaned[-1].endswith('\n'):
                f.write('\n')
        print(f"✅ 已清理: {file_path}")
    except Exception as e:
        print(f"❌ 写入失败 {file_path}: {e}")

def main():
    # ===== 请确认这个路径是否正确 =====
    target_folder = r"D:\C and C++\C++黑马学习\数据结构\大话数据结构源码\源码"
    # ================================

    extensions = ['.c', '.h', '.cpp', '.hpp', '.txt', '.md', '.cc', '.cxx']

    folder = pathlib.Path(target_folder)
    if not folder.exists():
        print(f"❌ 文件夹不存在：{target_folder}")
        return

    print(f"开始清理文件夹：{target_folder}")
    for ext in extensions:
        for file_path in folder.rglob(f'*{ext}'):
            if file_path.is_file():
                clean_file(file_path)
    print("🎉 全部处理完成！")

if __name__ == '__main__':
    main()