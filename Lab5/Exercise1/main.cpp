#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "Integers" << endl;
    cout << "Largest value for int: " << endl;
    cout << numeric_limits<int>::max() << endl;
    cout << "Smallest value for int: " << endl;
    cout << numeric_limits<int>::min() << endl;
    cout << numeric_limits<int>::lowest() << endl;
    cout << "--------------" << endl;
    cout << endl;
    cout << "Unsigned Integers" << endl;
    cout << "Largest value for unsigned int: " << endl;
    cout << numeric_limits<unsigned int>::max() << endl;
    cout << "Smallest value for unsigned int: " << endl;
    cout << numeric_limits<unsigned int>::min() << endl;
    cout << numeric_limits<unsigned int>::lowest() << endl;
    cout << "--------------" << endl;
    cout << endl;
    cout << "Long" << endl;
    cout << "Largest value for long: " << endl;
    cout << numeric_limits<long>::max() << endl;
    cout << "Smallest value for long: " << endl;
    cout << numeric_limits<long>::min() << endl;
    cout << numeric_limits<long>::lowest() << endl;
    cout << "--------------" << endl;
    cout << endl;
    cout << "Double" << endl;
    cout << "Largest value for double: " << endl;
    cout << numeric_limits<double>::max() << endl;
    cout << "Smallest value for double: " << endl;
    cout << numeric_limits<double>::min() << endl;
    cout << numeric_limits<double>::lowest() << endl;
    cout << "--------------" << endl;
    cout << endl;
    cout << "Float" << endl;
    cout << "Largest value for float: " << endl;
    cout << numeric_limits<float>::max() << endl;
    cout << "Smallest value for float: " << endl;
    cout << numeric_limits<float>::min() << endl;
    cout << numeric_limits<float>::lowest() << endl;
    cout << "--------------" << endl;


    

    return 0;
}