#! /bin/zsh
echo -n '\x01\x00\x00\x00\x00\x01\x00\x00\x00\x00\x01\x00\x00\x00\x00' | socat - UDP-DATAGRAM:255.255.255.255:4210,BROADCAST