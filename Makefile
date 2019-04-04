CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

nunchuck-test: nunchuck-test.o libnunchuck.a

libnunchuck.a: nunchuck.o
	ar rc libnunchuck.a nunchuck.o
	ranlib libnunchuck.a	

nunchuck-test.o: nunchuck-test.c nunchuck.h

nunchuck.o: nunchuck.c nunchuck.h

.PHONY: clean
clean:
	rm -rf libnunchuck.a  nunchuck-test *.o a.out 

.PHONY: test
test: clean nunchuck-test
	./nunchuck-test
