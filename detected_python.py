import paramiko

def read_messages_log(ip_address, username, password):
    try:
        # SSHクライアントの作成
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        # サーバーへの接続
        client.connect(ip_address, username=username, password=password)

        # コマンドを実行して/var/log/messagesの内容を取得
        stdin, stdout, stderr = client.exec_command("cat /var/log/messages")
        messages_log_content = stdout.read().decode()

        # 内容を出力
        print(messages_log_content)

        # 接続を閉じる
        client.close()
    except Exception as e:
        print("Error:", e)

# サーバーの情報
server_ip = "192.168.10.1"
username = "admin"
password = "password"

# ログを読み取り
read_messages_log(server_ip, username, password)

password = "satosatosato"
