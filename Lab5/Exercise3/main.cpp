#include<iostream>
#include<list>

using namespace std;

int main() {
    list<int> l;

    l.push_back(1);
    l.push_back(3);
    l.push_back(5);
    l.push_back(7);
    l.push_back(9);

    l.push_front(2);
    l.push_front(4);
    l.push_front(6);
    l.push_front(8);
    l.push_front(10);

    cout << "first element: " << l.front() << " last element: " << l.back() << endl;

    l.remove(3);
    l.sort();

    for(auto num : l) {
        cout << num << " ";
    }
    cout << endl;

    l.remove_if([](int num) { return num % 2 != 0; });

    for(auto num : l) {
        cout << num << " ";
    }
    cout << endl;
}