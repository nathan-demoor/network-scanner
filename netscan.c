#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please pass an IP and port argument\n");
        return -1;
    }

    char *target_ip = argv[1];
    int port = atoi(argv[2]);
    int status, client_fd;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd < 0) {
        printf("Could not create a socket\n");
        return -1;
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, target_ip, &my_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    if (status = connect(client_fd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    printf("Connection success\n");

    close(client_fd);
    return 0;
}