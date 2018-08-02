CFLAGS= -std=c89 -Wall -Werror

%: %.c
	$(CC) $(CFLAGS) $@.c -o exec_$@

# compila todos os exemplos usando o modelo acima
all: clean exemplo_base exemplo_cores exemplo_texto exemplo_draw
	# encontra nessa pasta todos os arquivos que comecam com exec_
	# executa-os pelo xargs
	find . -name "exec_*" -printf '%p\n' -exec sh -c {} \;
clean:
	rm -f exec_* figura_*
