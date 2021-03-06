#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(){
	char buf[100];
	int num, fd;
	/* fifo에 사용할 파일 지시자 생성 */
	if(mknod(FIFO_NAME, S_IFIFO|0666, 0) == -1){
		perror("mknod error");
	}

	/* fifo를통해 데이터 전송 받을 상대측 프로세스를 기다림 
	   상태측 프로세스가 fifo파일 지시자를 열면, 우리도 연다 */
	printf("Wirter: waiting for a reader. \n");
	fd = open(FIFO_NAME, O_WRONLY);

	printf("Writer : the reader ready. \n");
	printf("Writer : your input : ");

	/* 사용자로 부터 입력받은 데이터를 fifo를 통해 상대측에게 전달*/
	while(fgets(buf, sizeof(buf), stdin), !feof(stdin)){
		if((num=write(fd, buf, strlen(buf))) == -1)
			perror("write error");
		else
			printf("Writer : wrote %d bytes \n", num);
	}
	return 0 ;
}

