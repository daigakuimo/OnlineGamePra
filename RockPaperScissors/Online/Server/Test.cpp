#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <iostream>
// for convenience
using json = nlohmann::json;

int main()
{
    int sockfd;
    int client_sockfd;
    struct sockaddr_in addr;

    socklen_t len = sizeof( struct sockaddr_in );
    struct sockaddr_in from_addr;

    char buf[1024];

    // 受診バッファ初期化
    memset(buf, 0, sizeof(buf));

    // ソケット生成
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
    }

    // 待ち受け用IP・ポート番号
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    // バインド
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
    }

    // 受信待ち
    if(listen(sockfd,SOMAXCONN) < 0)
    {
        perror("listen");
    }

    // クライアントからのコネクト要求待ち
    if((client_sockfd = accept(sockfd, (struct sockaddr *)&from_addr, &len)) < 0)
    {
        perror("listen");
    }

    // 受信
    int rsize;
    while(1)
    {
        rsize = recv(client_sockfd, buf, sizeof(buf),0);

        if(rsize == 0)
        {
            break;
        }
        else if(rsize == -1)
        {
            perror("recv");
        }
        else
        {

            printf("receive:%s\n" , buf);
            json receiveJson = json::parse(buf);
            std::cout << receiveJson << std::endl; 
            std::string state = receiveJson["state"];
            int id = receiveJson["id"];
            std::cout << "state: " << state << std::endl;
            printf("id:%d\n" , id);


            sleep(1);

            // 応答
            printf("send:%s\n", buf);
            write(client_sockfd,buf,rsize);
        }   
    }

    // ソケットクローズ
    close(client_sockfd);
    close(sockfd);

    return 0;
    
    
}