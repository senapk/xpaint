CFLAGS= -std=c89 -Wall -Werror

%: %.c
	$(CC) $(CFLAGS) $@.c -o exec_$@

all: make_lib clean exemplo_base exemplo_cores exemplo_texto exemplo_draw exemplo_fractal
	# encontra nessa pasta todos os arquivos que comecam com exec_ e executa
	find . -name "exec_*" -printf '%p\n' -exec sh -c {} \;
clean:
	rm -f exec_* figura_*
make_lib:
	./make_xpaint.sh