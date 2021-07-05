/*
 * CopyAssignTest
 
 * Created by Michael Stiber
 * Modified by Yang Peng on 01/15/2018
 */

#include <iostream>
#include "MyClass.h"
#include "MySubClass.h"

using namespace std;

int main(int argc, char** argv)
{
	// create object m1 using default constructor
    MyClass m1;
	// update data members
    m1.setD(3.14159);
    m1.setI(42);
    m1.setS("This is a test");
    m1.setIp(7);

    cout << "m1 values:" << endl;
    cout << '\t' << m1.getD() << ", " << m1.getI() << ", " << m1.getS() 
         << ", " << m1.getIp() << endl;

	// create object m2 from m1 using copy constructor
    MyClass m2(m1);
    cout << "m2 values:" << endl;
    cout << '\t' << m2.getD() << ", " << m2.getI() << ", " << m2.getS() 
         << ", " << m2.getIp() << endl;

	// create object m3 from m1 using assignment operator
	MyClass m3 = m1;
    cout << "m3 values:" << endl;
    cout << '\t' << m3.getD() << ", " << m3.getI() << ", " << m3.getS() 
         << ", " << m3.getIp() << endl;

	// update m2's data
    m2.setD(1.7172);
    m2.setI(100);
    m2.setS("This is a NEW test");
    m2.setIp(8);
	// copy m2 to m1
    m1 = m2;
    cout << "m1 values:" << endl;
    cout << '\t' << m1.getD() << ", " << m1.getI() << ", " << m1.getS() 
         << ", " << m1.getIp() << endl;
	// only update m2's data IP which is using dynamically allocated memory
    m2.setIp(23);
    cout << "m1 values:" << endl;
    cout << '\t' << m1.getD() << ", " << m1.getI() << ", " << m1.getS() 
         << ", " << m1.getIp() << endl;
    cout << "m2 values; last should be different:" << endl;
    cout << '\t' << m2.getD() << ", " << m2.getI() << ", " << m2.getS() 
         << ", " << m2.getIp() << endl;

    // Testing MySubClass
    MySubClass s3;
    s3.setD(9.99);
    s3.setI(20);
    s3.setS("This is a subclass test");
    s3.setIp(12);
    s3.setData(999);

    MySubClass s4(s3);

    MySubClass s5;
    s5 = s4;

    cout << "s3 values:" << endl;
    cout << '\t' << s3.getD() << ", " << s3.getI() << ", " << s3.getS() 
         << ", " << s3.getIp() << ", " << s3.getData() << endl;
    cout << "s4 values:" << endl;
    cout << '\t' << s4.getD() << ", " << s4.getI() << ", " << s4.getS() 
         << ", " << s4.getIp() << ", " << s4.getData() << endl;
    cout << "s5 values:" << endl;
    cout << '\t' << s5.getD() << ", " << s5.getI() << ", " << s5.getS() 
         << ", " << s5.getIp() << ", " << s5.getData() << endl;



    return 0;
}
