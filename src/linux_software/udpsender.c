// UDP Packet Sending
// Some code generated with AI.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define UDP_PORT 25344
#define PACKET_SIZE 1028
#define NUM_SAMPLES 256

int main(int argc, char *argv[])
{
    // Show usage and quit if user does not provide 2 arguments.
    if (argc != 3) {
        printf("Usage: %s <destination_ip> <num_packets>\n", argv[0]);
        printf("Example: %s 192.168.1.23 10\n", argv[0]);
        return 1;
    }

    const char *dest_ip = argv[1];
    int num_packets = atoi(argv[2]);

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }

    // Configure destination
    struct sockaddr_in dest; // Used to store info about destination computer.
    memset(&dest, 0, sizeof(dest)); // Clear the struct by setting everything to zero.

    dest.sin_family = AF_INET; // Tells Linux we're using IPv4.
    dest.sin_port = htons(UDP_PORT); // Sets destination port to 25344 per Lab 11 UDP Data Format.

    // Convert human-readable IP address into binary form.
    // Needed so Linux can use the destination address.
    if (inet_pton(AF_INET, dest_ip, &dest.sin_addr) != 1) {
        printf("Invalid IP address\n");
        close(sock);
        return 1;
    }

    // Packet buffer
    uint8_t packet[PACKET_SIZE];

    // Main loop to send each packet.
    for (int p = 0; p < num_packets; p++) {

        // First 4 bytes are the packet counter.
        uint32_t counter = (uint32_t)p;
        memcpy(packet, &counter, 4);

        // Generate 256 complex samples
        for (int i = 0; i < NUM_SAMPLES; i++) {

            // Fake samples
            int16_t I = (int16_t)(i * 100);
            int16_t Q = (int16_t)(-i * 100);

            // Place the fake samples in the correct locations
            // in the packet per Lab 11 UDP Data Format.
            memcpy(&packet[4 + i * 4], &I, 2);
            memcpy(&packet[4 + i * 4 + 2], &Q, 2);
        }

        // Send packet
        ssize_t sent = sendto(
            sock, // Which UDP socket to use
            packet, // Data to send
            PACKET_SIZE, // Number of bytes to send
            0, // No special sending flags
            (struct sockaddr *)&dest, // Destination IP and port
            sizeof(dest) // Size of destination struct
        );

        if (sent != PACKET_SIZE) {
            perror("sendto");
            close(sock);
            return 1;
        }

        printf("Sent packet %d\n", p);
    }

    close(sock);

    printf("Finished sending packets!\n");

    return 0;
}
