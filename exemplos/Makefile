%: %.c
	gcc  $@.c -o run_$@ -Wall -Werror
%: %.cpp
	g++ -Wall  $@.cpp -o run_$@

all: clean
	gcc -c ../mode_fast/xpaint.c -o c.xpaint -Wall -Werror
	g++ -c ../mode_fast/xpaint.c -o p.xpaint -Wall -Werror
	find . -name "*.c" -printf '%f\n'   -exec gcc -c {} -Wall -Werror \;
	find . -name "*.o" -printf '%f\n'   -exec gcc {} c.xpaint -o $(basename {}).out -Wall -Werror \;
	rm *.o
	find . -name "*.cpp" -printf '%f\n'   -exec g++ -c {} -Wall -Werror \;
	find . -name "*.o"   -printf '%f\n'   -exec g++ {} p.xpaint -o $(basename {}).out -Wall -Werror \;
	find . -name "*.out" -printf '%p\n' -exec sh -c {} \;
	rm *.o
	rm *.out
clean:
	rm -f *.out figura_*.png
	rm -f c.xpaint p.xpaint
	rm -f *.o

