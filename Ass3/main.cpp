#include <cassert>
#include <iostream>
#include <sstream>

#include "creature.h"
#include "maze.h"


void test() {
    Maze M("maze.txt");
    Creature C(4, 4);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;
    cout << endl;
}

void test1() {
    Maze M1("maze1.txt");
    Creature C1(5, 5);

    stringstream Sstrm;
    Sstrm << C1;
    assert(Sstrm.str() == "C(5, 5)");
    Sstrm.str("");

    Sstrm << C1.solve(M1);
    assert(Sstrm.str() == "EEEEEEEEEEENNWWWWWWWWWWWWWSSSSEEEEEEEEEEEEEEENNNNNNWWWWWWWWWWWWWWWWWSSSSSSSSEEEEEEEEEEEEEEEEEE");
    cout << "Path: " << Sstrm.str() << endl;
    Sstrm.str("");

    Sstrm << C1;
    assert(Sstrm.str() == "C(9, 19)");
    Sstrm.str("");

    cout << M1 << endl;
    cout << "Test for maze1 completed." << endl;
    cout << endl;
}
void test2() {
    Maze M2("maze2.txt");
    Creature C2(1, 1);

    stringstream Sstrm;
    Sstrm << C2;
    assert(Sstrm.str() == "C(1, 1)");
    Sstrm.str("");

    Sstrm << C2.solve(M2);
    assert(Sstrm.str() == "SSSSEEEENNNNEESSSSEEEESSEEEESSEESSEEEESSWWSSEEEEEEEESSSSSSWWWWWWSSSSSSWWSSEESSSSEESSEESSSSSSSSSSEESSSSEEEESSEEEEEESSSSEEEESSEEEENNNNEESSEEEEEESSEESSEEEEE");
    cout << "Path: " << Sstrm.str() << endl;
    Sstrm.str("");

    Sstrm << C2;
    assert(Sstrm.str() == "C(59, 60)");
    Sstrm.str("");

    cout << M2 << endl;
    cout << "Test for maze2 completed." << endl;
    cout << endl;
}

void test3() {
    // This is a map with no exit, this test is here to illustrate that
    // the function returns an empty string and leaves the creature
    // at the starting position
    Maze M3("maze3.txt");
    Creature C3(4, 6);

    stringstream Sstrm;
    Sstrm << C3;
    assert(Sstrm.str() == "C(4, 6)");
    Sstrm.str("");

    Sstrm << C3.solve(M3);
    assert(Sstrm.str().empty());
    Sstrm.str("");

    Sstrm << C3;
    assert(Sstrm.str() == "C(4, 6)");
    Sstrm.str("");

    cout << M3 << endl;
    cout << "Test for maze3 completed." << endl;
    cout << endl;
}

int main() {
    test();
    test1();
    test2();
    test3();
    cout << "Done!" << std::endl;
    return 0;
}