all : init sender receiver
.PHONY : clean
init : init.o common.o
	cc -pthread -o init init.o common.o
sender : sender.o common.o
	cc -pthread -o sender sender.o common.o
receiver : receiver.o common.o
	cc -pthread -o receiver receiver.o common.o
init.o : common.h           
sender.o : common.h
receiver.o : common.h
clean : 
	rm  init 
	rm  receiver
	rm  sender 
	rm  *.o
