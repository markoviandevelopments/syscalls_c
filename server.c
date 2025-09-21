#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    // Create socket
    int server_fd = syscall(SYS_socket, AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        syscall(SYS_write, 2, "Socket creation failed\n", 22);
        return 1;
    }

    // Set up server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket
    if (syscall(SYS_bind, server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        syscall(SYS_write, 2, "Bind failed\n", 12);
        return 1;
    }

    // Listen
    if (syscall(SYS_listen, server_fd, 5) == -1) {
        syscall(SYS_write, 2, "Listen failed\n", 14);
        return 1;
    }

    // Accept connection
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = syscall(SYS_accept, server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1) {
        syscall(SYS_write, 2, "Accept failed\n", 14);
        return 1;
    }

    // Write to socket
    const char *message = "Hello from server!\n";
    syscall(SYS_write, client_fd, message, strlen(message));

    // Close sockets
    syscall(SYS_close, client_fd);
    syscall(SYS_close, server_fd);
    return 0;
}
