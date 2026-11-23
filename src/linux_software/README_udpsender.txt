Instructions for udpsender
Student: David Tso

Compile:

gcc udpsender.c -o udpsender

Run:

./udpsender <destination_ip> <number_of_packets>

Example:

./udpsender 192.168.1.23 10

Sends 10 packets to 192.168.1.23 on UDP port 25344.