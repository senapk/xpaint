#ifndef XIMAGE_H //XDDDX
#define XIMAGE_H //XDDDX

typedef  unsigned char uchar;

typedef struct{
    uchar r;
    uchar g;
    uchar b;
} XColor;

//cria e retorna uma cor passando rgb
XColor make_color(uchar r, uchar g, uchar b);

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

//ABRINDO E FECHANDO
//inicia um bitmap com essas dimensões
void x_init(int width, int height);
//finaliza o bitmap liberando os recursos
void x_close();
//para salvar um png no arquivo
void x_save(const char* filename);

//FUNCOES BASICAS
//a funcao plot pinta o pixel usando a cor
void x_plot(int x, int y);
//a funcao write escreve um texto text, na posição px, py.
//retorna o x da posição após o último caractere escrito.
int x_write(int x, int y, const char * format, ...);
//limpa a tela inteira com a mesma cor
void x_clear(XColor color);

//FUNCOES SET
//muda a cor do pincel para todas as funcoes de desenho
void xs_color(XColor color);
//define uma cor na palheta de caracteres
void xs_pallete(char c, XColor color);
//mudar o tamanho da fonte em pixels
void xs_font_size(int size);
//muda a font passando o path da nova fonte
void xs_font(const char* filename);

//FUNCOES GET
int    xg_height();
int    xg_width();
//retorna a cor corrente do pincel
XColor xg_color();
//retorna a cor do pixel dessa posicao
XColor xg_pixel(int x, int y);
//retorna uma cor dado um char. Opcoes de char rgbmcybk
XColor xg_pallete(char c);
#endif // IMAGE_H XDDDX
