#define XPAINT_FULL
#include "xpaint.h"
#include <vector>
#include <iostream>
#include <list>
#include <sstream>
using namespace std;

struct Item{
    bool wall;
    bool visited;
    int distance;
    Item(bool _wall = false, bool _visited = false, int _distance = -1):
        wall(_wall), visited(_visited), distance(_distance){
    }
};

struct LC{
    int l, c;
    LC(int _l = 0, int _c = 0):l(_l), c(_c){}
    bool operator==(const LC& other){return (l == other.l) && (c == other.c);}
    bool operator!=(const LC& other){return !(*this==other);}
    vector<LC> get_neibs(){
        vector<LC> neibs = {LC(l, c - 1), LC(l - 1, c), LC(l, c + 1), LC(l + 1, c)};
        return neibs;
    }
};

struct Matriz{
    int nl, nc;
    vector<vector<Item>> data;
    Matriz(int _nl, int _nc):
        nl(_nl), nc(_nc), data(_nl, vector<Item>(_nc)){
    }
    Item & get(LC pos){
        return data[pos.l][pos.c];
    }
    string toString(){
        stringstream ss;
        for(int l = 0; l < nl; l++){
            for(int c = 0; c < nc; c++)
                ss << (data[l][c].wall ? "#":" ");
            ss << "\n";
        }
        return ss.str();
    }
};

char WALL = 'k', EMPTY = 'w', VISITED = 'm', PATH = 'c';

void xgrid_matrix(Matriz mat, list<LC> path){
    x_clear();
    for(int l = 0; l < mat.nl; l++){
        for(int c = 0; c < mat.nc; c++){
            Item& item = mat.data[l][c];
            x_set_pcolor(item.wall ? WALL : EMPTY);
            x_grid_square(l, c);
            if(item.visited){
                x_set_pcolor(VISITED);
                x_grid_circle(l, c);
            }
            if(item.distance != -1){
                x_set_pcolor('k');
                x_grid_number(l, c, item.distance);
            }
        }
    }
    int i = 0;
    for(auto pos : path){
        x_set_color(X_COLOR_VIOLET);
        x_grid_number(pos.l, pos.c, i++);
    }
}

list<LC> find_path(Matriz mat, LC begin, LC end){
    list<LC> flood;
    Item & p = mat.get(begin);
    p.visited = true;
    p.distance = 0;
    flood.push_back(begin);
    while(!flood.empty()){
        LC top = flood.front();
        if(top == end)
            break;
        flood.pop_front();
        for(auto neib_pos : top.get_neibs()){
            Item &neib = mat.get(neib_pos);
            if(!neib.wall && !neib.visited){
                neib.visited = true;
                neib.distance = mat.get(top).distance + 1;
                flood.push_back(neib_pos);
            }
        }
    }

    list<LC> path;
    path.push_front(end);
    while(path.front() != begin){
        for(auto neib_pos : path.front().get_neibs()){
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
    cin >> nl >> nc;
    Matriz mat(nl, nc);
    int l, c;
    LC begin(0, 0), end(0, 0);
    for(l = 0; l < nl; l++){
        for(c = 0; c < nc; c++){
            char value;
            cin >> value;
            mat.data[l][c].wall = (value == '#');
            mat.data[l][c].visited = false;
            mat.data[l][c].distance = -1;
            if(value == 'O') {begin.l = l; begin.c = c;}
            if(value == 'X') {end.l = l; end.c = c;}
        }
    }
    auto path = find_path(mat, begin, end);
    char resp[nl][nc];
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            resp[l][c] = mat.data[l][c].wall ? '#':' ';
        }
    }
    int i = 0;
    for(auto pos : path)
        resp[pos.l][pos.c] = 'O';//(i++ % 10) + '0';
    
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            cout << resp[l][c];
        }
        cout << '\n';
    }
    /*
    x_open(1002, 402, "floodfill");
    x_set_viewer("eog");
    x_grid_init(1002/nc, 1);
    xgrid_matrix(mat, path);
    x_save();
    x_close();
    */
    return 0;
}