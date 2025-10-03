//
// Created by Baron Wang on 10/2/25.
//

#ifndef BOOK_H
#define BOOK_H
#include <string>
#include "product.h"
#include <set>
#include <iostream>
#include "util.h"

using namespace std;

class Book : public Product {
public:
    Book(const string name, double price, int qty, string isbn, string author);

    virtual ~Book() {}

    virtual set<string> keywords() const;
    virtual string displayString() const;
    virtual void dump(ostream& os) const;

private:
    string isbn_;
    string author_;
};

#endif //BOOK_H
