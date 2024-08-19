CFLAGS := -I. -g -Og

slab: slab.o main.o

%.o: %.c slab.h 
	$(CC) $(CFLAGS) -c -o $@ $<
