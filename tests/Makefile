
all:
	gcc -Wall main.c ../src/*.c -o main.out && ./main.out
# %: %.c
# 	gcc -Wall $@.c color.c xmath.c base.c lodepng.c draw.c text.c modules.c -o $@
# 	./$@

%: %.c
	gcc -Wall $@.c ../src/*.c -o $@
	./$@

# gcc -Wall -Wextra -Werror -fsanitize=address $@.cpp color.c xmath.c base.c lodepng.c draw.c text.c modules.c -o $@
#	./$@
