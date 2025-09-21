#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    // Create socket
    int client_fd = syscall(SYS_socket, AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        syscall(SYS_write, 2, "Socket creation failed\n", 22);
        return 1;
    }

    // Set up server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Connect to server
    if (syscall(SYS_connect, client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        syscall(SYS_write, 2, "Connection failed\n", 17);
        return 1;
    }

    // Read from socket
    char buffer[1024] = {0};
    ssize_t bytes_read = syscall(SYS_read, client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        syscall(SYS_write, 2, "Read failed\n", 12);
        return 1;
    }

    // Write to stdout
    syscall(SYS_write, 1, buffer, bytes_read);

    // Close socket
    syscall(SYS_close, client_fd);
    return 0;
}
