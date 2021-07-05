#include "ThreadedBST.h"
#include <iostream>
#include <limits>

using namespace std;

// Function to add values from 1 to n into the binary tree
void balancedAdd(int first, int last, ThreadedBST &tbst) {
  if (first > last)
    return;
  int Mid = (first + last) / 2;
  tbst.add(Mid);
  balancedAdd(first, Mid - 1, tbst);
  balancedAdd(Mid + 1, last, tbst);
}

int main() {
  int N;
  while(true) {
    cout << "Please enter a number (n > 0): ";
    if (cin >> N && N > 0) {
      break;
    } 

    if (N == -1) {
      exit(EXIT_SUCCESS);
    } 
    else {
        cout << "Please enter a valid integer (n > 0)." << endl;
        cout << "If you would like to exit, enter \"-1\"." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

  ThreadedBST Tbst;
  cout << "Tree 1 created." << endl;
  balancedAdd(1, N, Tbst);
  cout << "Tree 1 added from 1 to " << N << "." << endl;
  ThreadedBST Copy(Tbst);
  cout << "Copy of tree 1 created." << endl;

  for (auto It = Copy.begin(); It != Copy.end(); ++It) {
    int N = *It;
    if (N % 2 == 0) {
      --It; // We have to step back to make sure the node we used
            // to replace the deleted node is not a even number
      Copy.remove(N);
    }
  }
  cout << "Removed even numbers from copy." << endl;

  cout << "Final result: " << endl;
  cout << "Tree 1:\t\t" << Tbst << endl;
  cout << "Copy of Tree1:\t" << Copy << endl;
};
