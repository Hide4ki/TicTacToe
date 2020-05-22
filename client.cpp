#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

char message[1024] = "Artem is cool men. message from other Artem!\n";
char buf[1024];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    inet_aton("192.168.1.233", &addr.sin_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3432); // или любой другой порт...
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(buf), 0);
  
    close(sock);

    return 0;
}
