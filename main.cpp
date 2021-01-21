#include "Grid/grid.h"
#include <iostream>
int main(){
    Grid a(5);
    // a.set_coordinates_to_value({1,1},2);
    // a.set_coordinates_to_value({0,1},2);
    for(int i = 0; i < 5; ++i){
        a.set_coordinates_to_value({i, 1}, 2);
    }
    a.dfs({4, 4});
    std::cout << a;
}