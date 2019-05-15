#include "textdisplay.h"
#include "dungeon.h"
#include "gamestate.h"
#include "cheating.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>


using namespace std;

void TextDisplay::updateDisplay() {
    for (int row = 0; row < 25; ++row) {
        for (int col = 0; col < 79; ++col) {
            display[row][col] = dungeon->getSymbol(row, col);
        }
    }
}

void TextDisplay::printDisplay(ostream &out) const {
    for (int row = 0; row < 25; ++row) {
        for (int col = 0; col < 79; ++col) {
            out << display[row][col];
        }
        out << endl;
    }
}

void TextDisplay::printWelcome(ostream &out) const {
    for (const string &s : welcome_msg) {
        out << s << endl;
    }
}

void TextDisplay::printWelcomeCommandline(ostream &out) const {
    for (const string &s : welcome_c_msg) {
        out << s << endl;
    }
}

void TextDisplay::printWelcomeCursor(ostream &out) const {
    for (const string &s : welcome_e_msg) {
        out << s << endl;
    }
}

void TextDisplay::printGame(ostream &out) const {
    printDisplay(out);
    out << "Race: " << setw(7) << left << dungeon->getPCRace();
    
    string goldstr;
    double gold = dungeon->getPCGold();
    if (gold == ceil(gold)) goldstr = to_string((int)gold);
    else {
        stringstream ss;
        ss << fixed << setprecision(1) << gold;
        goldstr = ss.str();
    }
    ;
    out << "Gold: " << setw(51) << left << goldstr;
    out << "Floor: " << dungeon->currentLevel()+1 << endl;
    
    out << "HP: " << setw(16) << left << dungeon->getPCHP();
    if (cheatmode) {
        out << setw(58) << right << "CHEATING";
    }
    out  << endl;
    out << "Atk: " << dungeon->getPCAtk() << endl;
    out << "Def: " << dungeon->getPCDef() << endl;
    
    string action = "Action:";
    for (const string &s : actions) {
        if (action.size() + s.size() > 79) {
            out << action << endl;
            //       "Action:"
            action = "       ";
        }
        action += " " + s;
    }
    
    out << action << endl;
}

void TextDisplay::printSummary(ostream &out) const {
    if (dungeon->getState() == GameState::WON) {
        for (int i = 0; i < 17; ++i) {
            out << won_msg[i] << endl;
        }
    }
    else {
        for (int i = 0; i < 17; ++i) {
            out << lost_msg[i] << endl;
        }
    }
    
    // print score
    double score = dungeon->getPCScore();
    string scorestr;
    // do not have fraction part
    if (score == ceil(score)) {
        scorestr = to_string((int)score);
    }
    else {
        stringstream ss;
        ss << fixed << setprecision(1) << score;
        scorestr = ss.str();
    }
    int before = (77 - (int)scorestr.size()) / 2;
    int after = 77 - (int)scorestr.size() - before;
    out << "|" << setw(before) << " ";
    out << scorestr << setw(after) << " " << "|" << endl;
    
    if (dungeon->getState() == GameState::WON) {
        for (int i = 18; i < 20; ++i) {
            out << won_msg[i] << endl;
        }
        
        string msg;
        if (score < 5) {
            msg = won_0_4;
        }
        else if (score < 10) {
            msg = won_5_9;
        }
        else { // score >= 10
            msg = won_10;
        }
        int b = (77 - (int)msg.size()) / 2;
        int a = 77 - (int)msg.size() - b;
        out << "|" << setw(b) << " ";
        out << msg << setw(a) << " " << "|" << endl;
        
        for (int i = 21; i < 30; ++i) {
            out << won_msg[i] << endl;
        }
    }
    else {
        for (int i = 18; i < 30; ++i) {
            out << lost_msg[i] << endl;
        }
    }
}

TextDisplay::TextDisplay()
: dungeon{nullptr}, display{25, vector<char>(79, ' ')} {
    
    string line;
    
    ifstream in_welcome{"welcome.txt"};
    while (getline(in_welcome, line)) welcome_msg.emplace_back(line);
    
    ifstream in_welcome_c{"welcome_c.txt"};
    while (getline(in_welcome_c, line)) welcome_c_msg.emplace_back(line);
    
    ifstream in_welcome_e{"welcome_e.txt"};
    while (getline(in_welcome_e, line)) welcome_e_msg.emplace_back(line);
    
    ifstream in_won{"won.txt"};
    while (getline(in_won, line)) won_msg.emplace_back(line);
    
    ifstream in_lost{"lost.txt"};
    while (getline(in_lost, line)) lost_msg.emplace_back(line);
}

void TextDisplay::notify(const string &action) {
    actions.emplace_back(action);
}

void TextDisplay::setDungeon(Dungeon *dungeon) {
    this->dungeon = dungeon;
}

ostream &operator<<(ostream &out, TextDisplay &td) {
    GameState state = td.dungeon->getState();
    if (state == GameState::START) {
        td.printWelcome(out);
    }
    else if (state == GameState::START_COMMANDLINE) {
        td.printWelcomeCommandline(out);
    }
    else if (state == GameState::START_CURSOR ||
             state == GameState::START_GRAPHICS) {
        td.printWelcomeCursor(out);
    }
    else if (state == GameState::INGAME) {
        td.updateDisplay();
        td.printGame(out);
    }
    else /* if (state == GameState::WON || state == GameState::LOST) */ {
        td.printSummary(out);
    }
    td.actions.clear();
    return out;
}

