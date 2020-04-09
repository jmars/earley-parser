test: libbgc.a test.c libearley.o earley.h
	$(CC) -g test.c libbgc.a libearley.o -o test

libbgc.a:
	git submodule update --init --recursive
	$(MAKE) -C bgc
	ln -sf bgc/libbgc.a libbgc.a

libearley.o: earley.h earley.c
	$(CC) -g -c earley.c -o libearley.o