#include "Map.h"

Map::Map(int l_w, int l_h) : level_w(l_w), level_h(l_h), blocked(level_w, vector<bool>(level_h, false)){
  //printf("MAP INITIALIZED TO %d by %d\n", level_w, level_h);
}

vector<coordinate_t> Map::getPath(coordinate_t start, coordinate_t dest){
  //implement A*
  //isValid(start);
  printf("GETTING PATH\n");
  //ensure validity
  if (!isValid(start)){
    printf("invalid start for getPath\n");
    vector<coordinate_t> result;
    result.push_back(start);
    return result;
  }

  if (!isValid(dest)){
    printf("invalid destination for getPath\n");
    vector<coordinate_t> result(1, start);
    return result;
  }

  if (isBlocked(start)){
    printf("start is blocked for getPath\n");
    vector<coordinate_t> result(1, start);
    return result;
  }

  if (isBlocked(dest)){
    printf("destination is blocked for getPath\n");
    vector<coordinate_t> result(1, start);
    return result;
  }

  if (start == dest){
    printf("already at destination for getPath\n");

    vector<coordinate_t> result(1, start);
    return result;
  } 

  //initialize data for algorithm
  int i;
  int j;
  vector<vector<bool>> closed(level_w, vector<bool>(level_h, false));
  set<cost_t> open;
  struct path_node path[level_w][level_h];
  for(i = 0; i < level_w; i++){
    for(j = 0; j < level_h; j++){
      path[i][j].g = INT_MAX;
      path[i][j].h = INT_MAX;
      path[i][j].f = INT_MAX;
      path[i][j].parent.first = -1;
      path[i][j].parent.second = -1;
    }
  }


  //inititialize starting node
  i = start.first;
  j = start.second;
  path[i][j].g = 0;
  path[i][j].g = 0;
  path[i][j].g = 0;
  path[i][j].parent.first = i;
  path[i][j].parent.second = j; //signals end of path

  open.insert(make_pair(0, make_pair(i, j)));

  while(!open.empty()){
    //get next space
    cost_t c = *open.begin();
    i = c.second.first;
    j = c.second.second;
    //remove from open, add to closed
    open.erase(open.begin());
    closed[i][j] = true;

    //printf("SEARCHING FROM %d, %d\n", i, j);

    //check all adjacent nodes

    int g_next, h_next, f_next;
    coordinate_t next;
    
    //upward
    next = make_pair(i, j-1);
    
    if (isValid(next)){
      //check end condition
      if (next == dest){
        path[i][j-1].parent = make_pair(i, j); 

	vector<coordinate_t> result;
        coordinate_t temp = dest;
        while(!(path[temp.first][temp.second].parent == temp)){
          result.push_back(temp);
          temp = path[temp.first][temp.second].parent;
        }
        //printf("Found correct path while searching upward\n");

	return result;
      }

      //check if closed/blocked
      if (closed[i][j-1] == false && !isBlocked(next)){
        //calculate cost
	g_next = path[i][j].g + 1; //all terrain costs the same, so it's a flat bonus
	h_next = abs(next.first - dest.first) + abs(next.second - dest.second); //no diagonals, so this estimate of distance works
	f_next = g_next + h_next;

	//check if this path is an improvement
	if (f_next < path[i][j-1].f){
	  //add to open
	  open.insert(make_pair(f_next, next));

          //printf("added %d,%d to open with cost %d\n", next.first, next.second, f_next);

	  //update path_node
          path[i][j-1].g = g_next;
          path[i][j-1].h = h_next;
	  path[i][j-1].f = f_next;
	  path[i][j-1].parent = make_pair(i, j);
	}
      }
    }

    //downward
    next = make_pair(i, j+1);
    
    if (isValid(next)){
      //check end condition
      if (next == dest){
        path[i][j+1].parent = make_pair(i, j); 

	vector<coordinate_t> result;
        coordinate_t temp = dest;
        while(!(path[temp.first][temp.second].parent == temp)){
          result.push_back(temp);
          temp = path[temp.first][temp.second].parent;
        }
        //printf("Found correct path while searching downward\n");

	return result;
      }
      //check if closed/blocked
      if (closed[i][j+1] == false && !isBlocked(next)){
        //calculate cost
	g_next = path[i][j].g + 1; //all terrain costs the same, so it's a flat bonus
	h_next = abs(next.first - dest.first) + abs(next.second - dest.second); //no diagonals, so this estimate of distance works
	f_next = g_next + h_next;

	//check if this path is an improvement
	if (f_next < path[i][j+1].f){
	  //add to open
	  open.insert(make_pair(f_next, next));

	  //printf("added %d,%d to open with cost %d\n", next.first, next.second, f_next);

	  //update path_node
          path[i][j+1].g = g_next;
          path[i][j+1].h = h_next;
	  path[i][j+1].f = f_next;
	  path[i][j+1].parent = make_pair(i, j);
	}
      }
    }

    //leftward
    next = make_pair(i-1, j);
    
    if (isValid(next)){
      //check end condition
      if (next == dest){
        path[i-1][j].parent = make_pair(i, j); 

	vector<coordinate_t> result;
        coordinate_t temp = dest;
        while(!(path[temp.first][temp.second].parent == temp)){
          result.push_back(temp);
          temp = path[temp.first][temp.second].parent;
        }
	//printf("Found correct path while searching leftward\n");

	return result;
      }    
      //check if closed/blocked
      if (closed[i-1][j] == false && !isBlocked(next)){
        //calculate cost
	g_next = path[i][j].g + 1; //all terrain costs the same, so it's a flat bonus
	h_next = abs(next.first - dest.first) + abs(next.second - dest.second); //no diagonals, so this estimate of distance works
	f_next = g_next + h_next;

	//check if this path is an improvement
	if (f_next < path[i-1][j].f){
	  //add to open
	  open.insert(make_pair(f_next, next));

	  //printf("added %d,%d to open with cost %d\n", next.first, next.second, f_next);

	  //update path_node
          path[i-1][j].g = g_next;
          path[i-1][j].h = h_next;
	  path[i-1][j].f = f_next;
	  path[i-1][j].parent = make_pair(i, j);
	}
      }
    }

    //rightward
    next = make_pair(i+1, j);
    
    if (isValid(next)){
      //check end condition
      if (next == dest){
        path[i+1][j].parent = make_pair(i, j); 
      
      	vector<coordinate_t> result;
        coordinate_t temp = dest;
        while(!(path[temp.first][temp.second].parent == temp)){
          result.push_back(temp);
	  printf("pushed back %d, %d\n", temp.first, temp.second);
          temp = path[temp.first][temp.second].parent;
        }
	//printf("Found correct path while searching rightward\n");

	return result;
      } 
      //check if closed/blocked
      if (closed[i+1][j] == false && !isBlocked(next)){
        //calculate cost
	g_next = path[i][j].g + 1; //all terrain costs the same, so it's a flat bonus
	h_next = abs(next.first - dest.first) + abs(next.second - dest.second); //no diagonals, so this estimate of distance works
	f_next = g_next + h_next;

	//check if this path is an improvement
	if (f_next < path[i+1][j].f){
	  //add to open
	  open.insert(make_pair(f_next, next));

	  //printf("added %d,%d to open with cost %d\n", next.first, next.second, f_next);

	  //update path_node
          path[i+1][j].g = g_next;
          path[i+1][j].h = h_next;
	  path[i+1][j].f = f_next;
	  path[i+1][j].parent = make_pair(i, j);
	}
      }   
    }
  }

  //no path found!
  printf("No path found for for getPath\n");
  vector<coordinate_t> result(1, start);
  return result;
}
    
void Map::block(coordinate_t c, bool b){
  blocked[c.first][c.second] = b;
  //printf("blocked %d, %d\n", c.first, c.second);
}

bool Map::isBlocked(coordinate_t c){
  return blocked[c.first][c.second];
}

bool Map::isValid(coordinate_t c){
  if (c.first < 0 || c.first >= level_w){
    return false;
  }
  if (c.second < 0 || c.first >= level_h){
    return false;
  }
  return true;
}
