//
// Created by Baron Wang on 10/2/25.
//

#ifndef CLOTHING_H
#define CLOTHING_H
#include <string>
#include "product.h"

using namespace std;


class Clothing: public Product {
public:
    Clothing(string name, double price, int qty, string size, string brand);

    virtual set<string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(ostream& os) const;

private:
    string size_;
    string brand_;
};



#endif //CLOTHING_H
