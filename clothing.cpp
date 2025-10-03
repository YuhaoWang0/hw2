//
// Created by Baron Wang on 10/2/25.
//

#include "clothing.h"

#include <iomanip>

#include "util.h"
#include <sstream>
using namespace std;

Clothing::Clothing(string name, double price, int qty, string size, string brand)
    :Product("clothing", name, price, qty)
    ,size_(size), brand_(brand)
{
}

set<string> Clothing::keywords() const {
    set<string> result;
    set<string> ClothKeyWords = parseStringToWords(convToLower(name_));
    set<string> brandKeyWords = parseStringToWords(convToLower(brand_));
    result = setUnion(ClothKeyWords, brandKeyWords);

    return result;
}

string Clothing::displayString() const {
    ostringstream os;
    os << name_ << "\n"
    << "Size: " << size_ << " Brand: " << brand_ << "\n"
    << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

    return os.str();
}

void Clothing::dump(ostream& os) const {
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << size_ << endl;
    os << brand_ << endl;
}





