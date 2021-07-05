
// modified by mashhadi on 14th feb to add an alternative op<<

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

/** Stream operator overload
 *  overloads the << operator for printing out the list
 *  Pre: A valid ostream object and properly initialized SkipList is passed in
 *  Post: The SkipList is returned to the ostream object
 */
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.depth - 1; Index >= 0; Index--) {
    Out << "Level: " + to_string(Index) + " -- ";
    SNode *Curr = SkipL.FrontGuards[Index];
    while (Curr != nullptr) {
      Out << to_string(Curr->value) + ", ";
      Curr = Curr->forward;
    }
    Out << "\n";
  }
  return Out;
}

/** SNode Constructor
 *  Pre: A valid integer is passed in as value
 *  Post: A SNode is createdwith the provided value and all directions as
 *  nullptr
 */
SNode::SNode(int value) : value{ value } {
  this->forward = nullptr;
  this->backward = nullptr;
  this->up = nullptr;
  this->down = nullptr;
}

/** SkipList Constructor
 *  Pre: The integer parameters passed in must satisfy the following:
 *          depth > 0
 *          probability >= 0
 *          probability < 100
 *  Post: An empty SkipList is initialized with number of levels equal to depth
 *        FrontGuards and RearGuards will be created to form the two ends of the
 *        list
 */
SkipList::SkipList(int depth, int probability)
    : depth{ depth }, probability{ probability } {
  assert(depth > 0 && probability >= 0 && probability < 100);

  this->FrontGuards = new SNode *[depth];
  this->RearGuards = new SNode *[depth];
  auto *NewFront = new SNode(INT_MIN);
  auto *NewRear = new SNode(INT_MAX);
  // Linking the front and the rear
  connect2(NewFront, NewRear);
  // Filling up the front guards and rear guards with a Node
  // that represents the minimum and maximum possible int value
  this->FrontGuards[0] = NewFront;
  this->RearGuards[0] = NewRear;
  // Repeat the operation for the remaining level of the guards
  for (int Index = 1; Index < depth; Index++) {
    NewFront = new SNode(INT_MIN);
    NewRear = new SNode(INT_MAX);

    connect2(NewFront, NewRear);

    this->FrontGuards[Index] = NewFront;
    this->RearGuards[Index] = NewRear;

    // Linking the different levels of FrontGuards, and also for RearGuards
    connectVertical(NewFront, FrontGuards[Index - 1]);
    connectVertical(NewRear, RearGuards[Index - 1]);
  }
}

/** Decides whether the Node should be inserted at higher level
 *  Pre: The SkipList is correctly instantiated
 *  Post: A random bool value is returned
 */
bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

/** Add a collection of nodes to the SkipList
 *  Pre: The SkipList is correctly instantiated
 *       The vector contains valid integers for the nodes
 *  Post: Any value within the vector that does not already exist in the list
 *        will be added. If nothing can be added, returns false
 */
bool SkipList::add(const vector<int> &values) {
  // Add the entries one by one
  // If any add is successful returns true
  bool Out = false;
  for (int Value : values) {
    Out = add(Value) || Out;
  }
  return Out;
}

/** Add a Node to the SkipList
 *  Pre: The SkipList is correctly instantiated
 *       A valid integer is paased in as the parameter
 *  Post: A Node of value{value} is added to the list, returns true
 *        If the Node already exists in the list, returns false without
 * modifying
 */
bool SkipList::add(int value) {
  // A pointer to locate the Node that should be behind the new Node
  SNode *Curr = FrontGuards[0]->forward;

  // Walks through the list, finding the right position
  while (Curr->forward != nullptr && Curr->value < value) {
    Curr = Curr->forward;
  }
  // DUPLICATE: return false
  if (Curr->value == value) {
    return false;
  }

  // Creating a new Node
  auto *NewNode = new SNode(value);
  addBefore(NewNode, Curr);

  // Flipping the coin
  bool NextLevel = shouldInsertAtHigher();

  // Going higher
  int CurrDepth = 1;
  Curr = NewNode;
  while (NextLevel && (CurrDepth < this->depth)) {
    // Creating a Node above the Current Node and link
    auto *NewUpper = new SNode(value);
    connectVertical(NewUpper, Curr);

    // Moving back until a Node has valid up pointer
    Curr = Curr->backward;
    while (Curr->up == nullptr) {
      Curr = Curr->backward;
    }
    // Navigating to the correct Node to addBefore
    Curr = Curr->up->forward;
    addBefore(NewUpper, Curr);

    Curr = NewUpper;

    // Incrementing the level counter and
    // Decide whether to add higher again
    NextLevel = shouldInsertAtHigher();
    CurrDepth++;
  }

  return true;
}

// Destructor
SkipList::~SkipList() {
  // Temporary pointers used to traverse through the list
  SNode *NodeToBeDeleted;
  SNode *Temp;
  for (int Index = depth - 1; Index >= 0; Index--) {
    NodeToBeDeleted = FrontGuards[Index];
    while (NodeToBeDeleted != nullptr) {
      Temp = NodeToBeDeleted->forward;
      decouple(NodeToBeDeleted); // Unlink the Node from other nodes
      delete NodeToBeDeleted;
      NodeToBeDeleted = Temp; // Moving to the next Node
    }
  }

  // Removing the front and rear guards
  delete[] FrontGuards;
  delete[] RearGuards;
  FrontGuards = nullptr;
  RearGuards = nullptr;
}

/** Remove a Node from the lsit
 *  Pre: The SkipList is correctly instantiated
 *       A valid integer is passed in
 *  Post: The Node is deleted from the list, if it exists, returns true
 *        If the Node does not exist, returns false without modifying
 */
bool SkipList::remove(int data) {
  // Retrieve the Node from the list
  SNode *NodeToBeDeleted = containsSNode(data);
  if (NodeToBeDeleted == nullptr) {
    return false;
  } // Node doesn't exist

  SNode *Temp;                         // Temporary pointer to traverse
  while (NodeToBeDeleted != nullptr) { // Needs to delete the Node at all level
    // Links the previous and next Node
    connect2(NodeToBeDeleted->backward, NodeToBeDeleted->forward);
    // Goes down one level
    Temp = NodeToBeDeleted->down;
    // Unlink the Node from other nodes
    decouple(NodeToBeDeleted);
    delete NodeToBeDeleted;
    NodeToBeDeleted = Temp;
  }
  return true;
}

/** Given a SNode, place it before the given NextNode
 *  Pre: The NewNode and NextNode are valid nodes
 *  Post: The NewNode is added infront of NextNode
 */
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
  connect2(NextNode->backward, NewNode);
  connect2(NewNode, NextNode);
}

/** Checks to see whether or not a data value exists in the list
 *  Returns the NODE if the value exists in the SkipList.
 *  Returns nullptr otherwise
 *  Pre: The list is correctly instantiated, valid integer is passed
 *       into the function.
 *  Post: Returns the Node at the HIGHEST LEVEL if exists,
 *        returns nullptr if the Node with that value does not exist.
 */
SNode *SkipList::containsSNode(int data) const {
  // Start from the top left
  SNode *Current = FrontGuards[depth - 1];
  while (Current != nullptr) {
    // If the Current value is less than the target, go forward
    if (Current->value < data) {
      Current = Current->forward;
    }
    // If the Current value equals the target, return the Current Node
    else if (Current->value == data) {
      return Current;
    }
    // Current value is larger than the target,
    // go back one Node and go down one level
    else {
      Current = Current->backward->down;
    }
  }
  // Didn't find the Node
  return nullptr;
}

// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise
bool SkipList::contains(int data) const {
  return (containsSNode(data) != nullptr);
}

// Links two SNode horizontally
void SkipList::connect2(SNode *a, SNode *b) {
  a->forward = b;
  b->backward = a;
}

// Links two SNode vertically
void SkipList::connectVertical(SNode *top, SNode *bot) {
  top->down = bot;
  bot->up = top;
}

/** Setting all the pointers to nullptr, used before deleteing a Node
 *  Pre: a properly initialized SNode is passed in
 *  Post: all of the direction pointers of Node is set to nullptr
 */
void SkipList::decouple(SNode *Node) {
  Node->forward = nullptr;
  Node->backward = nullptr;
  Node->up = nullptr;
  Node->down = nullptr;
}