#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int scan_single_port(char ip[],  int port) {
    int client_fd;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd < 0) {
        printf("Could not create a socket\n");
        return -1;
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip, &my_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    printf("Connection success\n");

    close(client_fd);
    return 0;
}

int scan_all_ports(int ip) {
    int MAX_PORT = 65535;
    return 0; 
}

int main(int argc, char *argv[]) {
    char target_ip[16];
    int port, status;

    // Do mode selection first before asking for any values

    printf("Please enter an IP address: ");
    scanf("%s", &target_ip);
    printf("Please enter an IP port: ");
    scanf("%d", &port);
    
    status = scan_single_port(target_ip, port);
    return status;
}
