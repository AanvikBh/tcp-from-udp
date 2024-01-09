#include "headers.h"

int main()
{
    int sock;
    struct sockaddr_in server_addr;

    // Create a UDP socket
    sock = create_socket();
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    struct DataPacket packetArr[5];
    strcpy(packetArr[0].data, "This is data 1 sent from client\n");
    strcpy(packetArr[1].data, "This is data 2 sent from client\n");
    strcpy(packetArr[2].data, "This is data 3 sent from client\n");
    strcpy(packetArr[3].data, "This is data 4 sent from client\n");
    strcpy(packetArr[4].data, "This is data 5 sent from client\n");

    for (int i = 0; i < 5; i++)
    {
        packetArr[i].sequence_number = i + 1;
        packetArr[i].total_chunks = 5;
    }

    // int total_chunks = 5;


    // Arrays to track sent packets and received acknowledgments

    send_data_chunk(packetArr, 5, sock, server_addr);


    // struct timeval packetSentAt[total_chunks];
    // int ackReceived[total_chunks];
    // int countSentPackets[total_chunks];
    // memset(ackReceived, 0, sizeof(ackReceived));

    // // Initialize packetSentAt with current time
    // for (int i = 0; i < total_chunks; i++)
    // {
    //     gettimeofday(&packetSentAt[i], NULL);
    //     countSentPackets[i]=0;
    // }

    // int successfully_received = 0; // Count of successfully received packets

    // while (1)
    // {

    //     // Send all the packets once
    //     for (int i = 0; i < total_chunks; i++)
    //     {
    //         if(!ackReceived[i] && !countSentPackets[i])
    //             send_packet(sock, server_addr, packetArr[i]);
    //             countSentPackets[i]++;
    //         // Check if any ACKs are received
    //         struct AckPacket ack;
    //         struct sockaddr_in sender_addr;
    //         socklen_t sender_addr_len = sizeof(sender_addr);

    //         while (recvfrom(sock, &ack, sizeof(ack), MSG_DONTWAIT, (struct sockaddr *)&sender_addr, &sender_addr_len) > 0 && successfully_received < total_chunks)
    //         {
    //             // Mark the corresponding packet as acknowledged
    //             printf("ACK for packet with seq num %d received\n", ack.ack_number);
    //             if (ack.ack_number > 0 && ack.ack_number <= total_chunks)
    //             {
    //                 ackReceived[ack.ack_number - 1] = 1;
    //                 successfully_received++; // Increment the count of successfully received packets
    //             }
    //         }
    //     }

    //     for (int i = 0; i < total_chunks; i++)
    //     {
    //         // Check if ack for this packet has not been received
            
    //         if (!ackReceived[i])
    //         {
    //             struct timeval current_time;
    //             gettimeofday(&current_time, NULL);

    //             // Check if timeout has occurred (100 ms)
    //             if ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) -
    //                     (packetSentAt[i].tv_sec * 1000 + packetSentAt[i].tv_usec / 1000) >=
    //                 TIMEOUT_MS)
    //             {   
    //                 printf("ACK MISSING FOR %d\n", i+1);
    //                 // Retransmit the packet
    //                 send_packet(sock, server_addr, packetArr[i]);

    //                 // Update sent time
    //                 gettimeofday(&packetSentAt[i], NULL);
    //             }
    //         }
    //     }
    //     // If all packets have been acknowledged, break the loop
    //     if (successfully_received == total_chunks)
    //     {
    //         break;
    //     }
    // }

    // Send the count of successfully received packets to the server
    // send_ack_count(sock, server_addr, successfully_received);

    // close(sock);

    struct sockaddr_in client_addr, sender_addr;
    // bind_socket(sock, client_addr);
    // client_addr.sin_family = AF_INET;
    // client_addr.sin_port = htons(CLIENT_PORT);
    // client_addr.sin_addr.s_addr = AF_INET;

    // ERROR OVER HERE SOMEWHERE 
    // char* receiveClient = 
    receive_data(sock, server_addr);

    // printf("Received: %s", receiveClient);

    close(sock);

    return 0;
}
