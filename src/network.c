#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "network.h"

// 서버 시작 (위성)
int start_server() {
    int server_fd;
    struct sockaddr_in addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(1);
    }

    printf("[위성] 연결 대기 중 (포트%d)...\n", PORT);
    return server_fd;
}

// 연결 수락
int accept_connection(int server) {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = accept(server, (struct sockaddr*)&client_addr, &len);
    if (client_fd < 0) {
        perror("accept");
        exit(1);
    }
    printf("[위성] 지상국 연결됨!\n");
    return client_fd;
}

// 클라이언트 연결 (지상국)
int connect_to_server() {
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("[지상국] 위성에 연결 성공!\n");
    return sock;
}

// 메세지 보내기
int send_message(int sock, const char* msg) {
    return send(sock, msg, strlen(msg), 0);
}

// 메세지 받기
int receive_message(int sock, char* buffer, int size) {
    memset(buffer, 0, size);
    return recv(sock, buffer, size - 1, 0);
}
