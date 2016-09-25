#include <iostream>
#include <vector>
#include <queue>

/*
  @author: Narasimha Murthy
  This is a Maze Solver solved using three different algorithms: Depth-First Search, Breadth-First Search and A* algorithm.
  DFS does not give the shortest path whereas the other algorithms do.
*/

typedef std::pair<int, int> pi;
typedef std::vector<std::string > Maze; 

/*  Function object for the A* algorithm */
class Compare{
  public:
    bool operator()(std::pair<pi, int> a, std::pair<pi, int> b){
      return a.second > b.second;
    }
};

class MazeSolver{
  public:
    MazeSolver(Maze& m, int endx, int endy):maze(m), row(m.size()), col(m[0].size()), endX(endx), endY(endy){

      // Initialize node variables (reqd for BFS & A*)
      std::vector<int> vec1(col, -1);
      std::vector<pi> vec2(col, std::make_pair(-1,-1));
      dist = std::vector<std::vector<int> >(row, vec1);
      parent = std::vector< std::vector<pi> >(row, vec2);
    }

    // DFS
    bool solve_dfs(int x, int y){
      if(x == endX && y == endY){
        return true;
      }

      maze[x][y] = '*';
      if( x > 0 && (maze[x-1][y] == ' ' || maze[x-1][y] == 'O') && solve_dfs(x-1, y) )
        return true;
      if( x < row-1 && (maze[x+1][y] == ' ' || maze[x+1][y] == 'O') && solve_dfs(x+1, y) )
        return true;
      if( y > 0 && (maze[x][y-1] == ' ' || maze[x][y-1] == 'O') && solve_dfs(x, y-1) )
        return true;
      if( y < col-1 && (maze[x][y+1] == ' ' || maze[x][y+1] == 'O') && solve_dfs(x, y+1) )
        return true;
      maze[x][y] = 'o';
      return false;
    }

    // BFS
    bool solve_bfs(int sx, int sy){
      // Set the root distance to zero
      dist[sx][sy] = 0;

      std::queue<pi> q;
      q.push(std::make_pair(sx, sy));
      while(! q.empty()){
        int qx = q.front().first;
        int qy = q.front().second;
        q.pop();

        int x,y;

        std::vector<pi> arr{std::make_pair(-1,0),std::make_pair(1,0), std::make_pair(0,-1), std::make_pair(0,1)};

        for(int i=0; i < arr.size(); ++i){
          x = qx + arr[i].first;
          y = qy + arr[i].second;

          if(x >= 0 && x < row && y >= 0 && y < col && dist[x][y] == -1 && (maze[x][y] == ' ' || maze[x][y] == 'O')){
            dist[x][y] = dist[qx][qy] + 1;
            parent[x][y] = std::make_pair(qx,qy);

            if(maze[x][y] == 'O')
              return true;
            q.push(std::make_pair(x,y));
          }
        }
      }
      return false;
    }


    // A* algorithm : Similar to BFS but instead of blindly going to the neighbouring nodes,
    // this sorts the nodes w.r.t Manhattan distance from the end point and then traverses the neighbouring node that has the least distance
    bool solve_a_star(int sx, int sy){
      // Set the root distance to zero
      dist[sx][sy] = 0;

      // First pair of ints represents the point and the next int is the Manhattan Distance
      std::priority_queue<std::pair<pi,int>, std::vector<std::pair<pi, int>>, Compare> pq;
      pq.push(std::make_pair(std::make_pair(sx, sy), 0));
      while(! pq.empty()){
        int qx = pq.top().first.first;
        int qy = pq.top().first.second;
        pq.pop();

        int x,y;

        std::vector<pi> arr{std::make_pair(-1,0),std::make_pair(1,0), std::make_pair(0,-1), std::make_pair(0,1)};

        for(int i=0; i < arr.size(); ++i){
          x = qx + arr[i].first;
          y = qy + arr[i].second;

          if(x >= 0 && x < row && y >= 0 && y < col && dist[x][y] == -1 && (maze[x][y] == ' ' || maze[x][y] == 'O')){
            dist[x][y] = dist[qx][qy] + 1;
            parent[x][y] = std::make_pair(qx,qy);

            if(maze[x][y] == 'O')
              return true;
            pq.push(std::make_pair( std::make_pair(x,y), manhattan_distance(std::make_pair(endX, endY), std::make_pair(x,y)) + dist[x][y]));
          }
        }
      }
      return false;
    }

    // Manhattan Distance calculation
    int manhattan_distance(pi dst, pi src){
      return abs(dst.first - src.first) + abs(dst.second - src.second);
    }

  void printMaze(){
    for(int i=0; i < maze.size();++i){
      std::cout << maze[i] << std::endl;
    }
  }

  void printMaze_Bfs(int sx, int sy){
    pi par = parent[endX][endY];
    while(par != std::make_pair(sx, sy)){
      maze[par.first][par.second] = '*';
      par = parent[par.first][par.second];
    }

    printMaze();

    std::cout << "Distance traveled is " << dist[endX][endY] << std::endl;
  }

  private:
    Maze maze;
    int row;
    int col;
    int endX;
    int endY;
    std::vector< std::vector<int> > dist;
    std::vector< std::vector<pi> > parent;
};


int main(){
  Maze m;

  // Read the file
  std::string line;
  int row = 0;
  int sx, sy, ex, ey;
  while(std::getline(std::cin,line)){
    m.push_back(line);
    for(int i=0; i < line.size(); ++i){
      // 'X' denotes starting point
      if(line[i] == 'X'){
         sx = row;
         sy = i;
      }
      // 'O' denotes ending point
      else if(line[i] == 'O'){
        ex = row;
        ey = i;
      }   
    }
    ++row;
  }

  MazeSolver solver = MazeSolver(m, ex, ey);

  // Uncomment to run DFS. Comment out others.
/*
  if(solver.solve_dfs(sx,sy))
    solver.printMaze();
  else
    std::cout << "No solution" << std::endl;
*/
  
  if(solver.solve_bfs(sx,sy))
    solver.printMaze_Bfs(sx,sy);
  else
    std::cout << "No solution" << std::endl;
  
  // Uncomment to run A*. Comment out others
/*
  if(solver.solve_a_star(sx,sy))
    solver.printMaze_Bfs(sx,sy);
  else
    std::cout << "No solution" << std::endl;
*/
}
