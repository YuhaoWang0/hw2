//
// Created by Baron Wang on 10/1/25.
//

#include "util.h"
using namespace std;

int main() {
    // util.cpp Test
    string input = "Men's Shirt, size M!";
    set<string> words = parseStringToWords(input);

    cout << "Parsed keywords:" << endl;

    for (set<string>::iterator it = words.begin(); it != words.end(); it ++) {
        cout << *it << endl;
    }

    // util.h Tests
    set<int> a;
    set<int> b;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    b.insert(2);
    b.insert(3);
    b.insert(4);
    set<int> unionSet = setUnion(a,b);
    set<int> intersectionSet = setIntersection(a,b);

    cout << "Union Test:" << endl;
    for (set<int>::iterator it = unionSet.begin(); it != unionSet.end(); it++) {
        cout << *it << endl;
    }
    cout << "Intersection Test:" << endl;
    for (set<int>::iterator it = intersectionSet.begin(); it != intersectionSet.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
