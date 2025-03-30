#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
 
void señal_proceso(int sig) {
char *mensaje = "Soy el proceso P3 y he recibido una señal del proceso P5 \n";
write(1, mensaje, strlen(mensaje));
}

void señal_proceso_dos(int sig) {
char *mensaje_dos = "He recibido una señal de mi proceso padre \n";
write(1, mensaje_dos, strlen(mensaje_dos));
}

void señal_proceso_tres(int sig) {
char *mensaje_tres = " Soy P6 \n";

for(int i = 0; mensaje_tres[i] != '\0'; i++) {
	write(STDOUT_FILENO, &mensaje_tres[i], 1);
	sleep(1);
}

}


int main() {
pid_t pid1, pid2, pid3, pid4, pid5, pid6;
int contador = 0;
pid1 = fork(); // creamos p1 y su padre

if(pid1 == 0) {
	printf("Soy el proceso P1 con PID %d y PPID %d \n", getpid(), getppid());
	exit(0);
}

pid2 = fork();

if(pid2 == 0) {
	printf("Soy el proceso P2 con PID %d y PPID %d \n", getpid(), getppid());
    int fd_uno = open("practica_dos.txt", O_CREAT | O_RDWR, 0666);
	exit(0); // para que el proceso hijo no siga ejecutando el resto del código
}

pid3 = fork();

if(pid3 == 0) {
	printf("Soy el proceso P3 con PID %d y PPID %d \n", getpid(), getppid());
    signal(SIGUSR2, señal_proceso);
	pid5 = fork();
    
	if(pid5 == 0) {
		printf("Soy el proceso P5 con PID %d y PPID %d \n", getpid(), getppid());
		// exit(0);
        sleep(1);
        signal(SIGUSR1, señal_proceso_dos);
		sleep(1);
		kill(getppid(), SIGUSR2);
        exit(0);

	} else {

		sleep(1);
		kill(pid5, SIGUSR1);
		wait(NULL);
		exit(0);
	}
}

pid4 = fork();
if(pid4 == 0) {
	printf("Soy el proceso P4 con PID %d y PPID %d \n", getpid(), getppid());
	// execl("/bin/ls", "ls", "-l", NULL);

	pid6 = fork();
	if(pid6 == 0) {
		printf("Soy el proceso P6 con PID %d y PPID %d \n", getpid(), getppid());
		signal(SIGUSR1, señal_proceso_tres);
		pause();
		exit(0);
		
	} else {
		wait(NULL);
		// execl("/bin/ls", "ls", "-l", NULL);
		exit(0);
	}
}


for(int i = 0; i <= 3; i++) {
	wait(NULL);
}

return 0;
}

