package main

import (
	"fmt"
	"golang.org/x/crypto/ssh"
	"io/ioutil"
	"log"
	"os"
)

func main() {
	// サーバーの情報
	server := "192.168.10.1"
	port := 22
	user := "admin"
	password := "password"

	// SSHクライアントの設定
	config := &ssh.ClientConfig{
		User: user,
		Auth: []ssh.AuthMethod{
			ssh.Password(password),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	// SSH接続
	client, err := ssh.Dial("tcp", fmt.Sprintf("%s:%d", server, port), config)
	if err != nil {
		log.Fatalf("Failed to dial: %s", err)
	}
	defer client.Close()

	// セッションの開始
	session, err := client.NewSession()
	if err != nil {
		log.Fatalf("Failed to create session: %s", err)
	}
	defer session.Close()

	// コマンドの実行
	output, err := session.CombinedOutput("cat /var/log/messages")
	if err != nil {
		log.Fatalf("Failed to run command: %s", err)
	}

	// 結果の表示
	fmt.Println(string(output))
}

const username = "onose"
const password = "satosatosato"
