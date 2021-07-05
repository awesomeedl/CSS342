/*
 * ArrayDemo
 *
 * Created by Rob Nash
 *
 * Modified by Yang Peng on 01/09/18
 */

#include <iostream>
using namespace std;

// Forward declarations.
void display(int* data, int size);
// void bubble(int data[], int size);
void bubble(int* ptr, int size);
// void swap(int data[], int idx1, int idx2);
void swap(int* ptr1, int* ptr2);
int linearSearch(int* data, int size, int target);

int main(int argc, const char * argv[])
{
  const int SIZE = 7;
  // These are auto variables.
  // int set[] = {1,4,3,2,5,9,8}; // Size implicit
  // int set2[] = {30, 23, 25, 19, 100, 12, 7};
  // How does it look like in JAVA?
  // int[] myArray = new int[3];
  // int[] myArray = {1, 2, 3};
  // int[] myArray = new int[] {1, 2, 3};

  int* set = new int[SIZE] {1,4,3,2,5,9,8};
  int* set2 = new int[SIZE] {30, 23, 25, 19, 100, 12, 7};

  // Testing linear search
  cout << "Result of linearSearch: " << endl;
  cout << "Expected 5, got " << linearSearch(set, SIZE, 9) << endl;
  cout << "Expected -1, got " << linearSearch(set, SIZE, 10) << endl;  

  // You have to pass the size in; a C++ array is just a dumb block of
  // storage; no size information is carried with it and no bounds
  // checking is done.
  display(set, SIZE);
  bubble(set, SIZE);
  display(set, SIZE);

  delete[] set;
  set = nullptr;
  delete[] set2;
  set2 = nullptr;
    
  return 0;
}

void display(int* data, int size) {
  for(int i = 0; i < size; i++) {
    cout << data[i] << ",";
  }
  cout << std::endl;
}

// void bubble(int data[], int size) {
//   for(int i = 0; i < size; i++) {
//     for(int k = 0; k < size - 1 - i; k++) {
//       if(data[k] < data[k+1]) {
// 		  swap(data, k, k+1);
//       }
//     }
//   }
// }

void bubble(int* ptr, int size) {
  for(int i = 0; i < size; i++) {
    for(int k = 0; k < size - 1 - i; k++) {
      if(*(ptr + k) < *(ptr + k + 1)) {
        swap((ptr + k), (ptr + k + 1));
      }
    }
  }
}

// void swap(int data[], int idx1, int idx2) {
//   int temp = data[idx1];
//   data[idx1] = data[idx2];
//   data[idx2] = temp;
// }

void swap(int* ptr1, int* ptr2) {
  int temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}

int linearSearch(int* data, int size, int target) {
  for(int i = 0; i < size; i++) {
    if(data[i] == target) return i;
  }
  return -1;
}
 
