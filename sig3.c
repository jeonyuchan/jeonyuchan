#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>

void clock_tick(int signo){
	printf("\r%ld", time(NULL));
	alarm(1);
}

int main(void){
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	printf("\e[2J\e[H");

	if(signal(SIGALRM, clock_tick)==SIG_ERR)
		perror("cant catch SIGALRM");
	clock_tick(-1);
	for(;;)
		pause();
	return(EXIT_SUCCESS);
}
