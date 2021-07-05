#include <ostream>
#pragma once

class ThreadedBST {
  friend std::ostream &operator<<(std::ostream &out, const ThreadedBST &tbst);

public:
  class TreeNode {
  public:
    // TreeNode Public Members
    int Value;
    TreeNode *Left;
    TreeNode *Right;
    bool LeftThread;
    bool RightThread;

    // TreeNode Constructor
    explicit TreeNode(int value)
        : Value(value), Left(nullptr), Right(nullptr), LeftThread(false),
          RightThread(false) {}
  };

  class Iterator {
  public:
    // Iterator Constructor
    explicit Iterator(TreeNode *current) : current(current) {}

    // Iterator Public Functions
    Iterator operator++();
    Iterator operator--();
    int &operator*() const;
    bool operator==(const Iterator &rhs) const;
    bool operator!=(const Iterator &rhs) const;

  private:
    // Iterator Private Members
    TreeNode *current;
  };

  // TBST Constructors
  ThreadedBST() : root{ nullptr } {}
  ~ThreadedBST();
  ThreadedBST(const ThreadedBST &other);


  // TBST Public Functions
  bool add(int data);
  bool remove(int data);
  bool contains(int data) const;
  bool isEmpty() const;
  void clear();

  const Iterator begin() const;
  const Iterator end() const;

private:
  // TBST Private Members
  TreeNode *root;

  // TBST Private Functions
  void preOrderAdd(TreeNode *parent, TreeNode *otherNode);

  static void attach(TreeNode *node, TreeNode *parent);
  static void postOrderDelete(TreeNode *node, TreeNode *parent);
  static void deleteLeafNode(TreeNode *node, TreeNode *parent);
  static bool isLeafNode(TreeNode *node);

  static bool retrieve(int data, TreeNode **node, TreeNode **parent = nullptr);

  static TreeNode *leftMostNode(TreeNode *node);
  static TreeNode *rightMostNode(TreeNode *node);
};