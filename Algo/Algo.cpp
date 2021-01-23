#include "Algo.h"
std::vector<Grid::coord> Algo::offset{
            //Up, down, left, right
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0},
            //Diagonals
            {1, 1},
            {-1, -1},
            {1, -1},
            {-1, 1}
};
Grid Algo::bfs(const Grid &original, Grid::coord end, Grid::coord start){
    Grid _grid = original;
    if(!_grid.checkBoundary(start) || !_grid.checkBoundary(end)){
        std::cerr << "Out Of Bounds" << std::endl;
    }
    std::queue<Grid::coord>q;
    q.push(start);
    while(!q.empty()){
        auto top = q.front();
        q.pop();
        _grid.set_coordinates_to_value({top.x, top.y}, Grid::status::VISITED);
        if(top == end){
            _grid.set_coordinates_to_value({top.x, top.y},  Grid::status::GOAL);
            return _grid;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(_grid.checkBoundary({x, y})){
                 _grid.set_coordinates_to_value({x, y},  Grid::status::IN_QUEUE);
                q.push({x, y});
            }
        }
    }
    _grid.set_coordinates_to_value({end.x, end.y},  Grid::status::NOT_REACHEABLE);
    return _grid;
}

Grid Algo::dfs(const Grid &original, Grid::coord end, Grid::coord start){
    Grid _grid = original;
    if(!_grid.checkBoundary(start) || !_grid.checkBoundary(end)){
        std::cerr << "Out Of Bounds" << std::endl;
    }
    std::stack<Grid::coord>s;
    s.push(start);
    while(!s.empty()){
        auto top = s.top();
        s.pop();
        _grid.set_coordinates_to_value({top.x, top.y}, Grid::status::VISITED);
        if(top == end){
            _grid.set_coordinates_to_value({top.x, top.y}, Grid::status::GOAL);
            return _grid;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(_grid.checkBoundary({x, y})){
                 _grid.set_coordinates_to_value({x, y}, Grid::status::IN_QUEUE);
                s.push({x, y});
            }
        }
    }
    _grid.set_coordinates_to_value({end.x, end.y}, Grid::status::NOT_REACHEABLE);
    return _grid;
}