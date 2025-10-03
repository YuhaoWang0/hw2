//
// Created by Baron Wang on 10/2/25.
//

#include "book.h"
#include <iomanip>
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const string name, double price, int qty, string isbn, string author)
    : Product("book", name,price, qty)
    , isbn_(isbn), author_(author)
{
}

set<string> Book::keywords() const {
    set<string> result;

    set<string> bookKeyWords = parseStringToWords(convToLower(name_));
    set<string> authorKeyWords = parseStringToWords(convToLower(author_));

    result = setUnion(bookKeyWords, authorKeyWords);
    result.insert(convToLower(isbn_));

    return result;
}

string Book::displayString() const {
    ostringstream os;
    os << name_ << "\n"
    << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
    << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

    return os.str();
}

void Book::dump(std::ostream& os) const {
    os << "book" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << isbn_ << endl;
    os << author_ << endl;
}



