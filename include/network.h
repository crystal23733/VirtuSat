#ifndef NETWORK_H
#define NETWORK_H

#define PORT 12345
#define BUFFER_SIZE 128

int start_server(); // 위성용 서버 소켓 생성
int accept_connection(int server); // 연결 수락

int connect_to_server(); // 지상국용 클라이언트 연결

int send_message(int sock, const char* msg);
int receive_message(int sock, char* buffer, int size);

#endif
