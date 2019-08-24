all : nfqnl_test

nfqnl_test: parser.o nfqnl_test.o
	gcc -o nfqnl_test parser.o nfqnl_test.o -lnfnetlink -lnetfilter_queue

nfqnl_test.o: nfqnl_test.c
	gcc -Wall -c -o nfqnl_test.o nfqnl_test.c -lnfnetlink -lnetfilter_queue

parser.o: parser.h parser.c
	gcc -c -o parser.o parser.c
clean:
	rm -f nfqnl_test *.o