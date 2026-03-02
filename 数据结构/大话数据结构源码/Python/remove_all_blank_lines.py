import pathlib

def clean_file(file_path):
    """清理文件：删除所有空行，并去除行尾空白"""
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
    for line in lines:
        stripped = line.rstrip()          # 删除行尾空白
        if stripped:                       # 如果非空（空字符串为 False）
            cleaned.append(stripped)       # 只保留非空行
        # 空行直接跳过，不添加到 cleaned

    # 写回文件
    try:
        with open(file_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write('\n'.join(cleaned))
            # 如果原文件非空且最后一行没有换行，添加一个换行符（规范）
            if cleaned:
                f.write('\n')
        print(f"✅ 已清理: {file_path} (删除了所有空行)")
    except Exception as e:
        print(f"❌ 写入失败 {file_path}: {e}")

def main():
    # ===== 你的路径（已设置） =====
    target_folder = r"D:\C and C++\C++黑马学习\数据结构\大话数据结构源码\源码"
    # ============================

    # 要处理的文件扩展名（可自行增减）
    extensions = ['.c', '.h', '.cpp', '.hpp', '.txt', '.md', '.cc', '.cxx']

    folder = pathlib.Path(target_folder)
    if not folder.exists():
        print(f"❌ 文件夹不存在：{target_folder}")
        return

    print(f"开始清理文件夹（删除所有空行）：{target_folder}")
    for ext in extensions:
        for file_path in folder.rglob(f'*{ext}'):
            if file_path.is_file():
                clean_file(file_path)
    print("🎉 全部处理完成！")

if __name__ == '__main__':
    main()