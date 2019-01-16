//このコードが2用

#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/time.h>
#define MAX_BUF 1024
#define SERVER_PORT 8080
#define QUEUE_SIZE 5
#define SERVER_ADDR "10.4.193.175"



int main(int argc, char const *argv[])
{

    int sd,rc,wc;
    static char buf[MAX_BUF];
    char messege[]="ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";

    struct sockaddr_in sv_addr;
    scanf("%s",messege);

    for(int i=0;i<MAX_BUF;i++)
        buf[i]=0;

    if((sd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket");
        exit(1);
    }

    memset(&sv_addr,0,sizeof(sv_addr));

    sv_addr.sin_family=AF_INET;
    sv_addr.sin_port=htons(SERVER_PORT);
    sv_addr.sin_addr.s_addr=inet_addr(SERVER_ADDR);

    if(connect(sd,(struct sockaddr *)&sv_addr,sizeof(sv_addr))==-1){
        perror("connect");
        exit(1);
    }

    if((wc=write(sd,messege,strlen(messege)))==-1){
        perror("write");
        exit(1);
    }
    
    fprintf(stderr,"Sending %d bytes message \n",wc);

    if((rc=read(sd,buf,sizeof(buf)))==-1){
        perror("read");
        exit(1);
    }

    fprintf(stderr,"Receving %d bytes messege\n",rc);
    printf("%s \n",buf);

    close(sd);
    
    return 0;
}
