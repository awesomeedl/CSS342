#include <iostream>
using namespace std;

int myRoundingFunction(double a);

int main() 
{
    cout << 3.4 << " -> " << myRoundingFunction(3.4) << endl;
    cout << 3.6 << " -> " << myRoundingFunction(3.6) << endl;
    cout << -3.4 << " -> " << myRoundingFunction(-3.4) << endl;
    cout << -3.6 << " -> " << myRoundingFunction(-3.6) << endl;
}

int myRoundingFunction(double a) {
    int temp = (int)(a * 10);
    int result = temp / 10;
    temp %= 10;
    if(temp > 0)
    {
        return temp >= 5 ? result + 1 : result;
    }
    else
    {
        return temp >= -5 ? result : result - 1;
    }

}