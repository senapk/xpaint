CFLAGS= -Wall -Werror

%: %.c
	gcc  $@.c -o run_$@ $(CFLAGS)
%: %.cpp
	g++ -Wall  $@.cpp -o run_$@


all: clean ex_arvore ex_balls ex_cores ex_draw ex_floodfill ex_grid ex_rotate ex_texto ex_triangulo 
	find . -name "run_*" -printf '%p\n' -exec sh -c {} \;
clean:
	rm -f run_* figura_*.png
