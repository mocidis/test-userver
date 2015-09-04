#!/bin/bash
for i in `seq 0 300`; do
./client udp:127.0.0.1:23456 &
done
