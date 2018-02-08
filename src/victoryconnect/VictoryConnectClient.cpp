#include "VictoryConnectClient.h"

VictoryConnectClient::VictoryConnectClient()
{
    tcpClient = new TCPClient();
    logger.SetClass("VictoryConnectClient");
}

bool VictoryConnectClient::Connect(string host)
{
    do
    {   
        logger.Info("Connect", "Connecting to server at: " + host);
       

        if (tcpClient->setup(host, 9000))
        {
            logger.Success("Connect", "Connected to server!");
            tcpClient->Send("0 0 id victory_cv");
            logger.Info("Connect", "Sent ID Packet.");
            connected = true;
            thread tcpRecTread(VictoryConnectClient::recv_loop,tcpClient);
            tcpRecTread.detach();
            //return true;
        }
        else
        {
            logger.Error("Connect", "Failed to connect. Retrying in 3s");
            connected = false;
            sleep(3.0);
        }
    } while (connected == false);
}


bool VictoryConnectClient::SendPacket(int type, string topic, string value){
    return tcpClient->Send("0 " + to_string(type) + " " + topic + " " + value + "**");
}

void VictoryConnectClient::recv_loop(TCPClient *client)
{
    Logger logger;
    logger.SetClass("VictoryConnectClient-Static");
    logger.Info("recv_loop", "Starting Recieve Loop.");
    while (1)
    {

        string rec = client->receive();
        if (rec != "")
        {
            //cout << "Server Response:" << rec << endl;
            client->Send("0 0 heartbeat no_data");
        }
        sleep(0.1);
    }
}

