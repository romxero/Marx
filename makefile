# Simple Makefile for marxd

all : Marxd jobsender

Marxd : main.c
	@echo "Complie and Link Marxd"
	gcc  main.c -o Marxd -lpthread -lconfig -g 
#-Wall

jobsender : jobsender.c
	@echo "Complie and Link jobsender"
	gcc  jobsender.c -o jobsender -lpthread -lconfig -g 
#-Wall

install :
	@echo "For installing, just copying the default configfile"
	cp default_marxd.conf marxd.conf

clean :
	@echo "Cleanup Marxd and jobsender"
	rm -f Marxd jobsender

uninstall :
	@echo "Cleanup Marxd and jobsender"
	rm -f Marxd jobsender marxd.conf
