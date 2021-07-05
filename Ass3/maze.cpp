//
//

#include <fstream>
#include <iostream>

#include "maze.h"
#include <string>

using namespace std;

// Stream operator overload for Maze
ostream &operator<<(ostream &Out, const Maze &Maze) {
  for (int Row = 0; Row < Maze.Height; ++Row) {
    for (int Col = 0; Col < Maze.Width; ++Col) {
      Out << Maze.Field[Row][Col];
    }
    Out << endl;
  }
  Out << endl;
  return Out;
}

// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
Maze::Maze(const string &FileName) {
  ifstream InFile;
  InFile.open(FileName);
  if (!InFile) {
    cout << "Unable to open file";
    exit(1); // terminate with error
  }
  InFile >> Width >> Height;
  InFile >> ExitRow >> ExitColumn;
  string Str;
  getline(InFile, Str);
  for (int Row = 0; Row < Height; ++Row) {
    for (int Col = 0; Col < Width; ++Col) {
      InFile.get(Field[Row][Col]);
      // cout << Row << ", " << col << ": " << field[Row][col] << endl;
    }
    getline(InFile, Str);
  }

}

// returns the exit row
int Maze::getExitRow() const {
  return ExitRow;
}

// returns the exit column
int Maze::getExitColumn() const {
  return ExitColumn;
}

// MODIFIED: Added out of bound check to return false
// when a Row or Col that is outside of the Maze margin
// is passed into the function.
// It checks if Maze(Row, Col) is empty
bool Maze::isClear(int Row, int Col) const {
  if (Row < 0 || Col < 0 || Row >= Height || Col >= Width) { 
    return false; 
  }
  return Field[Row][Col] == ' ';
}

// Use to mark the correct path 
void Maze::markAsPath(int Row, int Col) {
  Field[Row][Col] = '*';
}

// Use to mark tiles that the algorithm
// reached but that are not part of the correct path
void Maze::markAsVisited(int Row, int Col) {
  Field[Row][Col] = '+';
}
