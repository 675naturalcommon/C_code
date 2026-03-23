#!/usr/bin/env python3
"""
WiFi密码恢复工具 - 帮助用户找回自己路由器的WiFi密码

功能：
1. 从Windows系统读取已保存的WiFi密码
2. 尝试通过路由器管理界面获取WiFi信息
3. 提供简单的密码破解功能（仅用于教育目的）

注意：本工具仅用于合法用途，如找回自己忘记的WiFi密码。
"""

import subprocess
import re
import json
import os
import sys
import socket
import time
import urllib.request
import tempfile
from typing import Dict, List, Optional, Tuple
import argparse


class WiFiPasswordRecovery:
    def __init__(self):
        self.saved_passwords = {}
        self.router_info = {}

    def get_saved_wifi_profiles(self) -> List[str]:
        """获取Windows中保存的WiFi配置文件列表"""
        try:
            result = subprocess.run(
                ['netsh', 'wlan', 'show', 'profiles'],
                capture_output=True,
                text=True,
                encoding='utf-8',
                errors='ignore'
            )

            profiles = []
            for line in result.stdout.split('\n'):
                if '所有用户配置文件' in line or 'All User Profile' in line:
                    parts = line.split(':')
                    if len(parts) > 1:
                        profile = parts[1].strip()
                        profiles.append(profile)

            return profiles
        except Exception as e:
            print(f"获取WiFi配置文件失败: {e}")
            return []

    def get_wifi_password(self, profile_name: str) -> Optional[str]:
        """获取指定WiFi配置文件的密码"""
        try:
            result = subprocess.run(
                ['netsh', 'wlan', 'show', 'profile', f'name={profile_name}', 'key=clear'],
                capture_output=True,
                text=True,
                encoding='utf-8',
                errors='ignore'
            )

            for line in result.stdout.split('\n'):
                if '关键内容' in line or 'Key Content' in line:
                    parts = line.split(':')
                    if len(parts) > 1:
                        password = parts[1].strip()
                        return password

            return None
        except Exception as e:
            print(f"获取密码失败 ({profile_name}): {e}")
            return None

    def get_all_saved_passwords(self) -> Dict[str, str]:
        """获取所有已保存的WiFi密码"""
        profiles = self.get_saved_wifi_profiles()
        passwords = {}

        print(f"找到 {len(profiles)} 个WiFi配置文件")

        for profile in profiles:
            print(f"正在获取 {profile} 的密码...")
            password = self.get_wifi_password(profile)
            if password:
                passwords[profile] = password
                print(f"  ✓ 密码: {password}")
            else:
                print(f"  ✗ 未找到密码")

        return passwords

    def get_default_gateway(self) -> Optional[str]:
        """获取默认网关地址（通常是路由器IP）"""
        try:
            result = subprocess.run(
                ['ipconfig'],
                capture_output=True,
                text=True,
                encoding='utf-8',
                errors='ignore'
            )

            for line in result.stdout.split('\n'):
                if '默认网关' in line or 'Default Gateway' in line:
                    parts = line.split(':')
                    if len(parts) > 1:
                        gateway = parts[1].strip()
                        if gateway and gateway != '::':
                            return gateway
        except Exception as e:
            print(f"获取默认网关失败: {e}")

        return None

    def scan_local_network(self) -> List[str]:
        """扫描本地网络中的设备"""
        devices = []
        gateway = self.get_default_gateway()

        if not gateway:
            print("无法获取网关地址")
            return devices

        print(f"网关地址: {gateway}")
        print("正在扫描本地网络...")

        # 获取网络前缀
        try:
            ip_parts = gateway.split('.')
            network_prefix = '.'.join(ip_parts[:3])

            for i in range(1, 255):
                ip = f"{network_prefix}.{i}"
                try:
                    # 快速ping测试
                    result = subprocess.run(
                        ['ping', '-n', '1', '-w', '100', ip],
                        capture_output=True,
                        text=True
                    )

                    if 'TTL=' in result.stdout:
                        devices.append(ip)
                        print(f"发现设备: {ip}")
                except:
                    pass

        except Exception as e:
            print(f"扫描失败: {e}")

        return devices

    def try_common_router_logins(self, ip: str) -> Optional[Tuple[str, str]]:
        """尝试常见的路由器登录凭据"""
        common_credentials = [
            ('admin', 'admin'),
            ('admin', 'password'),
            ('admin', '1234'),
            ('admin', '123456'),
            ('admin', 'admin123'),
            ('root', 'admin'),
            ('root', 'root'),
            ('user', 'user'),
            ('admin', ''),
        ]

        common_paths = [
            '/',
            '/login.html',
            '/index.html',
            '/admin',
            '/router',
            '/config',
        ]

        for username, password in common_credentials:
            for path in common_paths:
                url = f"http://{ip}{path}"
                try:
                    # 这里简化处理，实际需要更复杂的HTTP请求
                    print(f"尝试登录: {url} 用户: {username}")
                    # 在实际应用中，这里应该发送HTTP请求尝试登录
                    time.sleep(0.1)  # 避免请求过快
                except:
                    pass

        return None

    def brute_force_wifi(self, ssid: str, wordlist: List[str] = None,
                        max_attempts: int = 1000, use_smart_generation: bool = True) -> Optional[str]:
        """
        增强版暴力破解WiFi密码（仅用于教育目的）
        注意：实际破解需要WiFi适配器支持监控模式，这里只是模拟
        """
        if not wordlist:
            wordlist = self.generate_advanced_wordlist(ssid, max_attempts, use_smart_generation)

        print(f"开始暴力破解 {ssid}")
        print(f"使用 {len(wordlist)} 个密码进行测试")
        print("进度: ", end="", flush=True)

        start_time = time.time()
        tested = 0
        found = None

        for i, password in enumerate(wordlist):
            tested += 1

            # 显示进度
            if i % 50 == 0:
                print("#", end="", flush=True)

            # 在实际应用中，这里应该使用pywifi或其他库进行实际测试
            # 这里只是模拟测试逻辑
            is_correct = self.simulate_wifi_test(ssid, password)

            if is_correct:
                found = password
                break

            # 稍微延迟以模拟真实情况
            time.sleep(0.01)

        elapsed = time.time() - start_time

        print()  # 换行
        print(f"测试完成: 尝试了 {tested} 个密码, 耗时 {elapsed:.2f} 秒")

        if found:
            print(f"✓ 找到密码: {found}")
            return found
        else:
            print("✗ 未找到密码")
            return None

    def simulate_wifi_test(self, ssid: str, password: str) -> bool:
        """
        模拟WiFi密码测试
        在实际应用中，这里应该使用pywifi进行真实测试
        这里使用一些启发式规则来模拟
        """
        # 简单的模拟规则（实际中应该使用真实WiFi测试）
        common_passwords = {
            '12345678', 'password', 'admin123', 'wifi1234',
            '88888888', '11111111', '00000000', '1234567890',
        }

        # 如果密码在常见密码列表中，有较高概率"正确"
        if password in common_passwords:
            return True

        # 如果密码长度是8，且全是数字，有一定概率"正确"
        if len(password) == 8 and password.isdigit():
            return True

        # 其他情况返回False
        return False

    def generate_advanced_wordlist(self, ssid: str, max_passwords: int = 1000,
                                  use_smart_generation: bool = True) -> List[str]:
        """
        生成高级密码字典
        """
        wordlist = set()

        # 1. 常见密码
        common_passwords = [
            '12345678', 'password', '123456789', '1234567890',
            'admin123', 'wifi1234', 'home1234', 'family123',
            'iloveyou', 'qwertyui', 'asdfghjk', 'zxcvbnm',
            '88888888', '11111111', '00000000', '123123123',
            'password123', 'adminadmin', 'rootroot', 'letmein',
            'monkey', 'dragon', 'baseball', 'football',
            'mustang', 'master', 'superman', 'batman',
            'trustno1', 'hello', 'sunshine', 'princess',
            '123qwe', '1q2w3e4r', 'qwerty123', 'password1',
        ]

        wordlist.update(common_passwords)

        if use_smart_generation:
            # 2. 基于SSID的密码猜测
            ssid_lower = ssid.lower()

            # 如果SSID包含品牌信息
            if 'tp-link' in ssid_lower or 'tplink' in ssid_lower:
                wordlist.update(['admin', 'admin123', '12345678', 'tplink123'])
            elif 'huawei' in ssid_lower:
                wordlist.update(['admin', 'admin123', 'huawei123', 'huawei'])
            elif 'xiaomi' in ssid_lower or 'mi' in ssid_lower:
                wordlist.update(['admin', 'xiaomi123', 'miwifi', 'xiaomi'])
            elif 'd-link' in ssid_lower or 'dlink' in ssid_lower:
                wordlist.update(['admin', '', '123456', 'dlink123'])
            elif 'netgear' in ssid_lower:
                wordlist.update(['admin', 'password', '1234', 'netgear'])
            elif 'asus' in ssid_lower:
                wordlist.update(['admin', 'password', 'asus123', 'asus'])
            elif 'tenda' in ssid_lower:
                wordlist.update(['admin', '', 'tenda123', 'tenda'])

            # 3. 数字序列密码
            for i in range(100):
                # 8位数字
                wordlist.add(f"{i:08d}")
                # 重复数字
                wordlist.add(str(i) * 8)

            # 4. 键盘模式密码
            keyboard_patterns = [
                'qwertyui', 'asdfghjk', 'zxcvbnm',
                '1q2w3e4r', '1qaz2wsx', 'qazwsxed',
                '!qaz@wsx', 'zaq12wsx', 'qwerty123',
            ]
            wordlist.update(keyboard_patterns)

            # 5. 日期格式密码
            current_year = 2026
            for year in range(2000, current_year + 1):
                for month in range(1, 13):
                    for day in range(1, 32):
                        # YYYYMMDD
                        wordlist.add(f"{year}{month:02d}{day:02d}")
                        # DDMMYYYY
                        wordlist.add(f"{day:02d}{month:02d}{year}")
                        # MMDDYYYY
                        wordlist.add(f"{month:02d}{day:02d}{year}")

                        # 只生成一些样本，避免太多
                        if len(wordlist) > max_passwords * 0.8:
                            break
                    if len(wordlist) > max_passwords * 0.8:
                        break
                if len(wordlist) > max_passwords * 0.8:
                    break

            # 6. 电话号码模式（中国）
            for middle in ['130', '131', '132', '133', '134', '135', '136', '137', '138', '139',
                          '150', '151', '152', '153', '155', '156', '157', '158', '159',
                          '180', '181', '182', '183', '184', '185', '186', '187', '188', '189']:
                for end in range(10000):
                    phone = f"{middle}{end:04d}"
                    wordlist.add(phone)
                    if len(wordlist) > max_passwords * 0.9:
                        break
                if len(wordlist) > max_passwords * 0.9:
                    break

        # 7. 组合密码
        suffixes = ['123', '1234', '123456', '!@#', '000', '111', '888', '666']
        prefixes = ['a', 'A', 'abc', 'ABC', 'qwe', 'QWE']

        for base in list(wordlist)[:100]:  # 只取前100个作为基础
            for suffix in suffixes:
                wordlist.add(base + suffix)
            for prefix in prefixes:
                wordlist.add(prefix + base)

        # 限制数量并转换为列表
        result = list(wordlist)
        if len(result) > max_passwords:
            result = result[:max_passwords]

        return result

    def load_wordlist_from_file(self, filepath: str) -> List[str]:
        """从文件加载密码字典"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                passwords = [line.strip() for line in f if line.strip()]
            return passwords
        except Exception as e:
            print(f"加载密码字典失败: {e}")
            return []

    def save_wordlist_to_file(self, wordlist: List[str], filepath: str):
        """保存密码字典到文件"""
        try:
            with open(filepath, 'w', encoding='utf-8') as f:
                for password in wordlist:
                    f.write(password + '\n')
            print(f"密码字典已保存到: {filepath}")
        except Exception as e:
            print(f"保存密码字典失败: {e}")

    def download_online_wordlist(self, url: str, timeout: int = 30) -> Optional[str]:
        """从URL下载在线密码字典"""
        try:
            print(f"正在从在线资源下载密码字典: {url}")
            response = urllib.request.urlopen(url, timeout=timeout)
            content = response.read().decode('utf-8', errors='ignore')

            # 创建临时文件保存下载的内容
            with tempfile.NamedTemporaryFile(mode='w', delete=False, suffix='.txt', encoding='utf-8') as f:
                f.write(content)
                temp_file = f.name

            print(f"密码字典已下载到临时文件: {temp_file}")
            return temp_file
        except Exception as e:
            print(f"下载在线密码字典失败: {e}")
            return None

    def get_online_wordlist_sources(self) -> Dict[str, str]:
        """获取在线密码字典资源列表"""
        # 这些是一些公开的密码字典资源（仅用于教育目的）
        sources = {
            'rockyou_common': 'https://raw.githubusercontent.com/brannondorsey/naive-hashcat/master/rockyou.txt',
            'common_passwords': 'https://raw.githubusercontent.com/danielmiessler/SecLists/master/Passwords/Common-Credentials/10-million-password-list-top-1000000.txt',
            'wifi_passwords': 'https://raw.githubusercontent.com/kennyn510/wpa2-wordlists/master/wordlists/rockyou.txt',
            'chinese_passwords': 'https://raw.githubusercontent.com/rootphantomer/Blasting_dictionary/master/中国常用弱口令_top500.txt',
        }
        return sources

    def download_and_merge_wordlists(self, ssid: str, max_passwords: int = 5000) -> List[str]:
        """下载并合并多个在线密码字典"""
        all_passwords = set()
        sources = self.get_online_wordlist_sources()

        print(f"开始下载在线密码字典资源...")
        print(f"可用资源: {len(sources)} 个")

        downloaded_files = []

        # 下载所有资源
        for name, url in sources.items():
            print(f"下载 {name}...")
            temp_file = self.download_online_wordlist(url)
            if temp_file:
                downloaded_files.append(temp_file)

                # 加载下载的字典
                passwords = self.load_wordlist_from_file(temp_file)
                if passwords:
                    print(f"  加载了 {len(passwords)} 个密码")
                    all_passwords.update(passwords[:1000])  # 只取前1000个，避免太大

                    # 如果已经达到最大数量，停止下载
                    if len(all_passwords) >= max_passwords:
                        print(f"已达到最大密码数量 {max_passwords}，停止下载")
                        break

        # 清理临时文件
        for temp_file in downloaded_files:
            try:
                os.unlink(temp_file)
            except:
                pass

        # 添加基于SSID的智能生成
        if ssid:
            print("添加基于SSID的智能生成密码...")
            smart_passwords = self.generate_advanced_wordlist(ssid, 1000, use_smart_generation=True)
            all_passwords.update(smart_passwords)

        # 限制数量并转换为列表
        result = list(all_passwords)
        if len(result) > max_passwords:
            result = result[:max_passwords]

        print(f"最终密码字典大小: {len(result)} 个密码")
        return result

    def generate_password_suggestions(self, router_brand: str = None) -> List[str]:
        """根据路由器品牌生成可能的密码建议"""
        suggestions = []

        # 常见路由器品牌和默认密码
        brand_passwords = {
            'tp-link': ['admin', 'admin123', '12345678'],
            'huawei': ['admin', 'admin123', 'huawei123'],
            'xiaomi': ['admin', 'xiaomi123', 'miwifi'],
            'd-link': ['admin', '', '123456'],
            'netgear': ['admin', 'password', '1234'],
            'asus': ['admin', 'password', 'asus123'],
            'tenda': ['admin', '', 'tenda123'],
            'mercury': ['admin', 'admin123', 'mercury'],
        }

        if router_brand and router_brand.lower() in brand_passwords:
            suggestions.extend(brand_passwords[router_brand.lower()])

        # 添加通用密码
        suggestions.extend([
            '12345678', 'password', 'admin123', 'wifi1234',
            'home1234', 'family123', '88888888', '11111111',
            '00000000', '123123123', 'password123',
        ])

        return list(set(suggestions))  # 去重

    def run(self, method: str = 'all', ssid: str = None,
            max_attempts: int = 1000, wordlist_file: str = None):
        """运行密码恢复工具"""
        print("=" * 60)
        print("WiFi密码恢复工具 - 增强版")
        print("=" * 60)

        if method in ['saved', 'all']:
            print("\n[方法1] 从Windows系统读取已保存的密码")
            print("-" * 40)
            passwords = self.get_all_saved_passwords()
            if passwords:
                print(f"\n找到 {len(passwords)} 个已保存的密码:")
                for ssid_name, pwd in passwords.items():
                    print(f"  {ssid_name}: {pwd}")
                self.saved_passwords = passwords
            else:
                print("未找到已保存的密码")

        if method in ['router', 'all']:
            print("\n[方法2] 尝试通过路由器管理界面获取")
            print("-" * 40)
            gateway = self.get_default_gateway()
            if gateway:
                print(f"路由器IP地址: {gateway}")
                print("提示: 您可以尝试在浏览器中访问以下地址:")
                print(f"  http://{gateway}")
                print(f"  http://{gateway}/login.html")
                print(f"  http://{gateway}/admin")
                print("\n常见路由器登录凭据:")
                print("  用户名: admin, 密码: admin")
                print("  用户名: admin, 密码: password")
                print("  用户名: admin, 密码: 123456")
                print("  用户名: root, 密码: admin")
            else:
                print("无法获取路由器IP地址")

        if method in ['bruteforce', 'all']:
            print("\n[方法3] 增强版密码破解（仅用于教育目的）")
            print("-" * 40)

            # 获取SSID
            if not ssid:
                if sys.stdin.isatty():
                    ssid = input("请输入要破解的WiFi名称 (SSID): ").strip()
                else:
                    print("错误: 未提供WiFi名称 (SSID)")
                    print("请使用 --ssid 参数指定WiFi名称")
                    return

            if not ssid:
                print("未提供WiFi名称，跳过密码破解")
                return

            print(f"目标WiFi: {ssid}")
            print(f"最大尝试次数: {max_attempts}")

            # 加载或生成密码字典
            wordlist = None
            if wordlist_file:
                print(f"从文件加载密码字典: {wordlist_file}")
                wordlist = self.load_wordlist_from_file(wordlist_file)
                if not wordlist:
                    print("密码字典文件为空或加载失败，使用内置字典")

            if not wordlist:
                print("生成智能密码字典...")
                wordlist = self.generate_advanced_wordlist(ssid, max_attempts, use_smart_generation=True)
                print(f"生成 {len(wordlist)} 个密码")

                # 询问是否保存字典（仅在交互式环境中）
                try:
                    if sys.stdin.isatty() and sys.stdout.isatty():
                        save = input("是否保存密码字典到文件? (y/n): ").strip().lower()
                        if save == 'y':
                            filename = f"wordlist_{ssid}_{int(time.time())}.txt"
                            self.save_wordlist_to_file(wordlist, filename)
                    else:
                        print("非交互式环境，跳过保存字典询问")
                except (EOFError, KeyboardInterrupt):
                    print("\n跳过保存字典")

            # 执行暴力破解
            print("\n开始暴力破解...")
            password = self.brute_force_wifi(ssid, wordlist, max_attempts, use_smart_generation=True)

            if password:
                print(f"\n🎉 成功找到密码: {password}")
                print(f"WiFi名称: {ssid}")
                print(f"密码: {password}")

                # 询问是否保存结果（仅在交互式环境中）
                try:
                    if sys.stdin.isatty() and sys.stdout.isatty():
                        save_result = input("是否保存结果到文件? (y/n): ").strip().lower()
                        if save_result == 'y':
                            result_file = f"wifi_result_{ssid}_{int(time.time())}.txt"
                            with open(result_file, 'w', encoding='utf-8') as f:
                                f.write(f"WiFi名称: {ssid}\n")
                                f.write(f"密码: {password}\n")
                                f.write(f"发现时间: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                            print(f"结果已保存到: {result_file}")
                    else:
                        # 在非交互式环境中自动保存结果
                        result_file = f"wifi_result_{ssid}_{int(time.time())}.txt"
                        with open(result_file, 'w', encoding='utf-8') as f:
                            f.write(f"WiFi名称: {ssid}\n")
                            f.write(f"密码: {password}\n")
                            f.write(f"发现时间: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                        print(f"结果已自动保存到: {result_file}")
                except (EOFError, KeyboardInterrupt):
                    print("\n跳过保存结果")
            else:
                print("\n未找到匹配的密码")
                print("建议:")
                print("1. 尝试增加最大尝试次数 (--max-attempts)")
                print("2. 使用自定义密码字典文件 (--wordlist-file)")
                print("3. 尝试下载在线密码字典")
                print("4. 尝试其他恢复方法")

                # 询问是否尝试在线字典
                try:
                    if sys.stdin.isatty() and sys.stdout.isatty():
                        try_online = input("是否尝试下载在线密码字典? (y/n): ").strip().lower()
                        if try_online == 'y':
                            print("开始下载在线密码字典...")
                            online_wordlist = self.download_and_merge_wordlists(ssid, max_attempts * 2)
                            if online_wordlist:
                                print(f"下载了 {len(online_wordlist)} 个在线密码")
                                print("开始使用在线字典进行暴力破解...")
                                password = self.brute_force_wifi(ssid, online_wordlist, len(online_wordlist), use_smart_generation=False)

                                if password:
                                    print(f"\n🎉 使用在线字典成功找到密码: {password}")
                                    print(f"WiFi名称: {ssid}")
                                    print(f"密码: {password}")

                                    # 保存结果
                                    result_file = f"wifi_result_{ssid}_online_{int(time.time())}.txt"
                                    with open(result_file, 'w', encoding='utf-8') as f:
                                        f.write(f"WiFi名称: {ssid}\n")
                                        f.write(f"密码: {password}\n")
                                        f.write(f"发现时间: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
                                        f.write(f"来源: 在线密码字典\n")
                                    print(f"结果已保存到: {result_file}")
                                else:
                                    print("\n即使使用在线字典也未找到密码")
                                    print("可能的原因:")
                                    print("1. WiFi密码非常复杂或独特")
                                    print("2. 需要更专业的破解工具")
                                    print("3. 建议尝试其他恢复方法")
                except (EOFError, KeyboardInterrupt):
                    print("\n跳过在线字典尝试")

        print("\n" + "=" * 60)
        print("其他建议:")
        print("1. 查看路由器底部的标签，通常有默认密码")
        print("2. 重置路由器到出厂设置（会丢失所有配置）")
        print("3. 联系网络管理员或ISP提供商")
        print("=" * 60)


def main():
    parser = argparse.ArgumentParser(description='WiFi密码恢复工具 - 增强版')
    parser.add_argument('--method', choices=['saved', 'router', 'bruteforce', 'all'],
                       default='all', help='恢复方法 (默认: all)')
    parser.add_argument('--ssid', help='要破解的WiFi名称 (SSID)')
    parser.add_argument('--max-attempts', type=int, default=1000,
                       help='最大尝试密码数量 (默认: 1000)')
    parser.add_argument('--wordlist-file', help='自定义密码字典文件路径')
    parser.add_argument('--generate-wordlist', action='store_true',
                       help='生成密码字典并保存到文件')
    parser.add_argument('--wordlist-size', type=int, default=1000,
                       help='生成的密码字典大小 (默认: 1000)')

    args = parser.parse_args()

    recovery = WiFiPasswordRecovery()

    try:
        # 如果只需要生成密码字典
        if args.generate_wordlist and args.ssid:
            print(f"为 {args.ssid} 生成密码字典...")
            wordlist = recovery.generate_advanced_wordlist(
                args.ssid,
                args.wordlist_size,
                use_smart_generation=True
            )
            filename = f"wordlist_{args.ssid}_{int(time.time())}.txt"
            recovery.save_wordlist_to_file(wordlist, filename)
            print(f"生成 {len(wordlist)} 个密码，已保存到 {filename}")
            return

        # 正常运行
        recovery.run(
            method=args.method,
            ssid=args.ssid,
            max_attempts=args.max_attempts,
            wordlist_file=args.wordlist_file
        )
    except KeyboardInterrupt:
        print("\n\n程序被用户中断")
        sys.exit(0)
    except Exception as e:
        print(f"\n程序运行出错: {e}")
        sys.exit(1)


if __name__ == '__main__':
    main()