#include "../Algo/Algo.h"
#include "../Grid/grid.h"

int main(){
    Grid A(5);
    /* setting up barriers */
    for(int i = 0; i < 4; ++i){
        A.set_coordinates_to_value({i, 1}, Grid::status::BLOCKED);
    }
    for(int i = 4; i > 2; --i){
        A.set_coordinates_to_value({i, 3}, Grid::status::BLOCKED);
    }
    std::cout << Algo::bfs(A,{4, 4}) << std::endl;
    std::cout << Algo::dfs(A, {4, 4}) << std::endl;
}