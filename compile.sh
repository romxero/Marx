#!/bin/bash
#This is used to compile the distributed jobn scheduling program named Marx
#Created by Randy White
#Make sure we add gdb support to this application
gcc  main.c -o Marxd -lpthread -lconfig -g
gcc  client.c -o Marx -lpthread -lconfig -g

#this is a quick compile script used to change the binaries as I see fit, you can call it a ghetto make file
