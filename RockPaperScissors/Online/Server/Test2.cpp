#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sys/select.h>

// for convenience
using json = nlohmann::json;

int main()
{
    int sockfd;
    int client_sockfd;
    struct sockaddr_in addr;

    socklen_t len = sizeof( struct sockaddr_in );
    struct sockaddr_in from_addr;
    
    int fd2[2];        // 通信用ディスクリプタの配列

    char buf[1024];
    int     cnt;

    // 受診バッファ初期化
    memset(buf, 0, sizeof(buf));
    for ( int i = 0; i < sizeof(fd2)/sizeof(fd2[0]); i++ ){
        fd2[i] = -1;
    }

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
    if(listen(sockfd,1) < 0)
    {
        perror("listen");
    }

    int     maxfd;          // ディスクリプタの最大値
    fd_set  rfds;           // 接続待ち、受信待ちをするディスクリプタの集合
    struct timeval  tv;     // タイムアウト時間

    while(1)
    {
        // 接続待ちのディスクリプタをディスクリプタ集合に設定する
        FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);
        maxfd = sockfd;

        // 受信待ちのディスクリプタをディスクリプタ集合に設定する
        for ( int i = 0; i < sizeof(fd2)/sizeof(fd2[0]); i++ )
        {
            if(fd2[i] != -1)
            {
                FD_SET(fd2[i], &rfds);
                if ( fd2[i] > maxfd ) maxfd = fd2[i];
            }
        }

        // タイムアウト時間を10sec+500000μsec に指定する。
        tv.tv_sec = 0;
        tv.tv_usec = 0;


        cnt = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        if(cnt < 0)
        {
            if(errno == EINTR) continue;

            break;
        }
        else if(cnt == 0)
        {
            continue;
        }
        else
        {
            // 接続待ちディスクリプタに接続があるか調べる
            if(FD_ISSET(sockfd, &rfds))
            {
                for ( int i = 0; i < sizeof(fd2)/sizeof(fd2[0]); i++ )
                {
                    if ( fd2[i] == -1 )
                    {
                        if((fd2[i] = accept(sockfd, (struct sockaddr *)&from_addr, &len)) < 0)
                        {
                            perror("error accept");
                        }

                        
                        printf("socket[%d] connected\n" , fd2[i]);
                        break;
                    }
                }
            }

            for ( int i = 0; i < sizeof(fd2)/sizeof(fd2[0]); i++ )
            {
                if(FD_ISSET(fd2[i], &rfds))
                {
                    // データがあるならパケット受信する
                    cnt = recv( fd2[i], buf, sizeof(buf), 0 );
                    if ( cnt > 0 ) 
                    {
                        // パケット受信成功の場合
                        printf("recv[%d]:\"%s\"\n",fd2[i], buf );
                    }
                    else if ( cnt == 0 ) 
                    {
                        // 切断された場合、クローズする
                        printf("socket:%d  disconnected. \n", fd2[i] );
                        close( fd2[i] );
                        fd2[i] = -1;
                    } 
                    else 
                    {
                        perror("error recv");
                    }
                }
            }
        }
        
    }



    // クライアントからのコネクト要求待ち
    // if((client_sockfd = accept(sockfd, (struct sockaddr *)&from_addr, &len)) < 0)
    // {
    //     perror("listen");
    // }




    // // 受信
    // int rsize;
    
    // rsize = recv(client_sockfd, buf, sizeof(buf),0);

    // if(rsize == 0)
    // {
        
    // }
    // else if(rsize == -1)
    // {
    //     perror("recv");
    // }
    // else
    // {

    //     printf("receive:%s\n" , buf);
    //     json receiveJson = json::parse(buf);
    //     std::cout << receiveJson << std::endl; 
    //     std::string state = receiveJson["state"];
        

    //     // 応答
    //     printf("send id:%d\n", 1);
    //     json sendJson;
    //     sendJson["id"] = 1;
    //     std::string s = sendJson.dump(); 
    //     const char* buf = s.c_str();
    //     write(client_sockfd,buf,rsize);

    // }   

    // json sJson;
    // sJson["state"] = "start";
    // std::string si = sJson.dump(); 
    // const char* sbuf = si.c_str();
    // write(client_sockfd,sbuf,1024);

    // std::cout << sbuf << std::endl; 

    // while(1)
    // {
    //     char b[1024];
    //     rsize = recv(client_sockfd, b, sizeof(b),0);

    //     if(rsize == 0)
    //     {
    //         break;
    //     }
    //     else if(rsize == -1)
    //     {
    //         perror("recv");
    //     }
    //     else
    //     {
    //         printf("receive:%s\n" , b);
    //         if(b[0] != '\0')
    //         {
    //             json receiveJson = json::parse(b);
    //             std::cout << receiveJson << std::endl; 
    //             std::string state = receiveJson["state"];
                
    //             // 応答
    //             printf("send id:%d\n", 1);
    //             json j;
    //             j["state"] = "result";
    //             j["result"] = "draw";
    //             std::string s = j.dump(); 
    //             const char* sendBuf = s.c_str();
    //             write(client_sockfd,sendBuf,rsize);
    //         }
    //     }   
    // }


    // ソケットクローズ
    for ( int i = 0; i < sizeof(fd2)/sizeof(fd2[0]); i++ )
    {
        close(fd2[i]);
    }

    close(sockfd);

    return 0;
    
    
}