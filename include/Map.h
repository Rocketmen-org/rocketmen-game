//class representing game map

#ifndef Map_h
#define Map_h

#include "game.h"

#define LEVEL_W 12
#define LEVEL_H 12

typedef pair<int, coordinate_t> cost_t;

struct path_node{
   int g;
   int h;
   int f ;
   coordinate_t parent;
};

class Map{

  public:
    Map(int l_w, int l_h);
    vector<coordinate_t> getPath(coordinate_t start, coordinate_t dest);
    void block(coordinate_t c, bool b);
    bool isBlocked(coordinate_t c);
    bool isValid(coordinate_t c);

  private:

    int level_w;
    int level_h;
    vector<vector<bool>> blocked;

};

#endif
