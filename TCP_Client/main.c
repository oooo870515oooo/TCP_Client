//
//  main.c
//  TCP_Client
//
//  Created by 許韋中 on 2019/9/4.
//  Copyright © 2019 許韋中. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
    //socket的建立
    int sockfd=0;
    char message[1024];
    int time=1;
    while(time==1)
    {
        sockfd = socket(AF_INET , SOCK_STREAM , 0);
        if (sockfd == -1){
            printf("Fail to create a socket.");
        }

        //socket的連線
        struct sockaddr_in info;
        bzero(&info,sizeof(info));
        info.sin_family = PF_INET;
        //localhost test
        info.sin_addr.s_addr = inet_addr(argv[1]);
        info.sin_port = htons(atoi(argv[2]));
        int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
        if(err==-1){
            printf("Connection error");
        }

        //Send a message to server
        char end[]="exit";
        scanf("%s", message);
        char receiveMessage[100] = {};
        send(sockfd,message,sizeof(message),0);
        recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        printf("Get:%s\n",receiveMessage);
        if(!strcmp(receiveMessage, end))
        {
            time++;
        }
        if(!strcmp(message, end))
        {
            time++;
        }
    }
    close(sockfd);
    printf("close Socket\n");
    return 0;
}
