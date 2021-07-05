//
// 
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
  // Stream operator overload for Maze
  friend ostream &operator<<(ostream &Out, const Maze &Maze);
private:
  // Properties of the Maze
  const static int MAX_SIZE = 100;
  char Field[MAX_SIZE][MAX_SIZE];
  int Width, Height;
  int ExitRow, ExitColumn;
public:
  // Constructor for the maze, takes in a txt file
  // to build a maze
  explicit Maze(const string &FileName);

  // MODIFIED: Added out of bound check to return false
  // when a Row or Col that is outside of the Maze margin
  // is passed into the function.
  // It checks if Maze(Row, Col) is empty
  bool isClear(int Row, int Col) const;

  // Use to mark the correct path 
  void markAsPath(int Row, int Col);

  // Use to mark tiles that the algorithm
  // reached but that are not part of the correct path 
  void markAsVisited(int Row, int Col);

  // returns the exit row
  int getExitRow() const;

  // returns the exit column
  int getExitColumn() const;

};

#endif //ASS3_MAZE_H
