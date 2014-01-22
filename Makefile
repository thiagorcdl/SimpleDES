CFLAG=-Wall
	PROG = crypt
	PROG2 = decrypt
	OBJS = src/cryptDES.c
	OBJS2 = src/decryptDES.c
	CC = gcc

all: $(OBJS)
	gcc -o $(PROG) $(OBJS)
	gcc -o $(PROG2) $(OBJS2)

clean:
	@rm -r $(PROG) $(PROG2)
