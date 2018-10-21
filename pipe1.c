#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

int main(){
	int pfd[2]; //파이프용 파일 지시자
	char buf[30];
		if(pipe(pfd)== -1){
         perror("pipe error");
         exit(1);
	 }

	if(pipe(pfd)== -1){ //파이프생성
		perror("pipe error");
		exit(1);
	}
	// pfd[1]은 쓰기전용
	printf("Wtiting to the file descriptor #%d\n", pfd[1]);
	write(pfd[1], "pipe!", 5);
	// pfd[0]은 읽기 전용
	printf("reading from the file descriptor #%d\n", pfd[0]);
	read(pfd[0], buf, 5);

	printf("%s\n", buf);

	return 0;
}
