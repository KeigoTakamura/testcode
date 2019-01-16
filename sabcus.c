#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define MAX_BUF 1000000000

#define SERVER_PORT 8080
#define QUEUE_SIZE 5

int main(int argc,char *argv[]){

    int sv_sd,io_sd,rc,wc;
    int cl_len;
    static char buf[MAX_BUF];
    struct sockaddr_in sv_addr,cl_addr;
    cl_len=sizeof(cl_addr);

    for(int i=0;i<MAX_BUF;i++)
        buf[i]=0;

    if((sv_sd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket");
        exit(1);
    }

    memset(&sv_addr,0,sizeof(sv_addr));

    sv_addr.sin_family=AF_INET;
    sv_addr.sin_port=htons(SERVER_PORT);
    sv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sv_sd,(struct sockaddr *)&sv_addr,sizeof(sv_addr))==-1){
        perror("bind");
        exit(1);
    }

    if(listen(sv_sd,QUEUE_SIZE)==-1){
        perror("listen");
        exit(1);
    }


    
    while(1){
        /* code */
        if((io_sd=accept(sv_sd,(struct sockaddr *)&cl_addr,&cl_len))==-1){
            perror("accept");
            exit(1);
        }

        fprintf(stderr,"Receiving the messege...\n");
        if((rc=recv(io_sd,buf,sizeof(buf),MSG_WAITALL))==-1){
            perror("read");
            exit(1);
        }

        fprintf(stderr,"Seding the message...\n");

        if((wc=send(io_sd,buf,rc,0)==-1)){
            perror("write");
            exit(1);
        }

        fprintf(stderr,"Echo %d bytes message\n",rc);

        close(io_sd);
    }

    
return 0;
}