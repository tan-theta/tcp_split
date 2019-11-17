tcp_split: tcp_split.o
	gcc tcp_split.o -o tcp_split
tcp_split.o: tcp_split.c
	gcc -c tcp_split.c
clean:
	rm *.o


