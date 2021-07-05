//
//

#include "creature.h"
#include <iostream>

// Stream operator overload
/** 
 * This function overloads the << operator to print out the location
 * of the creature.
 * 
 * Precondition: The creature that is being passed into the function
 * must be properly constructed and has a valid Row and Col value. 
 * A valid ostream object must be passed into the function also.
 * 
 * Postcondition: The location of the creature in the form of
 * C(Row, Col) is sent to the ostream object. 
 */
std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
  Out << "C(" << Creature.Row << ", " << Creature.Col << ")";
  return Out;
}

// Parameterized constructor
/**
 * Precondition: Valid integers representing Row and Col must be passed
 * into the constructor in order for the creature to be initialized. 
 * Assuming the Row and Col variable is inside the range of Map
 * 
 * Postcondition: A creature that has a valid Row and Col data member
 * is created.
 */
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

// Checks whether the creature has reached the exit
/**
 * Precondition: A maze that is properly instantiated must be passed into the function.
 * The creature itself must also be properly initialized.
 * 
 * Postconditon: The function either returns true when the creature is indeed at the exit,
 * or false otherwise.
 */
bool Creature::atExit(const Maze &Maze) const {
  return (Row == Maze.getExitRow()) && (Col == Maze.getExitColumn());
}

// Launcher for recursive function
/**
 * This function serves as a launcher for a helper function that recursively looks for 
 * the correct path. 
 * 
 * Precondition: A maze that is properly instantiated must be passed into the function.
 * The creature itself must also be properly initialized.
 * 
 * Postcondition: The function would return whatever is being returned by the helper function,
 * either an empty string if no solution is found, or a string that represents the correct path.
 */
string Creature::solve(Maze &Maze) {
  // In order to keep track of the Path variable, a separate
  // helper function is created with an extra string parameter
  // to store and pass on Path
  return solve(Maze, "");
}

// Recursive helper function
/**
 * This is the function that implements most of the logic of this program. 
 * It is also the function that is doing all the recursion and backtracking.
 * 
 * Precondition: Maze and creature correctly instantiazed. The launcher function
 * should pass in an empty string to store the steps taken.
 * 
 * Postcondition: Either returns an empty string, indicating failure to find
 * a path to the exit, or a string that contains the correct step needed to 
 * reach the exit. The creature will be located at the exit if a solution is found,
 * otherwise it will remain at the starting location.
 */
string Creature::solve(Maze &Maze, string Path) {
  // Marking the current tile as path
  Maze.markAsPath(Row, Col);
  // Base case: the algorithm reached the exit, 
  // return the correct path
  if(atExit(Maze)) { return Path; }
  
  // Temporary variable to store the Result of recursion
  string Result;
  string Trial;
  // Start trying to go north
  Trial = goNorth(Maze);
  if (!Trial.empty()) { // Check if going north is valid
    // Trial is N if valid, empty if invalid
    // Recursion: Result is either an empty string, means further steps
    // have reached a dead end, or a string that represents the solution
    Result = solve(Maze, Path + Trial); // Append N to the Path param
    // If the recursion has found a solution, simply return the Result
    // and end this instance of solve()
    if (!Result.empty()) { return Result; }
    // Backtracking: further steps have reached a dead end, we mark the
    // current tile as visited, and undo the change from goNorth()
    Maze.markAsVisited(Row, Col);
    Row++; // Move south 1 tile, this undos goNorth()
  }// End of trying to go north

  // Similar logic as above
  // Start trying to go west
  Trial = goWest(Maze);
  if(!Trial.empty()) {
    Result = solve(Maze, Path + Trial);
    if (!Result.empty()) { return Result; }
    Maze.markAsVisited(Row, Col);
    Col++;
  } // End of trying to go west

  // Start trying to go East
  Trial = goEast(Maze);
  if(!Trial.empty()) {
    Result = solve(Maze, Path + Trial);
    if (!Result.empty()) { return Result; }
    Maze.markAsVisited(Row, Col);
    Col--;
  } // End of trying to go East

  // Start trying to go South
  Trial = goSouth(Maze);
  if(!Trial.empty()) {
    Result = solve(Maze, Path + Trial);
    if (!Result.empty()) { return Result; }
    Maze.markAsVisited(Row, Col);
    Row--;
  } // End of trying to go South

  // All directions are invalid, reached a dead end
  // Return an empty string to indicate failure
  return "";
}

// Go North
/**
 * Precondition: Maze and Creature correctly instantited.
 * 
 * Postconditon: If there is available space,the creature moves one row above,
 * a string "N" is returned. Otherwise, returns an empty string.
 */
string Creature::goNorth(const Maze &Maze) {
  if(Maze.isClear(Row - 1, Col)) {
    Row--;
    return "N";
  }
  return "";
}

// Go West
/**
 * Precondition: Maze and Creature correctly instantited.
 * 
 * Postconditon: If there is available space,the creature moves one column to the left,
 * a string "W" is returned. Otherwise, returns an empty string.
 */
string Creature::goWest(const Maze &Maze) {
  if(Maze.isClear(Row, Col - 1)) {
    Col--;
    return "W";
  }
  return "";
}

// Go East
/**
 * Precondition: Maze and Creature correctly instantited.
 * 
 * Postconditon: If there is available space,the creature moves one column to the right,
 * a string "E" is returned. Otherwise, returns an empty string.
 */
string Creature::goEast(const Maze &Maze) {
  if(Maze.isClear(Row, Col + 1)) {
    Col++;
    return "E";
  }
  return "";
}

// Go South
/**
 * Precondition: Maze and Creature correctly instantited.
 * 
 * Postconditon: If there is available space,the creature moves one row below,
 * a string "S" is returned. Otherwise, returns an empty string.
 */
string Creature::goSouth(const Maze &Maze) {
  if(Maze.isClear(Row + 1, Col)) {
    Row++;
    return "S";
  }
  return "";
}
