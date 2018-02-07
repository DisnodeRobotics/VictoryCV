#include "VictoryConnectClient.h"

VictoryConnectClient::VictoryConnectClient()
{
    tcpClient = new TCPClient();
   
}

bool VictoryConnectClient::Connect(string host)
{
    do
    {
        cout << "Connecting to server at " << host << endl;

        if (tcpClient->setup(host, 9000))
        {
            tcpClient->Send("0 0 id victory_cv");
            cout << "TCP Start" << endl;
            connected = true;
            thread tcpRecTread(VictoryConnectClient::recv_loop,tcpClient);
            tcpRecTread.detach();
            //return true;
        }
        else
        {
            cout << "Failed Connection. Attempting in 3s" <<endl;
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
    cout << "Starting Client Loop" << endl;
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

