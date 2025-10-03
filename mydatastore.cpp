//
// Created by Baron Wang on 10/2/25.
//

#include "mydatastore.h"
#include "util.h"

using namespace std;

mydatastore::mydatastore()
{
}

mydatastore::~mydatastore() {
    for (size_t i = 0; i < allProducts_.size(); i++) {
        delete allProducts_[i];
    }

    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); it++) {
        User* user = it->second;
        delete user;
    }
}

string mydatastore::normUser(const string& name) const {
    return convToLower(name);
}

void mydatastore::addUser(User* u) {
    if (u == nullptr) {
        return;
    }

    string username = convToLower(u->getName());
    users_[username] = u;

    if (carts_.find(username) == carts_.end()) {
        carts_[username] = vector<Product*>();
    }
}

vector<Product*> mydatastore::search(vector<string>& items, int type) {
    vector<string> normalizedTerms = items;
    for (vector<string>::iterator it = normalizedTerms.begin(); it != normalizedTerms.end(); it++) {
        *it = convToLower(*it);
    }
    if (normalizedTerms.empty()) {
        lastHits_.clear();
        return lastHits_;
    }

    set<Product*> accum;

    if (type == 0) {
        map<string, set<Product*> >::iterator it0 = keywordIndex_.find(normalizedTerms[0]);
        if (it0 != keywordIndex_.end()) {
            accum = it0->second;
        } else {
            accum.clear();
        }

        for (size_t i = 1; i < normalizedTerms.size();i++) {
            map<string, set<Product*> >::iterator jt = keywordIndex_.find(normalizedTerms[i]);

            set<Product*> tmp;  // 临时变量
            if (jt != keywordIndex_.end()) {
                tmp = jt->second;
            } else {
                tmp.clear();
            }

            accum = setIntersection(accum, tmp);

            if (accum.empty()) break;
        }
    } else {
        accum.clear();
        for (size_t i = 0; i < normalizedTerms.size(); i++) {
            map<string, set<Product*> >::iterator jt = keywordIndex_.find(normalizedTerms[i]);
            if (jt != keywordIndex_.end()) {
                set<Product*> tmp = jt->second;
                accum = setUnion(accum, tmp);
            }
        }

    }
    vector<Product*> hits;
    for (set<Product*>::iterator it = accum.begin(); it != accum.end(); it++) {
        hits.push_back(*it);
    }
    lastHits_ = hits;
    return hits;
}

void mydatastore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (size_t i = 0; i < allProducts_.size(); i++) {
        allProducts_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); it++) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void mydatastore::indexProduct(Product* p)
{
    if (p == nullptr) {
        return;
    }
    set<string> keys = p->keywords();
    for (set<string>::iterator it = keys.begin(); it != keys.end(); it++) {
        string k = convToLower(*it);
        keywordIndex_[k].insert(p);
    }
}

void mydatastore::addProduct(Product* p) {
    if (p == nullptr) {
        return;
    }

    allProducts_.push_back(p);
    indexProduct(p);
}

void mydatastore::setLastHits(const vector<Product*>& hits)
{
    lastHits_ = hits;
}

int mydatastore::addToCart(const string& username, int hitIndex)
{
    // 0 = OK，1 = Invalid username，2 = Invalid request
    string u = normUser(username);

    if (users_.find(u) == users_.end()) {
        return 1;
    }
    if (hitIndex <= 0 || (size_t)hitIndex > lastHits_.size()) {
        return 2;
    }
    Product* p = lastHits_[hitIndex - 1];
    carts_[u].push_back(p);
    return 0;
}

void mydatastore::viewCart(const string& username, ostream& os)
{
    string u = normUser(username);
    if (users_.find(u) == users_.end()) {
        os << "Invalid username" << endl;
        return;
    }
    vector<Product*>& cart = carts_[u];
    for (size_t i = 0; i < cart.size(); ++i) {
        os << "Item " << (i + 1) << endl;
        os << cart[i]->displayString() << endl;
        os << endl;
    }
}

void mydatastore::buyCart(const string& username)
{
    string u = normUser(username);
    if (users_.find(u) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    User* usr = users_[u];
    vector<Product*>& cart = carts_[u];

    vector<Product*> remain;
    for (size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];
        if (p->getQty() > 0 && usr->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            usr->deductAmount(p->getPrice());
        } else {
            remain.push_back(p);
        }
    }
    cart.swap(remain);
}
