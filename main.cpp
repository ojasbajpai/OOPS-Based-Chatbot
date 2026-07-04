#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

// Base class: Handles all chatbot logic
class Chatbot {
protected:
    string name;
    string filename;
    unordered_map<string, string> brain;

public:
    Chatbot(string botName, string file) : name(botName), filename(file) {
        loadResponses();
    }

    string toLowerCase(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    virtual void respond(string userInput) {
        string lowerInput = toLowerCase(userInput);
        bool found = false;

        for (auto const& [key, val] : brain) {
            if (lowerInput.find(key) != string::npos) {
                cout << "[" << name << "]: " << val << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "[" << name << "]: I don't understand that. Can you teach me?" << endl;
            string keyword, response;
            cout << "Enter a keyword: "; getline(cin, keyword);
            cout << "Enter the response: "; getline(cin, response);
            learn(keyword, response);
        }
    }

    void learn(string keyword, string response) {
        string cleanKeyword = toLowerCase(keyword);
        brain[cleanKeyword] = response;
        saveResponseToFile(cleanKeyword, response);
        cout << "I've learned that! Thanks." << endl;
    }

    void loadResponses() {
        ifstream infile(filename);
        string keyword, response;
        while (getline(infile, keyword) && getline(infile, response)) {
            if (!keyword.empty() && keyword.back() == '\r') keyword.pop_back();
            brain[toLowerCase(keyword)] = response;
        }
        infile.close();
    }

    void saveResponseToFile(string keyword, string response) {
        ofstream outfile(filename, ios::app);
        if (outfile.is_open()) {
            outfile << keyword << "\n" << response << "\n";
            outfile.close();
        }
    }
    string getName() { return name; }
};

// Inheritance: Specialized support bot
class EdTechSupportBot : public Chatbot {
public:
    EdTechSupportBot(string botName, string file) : Chatbot(botName, file) {}
};

// Composition: Separate support system
class LiveSupport {
public:
    void contactInfo() {
        cout << "[SUPPORT] Please email us at support@edtech.com or call +91 1800-000-123." << endl;
    }
};

// Derived Class: Uses both Inheritance and Composition
class FinalChatbot : public EdTechSupportBot {
private:
    LiveSupport liveSupport;
public:
    FinalChatbot(string botName, string file) : EdTechSupportBot(botName, file) {}
    void triggerLiveSupport() { liveSupport.contactInfo(); }
};

// Manager to handle multiple AI personas
class ChatbotManager {
private:
    vector<unique_ptr<Chatbot>> aiPool;
    Chatbot* activeAI;

public:
    ChatbotManager() {
        aiPool.push_back(make_unique<FinalChatbot>("Support", "support_memory.txt"));
        aiPool.push_back(make_unique<Chatbot>("Sales", "sales_memory.txt"));
        aiPool.push_back(make_unique<Chatbot>("Technical", "tech_memory.txt"));
        activeAI = aiPool[0].get();
    }

    void switchAI(string name) {
        for (auto& ai : aiPool) {
            if (ai->getName() == name) {
                activeAI = ai.get();
                cout << "Successfully switched to " << name << endl;
                return;
            }
        }
        cout << "AI persona not found." << endl;
    }

    void handleInput(string userInput) {
        string clean = activeAI->toLowerCase(userInput);
        
        // Robust command detection
        if (clean.find("change ai") != string::npos) {
            cout << "Available: Support, Sales, Technical. Enter name: ";
            string n; getline(cin, n);
            switchAI(n);
        } 
        else if (clean.find("support") != string::npos || clean.find("human") != string::npos) {
            auto* ptr = dynamic_cast<FinalChatbot*>(activeAI);
            if (ptr) ptr->triggerLiveSupport();
            else cout << "Live support is only available for the Support persona." << endl;
        } 
        else {
            activeAI->respond(userInput);
        }
    }
};

int main() {
    ChatbotManager manager;
    cout << "System Online. Type 'change ai' to switch personas, 'exit' to quit." << endl;
    string userInput;
    while (true) {
        cout << "\nYou: ";
        getline(cin, userInput);
        if (userInput == "exit") break;
        manager.handleInput(userInput);
    }
    return 0;
}