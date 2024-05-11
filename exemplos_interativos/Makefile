%: %.c
	gcc  $@.c -o run_$@ -Wall -Werror
%: %.cpp
	g++ -Wall  $@.cpp -o run_$@

all: clean
	find . -name "*.c" -printf '%f\n'   -exec gcc {} -o {}.out -Wall -Werror \;
	find . -name "*.cpp" -printf '%f\n' -exec g++ {} -o {}.out -Wall -Werror \;
	find . -name "*.out" -printf '%p\n' -exec sh -c {} \;
clean:
	rm -f *.out figura_*.png
