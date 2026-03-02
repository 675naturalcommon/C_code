import pathlib
import chardet

def convert_to_utf8(file_path):
    with open(file_path, 'rb') as f:
        raw = f.read()
        # 自动检测原始编码
        result = chardet.detect(raw)
        source_encoding = result['encoding'] or 'gbk'
        print(f"检测到 {file_path} 编码为: {source_encoding}")

        # 如果已经是 UTF-8，跳过以节省时间
        if source_encoding.lower() in ('utf-8', 'utf-8-sig', 'ascii'):
            return

        try:
            content = raw.decode(source_encoding)
            # 以 UTF-8 (without BOM) 写回原文件
            with open(file_path, 'w', encoding='utf-8') as f_out:
                f_out.write(content)
            print(f"✓ 已转换: {file_path}")
        except Exception as e:
            print(f"✗ 转换失败: {file_path}，错误：{e}")

# 遍历当前目录及其子目录下所有 .c 和 .h 文件
for p in pathlib.Path('.').rglob('*.[ch]'):
    if p.is_file():
        convert_to_utf8(p)

print("批量转换完成！")