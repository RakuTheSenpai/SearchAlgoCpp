#include "Algo.h"
std::vector<Grid::Coord> Algo::offset{
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
void Algo::bfs(Grid &_grid){
    std::queue<std::pair<Grid::Coord, std::vector<Grid::Coord>>>q;
    q.push({_grid.get_start(), {_grid.get_start()}});
    while(!q.empty()){
        auto tp = q.front();
        auto top = tp.first;
        q.pop();
        _grid.set_value(Grid::Coord{top.x, top.y}, Grid::Status::VISITED);
        if(top == _grid.get_goal()){
            for(auto ele:tp.second){
                _grid.set_value(ele, Grid::Status::PATH);
            }
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(_grid.checkBoundary(Grid::Coord{x, y}) && _grid.get_grid_value(Grid::Coord{x,y})==Grid::Status::CAN_CROSS){
                 _grid.set_value(Grid::Coord{x, y},  Grid::Status::IN_QUEUE);
                auto path = tp.second;
                path.push_back({x,y});
                q.push({{x, y}, path});
            }
        }
    }
    _grid.set_value(_grid.get_start(), Grid::Status::NOT_REACHEABLE);
    _grid.set_value(_grid.get_goal(),  Grid::Status::NOT_REACHEABLE);
}

void Algo::dfs(Grid &_grid){
    std::stack<std::pair<Grid::Coord, std::vector<Grid::Coord>>>s;
    s.push({_grid.get_start(), {_grid.get_start()}});
    while(!s.empty()){
        auto tp = s.top();
        auto top = tp.first;
        s.pop();
        _grid.set_value(Grid::Coord{top.x, top.y}, Grid::Status::VISITED);
        if(top == _grid.get_goal()){
            for(auto ele:tp.second){
                _grid.set_value(ele, Grid::Status::PATH);
            }
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = top.x + offset[i].x;
            int y = top.y + offset[i].y;
            if(_grid.checkBoundary({x, y}) && _grid.get_grid_value(Grid::Coord{x,y})==Grid::Status::CAN_CROSS){
                 _grid.set_value(Grid::Coord{x, y}, Grid::Status::IN_QUEUE);
                auto path = tp.second;
                path.push_back({x,y});
                s.push({{x, y}, path});
            }
        }
    }
    _grid.set_value(_grid.get_goal(),  Grid::Status::NOT_REACHEABLE);
    _grid.set_value(_grid.get_start(), Grid::Status::NOT_REACHEABLE);
}