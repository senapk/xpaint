libs:
	gcc -std=c89 -Wall -Werror exemplo_cores.c libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o exec_cores
	gcc -std=c89 -Wall -Werror exemplo_texto.c libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o exec_texto
	gcc -std=c89 -Wall -Werror exemplo_draw.c  libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o exec_draw
	./exec_cores
	./exec_texto
	./exec_draw
all:
	gcc -std=c89 -Wall -Werror exemplo_cores.c  -o exec_cores
	gcc -std=c89 -Wall -Werror exemplo_texto.c  -o exec_texto
	gcc -std=c89 -Wall -Werror exemplo_draw.c   -o exec_draw
	gcc -std=c89 -Wall -Werror exemplo_base.c   -o exec_base
	./exec_cores
	./exec_texto
	./exec_draw
	./exec_base
