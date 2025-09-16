#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Rule {
    vector<string> conditions; 
    string conclusion;        
};

bool backwardChaining(vector<Rule> &rules, set<string> &facts, string goal) {
    if (facts.find(goal) != facts.end()) {
        cout << "Goal " << goal << " is a known fact.\n";
        return true;
    }

    for (auto &rule : rules) {
        if (rule.conclusion == goal) {
            cout << "To prove " << goal << ", need: ";
            for (auto &c : rule.conditions) cout << c << " ";
            cout << endl;

            bool allConditionsTrue = true;
            for (auto &condition : rule.conditions) {
                if (!backwardChaining(rules, facts, condition)) {
                    allConditionsTrue = false;
                    break;
                }
            }

            if (allConditionsTrue) {
                cout << "Therefore, " << goal << " is true.\n";
                facts.insert(goal);
                return true;
            }
        }
    }

    cout << "Cannot prove " << goal << ".\n";
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

    cout << "Backward Chaining Inference:\n\n";
    if (backwardChaining(rules, facts, goal))
        cout << "\nGoal " << goal << " has been proved!\n";
    else
        cout << "\nGoal " << goal << " cannot be proved.\n";

    return 0;
}
