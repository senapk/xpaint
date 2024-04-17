# Escrevendo, desenhando e pintando em PNGs usando C

O objetivo desse projeto é criar uma biblioteca header only para programar em C que seja capaz de criar, escrever e desenhar em pngs sem a necessidade de bibliotecas externas ou dependências.

<!--TOC_BEGIN-->
- [Instalação Local](#instalação-local)
- [Instalação Global](#instalação-global)
    - [Linux](#linux)
    - [Windows](#windows)
- [Criando animações](#criando-animações)
- [Funções](#funções)
- [Compilando e rodando](#compilando-e-rodando)
- [Guia de Funções](#guia-de-funções)
    - [Abrindo e fechando](#abrindo-e-fechando)
    - [Limpando, plotando e salvando](#limpando-plotando-e-salvando)
    - [Abrindo automaticamento a imagem gerada](#abrindo-automaticamento-a-imagem-gerada)
    - [Controle interativo](#controle-interativo)
    - [Cores](#cores)
    - [Desenhando](#desenhando)
    - [Escrevendo texto](#escrevendo-texto)
    - [Vetores bidimensionais](#vetores-bidimensionais)
    - [Funções Matemáticas](#funções-matemáticas)
    - [Módulo de Matrizes](#módulo-de-matrizes)
    - [Módulo de Vetores](#módulo-de-vetores)
    - [Módulo Turtle de Desenho](#módulo-turtle-de-desenho)
<!--TOC_END-->

---
## Instalação Local

Para utilizar, basta você baixar a biblioteca para o diretório onde está o seu código fonte, compilar e executar. Se estiver no linux, pode usar os seguintes comandos para baixar a biblioteca e rodar um exemplo.


```
curl https://raw.githubusercontent.com/senapk/xpaint/master/xpaint.h -o xpaint.h
curl https://raw.githubusercontent.com/senapk/xpaint/master/exemplos/exemplo_base.c -o exemplo_base.c
gcc -Wall exemplo_base.c -o exemplo_base
./exemplo_base
```

Ao executar, deve ser criado o arquivo exemplo_base.png no seu diretório atual. 

Se estiver no windows, basta abrir os links e clicar em salvar como para salvar o arquivo.

- https://raw.githubusercontent.com/senapk/xpaint/master/xpaint.h


---
## Instalação Global

### Linux
```
sudo wget https://raw.githubusercontent.com/senapk/xpaint/master/xpaint.h -O /usr/local/include/xpaint.h
```

### Windows
Baixe o arquivo (xpaint.h)[https://raw.githubusercontent.com/senapk/xpaint/master/xpaint.h] e coloque dentro da pasta include da instalação do Mingw.




---
## Funções

O código a seguir cria um bitmap, escreve um texto, pinta um círculo, salva no arquivo exemplo.png e sai. Você precisará apenas da biblioteca **xpaint.h** para o seu computador e criar o arquivo **exemplo_base.c** com o seguinte conteúdo.


```c
#define XPAINT   /*voce precisa desse define ANTES do include" */
#include "xpaint.h"

int main(){
    int largura = 600, altura = 500;
    /* cria um bitmap de 600x500 que irá salvar como figura_base.png*/
    x_open(largura, altura, "figura_base"); 
    /* escreve usando a font default na posicao x=50, y=30 */
    /* utilizando o mesmo formato do printf */
    x_write(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    /* muda a cor do pincel para vermelho */
    x_color_set(RED);
    /* desenha um circulo preenchido com centro no meio da tela e raio 200 */
    x_fill_circle(largura/2, altura/2, 200);
    /* salva no arquivo exemplo.png */
    x_save();
    /* libera os recursos alocados */
    x_close();
    return 0;
}
```

## Compilando e rodando

Se estiver fazendo manual, copie o arquivo xpaint.h para mesma pasta do seu código fonte e compile seu código manualmente.
```
# rodando pelo terminal
gcc -Wall exemplo.c -o exemplo
./exemplo
```

Ele deve gerar o arquivo figura_base.png que se parece com isso:

![](exemplos/figura_base.png)

Se você clonar esse repositório, entrar na pasta exemplos e der um make, ele vai compilar e re-gerar todas as figuras.

Esta é uma biblioteca header only, ou seja, não está dividida em .c e .h. Declarações e definições estão todas no .h. 

Se você der o include na biblioteca ele vai incluir as declarações apenas, ou seja, os cabeçalhos.
No módulo principal do seu programa, você deve dar o #define `XPAINT` para incluir também as definições.

```
#define XPAINT
#include <xpaint.h> //se instalar globalmente
//ou
#include "xpaint.h" //se instalar localmente
```


## Guia de Funções

### Abrindo e fechando
```c
//inicia a figura
void x_open(unsigned int width, unsigned int height, const char * filename);  
// libera os recursos
void x_close();      
```

### Limpando, plotando e salvando
```c
void x_clear(void);                          // limpa a tela
void x_plot(int x, int y);                   // pinta o pixel usando a cor padrão
void x_save(void);                           // salva a figura no arquivo filename.png

int           x_get_height(void);            // retorna altura
int           x_get_width(void);             // retorna largura
const char *  x_get_filename(void);          // retorna filename

void x_set_filename(const char * filename);  // muda o nome do arquivo
```

### Abrindo automaticamento a imagem gerada
```c
void x_set_viewer(const char * viewer);      // define qual programa vai abrir a imagem
```

### Utilizando cores

```c
/* Cores default e char da paleta de cores */
#define WHITE     (X_Color) {238, 232, 213, 255} // w
#define BLACK     (X_Color) {7  , 54 , 66 , 255} // k
#define GREEN     (X_Color) {133, 153, 0  , 255} // g
#define RED       (X_Color) {211, 1  , 2  , 255} // r
#define BLUE      (X_Color) {38 , 139, 210, 255} // b
#define YELLOW    (X_Color) {181, 137, 0  , 255} // y
#define CYAN      (X_Color) {42 , 161, 152, 255} // c
#define MAGENTA   (X_Color) {211, 54 , 130, 255} // m
#define ORANGE    (X_Color) {253, 106,   2, 255} // o
#define VIOLET    (X_Color) {108, 113, 196, 255} // v

/* muda a cor do pincel*/
void x_color_set(X_Color color);

/* muda a cor do pincel usando a paleta de cores*/
void x_color_load(char color);

/* return the current color for brush */
X_Color x_color_get(void);
```

### Controle interativo
```c
/* Enable interactive save and lock control */
void x_set_lock();

/*
    define folder to saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void x_set_log(const char * folder);

/* creates a .mp4 video using all .png stored in folder using ffmpeg */
void x_make_video(int framerate);

```

### Cores

![](exemplos/figura_cores.png)
```c
/* struct que representa uma cor RGBA */
typedef struct{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
} X_Color;


X_Color x_color_make(uchar r, uchar g, uchar b, uchar a);


/* define uma cor na palheta de caracteres */
void x_color_set_palette(char c, X_Color color);

/* retorna uma cor dado um char.
   os char default da paleta são rgbmcybk
   outros podem ser definidos ou redefinidor com x_color_set_palette
*/
X_Color x_color_get_palette(char c);
```

### Desenhando

![](exemplos/figura_draw.png)

```c
/* Desenha as seguintes formas sem preenchimento */

/* desenha uma linha com espessura de 1 pixel entre os pontos (x0, y0) e (x1, y1) */
void x_draw_line(int x0, int y0, int x1, int y1);

/* desenha uma linha com espessura de thickness pixels entre os pontos (x0, y0) e (x1, y1) */
void x_fill_line(float x0, float y0, float x1, float y1, int thickness);

/* desenha um circulo com centro (centerx, centerx) e raio radius */
void x_draw_circle(int centerx, int centery, int radius);

/* desenha um circulo dado centro e raio */
void x_fill_circle(int centerx, int centery, int radius);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void x_draw_ellipse(int x0, int y0, int width, int height);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void x_fill_ellipse(int x0, int y0, int width, int height);

/* desenha uma curva de bezier entre os pontos (x0, y0) e (x2, y2) */
/* a curvatura eh dada pelo ponto (x1, y1) */
void x_draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2);

/* desenha um arco dado o ponto de centro, raio, espessura */
/* o angulo de inicio e o comprimento do arco em graus */
/* ambos os valores de ângulo podem ser negativos */
void x_fill_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_lenght);

/* desenha um triangulo dados os 3 vertices */
void x_fill_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);

/* desenha um retangulo dados os cantos superior esquerdo (x0, y0), largura e altura */
void x_fill_rect(int x0, int y0, int width, int height);

```

### Escrevendo texto
![](exemplos/figura_texto.png)

```c
// muda o tamanho da font
// OBS: a font só muda em múltiplos de 8, ex: 8, 16, 24, ...
void x_write_set_size(int size); 

// escreve utilizando o formato printf
int  x_write(int x, int y, const char * format, ...);
```
### Vetores bidimensionais

```c
/* Define um vetor bidimensional com x e y */
typedef struct{
    double x;
    double y;
} X_V2d;

/* cria e retorna um vetor */
X_V2d x_v2d_make(double x, double y);

/* retorna o tamanho de um vetor da origem */
double x_v2d_length(double x, double y);

/* retorna a distancia entre dois pontos */
double x_v2d_distance(double ax, double ay, double bx, double by);

/* retorna a + b */
X_V2d x_v2d_sum(X_V2d a, X_V2d b);

/* retorna a - b */
X_V2d x_v2d_sub(X_V2d a, X_V2d b);

/* retorna (a.x * value, a.y * value) */
X_V2d x_v2d_dot(X_V2d a, double value);

/* retorna o vetor normalizado */
X_V2d x_v2d_normalize(X_V2d v);

/* retorna o vetor orthogonal */
X_V2d x_v2d_ortho(X_V2d v);
```


### Funções Matemáticas
```c
/*
Essas funções foram adicionadas para que a biblioteca
xpaint não dependesse de incluir a biblioteca math.h
nos parametros de compilação com o -lm
*/

double x_math_sqrt(const double m);
double x_math_pow( double x, double y );
int    x_math_floor(double x);
double x_math_fmod(double a, double b);
int    x_math_ceil(double n);
/* degrees */
double x_math_sin(double d);
double x_math_cos(double d);
double x_math_acos(double x);
double x_math_fabs(double f);
/* Generates a int number in interval [min, max] */
int    x_math_rand(int min, int max);

```

### Módulo de Matrizes

[Código de matrizes](exemplos/exemplo_grid.c)

![](exemplos/figura_grid.png)

```c

/*
###############################################
############ FUNÇÕES DE GRID ##################
###############################################
*/

/*Init the grid*/
/*side is the size of the cell */
/*sep the space in black between cells */
void x_grid_init(int side, int sep);

/*plots a square in cell*/
void x_grid_square(int l, int c);

/*plots a circle in cell*/
void x_grid_circle(int l, int c);

/*writes a text until 5 char in cell*/
void x_grid_write(int l, int c, const char *format, ...);

```

### Módulo de Vetores

![](exemplos/figura_insertion.png)

```c
/**
 * @brief initialize the module to print bars for show sort
 * 
 * @param size the size of the array
 * @param max the max value of the array
 */
void x_bar_init(int size, int max);

/**
 * @brief print a single bar
 * 
 * @param i the index
 * @param value the value of the bar size
 */
void x_bar_one(int i, int value);

/**
 * @brief show the entire array
 * 
 * @param vet the vector with the values
 * @param size of the vector
 * @param colors the array of color to mark unique elements or NULL
 * @param indices the array with the unique indices to be marked with the colors
 */
void x_bar_all(int * vet, int size, const char * colors, int * indices);


/*
 * Save the array using vararg to pass multiple indexes 
*/
#define x_bar_save(vet, size, colors, ...)
```

### Módulo Turtle de Desenho

[Código do triângulo](exemplos/exemplo_triangulo.c)

![](exemplos/figura_triangulo.png)

[Código da árvore](exemplos/exemplo_arvore.c)

![](exemplos/figura_arvore.png)
```c
void   x_pen_set_angle(double degrees);
void   x_pen_set_thick(int thick);
void   x_pen_set_pos(double x, double y);
double x_pen_get_angle();
int    x_pen_get_thick();
double x_pen_get_x();
double x_pen_get_y();
void   x_pen_up(void);
void   x_pen_down(void); 
void   x_pen_walk(double distance);
void   x_pen_rotate(int degrees);
void   x_pen_goto(double x, double y);

```

## Criando animações

O exemplo_insertion.c mostra como criar animações. O nome do arquivo a ser gerado deve conter também o path onde os arquivos serão salvos.

Você pode usar a função `x_set_log(folder)` para definir a pasta onde salvar cada save gerado. 

Utilizando o ffmpeg, é possível juntar todos os pngs em uma animação através do comando:

```
ffmpeg -framerate 5 -pattern_type glob -i '*.png' -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p video.mp4
```

O framerate define a quantidade de imagens por segundo, se quiser que passe mais tempo numa imagem, diminua o framerate.

Será gerado o arquivo video.mp4 na pasta atual.
