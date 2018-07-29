lib:
	gcc -Wall -Werror ecores.c libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o ecores
	gcc -Wall -Werror etexto.c libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o etexto
	gcc -Wall -Werror edraw.c libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o edraw
	./ecores
	./etexto
	./edraw
full:
	gcc -Wall -Werror ecores.c  -o ecores
	gcc -Wall -Werror etexto.c  -o etexto
	gcc -Wall -Werror etexto.c  -o edraw
	./ecores
	./etexto
	./edraw
