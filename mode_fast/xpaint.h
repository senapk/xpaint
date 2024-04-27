#ifndef XPAINT_H
#define XPAINT_H
#ifdef __cplusplus
extern "C" {
#endif
/*
You must use the following define in your code before #include the library
#define XPAINT
*/


/*
Autor:
    nome: David Sena Oliveira
    email: sena.ufc@gmail.com

Principais fontes:
    png: https://lodev.org/lodepng
    funções de desenho e matemáticas estão comentadas nas funções

Licença: GPLv3

Versão: 1.1

*/

/* Exemplo de uso */

#if 0
#define XPAINT
#include "xpaint.h"
int main(){
    int largura = 600, altura = 500;
    open(largura, altura, "figura_base"); 
    text(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    background("white");
    stroke("black");
    fill("red")
    circle(largura/2, altura/2, 200);
    save();
    close();
    return 0;
}
#endif
#include <stdarg.h>


// ---------------------------- CORES -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// apelido para um char sem sinal
typedef unsigned char uchar;

// struct que representa uma cor RGBA
typedef struct{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
} Color;

// cria e retorna uma struct Color passando rgba
// rgba(255, 0, 0, 0); // vermelho
Color rgba(uchar r, uchar g, uchar b, uchar a);


// Cria ou obtém uma cor da paleta, possui vários modos
// 1: uso de hexadecimal como : "#00ffbb"
// 2: uso de rgba entre virgulas "144,123,12,255"
// 3. tons de cinza entre 0 e 255: "100", "0", "150"
// 4: uso de palavras chave ou letras
//     "black" ou "k"
//     "white" ou "w"
//     "red", "blue", "yellow", "pink", "cyan", ...
// 5: pode ser construído com a sintexa do printf
//     ("%d, %d, %d", 10, 20 , 30)
Color color(const char * format, ...);

// define uma entrada na paleta de cores
// entry: chave para a cor, que pode ser uma letra ou palavra
// color: cor a ser registrada
void setPallete(const char * entry, Color color);

// Printa todas as cores nomeadas atualmente cadastradas
void colorShowAll();

// Mostra a cor no terminal
void colorShow(Color color);

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// inicializa as cores da paleta e da base
void __init_colors(void);



#include <stdarg.h>

// inicia o canvas de width x height, e define o nome do arquivo png a ser gerado
void open(unsigned int width, unsigned int height, const char * filename);

// altura do canvas
int height(void);

// largura do canvas
int width(void);

// retorna o nome do arquivo
const char * getFilename(void);

// retorna o bitmap
uchar  * getBitmap(void);


// finaliza o canvas
void close(void);

// muda o nome do arquivo png a ser gerado
void setFilename(const char * filename);

// retorna a cor do pixel dessa posicao do bitmap
Color getPixel(int x, int y);

// limpa a tela inteira com a mesma cor
void background(const char * format, ...);

// gera o arquivo png com o valor atual do canvas
void save(void);

// habilita controle interativo dos loops no canvas
void setLock();


// define a pasta onde os arquivos serão salvos com um sufixo numérico no final
// se o nome do arquivo for img, chamadas sequenciais dessa função
// salvarão os seguintes arquivos
// img_00000.png img_00001.png img_00002.png img_00003.png
void setLog(const char * folder);

// chama a função ffmpeg para gerar um vídeo com os arquivos salvos
// na pasta definida por setLog
void makeVideo(int framerate, const char * mp4_filename);

typedef struct {
    double dx;
    double dy;
    double s;
    double angle;
} Transform;

// Cria um vetor bidimensional
typedef struct{
    double x;
    double y;
} V2d;

// cria um camada de transformação
void push();
// desfaz a última camada de transformação
void pop();
// define a translação da camada de transformação atual
void translate(double dx, double dy);
// define a escala da camada de transformação atual
void scale(double s);
// define a rotação da camada de transformação atual
void rotate(double angle); 

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void   __plot(int x, int y,  Color color);
V2d    __transform(double x, double y);
double __get_transform_scale();

#include <stdarg.h>


// ---------------------------- DESENHO -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// muda a espessura do traço
void strokeWeight(int thickness);

// plota um pixel utilizando a função stroke
void point(double x, double y);

// muda a cor do pincel para pontos, linhas e bordas
// pode ser uma cor hexadecimal, rgb, tons de cinza ou uma palavra chave
// internamente, chama a função color
void stroke(const char * format, ...);

// muda a cor do pincel para preenchimento
// pode ser uma cor hexadecimal, rgb, tons de cinza ou uma palavra chave
// internamente, chama a função color
void fill(const char * format, ...);

// define a cor de stroke passando o objeto Color
void setStroke(Color value);

// devolve a cor atual do fill
void setFill(Color value);

// desabilita pontos, linhas e bordas
void noStroke();

// desabilita o preenchimento
void noFill();

// devolve a cor atual do stroke
Color getStroke(void);

// devolve a cor atual do fill
Color getFill(void);

// desenha uma forma utilizando uma string e o mapa de cores default
int  ascArt(int x, int y, int zoom, const char * picture);

// desenha uma linha entre dois pontos
void line(double x0, double y0, double x1, double y1);

// desenha uma elipse dado o ponto de centro, largura e altura
void ellipse(double x0, double y0, double width, double height);

// desenha um arco dado o ponto de centro, diametro externo, diametro interno
// o angulo de inicio e o comprimento do arco em graus
// ambos os valores de ângulo podem ser negativos
void arc(double centerx, double centery, int out_diameter, int in_diameter, int degrees_begin, int degrees_lenght);

// desenha um círculo dado o ponto de centro e o diâmetro
void circle(int centerx, int centery, int diameter);

// desenha um retângulo dado o ponto de canto superior esquerdo, largura e altura
void rect(double x, double y, double witdh, double height);

// desenha um quadrado dado o ponto de canto superior esquerdo e o tamanho
void square(double x, double y, double size);

// desenha uma curva de bezier dado os pontos
// inicial A, final B e os pontos de controle C e D
void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd);

// desenha um triângulo dado os pontos
void triangle(double x0, double y0, double x1, double y1, double x2, double y2);


#include <stdarg.h>

// ---------------------------- TEXTO -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// muda o tamanho da font
// OBS: a font só muda em múltiplos de 10, ex: 10, 20, 30, ...
void textSize(int size);

// escreve utilizando o formato printf
// retorna a posicao final em x
// pode utilizar \n para quebra de linha
int text(int x, int y, const char * format, ...);

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

//inicializa o módulo de escrita
void __x_init_font();



/* Faz o SWAP entre dois tipos */
#define X_SWAP(x, y, T) do { T X_SWAP = x; x = y; y = X_SWAP; } while (0)

// ---------------------------- ALGEBRA DE VETORES ----------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// retorna a distancia entre dois pontos
double dist(double ax, double ay, double bx, double by);

// cria e retorna um vetor
V2d v2d(double x, double y);

// retorna o tamanho de um vetor da origem
double v2d_length(double x, double y);

// retorna a + b
V2d v2d_sum(V2d a, V2d b);

// retorna a - b
V2d v2d_sub(V2d a, V2d b);

// retorna (a.x * value, a.y * value)
V2d v2d_dot(V2d a, double value);

// retorna o vetor normalizado
V2d v2d_normalize(V2d v);

// retorna o vetor orthogonal
V2d v2d_ortho(V2d v);

// ---------------------------- FUNÇÕES MATEMÁTICAS ---------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// raiz quadrada
double xsqrt(const double m);

// função potência
double xpow( double x, double y );

// função piso
int    xfloor(double x);

// função de arredondamento
int    xround(double x);

// o módulo de um número, mas com o divisor sendo um double
double xfmod(double a, double b);

// função teto
int    xceil(double n);

// calcula o seno de um angulo em graus
double xsin(double d);

// calcula o cosseno de um angulo em graus
double xcos(double d);

// calcula o arco cosseno de x em graus
double xacos(double x);

// calcula o arco seno de x em graus
double xfabs(double f);

// gera um valor inteiro aleatório entre 0 e max
// não incluindo o max
int xrand(int max);

// xrand intervalo
int xrandi(int min, int max);




// ---------------------------- GRID ------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <stdarg.h>

// inicia o grid
// side é o tamanho da célula
// sep é o espaço em preto entre as células
void gridInit(int side, int sep);

// plota um quadrado na célula
void gridSquare(int x, int y);

// plota um círculo na célula
void gridCircle(int x, int y);

V2d gridPos(int x, int y);

// escreve o texto na posição da grid (x, y)
// texto pode ser ajustado usando dx e dy
void gridText(int x, int y, int dx, int dy, const char *format, ...);


// ---------------------------- VETORES ---------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// inicia o vetor
// size é o tamanho do vetor
// max é o valor máximo do vetor
void barInit(int size, int max);

// plota um valor no vetor
// i é a posição do valor
// value é o valor a ser plotado
void barDrawOne(int i, int value);

// plota todos os valores do vetor
// colors é um vetor de cores para marcar elementos únicos ou NULL
// indices é um vetor com os índices únicos a serem marcados com as cores
void barDrawColors(int * vet, int size, const char * colors, int * indices);


#define barDrawAll(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    barDrawColors(vet, size, colors, __indices);\
} while(0);


// ---------------------------- CANETA ---------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void   penSetAngle(double degrees);
void   penSetThick(int thick);
void   penSetPos(double x, double y);
double penGetAngle();
int    penGetThick();
double penGetX();
double penGetY();
void   penUp(void);
void   penDown(void);
void   penWalk(double distance);
void   penRotate(int degrees);
void   penGoto(double x, double y);




#ifdef __cplusplus
}
#endif
#endif /* XPAINT_H */
