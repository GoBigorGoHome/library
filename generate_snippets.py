import json
import os
import platform
import time

# ================= 配置区域 =================
# 1. 你的代码库文件夹路径
SOURCE_DIR = os.path.dirname(os.path.abspath(__file__))

# 2. 包含哪些后缀的文件
EXTENSIONS = ('.cpp', '.h', '.hpp', 'py') 

# 3. 生成的 snippet 文件名
OUTPUT_SNIPPET_FILENAME = 'my_library_collection.code-snippets'
# ===========================================

def get_vscode_snippets_path():
    system = platform.system()
    if system == "Windows":
        return os.path.join(os.environ['APPDATA'], 'Code', 'User', 'snippets')
    elif system == "Darwin": # macOS
        return os.path.expanduser('~/Library/Application Support/Code/User/snippets')
    else: # Linux
        return os.path.expanduser('~/.config/Code/User/snippets')

def sync_all_files():
    snippets_dir = get_vscode_snippets_path()
    target_path = os.path.join(snippets_dir, OUTPUT_SNIPPET_FILENAME)
    
    all_snippets = {}

    if not os.path.exists(SOURCE_DIR):
        print(f"错误: 找不到路径 {SOURCE_DIR}")
        return

    for root, dirs, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith(EXTENSIONS):
                if file == 'generate_snippets.py': # 跳过这个生成 snippets 的脚本自己
                    continue
                file_path = os.path.join(root, file)
                # 获取文件名（不带后缀）作为触发词
                prefix = os.path.splitext(file)[0]
                try:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                    
                    # 构造单个 snippet
                    all_snippets[f"{file}"] = {
                        "prefix": prefix,
                        "body": content.splitlines(),
                        "description": f"From: {file_path}"
                    }
                except Exception as e:
                    print(f"读取文件 {file} 失败: {e}")

    # 写入 VS Code 配置
    with open(target_path, 'w', encoding='utf-8') as f:
        json.dump(all_snippets, f, indent=4, ensure_ascii=False)
    
    print(f"[{time.strftime('%H:%M:%S')}] 已成功同步 {len(all_snippets)} 个文件到 VS Code！")

if __name__ == "__main__":
    sync_all_files()
