#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// int collatz(int n);
class NodeTest1 {
    public:
        static int NodeCount;
        int Value;
        NodeTest1 *Next;
        
        explicit NodeText1(int Value = 0, NodeTest1 *Next = nullptr):
        Value{Value}, Next{Next} {
            ++NodeCount;
        }

        ~NodeTest1() {
            --NodeCount;
        }
};

NodeTest1 test1(NodeTest1*& aNode) {
    NodeTest1 N1(1);
    NodeTest1 *N1Ptr;
    N1Ptr = N1;
    aNode = &N1Ptr;
    assert(N1Ptr == nullptr);
    auto *N2Ptr = new NodeTest1(3);
    auto *N3Arr = new NodeTest1[10];
    for (int i = 0; i < 5; i++) {
        NodeTest1 tmp(i*i);
        N3Arr[i] = tmp;
    }
    delete N1;
    return aNode;
}
int main() {
    NodeTest1* nt1 = new NodeTest1();
    test1(nt1);
    // vector<int> vec;
    // for(int i = 1; i <= 5; ++i) {
    //     vec.push_back(rand() % 10 * 2);
    // }

    // for(auto it = vec.begin(); it != vec.end(); ++it) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    // for(int i = 1; i <= 5; ++i) {
    //     vec.push_back(rand() % 10 * 2 + 1);
    // }

    // sort(vec.begin(), vec.end());

    // for(auto it = vec.begin(); it != vec.end(); ++it) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    return 0;
}

// int collatz(int n) {
//     cout << "N: " << n << endl;
//     int next;
//     if (n== 1) {
//         cout << "done!" << endl;
//         return n;
//     }
//     if (n%2==0) {
//         next = collatz(n/2);
//     } else {
//         next = collatz(3*n+1);
//     }
//     cout << "N: " << n << "-> Next: " << next << endl;
//     return next;
// }