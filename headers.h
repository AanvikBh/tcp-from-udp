#ifndef __HEADERS_H__
#define __HEADERS_H__

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdint.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/time.h>

// #define MAX_DATA_SIZE 1024
// #define TIMEOUT_MS 100

// #include "protocol.h"

// struct DataPacket {
//     uint32_t sequence_number;
//     uint32_t total_chunks;
//     char data[MAX_DATA_SIZE];
//     int checksum;
//     int srcPort;
//     int destPort;
// };

// struct AckPacket {
//     uint32_t ack_number;
//     int srcPort;
//     int destPort;
// };


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h> // Include the select library



#define MAX_DATA_SIZE 1024
#define SERVER_PORT 12345 // Define the server port
#define CLIENT_PORT 12345 // Since this is a two way comms between one client and server, a single port will be used for both
#define TIMEOUT_MS 100

struct DataPacket {
    int sequence_number;
    int total_chunks;
    char data[MAX_DATA_SIZE];
};

struct AckPacket {
    int ack_number;
};


#include "protocol.h"

#endif