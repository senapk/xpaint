#include "text.h" /*XDDDX*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base.h" /*XDDDX*/
#include "draw.h" /*XDDDX*/

#define __X_LETTER_SIZE 10
#define __X_LETTER_FIRST ' '
#define __X_LETTER_LAST '~'
const char * __x_asc_map[256];
static int   __x_font_size = 10;

void __x_init_font();

void __show_asc_map(){
    for(int i = __X_LETTER_FIRST; i <= __X_LETTER_LAST; i++){
        printf("%c\n", i);
        puts(__x_asc_map[i]);
    }
}

const int __x_agudo = 1;
const int __x_til = 2;
const int __x_circu = 3;
const int __x_crase = 4;
const int __x_rabo = 5;

typedef struct{
    char value;
    int acento;
}__x_Letter;

__x_Letter __x_replace_one(char c){
    int value = c;
    value += 128;
    if(value == -1)      return (__x_Letter){0, 0};
    else if(value ==  0) return (__x_Letter){'A', __x_crase};//À
    else if(value ==  1) return (__x_Letter){'A', __x_agudo};//Á
    else if(value ==  2) return (__x_Letter){'A', __x_circu};//Â
    else if(value ==  3) return (__x_Letter){'A', __x_til};//Ã

    else if(value ==  7) return (__x_Letter){'C', __x_rabo};//Ç

    else if(value ==  8) return (__x_Letter){'E', __x_crase};//È
    else if(value ==  9) return (__x_Letter){'E', __x_agudo};//É
    else if(value == 10) return (__x_Letter){'E', __x_circu};//Ê

    else if(value == 12) return (__x_Letter){'I', __x_crase};//Ì
    else if(value == 13) return (__x_Letter){'I', __x_agudo};//Í
    else if(value == 14) return (__x_Letter){'I', __x_circu};//Î

    else if(value == 18) return (__x_Letter){'O', __x_crase};//Ò
    else if(value == 19) return (__x_Letter){'O', __x_agudo};//Ó
    else if(value == 20) return (__x_Letter){'O', __x_circu};//Ô
    else if(value == 21) return (__x_Letter){'O', __x_til};//Õ

    else if(value == 25) return (__x_Letter){'U', __x_crase};//Ù
    else if(value == 26) return (__x_Letter){'U', __x_agudo};//Ú
    else if(value == 27) return (__x_Letter){'U', __x_circu};//Û

    else if(value == 32) return (__x_Letter){'a', __x_crase};//à
    else if(value == 33) return (__x_Letter){'a', __x_agudo};//á
    else if(value == 34) return (__x_Letter){'a', __x_circu};//â
    else if(value == 35) return (__x_Letter){'a', __x_til};//ã

    else if(value == 39) return (__x_Letter){'c', __x_rabo};//ç

    else if(value == 40) return (__x_Letter){'e', __x_crase};//è
    else if(value == 41) return (__x_Letter){'e', __x_agudo};//é
    else if(value == 42) return (__x_Letter){'e', __x_circu};//ê

    else if(value == 44) return (__x_Letter){'i', __x_crase};//ì
    else if(value == 45) return (__x_Letter){'i', __x_agudo};//í
    else if(value == 46) return (__x_Letter){'i', __x_circu};//î

    else if(value == 50) return (__x_Letter){'o', __x_crase};//ò
    else if(value == 51) return (__x_Letter){'o', __x_agudo};//ó
    else if(value == 52) return (__x_Letter){'o', __x_circu};//ô
    else if(value == 53) return (__x_Letter){'o', __x_til};//õ

    else if(value == 57) return (__x_Letter){'u', __x_crase};//ù
    else if(value == 58) return (__x_Letter){'u', __x_agudo};//ú
    else if(value == 59) return (__x_Letter){'u', __x_circu};//û

    else return (__x_Letter){0, 0};
}

void __x_replace_unicode(char * text, __x_Letter * output, size_t * length){
    int size = 0;
    int i = 0;
    while(text[i] != '\0'){
        if((int) text[i] > 0){
            output[size] = (__x_Letter){text[i], 0};
            size++;
            i += 1;
        }else if((int) text[i] == -61){
            __x_Letter v = __x_replace_one(text[i + 1]);
            if(v.value != 0){
                output[size] = v;
                size++;
            } else
                printf("%d \n", text[i + 1] + 128);
            i += 2;
        }else{
            printf("%d \n", text[i]);
            i += 1;
        }
    }
    output[size] = (__x_Letter){'\0', 0};
    *length = size;
}

void set_font_size(int value){
    __x_font_size = value;
}

int __x_write(int x, int y, __x_Letter * text, size_t length){
    size_t dx = 0;
    size_t dy = 0;
    int zoom = (__x_font_size)/__X_LETTER_SIZE;
    for(size_t i = 0; i < length; i++){
        int delta = (4) * zoom;
        if(text[i].value == '\n'){
            dy += 1;
            dx = 0;
            continue;
        }
        if(text[i].value != ' '){
            delta = draw_art(x + dx, y + dy * __X_LETTER_SIZE * zoom, zoom, __x_asc_map[(int)text[i].value]);
            int adx = 0, ady = 0, Adx = 0, Ady = 0;
            if(text[i].acento != 0){
                if(text[i].acento == __x_agudo){
                    adx = -1; ady = 0; Adx = -1; Ady = -2;
                }else if(text[i].acento == __x_til){
                    adx = -2; ady = 0;  Adx = -2; Ady = -2;
                }else if(text[i].acento == __x_circu){
                    adx = -2; ady = 0;  Adx = -2; Ady = -2;
                }else if(text[i].acento == __x_crase){
                    adx = -2; ady = 0; Adx = -2; Ady = -2;
                }else{
                    adx = -1; ady = 0;   Adx = -1; Ady = 0;
                }

                int px = 0, py = 0;
                if(text[i].value >= 'a'){
                    px = adx * zoom + x + dx + delta/2;
                    py = ady * zoom + y + dy * __X_LETTER_SIZE * zoom;
                }else{
                    px = Adx * zoom + x + dx + delta/2;
                    py = Ady * zoom + y + dy * __X_LETTER_SIZE * zoom;
                }
                draw_art(px, py, zoom, __x_asc_map[text[i].acento]);
            }
        }
        dx += delta;
    }
    return x + dx;
}

int write(int x, int y, const char * format, ...){
    static int init_asc = 0;
    if(!init_asc){
        init_asc = 1;
        __x_init_font();
        //show_asc_map();
    }
    char text[1000];
    va_list args;
    va_start( args, format );
    vsprintf(text, format, args);
    va_end( args );

    __x_Letter output[1000];
    size_t length = strlen(text);
    __x_replace_unicode(text, output, &length);

    int dx =__x_write(x, y, output, length);
    return dx;
}

void __x_init_font(){
__x_asc_map[__x_agudo] = (\
"   \n"
" #\n"
"#\0");
__x_asc_map[__x_til] = (\
"   \n"
" # #\n"
"# #\0");

__x_asc_map[__x_circu] = (\
"   \n"
" #\n"
"# #\0");

__x_asc_map[__x_crase] = (\
"\n"
"#\n"
" #\0");
__x_asc_map[__x_rabo] = (\
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"#\n"
" #\n"
"#\0");

__x_asc_map[' '] = "\n\n\n\n\n\n\0";
__x_asc_map['!'] = (\
"\n"
"\n"
"###\n"
"###\n"
"###\n"
" # \n"
"\n"
"###\n"
"###\0");
__x_asc_map['"'] = (\
"\n"
"\n"
" # #\n"
"# # \n"
"# #");
__x_asc_map['#'] = (\
"\n"
"\n"
"  # #  \n"
"  # #  \n"
"#######\n"
"  # #  \n"
"#######\n"
"  # #  \n"
"  # #  \0");
__x_asc_map['$'] = (\
"\n"
"\n"
"   #   \n"
" ##### \n"
"#  #   \n"
" ####  \n"
"   # # \n"
"#####  \n"
"   #   \0");
__x_asc_map['%'] = (\
"\n"
"\n"
"      \n"
"##  # \n"
"## #  \n"
"  #   \n"
" # ## \n"
"#  ## \n"
"\0");
__x_asc_map['&'] = (\
"\n"
"\n"
" ###  \n"
"#   # \n"
"#  #  \n"
" ##   \n"
" # #  \n"
"#   # \n"
" ##  #\0");
__x_asc_map['\''] = (\
"\n"
"\n"
"   \n"
"## \n"
"## \n"
"## \n"
"   \n"
"   \n"
"   \0");
__x_asc_map['('] = (\
"\n"
"\n"
"  ## \n"
" #   \n"
"#    \n"
"#    \n"
"#    \n"
" #   \n"
"  ## \0");
__x_asc_map[')'] = (\
"\n"
"\n"
"##    \n"
"  #   \n"
"   #  \n"
"   #  \n"
"   #  \n"
"  #   \n"
"##    \0");
__x_asc_map['*'] = (\
"\n"
"\n"
"\n"
"# #   \n"
" #   \n"
"# #   \n"
"\n"
"\n"
"\0");
__x_asc_map['+'] = (\
"\n"
"\n"
"      \n"
"  #   \n"
"  #   \n"
"##### \n"
"  #   \n"
"  #   \n"
"\0");
__x_asc_map[','] = (\
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
" ##  \n"
" ##  \n"
" #   \n"
"#    \0");
__x_asc_map['-'] = (\
"\n"
"\n"
"\n"
"\n"
"\n"
"##### \n"
"\n"
"\n"
"\0");
__x_asc_map['.'] = (\
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"##\n"
"##\0");
__x_asc_map['/'] = (\
"\n"
"\n"
"      #\n"
"     # \n"
"    #  \n"
"   #   \n"
"  #    \n"
" #     \n"
"#      \0");
__x_asc_map['0'] = (\
"\n"
"\n"
"  ###  \n"
" #   # \n"
"#     #\n"
"#  #  #\n"
"#     #\n"
" #   # \n"
"  ###  \0");
__x_asc_map['1'] = (\
"\n"
"\n"
"   #   \n"
"  ##   \n"
" # #   \n"
"   #   \n"
"   #   \n"
"   #   \n"
" ##### \0");
__x_asc_map['2'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"      #\n"
" ##### \n"
"#      \n"
"#      \n"
"#######\0");
__x_asc_map['3'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"      #\n"
" ##### \n"
"      #\n"
"#     #\n"
" ##### \0");
__x_asc_map['4'] = (\
"\n"
"\n"
"#      \n"
"#    # \n"
"#    # \n"
"#    # \n"
"#######\n"
"     # \n"
"     # \0");
__x_asc_map['5'] = (\
"\n"
"\n"
"#######\n"
"#      \n"
"#      \n"
"###### \n"
"      #\n"
"#     #\n"
" ##### \0");
__x_asc_map['6'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#      \n"
"###### \n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['7'] = (\
"\n"
"\n"
"#######\n"
"#    # \n"
"    #  \n"
"   #   \n"
"  #    \n"
"  #    \n"
"  #    \0");
__x_asc_map['8'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#     #\n"
" ##### \n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['9'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#     #\n"
" ######\n"
"      #\n"
"#     #\n"
" ##### \0");
__x_asc_map[':'] = (\
"\n"
"\n"
"\n"
" ##\n"
" ##\n"
"\n"
" ##\n"
" ##");
__x_asc_map[';'] = (\
"\n"
"\n"
"\n"
"\n"
" ##  \n"
" ##  \n"
"\n"
" ##  \n"
" #   \n"
"#    \0");
__x_asc_map['<'] = (\
"\n"
"\n"
"     # \n"
"   #   \n"
" #     \n"
"#      \n"
" #     \n"
"   #   \n"
"     # \0");
__x_asc_map['='] = (\
"\n"
"\n"
"       \n"
"       \n"
"#######\n"
"       \n"
"#######\n"
"       \n"
"       \0");
__x_asc_map['>'] = (\
"\n"
"\n"
" #     \n"
"   #   \n"
"     # \n"
"      #\n"
"     # \n"
"   #   \n"
" #     \0");
__x_asc_map['?'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"      #\n"
"   ### \n"
"   #   \n"
"       \n"
"   #   \0");
__x_asc_map['@'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"# ### #\n"
"# ### #\n"
"# #### \n"
"#      \n"
" ##### \0");
__x_asc_map['A'] = (\
"\n"
"\n"
"   #   \n"
"  # #  \n"
" #   # \n"
"#     #\n"
"#######\n"
"#     #\n"
"#     #\0");
__x_asc_map['B'] = (\
"\n"
"\n"
"###### \n"
"#     #\n"
"#     #\n"
"###### \n"
"#     #\n"
"#     #\n"
"###### \0");
__x_asc_map['C'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#      \n"
"#      \n"
"#      \n"
"#     #\n"
" ##### \0");
__x_asc_map['D'] = (\
"\n"
"\n"
"###### \n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
"###### \0");
__x_asc_map['E'] = (\
"\n"
"\n"
"#######\n"
"#      \n"
"#      \n"
"#####  \n"
"#      \n"
"#      \n"
"#######\0");
__x_asc_map['F'] = (\
"\n"
"\n"
"#######\n"
"#      \n"
"#      \n"
"#####  \n"
"#      \n"
"#      \n"
"#      \0");
__x_asc_map['G'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#      \n"
"#  ####\n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['H'] = (\
"\n"
"\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#######\n"
"#     #\n"
"#     #\n"
"#     #\0");
__x_asc_map['I'] = (\
"\n"
"\n"
"###  \n"
" #   \n"
" #   \n"
" #   \n"
" #   \n"
" #   \n"
"###  \0");
__x_asc_map['J'] = (\
"\n"
"\n"
"      #\n"
"      #\n"
"      #\n"
"      #\n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['K'] = (\
"\n"
"\n"
"#    # \n"
"#   #  \n"
"#  #   \n"
"###    \n"
"#  #   \n"
"#   #  \n"
"#    # \0");
__x_asc_map['L'] = (\
"\n"
"\n"
"#      \n"
"#      \n"
"#      \n"
"#      \n"
"#      \n"
"#      \n"
"#######\0");
__x_asc_map['M'] = (\
"\n"
"\n"
"#     #\n"
"##   ##\n"
"# # # #\n"
"#  #  #\n"
"#     #\n"
"#     #\n"
"#     #\0");
__x_asc_map['N'] = (\
"\n"
"\n"
"#     #\n"
"##    #\n"
"# #   #\n"
"#  #  #\n"
"#   # #\n"
"#    ##\n"
"#     #\0");
__x_asc_map['O'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['P'] = (\
"\n"
"\n"
"###### \n"
"#     #\n"
"#     #\n"
"###### \n"
"#      \n"
"#      \n"
"#      \0");
__x_asc_map['Q'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#     #\n"
"#     #\n"
"#   # #\n"
"#    # \n"
" #### #\0");
__x_asc_map['R'] = (\
"\n"
"\n"
"###### \n"
"#     #\n"
"#     #\n"
"###### \n"
"#   #  \n"
"#    # \n"
"#     #\0");
__x_asc_map['S'] = (\
"\n"
"\n"
" ##### \n"
"#     #\n"
"#      \n"
" ##### \n"
"      #\n"
"#     #\n"
" ##### \0");
__x_asc_map['T'] = (\
"\n"
"\n"
"#######\n"
"   #   \n"
"   #   \n"
"   #   \n"
"   #   \n"
"   #   \n"
"   #   \0");
__x_asc_map['U'] = (\
"\n"
"\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
" ##### \0");
__x_asc_map['V'] = (\
"\n"
"\n"
"#     #\n"
"#     #\n"
"#     #\n"
"#     #\n"
" #   # \n"
"  # #  \n"
"   #   \0");
__x_asc_map['W'] = (\
"\n"
"\n"
"#     #\n"
"#  #  #\n"
"#  #  #\n"
"#  #  #\n"
"#  #  #\n"
"#  #  #\n"
" ## ## \0");
__x_asc_map['X'] = (\
"\n"
"\n"
"#     #\n"
" #   # \n"
"  # #  \n"
"   #   \n"
"  # #  \n"
" #   # \n"
"#     #\0");
__x_asc_map['Y'] = (\
"\n"
"\n"
"#     #\n"
" #   # \n"
"  # #  \n"
"   #   \n"
"   #   \n"
"   #   \n"
"   #   \0");
__x_asc_map['Z'] = (\
"\n"
"\n"
"#######\n"
"     # \n"
"    #  \n"
"   #   \n"
"  #    \n"
" #     \n"
"#######\0");
__x_asc_map['['] = (\
"\n"
"\n"
"  ###  \n"
"  #    \n"
"  #    \n"
"  #    \n"
"  #    \n"
"  #    \n"
"  ###  \0");
__x_asc_map['\\'] = (\
"\n"
"\n"
"#      \n"
" #     \n"
"  #    \n"
"   #   \n"
"    #  \n"
"     # \n"
"      #\0");
__x_asc_map[']'] = (\
"\n"
"\n"
"  ###  \n"
"    #  \n"
"    #  \n"
"    #  \n"
"    #  \n"
"    #  \n"
"  ###  \0");
__x_asc_map['^'] = (\
"\n"
"\n"
"   #   \n"
"  # #  \n"
" #   # \n"
"       \n"
"       \n"
"       \n"
"       \0");
__x_asc_map['_'] = (\
"\n"
"\n"
"       \n"
"       \n"
"       \n"
"       \n"
"       \n"
"       \n"
"####\0");
__x_asc_map['`'] = (\
"\n"
"\n"
" ##    \n"
"   #   \n"
"    #  \n"
"       \n"
"       \n"
"       \n"
"       \0");
__x_asc_map['a'] = (\
"\n"
"\n"
"\n"
"\n"
" ### \n"
"    #\n"
" ####\n"
"#   #\n"
" ####\0");
__x_asc_map['b'] = (\
"\n"
"\n"
"#     \n"
"#     \n"
"####  \n"
"#   # \n"
"#   # \n"
"#   # \n"
"####  \0");
__x_asc_map['c'] = (\
"\n"
"\n"
"      \n"
"      \n"
" ###  \n"
"#   # \n"
"#     \n"
"#   # \n"
" ###  \0");
__x_asc_map['d'] = (\
"\n"
"\n"
"    # \n"
"    # \n"
" #### \n"
"#   # \n"
"#   # \n"
"#   # \n"
" #### \0");
__x_asc_map['e'] = (\
"\n"
"\n"
"      \n"
"      \n"
" ###  \n"
"#   # \n"
"####  \n"
"#     \n"
" ###  \0");
__x_asc_map['f'] = (\
"\n"
"\n"
"      \n"
" ###  \n"
"#   # \n"
"#     \n"
"###   \n"
"#     \n"
"#     \0");
__x_asc_map['g'] = (\
"\n"
"\n"
"      \n"
"      \n"
" ###  \n"
"#   # \n"
"#   # \n"
"#   # \n"
" #### \n"
"    # \n"
" ###  \0");
__x_asc_map['h'] = (\
"\n"
"\n"
"#     \n"
"#     \n"
"####  \n"
"#   # \n"
"#   # \n"
"#   # \n"
"#   # \0");
__x_asc_map['i'] = (\
"\n"
"\n"
"#\n"
"  \n"
"# \n"
"# \n"
"# \n"
"# \n"
"# \0");

__x_asc_map['j'] = (\
"\n"
"\n"
"   #   \n"
"      \n"
"   #  \n"
"   #  \n"
"   #  \n"
"   #  \n"
"   #  \n"
"#  #  \n"
" ##   \0");
__x_asc_map['k'] = (\
"\n"
"\n"
"       \n"
"#      \n"
"#   #  \n"
"#  #   \n"
"###    \n"
"#  #   \n"
"#   #  \0");
__x_asc_map['l'] = (\
"\n"
"\n"
"# \n"
"# \n"
"# \n"
"# \n"
"# \n"
"# \n"
" # \0");
__x_asc_map['m'] = (\
"\n"
"\n"
"       \n"
"       \n"
"###### \n"
"#  #  #\n"
"#  #  #\n"
"#  #  #\n"
"#  #  #\0");
__x_asc_map['n'] = (\
"\n"
"\n"
"       \n"
"       \n"
"####   \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
"#   #  \0");
__x_asc_map['o'] = (\
"\n"
"\n"
"       \n"
"       \n"
" ###   \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
" ###   \0");
__x_asc_map['p'] = (\
"\n"
"\n"
"       \n"
"       \n"
"####   \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
"####   \n"
"#      \n"
"#      \0");
__x_asc_map['q'] = (\
"\n"
"\n"
"       \n"
"       \n"
" ###   \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
" ####  \n"
"    #  \n"
"    #  \0");
__x_asc_map['r'] = (\
"\n"
"\n"
"       \n"
"       \n"
"# ###  \n"
"##     \n"
"#      \n"
"#      \n"
"#      \0");
__x_asc_map['s'] = (\
"\n"
"\n"
"       \n"
"       \n"
" ####  \n"
"#      \n"
" ###   \n"
"    #  \n"
"####   \0");
__x_asc_map['t'] = (\
"\n"
"\n"
" #    \n"
" #    \n"
"####  \n"
" #    \n"
" #    \n"
" # #  \n"
"  #   \0");
__x_asc_map['u'] = (\
"\n"
"\n"
"       \n"
"       \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
" ####  \0");
__x_asc_map['v'] = (\
"\n"
"\n"
"       \n"
"       \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
" # #   \n"
"  #    \0");
__x_asc_map['w'] = (\
"\n"
"\n"
"       \n"
"       \n"
"#   #  \n"
"#   #  \n"
"# # #  \n"
"# # #  \n"
" # #   \0");
__x_asc_map['x'] = (\
"\n"
"\n"
"\n"
"\n"
"#   #\n"
" # # \n"
"  #  \n"
" # # \n"
"#   #\0");
__x_asc_map['y'] = (\
"\n"
"\n"
"       \n"
"       \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
"#   #  \n"
" ####  \n"
"    #  \n"
" ###   \0");
__x_asc_map['z'] = (\
"\n"
"\n"
"       \n"
"       \n"
"#####  \n"
"    #  \n"
" ###   \n"
"#      \n"
"#####  \0");
__x_asc_map['{'] = (\
"\n"
" ### \n"
" #   \n"
" #   \n"
" #   \n"
"#    \n"
" #   \n"
" #   \n"
" #   \n"
" ### \0");
__x_asc_map['|'] = (\
"\n"
"\n"
" #   \n"
" #   \n"
" #   \n"
" #   \n"
" #   \n"
" #   \n"
" #   \0");
__x_asc_map['}'] = (\
"\n"
"###   \n"
"  #   \n"
"  #   \n"
"  #   \n"
"   #  \n"
"  #   \n"
"  #   \n"
"  #   \n"
"###   \0");
__x_asc_map['~'] = (\
"\n"
"\n"
"       \n"
"       \n"
" ###  #\n"
" #  ###\n"
"       \n"
"       \n"
"       \0");
}
