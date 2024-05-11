# Opções de compilação
CFLAGS = -Wall -Wextra -g

main: xpaint.o main.c
	gcc main.c -c $(CFLAGS)
	gcc main.o xpaint.o -o main.out $(CFLAGS)

xpaint.o: xpaint.c
	gcc -c xpaint.c $(CFLAGS)

%: %.c xpaint.o
	gcc  $@.c -c $(CFLAGS) 
	gcc  $@.o xpaint.o -o $@.out $(CFLAGS)


