# Networks Report 
Aanvik Bhatnagar 
2022101103

# Implementation of TCP with UDP

In the implementation given, Data Sequencing is done already in a hard-coded manner for the sake of illustration of the implementation. This can be further implemented into a mroe generalised Data Sequencing routine by taking a fixed data size in the struct and iterating in the original text and setting up seq nums accordingly. 

send_data_chunks() and receive_data() are two generalised functions with the name being self explanatory. There are many other helper functions like send_packet(), send_ack_packet(), create_socket(), bind_socket() which use UDP protocol functions to implement the following aspects of TCP:

a. ACK receiving: After a time slice of 0.1 sec, sender will check in a boolean array for chunks whether the ACK for the packet has not been received in time slice, and accordingly take actions. It will first fire packets and if by change any ack after firing that packet has been received, then it will update the boolean array, and keep on firing the packets. 

b. Sequencing of received data: Since in this implementation, sequence number is the index of the chunk, so if we sort all the data packets (only when all the packets sent by the sender are received) based on ascending sequence number, then we will get the original text. Total number of packets sent and received are kept track in the helper functions, so that necessary break conditions are reached.


Differences from Traditional TCP:
a. Since for the sake of simplicity, SYN, FIN bits functionality has not been set up, but can be set up by sending a request packet from client's side to the server for letting the server know that it wants to send packets. And then similarly for ending the connection. This can be done with adding additional fields to the DataPacket struct.
b. In original TCP, at the time of connection, both the parties are aware of each other's addresses. But in our model, since UDP is connectionless, we get to know the address of the sender based on the first packet received. Other information like total_chunks are also known only after the first transmission.

# Incorporating FLow Control 

Sliding Window Technique:
Plan to Implement it- Add another field in the struct called size_of_window. This can be received based on sending the first package (can be treated as the SYN package), where client gets to know the window size set by the server. Then client will first break the text message into chunks of window size, and if window_size>data_chunk_size, then each of these chunks will be broken down into subsequent sub chunks, and only sub chunks of a particular window will be sent at once. Only if all the ACKs for that particular window are received, then only another window gets transmitted. 
If the receiver wants to increase window_size, it can send one PAUSE packet to the client, and after letting the client know about the change, in the remaining transmissions, new window size can be chosen by the server. 