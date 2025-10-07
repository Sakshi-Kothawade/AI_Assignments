#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<string, vector<string>> parents;

// getChildren     vector<string>
// isParent        bool
// getSiblings     vector<string>
// getGrandparents vector<string>
// findAncestors   void (helper for getAncestors)
// getAncestors    vector<string>
// printVector     void (cout)

vector<string> getChildren(string person){
    if(parents.find(person) != parents.end()){
        return parents[person];
    }
    return vector<string>();
}

bool isParent(string parent, string child){
    vector<string> children;
    if(parents.find(parent) != parents.end()){
        children = parents[parent];
    }
    for(string it : children){
        if(it == child){
            return true;
        }
    }
    return false;
}

vector<string> getSiblings(string person){
    vector<string> siblings;
    bool found = false;
    string parentName = "";

    for(auto &entry : parents){
        string p = entry.first;
        vector<string> children = entry.second;
        
        for(string child : children){
            if(person == child){
                parentName = p;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if(found){
        vector<string> tempSiblings = parents[parentName];
        for(int i=0; i<tempSiblings.size(); i++){
            if(tempSiblings[i] != person){
                siblings.push_back(tempSiblings[i]);
            }
        }
    }
    return siblings;
}

vector<string> getGrandparents(string person){
    vector<string> grandParents;
    for(auto &entry : parents){
        string possibleGrandParent = entry.first;
        vector<string> children = entry.second;
        
        for(int j=0; j<children.size(); j++){
            if(isParent(children[j], person)){
                grandParents.push_back(possibleGrandParent);
            }
        }
    }
    return grandParents;
}

void findAncestors(string person, vector<string> &ancestors){
    for(auto &entry : parents){
        string parent = entry.first;
        vector<string> children = entry.second;
        
        for(int i=0; i<children.size(); i++){
            if(children[i] == person){
                ancestors.push_back(parent);
                findAncestors(parent, ancestors);
            }
        }
    }
}

vector<string> getAncestors(string person){
    vector<string> ancestors;
    findAncestors(person, ancestors);
    return ancestors;
}

void printVector(vector<string> v){
    if(v.size() == 0){
        cout << "Empty Vector" << endl;
        return;
    }
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(){
    
    // Parent --> Children
    
    parents["Dutch"] = {"Arthur", "John", "Micha"};
    parents["John"] = {"Jack"};
    parents["Arthur"] = {"Arthur Jr.1", "Arthur Jr.2"};
    
    cout << "Children of Dutch: ";
    printVector(getChildren("Dutch"));
    
    cout << "Siblings of John: ";
    printVector(getSiblings("John"));
    
    cout << "Grandparents of Jack: ";
    printVector(getGrandparents("Jack"));
    
    cout << "Ancestors of Jack: ";
    printVector(getAncestors("Jack"));
    
    return 0;
}