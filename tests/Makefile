
all: main
# %: %.c
# 	gcc -Wall $@.c color.c xmath.c base.c lodepng.c draw.c text.c modules.c -o $@
# 	./$@

%: %.c
	gcc -Wall -Wextra -Werror -fsanitize=address $@.c ../src/*.c -o $@
	./$@
	rm -f ./$@

%: %.cpp
	gcc -Wall $@.cpp color.c xmath.c base.c lodepng.c draw.c text.c modules.c -o $@
	./$@

