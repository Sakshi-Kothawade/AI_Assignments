#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Knowledge Base: parent -> list of children
map<string, vector<string>> parents;

// Get children of a person
vector<string> getChildren(string person) {
    if (parents.find(person) != parents.end()) {
        return parents[person];
    }
    return vector<string>();
}

// Check if X is parent of Y
bool isParent(string parent, string child) {
    if (parents.find(parent) != parents.end()) {
        vector<string> kids = parents[parent];
        for (int i = 0; i < kids.size(); i++) {
            if (kids[i] == child) {
                return true;
            }
        }
    }
    return false;
}

// Get siblings of a person
vector<string> getSiblings(string person) {
    vector<string> siblings;
    for (map<string, vector<string>>::iterator it = parents.begin(); it != parents.end(); it++) {
        vector<string> kids = it->second;
        bool found = false;
        for (int i = 0; i < kids.size(); i++) {
            if (kids[i] == person) {
                found = true;
                break;
            }
        }
        if (found) {
            for (int i = 0; i < kids.size(); i++) {
                if (kids[i] != person) {
                    siblings.push_back(kids[i]);
                }
            }
        }
    }
    return siblings;
}

// Get grandparents of a person
vector<string> getGrandparents(string person) {
    vector<string> grandparents;
    for (map<string, vector<string>>::iterator it = parents.begin(); it != parents.end(); it++) {
        string possibleGrandparent = it->first;
        vector<string> children = it->second;
        for (int i = 0; i < children.size(); i++) {
            if (isParent(children[i], person)) {
                grandparents.push_back(possibleGrandparent);
            }
        }
    }
    return grandparents;
}

// Recursive: get ancestors of a person
void findAncestors(string person, vector<string> &ancestors) {
    for (map<string, vector<string>>::iterator it = parents.begin(); it != parents.end(); it++) {
        string possibleParent = it->first;
        vector<string> children = it->second;
        for (int i = 0; i < children.size(); i++) {
            if (children[i] == person) {
                ancestors.push_back(possibleParent);
                findAncestors(possibleParent, ancestors);
            }
        }
    }
}

vector<string> getAncestors(string person) {
    vector<string> ancestors;
    findAncestors(person, ancestors);
    return ancestors;
}

// Helper: print results
void printVector(vector<string> v) {
    if (v.size() == 0) {
        cout << "None";
    } else {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
    }
    cout << endl;
}

// Main program
int main() {
    // Knowledge base: parent -> children
    parents["john"] = {"mary", "david"};
    parents["susan"] = {"mary", "david"};
    parents["mary"] = {"alice", "bob"};

    cout << "Children of John: ";
    printVector(getChildren("john"));

    cout << "Siblings of Mary: ";
    printVector(getSiblings("mary"));

    cout << "Grandparents of Alice: ";
    printVector(getGrandparents("alice"));

    cout << "Ancestors of Bob: ";
    printVector(getAncestors("bob"));

    return 0;
}
