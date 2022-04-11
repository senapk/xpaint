#define XPAINT
#include "../xpaint.h"
#include <vector>
#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
using namespace std;

struct Item{
    bool wall;
    bool visited;
    int distance;
    Item(bool _wall = false, bool _visited = false, int _distance = -1):
        wall(_wall), visited(_visited), distance(_distance){
    }
};

struct Pos{
    int l, c;
};
bool operator==(Pos one, Pos two){ return (one.l == two.l) && (one.c == two.c);}
bool operator!=(Pos one, Pos two){ return !(one == two);}

#define get_neibs(p)  {{p.l + 0, p.c - 1}, {p.l - 1, p.c + 0}, {p.l + 0, p.c + 1}, {p.l + 1, p.c + 0}}

template <class T>
struct matriz{
    int nl, nc;
    vector<T> data;
    matriz(int _nl, int _nc, T def): nl(_nl), nc(_nc), data(_nl * _nc, def){}
    T & get(Pos p){return data[p.l * nc + p.c]; }
    bool inside(Pos p) {return (p.l >=0) && (p.l < nl) && (p.c >= 0) && (p.c < nc);}
};

void print(Item mat[], int nl, int nc){
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++)
            cout << (mat[l * nc + c].wall ? "#":" ");
        cout << "\n";
    }
}

char WALL = 'k', EMPTY = 'w', VISITED = 'y', PATH = 'c';

void xgrid_matrix(matriz<Item> mat, list<Pos> path){
    x_clear();
    for(int l = 0; l < mat.nl; l++){
        for(int c = 0; c < mat.nc; c++){
            Item& item = mat.get(Pos{l, c});
            x_set_color("%c", item.wall ? WALL : EMPTY);
            x_grid_square(l, c);
            if(item.distance != -1){
                x_set_color("k");
                x_grid_number(l, c, item.distance);
            }
        }
    }
    int i = 0;
    for(auto p : path){
        x_set_color(VIOLET);
        x_grid_circle(p.l, p.c);
        x_set_color("k");
        x_grid_number(p.l, p.c, i++);
    }
}

list<Pos> find_path(matriz<Item> mat, Pos begin, Pos end){
    list<Pos> flood;
    Item & p = mat.get(begin);
    p.visited = true;
    p.distance = 0;
    flood.push_back(begin);
    while(!flood.empty()){
        Pos top = flood.front();
        if(top == end)
            break;
        flood.pop_front();
        vector<Pos> neibs = get_neibs(top);
        for(auto neib_pos : neibs){
            if(!mat.inside(neib_pos))
                continue;
            Item &neib = mat.get(neib_pos);
            if(!neib.wall && !neib.visited){
                neib.visited = true;
                neib.distance = mat.get(top).distance + 1;
                flood.push_back(neib_pos);
            }
        }
    }

    list<Pos> path;
    path.push_front(end);
    while(path.front() != begin){
        vector<Pos> neibs = get_neibs(path.front());
        for(auto neib_pos : neibs){
            if(mat.get(neib_pos).distance == mat.get(path.front()).distance - 1){
                path.push_front(neib_pos);
                break;
            }
        }
    }
    return path;
}



int main(){
    int nl, nc;
    ifstream mapa("floodfill_map.txt");
    mapa >> nl >> nc;
    matriz<Item> mat(nl, nc, Item(false, false, -1));
    int l, c;
    Pos begin{0, 0}, end{0, 0};
    for(l = 0; l < nl; l++){
        for(c = 0; c < nc; c++){
            char value;
            mapa >> value;
            Pos p{l, c};
            mat.get(p).wall = (value == '#');
            mat.get(p).visited = false;
            mat.get(p).distance = -1;
            if(value == 'O') {begin.l = l; begin.c = c;}
            if(value == 'X') {end.l = l; end.c = c;}
        }
    }
    auto path = find_path(mat, begin, end);
/*     char resp[nl][nc];
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            resp[l][c] = mat.get(Pos{l, c}).wall ? '#':' ';
        }
    } */
//    int i = 0;
/*     for(auto p : path)
        resp[p.l][p.c] = 'o';//(i++ % 10) + '0';
    
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            if(resp[l][c] == '#')
                cout << "█";
            else
                cout << resp[l][c];
        }
        cout << '\n';
    } */
    
    x_open(1002, 402, "figura_floodfill");
    //x_set_viewer("gthumb");
    x_grid_init(1002/nc, 1);
    xgrid_matrix(mat, path);
    x_save();
    x_close();
    
    return 0;
}