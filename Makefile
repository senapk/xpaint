CFLAGS= -std=c89 -Wall -Werror

all: clean
	$(CC) $(CFLAGS) exemplo_cores.c  -o exec_cores
	$(CC) $(CFLAGS) exemplo_texto.c  -o exec_texto
	$(CC) $(CFLAGS) exemplo_draw.c   -o exec_draw
	$(CC) $(CFLAGS) exemplo_base.c   -o exec_base
	./exec_cores
	./exec_texto
	./exec_draw
	./exec_base

clean:
	rm -f exec_* figura_*
