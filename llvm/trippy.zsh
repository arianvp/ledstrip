#! /bin/zsh
echo -n '\x01\xcd\xcc\x4c\x3d\x06\x06\x08\x01\x00\x00\x00\x3f\x06\x01\x00\x00\x00\x3f\x04\x01\x00\x00\x80\x3f\x01\x00\x00\x00\x3f' | socat - UDP-DATAGRAM:255.255.255.255:4210,BROADCAST
