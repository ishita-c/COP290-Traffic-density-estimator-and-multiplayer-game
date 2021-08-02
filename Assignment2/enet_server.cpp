#include <enet/enet.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main() {
    if (enet_initialize () != 0) {
        printf("An error occurred while initializing ENet.\n");
        return 1;
    }

    ENetAddress address = {0};

    address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
    address.port = 7778; /* Bind the server to port 7777. */

    #define MAX_CLIENTS 2

    /* create a server */
    ENetHost * server = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

    if (server == NULL) {
        printf("An error occurred while trying to create an ENet server host.\n");
        return 1;
    }

    printf("Started a server...\n");

    ENetEvent event;
    ENetPeer * p;
    int connected=0;

    /* Wait up to 1000 milliseconds for an event. (WARNING: blocking) */
    //while(true){
    vector<ENetPeer*> peers; 
    while (enet_host_service(server, &event, 30000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:{
                printf("A new client connected from %x:%u.\n",  event.peer->address.host, event.peer->address.port);
                /* Store any relevant client information here. */
                /*string s="Client information";
                const char* pdata=s.c_str();
                const void* tmp=pdata;
                void* p=const_cast<void *>(tmp);
                event.peer->data=p;*/
                connected++;
                peers.push_back(event.peer);
                if (connected==2){
                ENetPacket * packet = enet_packet_create ("start", 
                                          strlen ("start") + 1, 
                                          ENET_PACKET_FLAG_RELIABLE);
                enet_host_broadcast(server, 0, packet);
                }
                break;
                }

            case ENET_EVENT_TYPE_RECEIVE:{
                printf("A packet of length %lu containing %s was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);
                /* Clean up the packet now that we're done using it. */
                if (connected<=1){
                ENetPacket * packet = enet_packet_create ("0", 
                                          strlen ("0") + 1, 
                                          ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(event.peer, 0, packet);
                break;
                }
                else{
                if (event.peer==peers[0])
                	enet_peer_send(peers[1],0,event.packet);
                if (event.peer==peers[1])
                	enet_peer_send(peers[0],0,event.packet);
                }
                break;
                }

            case ENET_EVENT_TYPE_DISCONNECT:{
                printf("%p disconnected.\n", event.peer->data);
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                connected--;
                break;
                }

            /*case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                printf("%s disconnected due to timeout.\n", event.peer->data);
                //Reset the peer's client information. 
                event.peer->data = NULL;
                break;*/

            case ENET_EVENT_TYPE_NONE:{
                break;
                }
        }
    }
    //}

    enet_host_destroy(server);
    enet_deinitialize();
    return 0;
}

