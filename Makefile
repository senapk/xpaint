all:
	#gcc -std=c89 -Wall -Werror ecores.c ../libs/xdraw.c ../libs/ximage.c ../libs/xmath.c ../libs/xpng.c ../libs/xy.c -o ecores_exe
	#gcc -std=c89 -Wall -Werror etexto.c ../libs/xdraw.c ../libs/ximage.c ../libs/xmath.c ../libs/xpng.c ../libs/xy.c -o etexto_exe
	gcc -std=c89 -Wall -Werror exemplos/edraw.c  libs/xdraw.c libs/ximage.c libs/xmath.c libs/xpng.c libs/xy.c -o exemplos/edraw_exe
	#./ecores_exe
	#./etexto_exe
	./exemplos/edraw_exe
full:
	gcc -std=c89 -Wall -Werror ecores.c  -o ecores_exe
	gcc -std=c89 -Wall -Werror etexto.c  -o etexto_exe
	gcc -std=c89 -Wall -Werror edraw.c   -o edraw_exe
	./ecores_exe
	./etexto_exe
	./edraw_exe
