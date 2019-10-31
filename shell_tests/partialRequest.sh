#!/usr/bin/env bash

#mkdir tmp
#tempfifo=tmp/fifo
mkfifo fifo

../build/bin/server ./test_config &
SERVER_PID=$!
sleep .5

exec 3<> fifo

nc localhost 5566 <fifo &
NC_PID=$!

sleep .5
printf "GET /static/bearlist.txt HTTP/1.1\r\nUser-Agent: nc/0." >&3
sleep .5
printf "0.1\r\nHost: 127.0.0.1\r\nAccept: */*\r\n\r\n" >&3

#cat <&3

sleep 1

kill $NC_PID
kill $SERVER_PID
exec 3>&-
rm fifo