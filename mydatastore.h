//
// Created by Baron Wang on 10/2/25.
//

#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class mydatastore: public DataStore {
public:
    mydatastore();
    virtual ~mydatastore();

    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
    virtual vector<Product*> search(vector<string>& item, int type);
    virtual void dump(ostream& ofile);

    void setLastHits(const vector<Product*>& hits);
    int addToCart(const string& username, int hitIndex);
    void viewCart(const string& username, ostream& os);
    void buyCart(const string& username);

private:
    map<string, set<Product*> > keywordIndex_;

    vector<Product*> allProducts_;

    map<string, User*> users_;

    map<string, vector<Product*>> carts_;

    vector<Product*> lastHits_;

    string normUser(const string& name) const;
    void indexProduct(Product* p);
};



#endif //MYDATASTORE_H
