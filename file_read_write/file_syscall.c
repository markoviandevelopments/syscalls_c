#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    // Open file for writing (create if doesn't exist, truncate if it does)
    int fd = syscall(SYS_open, "example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        syscall(SYS_write, 2, "Failed to open file for writing: ", 32);
        syscall(SYS_write, 2, strerror(errno), strlen(strerror(errno)));
        syscall(SYS_write, 2, "\n", 1);
        return 1;
    }

    // Write to file
    const char *message = "Hello, this is a test file!\n";
    ssize_t bytes_written = syscall(SYS_write, fd, message, strlen(message));
    if (bytes_written == -1)
    {
        syscall(SYS_write, 2, "Write failed: ", 14);
        syscall(SYS_write, 2, strerror(errno), strlen(strerror(errno)));
        syscall(SYS_write, 2, "\n", 1);
        syscall(SYS_close, fd);
        return 1;
    }

    // Close file after writing
    syscall(SYS_close, fd);

    // Open file for reading
    fd = syscall(SYS_open, "example.txt", O_RDONLY, 0);
    if (fd == -1)
    {
        syscall(SYS_write, 2, "Failed to open file for reading: ", 32);
        syscall(SYS_write, 2, strerror(errno), strlen(strerror(errno)));
        syscall(SYS_write, 2, "\n", 1);
        return 1;
    }

    // Read from file
    char buffer[1024] = {0};
    ssize_t bytes_read = syscall(SYS_read, fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
    {
        syscall(SYS_write, 2, "Read failed: ", 13);
        syscall(SYS_write, 2, strerror(errno), strlen(strerror(errno)));
        syscall(SYS_write, 2, "\n", 1);
        syscall(SYS_close, fd);
        return 1;
    }

    // Write contents to stdout
    syscall(SYS_write, 1, "File contents:\n", 15);
    syscall(SYS_write, 1, buffer, bytes_read);

    // Close file
    syscall(SYS_close, fd);
    return 0;
}