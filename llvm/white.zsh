#! /bin/zsh
echo -n '\x01\x00\x00\x80\x3f\x01\x00\x00\x00\x00\x01\x00\x00\x80\x3f' | socat - UDP-DATAGRAM:192.168.1.143:4210

