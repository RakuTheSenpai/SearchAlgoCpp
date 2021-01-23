#include "grid.h"
bool Grid::checkBoundary(coord current){
    if(current.x < 0 || current.x >= _grid[0].size() || current.y < 0 || current.y >= _grid.size()){
        return false;
    }
    return _grid[current.x][current.y] == Grid::status::CAN_CROSS;
}

void Grid::set_coordinates_to_value(coord coordinates, status value){
    int x = coordinates.x, y = coordinates.y;
    _grid[x][y] = value;
}
