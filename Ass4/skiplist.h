/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 * also used by MemSQL
 * https://www.singlestore.com/blog/what-is-skiplist-why-skiplist-index-for-memsql/
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 *
 */

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  friend class SkipList;
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  /** SNode Constructor
   *  Pre: A valid integer is passed in as value
   *  Post: A SNode is createdwith the provided value and all directions as
   *  nullptr
   */
  explicit SNode(int value);

  // data contained in the object
  int value{0};

  // link to the next SNode 
  SNode* forward;

  // link to the previous SNode
  SNode* backward;
   
  //link to up node 
  SNode* up;

  // link to down SNode
  SNode* down;
};

class SkipList {
  /** Stream operator overload
   *  overloads the << operator for printing out the list
   *  Pre: A valid ostream object and properly initialized SkipList is passed in
   *  Post: The SkipList is returned to the ostream object
   */
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // maximum number of levels
  int depth = 1;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability = 0;

  // head of linked levels
  SNode **FrontGuards;

  // tail of linked levels
  SNode **RearGuards;

  /** Given a SNode, place it before the given NextNode
   *  Pre: The NewNode and NextNode are valid nodes
   *  Post: The NewNode is added infront of NextNode
   */
  void addBefore(SNode *newNode, SNode *nextNode);

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  /** Decides whether the Node should be inserted at higher level
   *  Pre: The SkipList is correctly instantiated
   *  Post: A random bool value is returned
   */
  bool shouldInsertAtHigher() const;

  // connect 2 nodes horizontally
  static void connect2(SNode *a, SNode *b);

  // connect 2 nodes vertically
  static void connectVertical(SNode* top, SNode* bot);

  /** Checks to see whether or not a data value exists in the list
   *  Returns the NODE if the value exists in the SkipList.
   *  Returns nullptr otherwise
   *  Pre: The list is correctly instantiated, valid integer is passed
   *       into the function.
   *  Post: Returns the Node at the HIGHEST LEVEL if exists,
   *        returns nullptr if the Node with that value does not exist.
   */
  SNode *containsSNode(int data) const;

  /** Setting all the pointers to nullptr, used before deleteing a Node
   *  Pre: a properly initialized SNode is passed in
   *  Post: all of the direction pointers of Node is set to nullptr
   */
  static void decouple(SNode* node);

public:
  /** SkipList Constructor
   *  Pre: The integer parameters passed in must satisfy the following:
   *          depth > 0
   *          probability >= 0
   *          probability < 100
   *  Post: An empty SkipList is initialized with number of levels equal to depth
   *        FrontGuards and RearGuards will be created to form the two ends of the
   *        list
   */
  explicit SkipList(int depth = 1, int probability = 0);

  // destructor
  virtual ~SkipList();

  // copy not allowed
  SkipList(const SkipList &other) = delete;

  // move not allowed
  SkipList(SkipList &&other) = delete;

  // assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  /** Add a Node to the SkipList
   *  Pre: The SkipList is correctly instantiated
   *       A valid integer is paased in as the parameter
   *  Post: A Node of value{value} is added to the list, returns true
   *        If the Node already exists in the list, returns false without
   * modifying
   */
  bool add(int value);

  /** Add a collection of nodes to the SkipList
   *  Pre: The SkipList is correctly instantiated
   *       The vector contains valid integers for the nodes
   *  Post: Any value within the vector that does not already exist in the list
   *        will be added. If nothing can be added, returns false
   */
  bool add(const vector<int> &values);

  /** Remove a Node from the lsit
   *  Pre: The SkipList is correctly instantiated
   *       A valid integer is passed in
   *  Post: The Node is deleted from the list, if it exists, returns true
   *        If the Node does not exist, returns false without modifying
   */
  bool remove(int data);

  // Checks to see whether or not a data value exists in the list
  // Returns true if the value exists in the SkipList.
  // Returns false otherwise
  bool contains(int data) const;
};

#endif // ASS4_SKIPLIST_H
