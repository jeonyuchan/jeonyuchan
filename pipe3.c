#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	int pfd[2];

	if(pipe(pfd)== -1){ //파이프 생성
		perror("pipe error");
		exit(1);
	}

	if(!fork()){ //포크 실행
		close(1);		//표준 출력(모니터 출력)을 닫음
		dup(pfd[1]);	//표준 출력을 파이프의 입력으로 연결
		close(pfd[0]);

		execlp("ls", "ls", NULL); //화면에 출력되어야 할 결과가 파이프의 입력으로 됨
	}

	else{
		close(0); //표준 입력(키보드 입력)을 닫음
		dup(pfd[0]);//표준 입력을 파이프의 출력으로 연결
		close(pfd[1]);

		execlp("wc", "wc", "-1", NULL); //파이프의 출력(즉, 자식 프로세스에서 실행한 ls의 결과)이 wc의 입력이 됨
	}

	return 0;
}

