#include "ThreadedBST.h"
#include <iostream>

// Stream operator overload for printing the tree out
std::ostream &operator<<(std::ostream &out, const ThreadedBST &tbst) {
  for (auto It = tbst.begin(); It != tbst.end(); ++It) {
    out << *It << " ";
  }
  return out;
}

// Destructor
ThreadedBST::~ThreadedBST() { clear(); }

// Copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST &other) : root{ nullptr } {
  preOrderAdd(root, other.root);
}

/** Function to deep copy the subtree rooted at "otherNode". 
 *  Uses preorder traversal to retain the structure of the tree.
 *  Precon:   parent is a TreeNode in a TBST
 *            otherNode is a TreeNode in another TBST
 *  Postcon:  the subTree rooted at otherNode is copied to parent
 *  @param parent the parent to the root of the new subtree, use nullptr
 *  if adding to an empty TBST
 *  @param otherNode the root of the subtree that is being copied
 */
void ThreadedBST::preOrderAdd(TreeNode *parent, TreeNode *otherNode) {
  if (otherNode == nullptr) {
    // can't copy an empty tree
    std::cout << "preOrderAdd(): otherNode is nullptr, nothing is copied"
              << std::endl;
    return;
  }

  auto NewNode = new TreeNode(otherNode->Value);

  if (parent == nullptr) { // parent is null, indicating we are at the root
    if (root == nullptr) { // make sure we are at the root
      root = NewNode;      // assign NewNode to be the root

    } else {
      // If we reached here, it means we passed in nullptr to parent when we are
      // NOT at the root, this is not allowed
      std::cerr << "Error: in preOrderAdd(), nullptr is passed in as parent "
                   "when root is not null" << std::endl;
      delete NewNode;
      exit(EXIT_FAILURE);
    }

  } else {
    // Under normal circumstances, we just attach NewNode to its parent
    attach(NewNode, parent);
  }

  // If otherNode has a left child, we go left
  if (!otherNode->LeftThread && otherNode->Left != nullptr) {
    preOrderAdd(NewNode, otherNode->Left);
  }
  // If otherNode has a righR child, we go right
  if (!otherNode->RightThread && otherNode->Right != nullptr) {
    preOrderAdd(NewNode, otherNode->Right);
  }
}

/** Function to add a new node to the tree.
 *  Also creates the threads for each node
 *  Precon: an instance of TBST is initialized
 *  Postcon: if data does not already exist in the tree, 
 *           it will be added into the tree.
 *  @param data the number you want to add
 *  @return true if added, false if the number is a duplicate
 */
bool ThreadedBST::add(int data) {
  // If the tree is empty, just create a plain new node
  if (root == nullptr) {
    root = new TreeNode(data);
    return true;
  }

  // Use retrieve() to find the parent to the new node
  TreeNode *Parent = root;
  if (retrieve(data,
               &Parent)) { // This alters "parent" to point to the actual parent
    // If we found the node then there is duplicate, addition failed
    std::cout << "add(): duplicate for " << data << " found, not added"
              << std::endl;
    return false;
  }

  // Under normal circumstances, we create a new node and attach it to the
  // parent we found
  auto NewNode = new TreeNode(data);
  attach(NewNode, Parent);
  // add successful
  return true;
}

/** Helper function to attach a node to the parent
 *  Precon: node and parent should be valid TreeNode that are not null
 *  Postcon: node becomes either the left or the right child of parent
 *  @param node the node that is newly created
 *  @param parent the parent that the node should attach to
 */
void ThreadedBST::attach(TreeNode *node, TreeNode *parent) {
  if (node == nullptr || parent == nullptr) {
    std::cerr << "Error: in attach(), at least one of the param is nullptr"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  // node should be added to the leLeftft of the parent
  if (node->Value < parent->Value) {
    // inherits the left pointer from parent
    node->Left = parent->Left;
    // the only case where the new node doesn't have a left thread
    // is when the parent's Left pointer points to null
    node->LeftThread = (node->Left != nullptr);
    // inherits the right pointer from pareent
    node->Right = parent;
    // in all cases the new node will have a right thread
    node->RightThread = true;
    // the parent's left is now the new node
    parent->Left = node;
    // the parent no longer has a left thread
    parent->LeftThread = false;
  }

  // node should be added to the right of the parent
  else {
    // similar logic as above
    node->Right = parent->Right;
    node->RightThread = (node->Right != nullptr);
    node->Left = parent;
    node->LeftThread = true;

    parent->Right = node;
    parent->RightThread = false;
  }
}

/** Function to find the left most descendent of a given node
 *  Useful in finding the inorder SUCCESSOR of a node
 *  @return the left most descendent of node, returns nullptr if node doesn't exist
 */
ThreadedBST::TreeNode *ThreadedBST::leftMostNode(TreeNode *node) {
  if (node != nullptr) {
    // just keep going left until we ran out of left
    while (node->Left != nullptr && !node->LeftThread) {
      node = node->Left;
    }
  }
  return node;
}

/** Function to find the right most descendent of a give node
 *  Useful in finding the inorder PREDECESSOR of a node
 *  @return the right most descendent of node, returns nullptr if node doesn't exist
 */
ThreadedBST::TreeNode *ThreadedBST::rightMostNode(TreeNode *node) {
  if (node == nullptr) {
    return nullptr;
  }
  // just keep going right until we ran out of right
  while (node->Right != nullptr && !node->RightThread) {
    node = node->Right;
  }
  return node;
}

/** Function to find the node that has the same value as data.
 *  Precon:   node and parent must be of type pointer to a TreeNode pointer
 *  Postcon:  If found, node will be altered to point at the target.
 *            If not found, node will point to the parent of the potential node.
 *            Parent will  point to the parent of the node.
 *            
 *  @param node A pointer to the pointer of the target node.
 *  @param parent (optional) A pointer to the pointer of the parent node.
 *  @return Returns true if such node is found, false otherwise.
 */
bool ThreadedBST::retrieve(int data, TreeNode **node, TreeNode **parent) {
  while (data != (*node)->Value) {
    // Going left
    if (data < (*node)->Value) {
      if ((*node)->LeftThread || (*node)->Left == nullptr) {
        return false;
      }
      if (parent != nullptr) {
        *parent = *node;
      }
      *node = (*node)->Left;
      // Going right
    } else if (data > (*node)->Value) {
      if ((*node)->RightThread || (*node)->Right == nullptr) {
        return false;
      }
      if (parent != nullptr) {
        *parent = *node;
      }
      *node = (*node)->Right;
    }
  }
  return true;
}

/** Function to find whether a number exists in the binary tree already.
 *  @return true if the data exists somewhere in the tree
 */
bool ThreadedBST::contains(int data) const {
  TreeNode *Node = root;
  return retrieve(data, &Node);
}

/** Function to test whether the tree is empty
 *  @return true if the tree contains no node
 */
bool ThreadedBST::isEmpty() const { return root == nullptr; }

/** Function to test whether a give node is a leaf node (has no child)
 *  Precon: node must be a TreeNode that is not null
 *  @return true if the node has no child
 */
bool ThreadedBST::isLeafNode(TreeNode *node) {
  if (node == nullptr) {
      std::cerr << "Error: cannot call isLeafNode() on nullptr" << std::endl;
      exit(EXIT_FAILURE);
  }
  // If the node has both left and right thread, it must bt a leaf node
  if (node->LeftThread && node->RightThread) {
    return true;
  }
  // If both the left and the right point to null, it must be a leaf node
  // This only happens when the root is the only node in the tree
  if (node->Left == nullptr && node->Right == nullptr) {
    return true;
  }
  // If one side of the node points to null, the node is a leaf node
  // only when the other side is a thread
  if (node->Left == nullptr) {
    return (node->RightThread);
  }
  if (node->Right == nullptr) {
    return (node->LeftThread);
  }

  // All checks failed, the node has at least 1 child
  return false;
}

/** Function to delete a node that has value equals to data
 *  Postcon:  if data exists in the tree, it is removed.
 *  @return true if deletion is successful, false if node is not found
 */
bool ThreadedBST::remove(int data) {
  if (root == nullptr) {
    std::cout << "Warning: trying to call remove() on an empty tree"
              << std::endl;
    return false;
  }

  // CASE 1: The target node is the only node in the tree
  if (data == root->Value && isLeafNode(root)) {
    // This is an easy job, just delete the root
    delete root;
    root = nullptr;
    return true;
  }

  // Set up variables to store the result of retrieve();
  TreeNode *Node = root;
  TreeNode *Parent = nullptr;

  if (!retrieve(data, &Node, &Parent)) {
    std::cout << "remove(): " << data
              << " not found in the tree, deletion failed" << std::endl;
    // If retrieve() returns false it means the node is not in the tree
    // deletion failed
    return false;
  }

  // CASE 2: The target node has at least 1 child

  /*
  Idea: we replace the content of the node with either the inorder successor
  or the inorder predecessor (depending on what's available) of the node.
  Then, if the descendant we used to replace is a leaf node, we can just jump to
  case 3
  However, if the descendant we used is not a leaf node (case 2 again), we keep
  swaping it
  with its own inorder successor/predecessor, until we reach a leaf node, then
  we can proceed
  to case 3.
  */

  // temporary vaiables for swapping
  TreeNode *Dummy;
  int Temp;
  while (!isLeafNode(Node)) {
    if (Node->RightThread || Node->Right == nullptr) {
      // if the node doesn't have a right child, we go left once
      // then keep going right to find the inorder predeccessor
      Temp = rightMostNode(Node->Left)->Value;
    } else { // the node has a right child
      // we go right once and keep going left to find the
      // inorder successor
      Temp = leftMostNode(Node->Right)->Value;
    }
    // we save the reference to the node first
    Dummy = Node;
    // we then find the next node to be swapped or deleted
    retrieve(Temp, &Node, &Parent);
    // we then set the original node to be the new value
    Dummy->Value = Temp;
  }

  // CASE 3: The target node is a leaf node, we simply call deleteLeafNode()
  deleteLeafNode(Node, Parent);
  return true;
}

/** Function to delete a node that is a leaf node
 *  Precon:   node needs to be tested with isLeafNode() to verify it is 
 *            indeed a leaf node.
 *            if a non-null parent is passed in, it must be the direct
 *            parent of node.
 *  Postcon:  node is deleted from the tree.
 *  @param node the node that needs to be deleted. It MUST be a leaf node
 *  @param parent the parent of node. It MUST be either the parent,
 *  or nullptr to indicate the node to be delted is the root.
 */
void ThreadedBST::deleteLeafNode(TreeNode *node, TreeNode *parent) {
  if (node == nullptr || !isLeafNode(node)) {
    // Attempting to delete a nullptr or something that's not a leaf node, this
    // is not allowed
    std::cerr
        << "Error: calling deleteLeafNode() on a node that is not a leaf node"
        << std::endl;
    exit(EXIT_FAILURE);
  }

  if (parent != nullptr) { // We are not at the root of the tree

    if (node != parent->Left && node != parent->Right) {
      // The node is neither the left child or the right child of the parent,
      // this shouldn't happen
      std::cerr
          << "Error: in deleteLeafNode(), the parent and the node doesn't match"
          << std::endl;
      exit(EXIT_FAILURE);
    }

    // The target node is on the left side of its parent
    if (parent->Left == node) {
      parent->Left = node->Left;
      parent->LeftThread = (parent->Left != nullptr);
    }
    // The target node is on the right side of its parent
    else {
      parent->Right = node->Right;
      parent->RightThread = (parent->Right != nullptr);
    }

    node->Left = nullptr;
    node->Right = nullptr;
  }

  delete node;
}

/** Function to delete the subtree rooted at node.
 *  Uses postorder traversal so that every deletion is deleting
 *  a leaf node to achieve better efficiency
 *  Postcon:  The tree becomes empty.
 *  @param node the root of the subtree that needs to be deleted
 *  @param parent the parent of node, use nullptr if node is the root
 *  of the whole tree
 */
void ThreadedBST::postOrderDelete(TreeNode *node, TreeNode *parent) {
  if (node == nullptr) {
    // nothing should happen when we clear an empty tree
    return;
  }

  // delete the left subtree
  if (!node->LeftThread && node->Left != nullptr) {
    postOrderDelete(node->Left, node);
  }
  // delete the right subtree
  if (!node->RightThread && node->Right != nullptr) {
    postOrderDelete(node->Right, node);
  }

  deleteLeafNode(node, parent);
  // deleteLeafNode will help catch errors like node node and parent doesn't
  // match
}

// function to wipe everything from the tree
void ThreadedBST::clear() {
  postOrderDelete(root, nullptr);
  root = nullptr;
}

// Begin for iterator
const ThreadedBST::Iterator ThreadedBST::begin() const {
  return ThreadedBST::Iterator(leftMostNode(root));
}

// End for Iterator
const ThreadedBST::Iterator ThreadedBST::end() const {
  return ThreadedBST::Iterator(nullptr);
}

//-------------------------------------------------------------------
// iterator function:

// Step forward
ThreadedBST::Iterator ThreadedBST::Iterator::operator++() {
  if (current != nullptr) {
    if (current->RightThread) {
      current = current->Right;
    } else {
      current = leftMostNode(current->Right);
    }
  } else {
    std::cout << "cannot increment iterator pass the end" << std::endl;
  }
  return *this;
}

// Step backward
ThreadedBST::Iterator ThreadedBST::Iterator::operator--() {
  if (current != nullptr) {
    if (current->LeftThread) {
      current = current->Left;
    } else {
      current = rightMostNode(current->Left);
    }
  } else {
    std::cout << "trying to decrement invalid iterator" << std::endl;
  }
  return *this;
}

// Dereferncing overload
int &ThreadedBST::Iterator::operator*() const {
  if (current == nullptr) {
    std::cerr << "Error: Attempt to dereference invalid iterator. "
              << std::endl;
    exit(EXIT_FAILURE);
  }
  return current->Value;
}

// Overloads to test iterators' equality
bool ThreadedBST::Iterator::operator==(const Iterator &rhs) const {
  return (current == rhs.current);
}

// Overload to test iterators' inequality
bool ThreadedBST::Iterator::operator!=(const Iterator &rhs) const {
  return (current != rhs.current);
}
