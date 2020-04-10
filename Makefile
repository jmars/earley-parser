test: test.c libearley.a earley.h
	$(CC) -g test.c libearley.a -o test

libbgc.a:
	git submodule update --init --recursive
	$(MAKE) -C bgc
	ln -sf bgc/libbgc.a libbgc.a

libearley.o: earley.h earley.c
	$(CC) -g -c earley.c -o libearley.o

earley.a: libearley.o
	ar rcs earley.a libearley.o

libearley.a: earley.a libbgc.a libearley.mri
	ar -M <libearley.mri