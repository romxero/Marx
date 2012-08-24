#!/bin/bash
#This is used to compile the distributed jobn scheduling program named Marx
#Created by Randy White
#Make sure we add gdb support to this application
gcc -O2 main.c -o Marx -lpthread -g
