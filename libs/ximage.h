#ifndef XIMAGE_H /* XDDDX */
#define XIMAGE_H /* XDDDX */

#ifdef __cplusplus
extern "C" {
#endif

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
extern XColor WHITE;
extern XColor BLACK;

/* variantes 
extern XColor RED_B;
extern XColor GREEN_B;
extern XColor BLUE_B;
extern XColor YELLOW_B;
extern XColor CYAN_B;
extern XColor MAGENTA_B;
extern XColor ORANGE_B;
extern XColor WHITE_B;
extern XColor BLACK_B;
*/

/*
###############################################
######## ABRINDO, FECHANDO, SALVANDO ##########
###############################################
*/

/* abre um bitmap com essas dimensões */
void x_open(unsigned int width, unsigned int height);

/* finaliza o bitmap liberando os recursos */
void x_close();

/* para salvar um png no arquivo
   não inclua a extensão .png no nome do arquivo
*/
void x_save(const char *filename);

/*  Define um diretório onde serão salvos todas imagens invocadas no comando x_step.

    Se directory for "", ele não salvará os estados.
    Utilize o path completo incluindo a /
    Exemplo xs_log("imgs/")

    00000.png 00001.png 00002.png 00003.png
*/
void xs_log(const char *directory);

/*
    Redefine o valor de salto do x_step
*/
void xs_jump(int value);

/*  salva o arquivo, mas permite ao usuário controlar
    os estados salvos intermediários através da interação com o terminal.
*/
int x_step(const char *filename);

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

#ifdef __cplusplus
}
#endif

#endif /* IMAGE_H XDDDX */


