#include <iostream>
#include <map>

using namespace std;

int main() {
    map<string, int> myMap;
    myMap.insert(pair<string, int>("Apple", 10));
    myMap.insert(pair<string, int>("Orange", 8));
    myMap.insert(pair<string, int>("Strawberry", 3));
    myMap.insert(pair<string, int>("Pineapple", 16));
    myMap.insert(pair<string, int>("Pear", 5));
    
    for(auto it =  myMap.begin(); it != myMap.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    cout << endl;

    myMap.insert({"Orange", 20}); // Doesn't work
    cout << "Orange: " << myMap["Orange"] << endl; 
    myMap.insert({"Banana", 15});
    cout << "Banana: " << myMap["Banana"] << endl;

    cout << endl;


    // Updating values with key does not exist already
    myMap["Grapes"] = 30; // Works
    //myMap.insert({"Grapes", 30}); // Also Works

    // Updating values with key already exists
    myMap["Orange"] = 20; // Works
    //myMap.insert(pair<string, int>("Orange", 20)); // does NOT work

    for(auto it =  myMap.begin(); it != myMap.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}