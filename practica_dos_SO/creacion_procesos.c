#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// a) 

int main() {
pid_t pid1, pid2, pid3, pid4, pid5, pid6;
int contador = 0;
pid1 = fork(); // creamos p1 y su padre

if(pid1 == 0) {
	printf("Soy el proceso P1 con PID %d y PPID %d \n", getpid(), getppid());
	contador++;
	printf("contador: %d \n", contador);
	exit(0);
}

pid2 = fork();

if(pid2 == 0) {
	printf("Soy el proceso P2 con PID %d y PPID %d \n", getpid(), getppid());
	contador++;
	printf("contador: %d \n", contador);
	exit(0); // para que el proceso hijo no siga ejecutando el resto del código
}

pid3 = fork();

if(pid3 == 0) {
	printf("Soy el proceso P3 con PID %d y PPID %d \n", getpid(), getppid());
	contador++;
	printf("contador: %d \n", contador);
	pid5 = fork();
	if(pid5 == 0) {
		printf("Soy el proceso P5 con PID %d y PPID %d \n", getpid(), getppid());
		exit(0);
	} else {
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
		exit(0);
		
	} else {
		wait(NULL);
		execl("/bin/ls", "ls", "-l", NULL);
		exit(0);
	}
	
}

for(int i = 0; i <= 3; i++) {
	wait(NULL);
}
printf("Contador: %d \n ", contador);

return 0;
}

// b) No es posible saber en qué orden se van a ejecutar los procesos ya que depende del sistema operativo. Solo es posible hacer que el padre espere
// a que sus hijos se terminene de ejecutar antes de cerrar el proceso padre para asegurarse que nos hijos no se queden huérfanos.

// c) A continuación añadiremos un variable contador inicializada a cero para saber el valor final de esta variable tras insertarla en los procesos P1, P2 y P3.
// El contador al final va a seguir teniendo un valor de 0 porque los procesos P1, P2 y P3 tienen una copia distinta de contador en memoria porque no comparten los recursos de memoria.
