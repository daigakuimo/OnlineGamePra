#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;
 
int main() {
    int sockfd;
    struct sockaddr_in addr;
 
    // ソケット生成
    if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
        perror( "socket" );
    }
 
    // 送信先アドレス・ポート番号設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons( 1234 );
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
 
    // サーバ接続
    connect( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ) );
 
    // データ送信
    char receive_str[1024];
    
    json sendJson;
    sendJson["state"] = "init";
    sendJson["id"] = 1;
    sendJson["hand"] = 0;
    std::string s = sendJson.dump(); 
    const char* send_str = s.c_str();
    printf( "send:%s\n", send_str );
    if( send( sockfd, send_str, 1024, 0 ) < 0 ) {
        perror( "send" );
    } else {
        recv( sockfd, receive_str, 1024, 0 );
        printf( "receive:%s\n", receive_str );
    }
    sleep( 1 );
    
 
    // ソケットクローズ
    close( sockfd );
 
    return 0;
}