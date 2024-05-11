#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/

#include <stdarg.h>

// inicia o canvas de width x height, e define o nome do arquivo png a ser gerado
void create(unsigned int width, unsigned int height, const char * filename);

// altura do canvas
int height(void);

// largura do canvas
int width(void);

// retorna o nome do arquivo
const char * getFilename(void);

// retorna o bitmap
uchar  * getBitmap(void);


// finaliza o canvas
void destroy(void);

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
    double cx;
    double cy;
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
// define a rotação da camada de transformação atual no sentido horario
void rotate(double angle); 

// define o centro de rotação da transformação atual
void center(double x, double y);

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void   __plot(double x, double y,  Color color);
V2d    __transform(double x, double y);
double __get_transform_scale();

#endif /*XDDDX*/
