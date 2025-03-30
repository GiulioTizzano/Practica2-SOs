#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

int fd;
int buffer[1024];
if(argc != 2) {
    exit(1);
}

fd = open(argv[1], O_RDONLY);
if(fd == -1) {
    write(STDOUT_FILENO, "Error al abir el archivo", strlen("Error al abir el archivo"));
    exit(1);
}
int read_bytes;
while((read_bytes = read(fd, buffer, 1024)) > 0) {
    write(STDOUT_FILENO, buffer, read_bytes);
}

}