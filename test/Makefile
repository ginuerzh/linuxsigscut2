ipmsg_test : *.c *.h ../core/*.c ../core/*h
	gcc -g -o ipmsg_test ipmsg_test.c ../core/core.c ../core/ipmsg_protocol.c ../core/messageUtils.c ../core/userUtils.c ../core/network.c -lpthread

clean:
	rm ipmsg_test
