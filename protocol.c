
#include "headers.h"

int create_socket()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Error creating socket");
        exit(1);
    }
    return sock;
}

void bind_socket(int sock, struct sockaddr_in addr)
{
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Error binding socket");
        exit(1);
    }
}

void send_packet(int sock, struct sockaddr_in dest_addr, struct DataPacket packet)
{
    if (sendto(sock, &packet, sizeof(struct DataPacket), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) > 0)
    {
        printf("Packet with sequence num %d sent successfully\n", packet.sequence_number);
    }
}


void send_ack(int sock, struct sockaddr_in sender_addr, int sequence_number)
{
    struct AckPacket ack;
    ack.ack_number = sequence_number;
    if (sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&sender_addr, sizeof(sender_addr)) > 0)
    {   
        printf("Packet with ACK num %d sent successfully\n", ack.ack_number);
    }
}

void send_data_chunk(struct DataPacket packetArr[], int total_chunks, int sock, struct sockaddr_in server_addr){
    struct timeval packetSentAt[total_chunks];
    int ackReceived[total_chunks];
    int countSentPackets[total_chunks];
    memset(ackReceived, 0, sizeof(ackReceived));
    memset(countSentPackets, 0, sizeof(countSentPackets));

    // Initialize packetSentAt with current time
    for (int i = 0; i < total_chunks; i++)
    {
        gettimeofday(&packetSentAt[i], NULL);
        countSentPackets[i]=0;
    }

    int successfully_received = 0; // Count of successfully received packets

    while (1)
    {

        // Send all the packets once
        for (int i = 0; i < total_chunks; i++)
        {
            if(!ackReceived[i] && !countSentPackets[i])
                send_packet(sock, server_addr, packetArr[i]);
                countSentPackets[i]++;
            // Check if any ACKs are received
            struct AckPacket ack;
            struct sockaddr_in sender_addr;
            socklen_t sender_addr_len = sizeof(sender_addr);

            while (recvfrom(sock, &ack, sizeof(ack), MSG_DONTWAIT, (struct sockaddr *)&sender_addr, &sender_addr_len) > 0 && successfully_received < total_chunks)
            {
                // Mark the corresponding packet as acknowledged
                printf("ACK for packet with seq num %d received\n", ack.ack_number);
                if (ack.ack_number > 0 && ack.ack_number <= total_chunks)
                {
                    ackReceived[ack.ack_number - 1] = 1;
                    successfully_received++; // Increment the count of successfully received packets
                }
            }
        }

        for (int i = 0; i < total_chunks; i++)
        {
            // Check if ack for this packet has not been received
            
            if (!ackReceived[i])
            {
                struct timeval current_time;
                gettimeofday(&current_time, NULL);

                // Check if timeout has occurred (100 ms)
                if ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) -
                        (packetSentAt[i].tv_sec * 1000 + packetSentAt[i].tv_usec / 1000) >=
                    TIMEOUT_MS)
                {   
                    printf("ACK MISSING FOR %d\n", i+1);
                    // Retransmit the packet
                    send_packet(sock, server_addr, packetArr[i]);

                    // Update sent time
                    gettimeofday(&packetSentAt[i], NULL);
                }
            }
        }
        // If all packets have been acknowledged, break the loop
        if (successfully_received == total_chunks)
        {
            break;
        }
    }

    // Send the count of successfully received packets to the server
    // send_ack_count(sock, server_addr, successfully_received);

    // close(sock);
}



struct sockaddr_in receive_data(int sock, struct sockaddr_in sender_addr)
{
    int total_chunks = INT16_MAX; // You should set the total_chunks accordingly
    char* received_data=(char*)malloc(MAX_DATA_SIZE * total_chunks);
    memset(received_data, 0, sizeof(received_data));
    socklen_t sender_addr_len = sizeof(sender_addr);


    struct DataPacket* receivedPackets=(struct DataPacket*)malloc(sizeof(struct DataPacket)*total_chunks);
    int receivedPacketCount = 0;
    int j = 0;
    while (receivedPacketCount < total_chunks)
    {
        
        struct DataPacket packet;
        // Receive a packet
        while (recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&sender_addr, &sender_addr_len) > 0 )
        {   // printf("%d %d\n",receivedPacketCount, total_chunks);
            total_chunks = packet.total_chunks;
            receivedPackets=(struct DataPacket*)realloc(receivedPackets, sizeof(struct DataPacket)*total_chunks);
            // Send ack packet back if the packet sent has been received

            // to check ack being sent and retransmission happening 
            // if (packet.sequence_number == 3 && j < 3) {
            //     j++;
            //     continue;
            // }
            send_ack(sock, sender_addr, packet.sequence_number);

            // Check if packet.sequence_number is within the expected range
            if (packet.sequence_number > 0 && packet.sequence_number <= total_chunks)
            {
                // Store the received packet in the array
   
                receivedPackets[packet.sequence_number - 1] = packet;
                receivedPacketCount++;
                if ( receivedPacketCount == total_chunks){
                    break;
                }
                // printf("Hi %d\n", receivedPacketCount);
            }
        }
        // printf("Here %d\n", receivedPacketCount);
        
    }

    // printf("Here\n");

    // Sort receivedPackets based on sequence_number
    qsort(receivedPackets, total_chunks, sizeof(struct DataPacket), compare_sequence_numbers);

    // Merge all data packets in the sorted order
    for (int i = 0; i < total_chunks; i++)
    {
        strcat(received_data, receivedPackets[i].data);
    }
    printf("%s\n",received_data);

    return sender_addr;
}

int compare_sequence_numbers(const void* a, const void* b) {
    const struct DataPacket* packetA = (const struct DataPacket*)a;
    const struct DataPacket* packetB = (const struct DataPacket*)b;
    return packetA->sequence_number - packetB->sequence_number;
}