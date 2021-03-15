# SearchAlgoCpp
A small project about search algorithms and their visual representation.

## Building
You can use and edit the provided make file to suit your needs. Personally I use Linux and the g++ compiler, so that's how it is configured.

## Usage
Using the application is pretty simple, you just need to hover over the tiles and click (like a Ms paint). The only exceptions are the position of the start and goal since they must be a single point.

|Hotkey | Description|
|-------|------------|
|Q | Activates the clear "brush", now you can delete walls where you have draw them.|
|W | Activates the wall "brush", now you can paint walls where you want them.|
|E | Set Start position.|
|R | Set Goal position.|
|C | Clears the grid of any previous performed algorithms.|
|D | Clears the grid along with walls.|
|1 | Perform BFS on Grid.|
|2 | Perform DFS on Grid.|

## Examples
### W
![W](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/w.gif)

### Q
![Q](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/q.gif)

### E
![E](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/e.gif)

### R
![R](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/r.gif)

### C
![C](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/c.gif)

### D
![D](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/d.gif)

### 1
![1](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/1.gif)

### 2
![2](https://github.com/RakuTheSenpai/SearchAlgoCpp/blob/main/Examples/2.gif)


## Todo
* Generate walls randomly.
* Expand or substract the number of tiles.
* Add A*.
