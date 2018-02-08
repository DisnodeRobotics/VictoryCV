#define PORT = 9000
#include <iostream>
#include "tcp/TCPClient.h"
#include <signal.h>
#include <thread>
#include <string.h>
#include "../logging/Logger.h"
using namespace std;

class VictoryConnectClient
{
  private:
    TCPClient *tcpClient;
    Logger logger;
    bool connected;
    void sig_exit(int s)
    {
        tcpClient->exit();
        exit(0);
    }
    static void recv_loop(TCPClient *client);
  public:
    VictoryConnectClient();
    bool Connect(string host);
    bool SendPacket(int type, string topic, string value);
    bool isConnected();
};
