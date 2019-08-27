
all:
	gcc -Wall main.c color.c xmath.c base.c save.c lodepng.c draw.c text.c modules.c -o main
	./main

%: %.c
	gcc -Wall $@.c color.c xmath.c base.c save.c lodepng.c draw.c text.c modules.c -o $@
	./$@