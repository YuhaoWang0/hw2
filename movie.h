//
// Created by Baron Wang on 10/2/25.
//

#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
using namespace std;

class Movie: public Product {
public:
    Movie(string name, double price, int qty, string genre, string rating);

    virtual set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    string genre_;
    string rating_;
};



#endif //MOVIE_H
