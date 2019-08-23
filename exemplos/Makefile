CFLAGS= -std=c89 -Wall -Werror
CC = gcc

%: %.c
	$(CC)  $@.c -o exec_$@ $(CFLAGS)
%: %.cpp
	g++ -Wall  $@.cpp -o exec_$@

all: clean exemplo_base exemplo_cores exemplo_arvore exemplo_texto exemplo_draw exemplo_triangulo exemplo_grid
	# encontra nessa pasta todos os arquivos que comecam com exec_ e executa
	find . -name "exec_*" -printf '%p\n' -exec sh -c {} \;
clean:
	rm -f exec_* imgs/figura_*
