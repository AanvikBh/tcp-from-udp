#include "headers.h"

int main()
{
    int sock;
    struct sockaddr_in server_addr, client_addr;

    // Create a UDP socket and bind it to the server address
    sock = create_socket();
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind_socket(sock, server_addr);
    // client_addr.sin_family = AF_INET;
    // client_addr.sin_port = htons(CLIENT_PORT);
    // client_addr.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in sender_addr;

    client_addr = (receive_data(sock, sender_addr));

    // socklen_t sender_addr_len = sizeof(sender_addr);

    // int total_chunks = INT16_MAX; // You should set the total_chunks accordingly
    // char received_data[MAX_DATA_SIZE * total_chunks];
    // memset(received_data, 0, sizeof(received_data));


    

    // struct DataPacket receivedPackets[total_chunks];
    // int receivedPacketCount = 0;
    // int j = 0;
    // while (receivedPacketCount < total_chunks)
    // {
    //     struct DataPacket packet;
    //     // Receive a packet
    //     while (recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&sender_addr, &sender_addr_len) > 0 )
    //     {
    //         total_chunks = packet.total_chunks;
    //         // Send ack packet back if the packet sent has been received

    //         // to check ack being sent and retransmission happening 
    //         // if (packet.sequence_number == 3 && j < 3) {
    //         //     j++;
    //         //     continue;
    //         // }

    //         send_ack(sock, sender_addr, packet.sequence_number);

    //         // Check if packet.sequence_number is within the expected range
    //         if (packet.sequence_number > 0 && packet.sequence_number <= total_chunks)
    //         {
    //             // Store the received packet in the array
   
    //             receivedPackets[packet.sequence_number - 1] = packet;
    //             receivedPacketCount++;
    //             if ( receivedPacketCount == total_chunks){
    //                 break;
    //             }
    //             // printf("Hi %d\n", receivedPacketCount);
    //         }
    //     }
    //     // printf("Here %d\n", receivedPacketCount);
        
    // }

    // // printf("Here\n");

    // // Sort receivedPackets based on sequence_number
    // qsort(receivedPackets, total_chunks, sizeof(struct DataPacket), compare_sequence_numbers);

    // // Merge all data packets in the sorted order
    // for (int i = 0; i < total_chunks; i++)
    // {
    //     strcat(received_data, receivedPackets[i].data);
    // }

    // Display or use the aggregated received_data
    // printf("Received: %s", received_data);

    struct DataPacket packetArr2[4];
    strcpy(packetArr2[0].data, "This is data 1 sent from server\n");
    strcpy(packetArr2[1].data, "This is data 2 sent from server\n");
    strcpy(packetArr2[2].data, "This is data 3 sent from server\n");
    strcpy(packetArr2[3].data, "This is data 4 sent from server\n");
    for (int i = 0; i < 4; i++)
    {
        packetArr2[i].sequence_number = i + 1;
        packetArr2[i].total_chunks = 4;
    }
    // char *client_ip = inet_ntoa(sender_addr.sin_addr);
    // int client_port = ntohs(sender_addr.sin_port);
    

    send_data_chunk(packetArr2, 4, sock, client_addr);


    close(sock);
    return 0;
}
