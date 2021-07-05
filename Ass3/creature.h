//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature {
public:
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
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  // Variables storing the location of the creature
  int Row;
  int Col;

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
  string solve(Maze &Maze, string Path);

public:
  // Parameterized constructor
  /**
   * Precondition: Valid integers representing Row and Col must be passed
   * into the constructor in order for the creature to be initialized. 
   * Assuming the Row and Col variable is inside the range of Map
   * 
   * Postcondition: A creature that has a valid Row and Col data member
   * is created.
   */
  Creature(int Row, int Col);

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
  string solve(Maze &Maze);

  // Checks whether the creature has reached the exit
  /**
   * Precondition: A maze that is properly instantiated must be passed into the function.
   * The creature itself must also be properly initialized.
   * 
   * Postconditon: The function either returns true when the creature is indeed at the exit,
   * or false otherwise.
   */
  bool atExit(const Maze &Maze) const;

  // Go North
  /**
   * Precondition: Maze and Creature correctly instantited.
   * 
   * Postconditon: The creature moves one row above,
   * a string "N" is returned.
   */
  string goNorth(const Maze &Maze);

  // Go South
  /**
   * Precondition: Maze and Creature correctly instantited.
   * 
   * Postconditon: The creature moves one row below,
   * a string "S" is returned.
   */
  string goSouth(const Maze &Maze);

  // Go East
  /**
   * Precondition: Maze and Creature correctly instantited.
   * 
   * Postconditon: The creature moves one column to the right,
   * a string "E" is returned.
   */
  string goEast(const Maze &Maze);

  // Go West
  /**
   * Precondition: Maze and Creature correctly instantited.
   * 
   * Postconditon: The creature moves one column to the left,
   * a string "W" is returned.
   */
  string goWest(const Maze &Maze);
};

#endif //ASS3_CREATURE_H
