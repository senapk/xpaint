#ifndef XIMAGE_H /* XDDDX */
#define XIMAGE_H /* XDDDX */


/*
###############################################
######## DEFINES e TIPOS BASICOS ##############
###############################################
*/

/* apelido para um char sem sinal */
typedef unsigned char uchar;

/* struct que representa uma cor RGB */
typedef struct{
    uchar r;
    uchar g;
    uchar b;
} XColor;

/* cria e retorna uma struct XColor passando rgb */
XColor make_xcolor(uchar r, uchar g, uchar b);

/* lista de cores default */
extern XColor RED;
extern XColor GREEN;
extern XColor BLUE;
extern XColor YELLOW;
extern XColor CYAN;
extern XColor MAGENTA;
extern XColor ORANGE;
extern XColor VIOLET;
extern XColor WHITE;
extern XColor BLACK;

/*
###############################################
######## ABRINDO, FECHANDO, SALVANDO ##########
###############################################
*/

/* abre um bitmap com essas dimensões */
void x_open(int width, int height);

/* finaliza o bitmap liberando os recursos */
void x_close();

/* para salvar um png no arquivo
   não inclua a extensão .png no nome do arquivo
*/
void x_save(const char* filename);

/*
###############################################
#### PLOTANDO, ESCREVENDO, LIMPANDO ###########
###############################################
*/

/* a funcao plot pinta o pixel usando a cor */
void x_plot(int x, int y);

/* a funcao write escreve um texto text, na posição px, py.
   retorna o x da posição após o último caractere escrito.
*/
int x_write(int x, int y, const char * format, ...);

/* limpa a tela inteira com a mesma cor */
void x_clear(XColor color);

/*
###############################################
### FUNÇÕES SET: Cor, Fonte, Paleta de Cores ##
###############################################
*/

/* muda a cor do pincel para todas as funcoes de desenho */
void xs_color(XColor color);

/* define uma cor na palheta de caracteres */
void xs_palette(char c, XColor color);

/* mudar o tamanho da fonte em pixels */
void xs_font_size(int size);

/* muda a font passando o path da nova fonte */
void xs_font(const char* filename);

/*
###############################################
############## FUNÇÕES GET ####################
###############################################
*/

/* retorna altura e largura do bitmap criado */
int    xg_height();
int    xg_width();

/* retorna a cor corrente do pincel */
XColor xg_color();

/* retorna a cor do pixel dessa posicao do bitmap */
XColor xg_pixel(int x, int y);

/* retorna uma cor dado um char. 
   os char default da paleta são rgbmcybk
   outros podem ser definidos ou redefinidor com xs_palette
*/
XColor xg_palette(char c);
#endif /* IMAGE_H XDDDX */
