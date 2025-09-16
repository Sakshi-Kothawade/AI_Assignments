#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Rule {
    vector<string> conditions; 
    string conclusion;         
};

bool forwardChaining(vector<Rule> rules, set<string> facts, string goal) {
    bool newFactAdded = true;

    while (newFactAdded) {
        newFactAdded = false;

        for (auto &rule : rules) {
            bool allConditionsTrue = true;

            for (auto &cond : rule.conditions) {
                if (facts.find(cond) == facts.end()) {
                    allConditionsTrue = false;
                    break;
                }
            }

            if (allConditionsTrue && facts.find(rule.conclusion) == facts.end()) {
                cout << "Inferred: " << rule.conclusion << " from rule.\n";
                facts.insert(rule.conclusion);
                newFactAdded = true;

                if (rule.conclusion == goal) {
                    cout << "Goal " << goal << " reached!\n";
                    return true;
                }
            }
        }
    }

    cout << "Goal " << goal << " NOT reached.\n";
    return false;
}

int main() {
    vector<Rule> rules = {
        {{"A"}, "B"},      
        {{"B", "C"}, "D"},   
        {{"D"}, "E"}        
    };

    set<string> facts = {"A", "C"};

    string goal = "E";

    cout << "Forward Chaining Inference:\n";
    forwardChaining(rules, facts, goal);

    return 0;
}
