all:
	./make_xpaint.sh
	gcc -Wall -Werror ecores.c -o ecores
	gcc -Wall -Werror etexto.c -o etexto
	./ecores
	./etexto