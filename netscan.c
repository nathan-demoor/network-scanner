#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int scan_single_port(char ip[], int port) {
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        printf("Could not create a socket\n");
        return -1;
    }
    
    if (inet_pton(AF_INET, ip, &my_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    if (connect(fd, (struct sockaddr*)&my_addr, sizeof(my_addr)) == 0) {
        printf("Connection success port: %d\n", port);
    }

    close(fd);
    return 0;
}

int scan_all_ports(char ip[]) {
    int MAX_PORT = 65535, status; // 65535

    for (int i = 1; i < MAX_PORT; i++) {
        status = scan_single_port(ip, i);
    }

    return status; 
}

void help(int argc, char *argv[]) {
    printf("Usage: %s -u IP [-p PORT] [-m] MODE ((S) Single | (M) Multiple)\n", argv[0]);
}

int main(int argc, char *argv[]) {
    char *target_ip = malloc(100);
    char mode;
    int port, status, opt; 

     while ((opt = getopt(argc, argv, "u:p:m:h")) != -1) {
        switch (opt) {
            case 'u':
                target_ip = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'm':
                mode = *optarg;
                if (mode == 'S') {
                    status = scan_single_port(target_ip, port);
                 } else if (mode == 'M') {
                    status = scan_all_ports(target_ip);
                } else {
                    printf("Incorrect mode specified\n");
                    return 1;
                }
                break;
	    case 'h':
		help(argc, argv);
		return 1;
            default:
                help(argc, argv);
                return 1;
        }
    }
    
    return status;
}
