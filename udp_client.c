#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char* argv[]){
        if(argc != 3){
                printf("Usage:%s ip port\n",argv[0]);
                return 1;
        }
        int sock = socket(AF_INET, SOCK_DGRAM , 0 );// SOCK_DGRAM 表示UDP
        if(sock < 0){
                perror("socket");
                return 2;
        }
        printf("sock:%d\n",sock);
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[2]));//端口号是2位的数
        server.sin_addr.s_addr = inet_addr(argv[1]);

        char buf[1024];//缓冲区
        while(1){
                printf("Please Enter# ");
                fflush(stdout);
                ssize_t s = read(0, buf, sizeof(buf)-1);//-1是为了去掉‘/0’
                if( s > 0 ){
					    buf[s-1] = 0;
                        sendto( sock, buf, strlen(buf) , 0 , (struct sockaddr*)&server, sizeof(server));
                        ssize_t _s = recvfrom(sock,buf,sizeof(buf)-1,0,NULL,NULL);
                        if(_s > 0){
                                buf[_s] = 0;
                                printf("server echo# %s\n",buf);
                        }
                }
        }
        close(sock);//最后记得关闭sock,因为文件描述符也会有文件描述符泄漏
        return 0;
}
