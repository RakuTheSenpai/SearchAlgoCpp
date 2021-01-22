#include "grid.h"
bool Grid::checkBoundary(coord current){
    if(current.x < 0 || current.x >= _grid[0].size() || current.y < 0 || current.y >= _grid.size()){
        return false;
    }
    return _grid[current.x][current.y] == 0;
}
void Grid::bfs(coord end, coord start){
    if(!checkBoundary(start) || !checkBoundary(end)){
        std::cerr << "Out Of Bounds" << std::endl;
    }
    std::queue<coord>q;
    q.push(start);
    while(!q.empty()){
        auto top = q.front();
        q.pop();
        _grid[top.x][top.y] = 4;
        if(top == end){
            _grid[top.x][top.y] = 5;
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(checkBoundary({x, y})){
                _grid[x][y] = 3;
                q.push({x, y});
            }
        }
    }
    _grid[end.x][end.y] = 6;
    return;
}

void Grid::dfs(coord end, coord start){
    if(!checkBoundary(start) || !checkBoundary(end)){
        std::cerr << "Out Of Bounds" << std::endl;
    }
    std::stack<coord>s;
    s.push(start);
    while(!s.empty()){
        auto top = s.top();
        s.pop();
        _grid[top.x][top.y] = 4;
        if(top == end){
            _grid[top.x][top.y] = 5;
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(checkBoundary({x, y})){
                _grid[x][y] = 3;
                s.push({x, y});
            }
        }
    }
    _grid[end.x][end.y] = 6;
    return;
}

void Grid::set_coordinates_to_value(coord coordinates, unsigned value){
    int x = coordinates.x, y = coordinates.y;
    _grid[x][y] = value;
}