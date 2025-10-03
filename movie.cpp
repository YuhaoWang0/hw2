//
// Created by Baron Wang on 10/2/25.
//

#include "movie.h"

#include <iomanip>

#include "util.h"
#include <sstream>
using namespace std;

Movie::Movie(string name, double price, int qty, string genre, string rating)
    : Product("movie", name, price, qty)
    ,genre_(genre), rating_(rating)
{
}

set<string> Movie::keywords() const {
    set<string> result;

    set<string> title = parseStringToWords(name_);
    
    result = setUnion(title, result);
    result.insert(convToLower(genre_));

    return result;
}

string Movie::displayString() const {
    ostringstream os;
    os << name_ << "\n"
    << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
    << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

    return os.str();
}

void Movie::dump(ostream& os) const {
    os << "movie" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << genre_ << endl;
    os << rating_ << endl;
}

