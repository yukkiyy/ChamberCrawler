#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "observer.h"
#include <string>
#include <vector>
#include <iostream>

class Dungeon;

class TextDisplay : public Observer {
    Dungeon *dungeon;
    // only store current level
    std::vector<std::vector<char>> display;
    std::vector<std::string> actions;
    
    
    // welcome.txt
    std::vector<std::string> welcome_msg;
    // welcome_c.txt
    std::vector<std::string> welcome_c_msg;
    // welcome_e.txt
    std::vector<std::string> welcome_e_msg;
    // won.txt
    std::vector<std::string> won_msg;
    const std::string won_0_4 = "You need to improve your gaming talent :)";
    const std::string won_5_9 = "WELL DONE! You can do even better next time.";
    const std::string won_10 = "You are such a master! AMAZING!";
    // lost.txt
    std::vector<std::string> lost_msg;
    
    
    void updateDisplay();
    
    void printDisplay(std::ostream &out) const;
    
    void printWelcome(std::ostream &out) const;
    void printWelcomeCommandline(std::ostream &out) const;
    void printWelcomeCursor(std::ostream &out) const;
    void printGame(std::ostream &out) const;
    void printSummary(std::ostream &out) const;
public:
    TextDisplay();
    void notify(const std::string &action) override;
    void setDungeon(Dungeon *dungeon);
    
    friend std::ostream &operator<<(std::ostream &out, TextDisplay &td);
};

#endif
