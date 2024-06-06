#!/usr/bin/env python3
import socket

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 8000

sockt = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

sockt.connect((SERVER_HOST,SERVER_PORT))

print("Welcome to Bare Metal Chat")
try:

	while(True):
		print("Enter your message")
		msg = input()
		if msg.lower() == "exit":
			break
		sockt.sendall(msg.encode())

		resp = sockt.recv(1024)

		print("\tServer response",resp.decode())

finally:
	sockt.close()
