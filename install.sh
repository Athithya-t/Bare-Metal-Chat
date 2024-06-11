#!/bin/bash

if ["$(id -u)" -ne 0]; then
	echo "Please run as root"
	exit 1
fi

gcc server/chat_server.c -o chat_server

mv chat_server /usr/local/bin/

chmod +x /usr/local/bin/chat_server

cp client/chat_client.py /usr/local/bin/chat_client

chmod +x /usr/local/bin/chat_client

echo "Installation complete.\n Use command 'chat_server' to run server. \n and command 'chat_client' to run client"
