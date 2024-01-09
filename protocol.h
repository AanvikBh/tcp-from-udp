#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

// void send_packet(int sock, struct sockaddr_in dest_addr, struct DataPacket packet);

// int wait_for_ack(int sock, struct sockaddr_in sender_addr, uint32_t expected_sequence_number);

// void send_ack(int sock, struct sockaddr_in sender_addr, uint32_t sequence_number);

int create_socket();
void bind_socket(int sock, struct sockaddr_in addr);
void send_packet(int sock, struct sockaddr_in dest_addr, struct DataPacket packet);
// int wait_for_ack(int sock, struct sockaddr_in sender_addr, int expected_sequence_number);
void send_ack(int sock, struct sockaddr_in sender_addr, int sequence_number);


void send_data_chunk(struct DataPacket packetArr[], int total_chunks, int sock, struct sockaddr_in server_addr);
struct sockaddr_in receive_data(int sock, struct sockaddr_in sender_addr);
int compare_sequence_numbers(const void* a, const void* b);
#endif