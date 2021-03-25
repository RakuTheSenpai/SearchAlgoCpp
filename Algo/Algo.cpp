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
    std::queue<Grid::Coord>q;
    std::unordered_map<Grid::Coord, Grid::Coord>came_from;
    q.push(_grid.get_start());
    while(!q.empty()){
        auto current = q.front();
        q.pop();
        _grid.set_status(current, Grid::Status::VISITED);
        if(current == _grid.get_goal()){
            construct_path(came_from, _grid, current);
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = current.x + offset[i].x;
            int y = current.y + offset[i].y;
            Grid::Coord neighbor{x, y};
            if(_grid.check_boundary(neighbor) && (_grid.get_status(neighbor)==Grid::Status::CAN_CROSS || _grid.get_status(neighbor)==Grid::Status::GOAL)){
                _grid.set_status(neighbor,  Grid::Status::IN_QUEUE);
                came_from[neighbor] = current;
                q.push(neighbor);
            }
        }
        _grid.draw();
    }
    _grid.set_status(_grid.get_start(), Grid::Status::NOT_REACHEABLE);
    _grid.set_status(_grid.get_goal(),  Grid::Status::NOT_REACHEABLE);
}

void Algo::dfs(Grid &_grid){
    std::stack<Grid::Coord>q;
    std::unordered_map<Grid::Coord, Grid::Coord>came_from;
    q.push(_grid.get_start());
    while(!q.empty()){
        auto current = q.top();
        q.pop();
        _grid.set_status(current, Grid::Status::VISITED);
        if(current == _grid.get_goal()){
            construct_path(came_from, _grid, current);
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = current.x + offset[i].x;
            int y = current.y + offset[i].y;
            Grid::Coord neighbor{x, y};
            if(_grid.check_boundary(neighbor) && (_grid.get_status(neighbor)==Grid::Status::CAN_CROSS || _grid.get_status(neighbor)==Grid::Status::GOAL)){
                _grid.set_status(neighbor,  Grid::Status::IN_QUEUE);
                came_from[neighbor] = current;
                q.push(neighbor);
            }
        }
        _grid.draw();
    }
    _grid.set_status(_grid.get_start(), Grid::Status::NOT_REACHEABLE);
    _grid.set_status(_grid.get_goal(),  Grid::Status::NOT_REACHEABLE);
}

float Algo::d(Grid::Coord a, Grid::Coord b){
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

void Algo::construct_path(std::unordered_map<Grid::Coord, Grid::Coord>&came_from, Grid&_grid, Grid::Coord current){
    while(came_from.count(current)){
        _grid.set_status(current, Grid::Status::PATH);
        current = came_from[current];
    }
    _grid.set_status(_grid.get_start(), Grid::Status::START);
}

void Algo::a_star(Grid &_grid){
    std::priority_queue<std::pair<float, Grid::Coord>, std::vector<std::pair<float,Grid::Coord>>, std::greater<>>q;
    q.push({d(_grid.get_start(), _grid.get_goal()), _grid.get_start()});
    std::unordered_map<Grid::Coord, Grid::Coord>came_from;
    std::unordered_map<Grid::Coord, float>score;
    //easy looks up at the expense of more memory
    std::set<Grid::Coord>open_set;
    open_set.insert(_grid.get_start());
    int count = 0;
    while(!q.empty()){
        auto top = q.top();
        auto current = top.second;
        q.pop();
        _grid.set_status(current, Grid::Status::VISITED);
        open_set.erase(current);
        if(current == _grid.get_goal()){
            construct_path(came_from, _grid, current);
            return;
        }
        for(int i = 0; i < 8; ++i){
            int x = current.x + offset[i].x;
            int y = current.y + offset[i].y;
            Grid::Coord neighbor{x, y};
            //proximity to goal
            float tentative_score = score[current] + d(current, neighbor);

            if(_grid.check_boundary(neighbor) &&
            ((_grid.get_status(neighbor)==Grid::Status::CAN_CROSS  || _grid.get_status(Grid::Coord{x,y})==Grid::Status::GOAL)&& 
                (score.count(neighbor) == 0 || tentative_score < score[neighbor]))){
                    //score.count(neighbor) == 0 meaning the distance is not know therefore infinite.
                 _grid.set_status(Grid::Coord{x, y}, Grid::Status::IN_QUEUE);
                 came_from[neighbor] = current;
                 score[neighbor] = tentative_score;
                 float fscore = score[neighbor] + d(neighbor, _grid.get_goal());
                 if(open_set.count(neighbor) == 0){
                    _grid.set_status(Grid::Coord{x, y}, Grid::Status::IN_QUEUE);
                    q.push({fscore, neighbor});
                    open_set.insert(neighbor);
                 }
            }
        }
        _grid.draw();
    }
    _grid.set_status(_grid.get_goal(),  Grid::Status::NOT_REACHEABLE);
    _grid.set_status(_grid.get_start(), Grid::Status::NOT_REACHEABLE);
}