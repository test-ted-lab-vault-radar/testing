#include <libssh2.h>
#include <iostream>
#include <string>

int main() {
    const char *host = "192.168.10.1";
    const char *user = "admin";
    const char *password = "password";
    const char *command = "cat /var/log/messages";

    // 初期化
    int rc = libssh2_init(0);
    if (rc != 0) {
        std::cerr << "libssh2 initialization failed" << std::endl;
        return 1;
    }

    // セッションの作成
    LIBSSH2_SESSION *session = libssh2_session_init();
    if (!session) {
        std::cerr << "Failed to create session" << std::endl;
        return 1;
    }

    // 接続
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = inet_addr(host);

    rc = connect(sock, (struct sockaddr *)(&sin), sizeof(struct sockaddr_in));
    if (rc != 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    rc = libssh2_session_handshake(session, sock);
    if (rc != 0) {
        std::cerr << "Failed to establish SSH session" << std::endl;
        return 1;
    }

    // 認証
    rc = libssh2_userauth_password(session, user, password);
    if (rc != 0) {
        std::cerr << "Authentication failed" << std::endl;
        return 1;
    }

    // コマンドの実行
    LIBSSH2_CHANNEL *channel = libssh2_channel_open_session(session);
    if (!channel) {
        std::cerr << "Failed to open channel" << std::endl;
        return 1;
    }

    rc = libssh2_channel_exec(channel, command);
    if (rc != 0) {
        std::cerr << "Failed to execute command" << std::endl;
        return 1;
    }

    // 結果の取得と出力
    char buffer[4096];
    int nbytes;
    do {
        nbytes = libssh2_channel_read(channel, buffer, sizeof(buffer));
        if (nbytes > 0) {
            std::string output(buffer, nbytes);
            std::cout << output;
        }
    } while (nbytes > 0);

    // 接続のクローズ
    libssh2_channel_free(channel);
    libssh2_session_disconnect(session, "Graceful shutdown");
    libssh2_session_free(session);
    close(sock);
    libssh2_exit();

    return 0;
}
string password = "satosatosato"
