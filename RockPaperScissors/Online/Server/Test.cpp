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
    
    rsize = recv(client_sockfd, buf, sizeof(buf),0);

    if(rsize == 0)
    {
        
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
        

        // 応答
        printf("send id:%d\n", 1);
        json sendJson;
        sendJson["id"] = 1;
        std::string s = sendJson.dump(); 
        const char* buf = s.c_str();
        write(client_sockfd,buf,rsize);

    }   

    json sJson;
    sJson["state"] = "start";
    std::string si = sJson.dump(); 
    const char* sbuf = si.c_str();
    write(client_sockfd,sbuf,1024);

    std::cout << sbuf << std::endl; 

    while(1)
    {
        char b[1024];
        rsize = recv(client_sockfd, b, sizeof(b),0);

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
            printf("receive:%s\n" , b);
            if(b[0] != '\0')
            {
                json receiveJson = json::parse(b);
                std::cout << receiveJson << std::endl; 
                std::string state = receiveJson["state"];
                
                // 応答
                printf("send id:%d\n", 1);
                json j;
                j["state"] = "result";
                j["result"] = "draw";
                std::string s = j.dump(); 
                const char* sendBuf = s.c_str();
                write(client_sockfd,sendBuf,rsize);
            }
        }   
    }

    



    

    // ソケットクローズ
    close(client_sockfd);
    close(sockfd);

    return 0;
    
    
}