//시그널을 처리하는 도안 블록화할 시그널을 14라인에서 모든 시그널로 설정하여 시그널을 처리하는 동안 즉 signalHandler 함수를 실행하는 동안 발생한 시그널은 블록화되고 함수 실행이 끝나면 블록이 해제되어 블록화 되었던 시그널을 받게 된다.
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);

int main() 
{ 
	struct sigaction act;

		    /* 시그널이 오면 signalHandler를 실행하도록 설정 */
	act.sa_handler = signalHandler;
			    /* 모든 시그널은 시그널을 처리하는 동안 블록되도록 설정 */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
					    /* SIGINT에 대해 act 행동을 하도록 설정 */
	sigaction(SIGINT, &act, NULL);
	printf("%d : call sigaction\n",getpid());
	while(1)
		sleep(5);
}

void signalHandler(int signo)
{
	int i=1;
	
	printf("start handler\n");
	
	for(;i<4;){
		printf("%d\n", i);
		sleep(1);
		i++;
	}
	printf("end handler\n");
}

