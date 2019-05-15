#include "game.h"
#include "dungeon.h"
#include "textdisplay.h"

#include "direction.h"
#include "pctype.h"
#include "gamestate.h"

#include "playerdead.h"
#include "invalid.h"
#include "cheating.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <ncurses.h>

#include "utility.h"
#include "window.h"
#include <sys/time.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

bool Game::isDirectionKey(char c) const {
    return  (c == 'w') || (c == 'a') ||
            (c == 's') || (c == 'd') ||
            (c == '1') || (c == '3') ||
            (c == 'z') || (c == 'c');
}

Direction Game::keyToDirection(char c) const {
    if (c == 'w') return Direction::NO;
    if (c == 'a') return Direction::WE;
    if (c == 's') return Direction::SO;
    if (c == 'd') return Direction::EA;
    if (c == '1') return Direction::NW;
    if (c == '3') return Direction::NE;
    if (c == 'z') return Direction::SW;
    //  c == 'c'
    return Direction::SE;
}

void Game::printToCursor() {
    clear();
    stringstream ss;
    ss << td;
    string line;
    if (dungeon.getState() == GameState::INGAME) {
        for (int r = 0; r < 25 && getline(ss, line); ++r) {
            for (int c = 0; c < 79; ++c) {
                if (line[c] == '@' || line[c] == '\\') attron(A_BOLD);
                if (line[c] == '\\') attron(COLOR_PAIR(2));
                if (line[c] == '@') attron(COLOR_PAIR(3));
                if (line[c] == 'P') attron(COLOR_PAIR(4));
                if (line[c] == 'G') attron(COLOR_PAIR(5));
                
                mvaddch(r, c, line[c]);
                
                if (line[c] == '@' || line[c] == '\\') attroff(A_BOLD);
                if (line[c] == '\\') attroff(COLOR_PAIR(2));
                if (line[c] == '@') attroff(COLOR_PAIR(3));
                if (line[c] == 'P') attroff(COLOR_PAIR(4));
                if (line[c] == 'G') attroff(COLOR_PAIR(5));
            }
        }
        
        for (int r = 25; getline(ss, line); ++r) {
            mvaddstr(r, 0, line.c_str());
        }
        
        
    }
    else {
        for (int r = 0; r < 30 && getline(ss, line); ++r) {
            mvaddstr(r, 0, line.c_str());
        }
    }
    
    
    refresh();
}

void Game::playCommandline() {
    // welcome commandline
    cout << td;
    string cmd;
    while (cin >> cmd) {
        GameState state = dungeon.getState();
        
        if ((state == GameState::WON ||
             state == GameState::LOST) &&
            cmd != "r") {
            quitting = true;
            break;
        }
        
        string cmd2;
        if (cmd == "u" || cmd == "a") {
            cin >> cmd2;
        }
        
        // quit
        if (cmd == "q") {
            quitting = true;
            break;
        }
        // restart
        else if (cmd == "r") {
            dungeon.setState(GameState::START);
            break;
        }
        // set PC race
        else if (isPCType(cmd[0]) && state == GameState::START_COMMANDLINE) {
            dungeon.load(filename);
            dungeon.setPlayer(toPCType(cmd[0]));
        }
        else if (state == GameState::START_COMMANDLINE) {
            dungeon.load(filename);
            dungeon.setPlayer();
        }
        // move
        else if (isDirection(cmd)) {
            try {
                dungeon.move(toDirection(cmd));
                if (dungeon.getState() == GameState::INGAME) {
                    dungeon.enemyTurn();
                }
            } catch (Invalid &e) {}
        }
        // use
        else if (cmd == "u" && isDirection(cmd2)) {
            try {
                dungeon.use(toDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
            catch (PlayerDead &e) {}
        }
        // attack
        else if (cmd == "a" && isDirection(cmd2)) {
            try {
                dungeon.attack(toDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
        }
        else if (cmd == "MEOW" && state == GameState::INGAME) {
            cheatmode = !cheatmode;
            string msg = "WARNING! Cheating Mode has been ";
            msg += (cheatmode ? "ENABLED." : "DISABLED.");
            td.notify(msg);
        }
        else if (cmd == "TP" && state == GameState::INGAME && cheatmode) {
            td.notify("WARNING! Warp Drive active!");
            dungeon.transport();
        }
        else {
            td.notify("ERROR: Invalid Command!");
        }
        
        cout << td;
        
    }
}

void Game::playCursor() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    // '\\'
    init_pair(2, COLOR_RED, COLOR_BLACK);
    // '@'
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    // 'P'
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    // 'G'
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    // print welcome cursor page
    printToCursor();
    int cmd;
    while ((cmd = getch())) {
        GameState state = dungeon.getState();
        
        if ((state == GameState::WON ||
             state == GameState::LOST) &&
            cmd != 'r') {
            quitting = true;
            break;
        }
        
        int cmd2 = -1;
        //  attack        use
        if (cmd == 'j' || cmd == 'k') {
            cmd2 = getch();
        }
        
        // quit
        if (cmd == 'q') {
            quitting = true;
            break;
        }
        // restart
        else if (cmd == 'r') {
            dungeon.setState(GameState::START);
            break;
        }
        // random PC race
        else if (cmd == '/' && state == GameState::START_CURSOR) {
            dungeon.load(filename);
            dungeon.setPlayer(toPCType('?'));
        }
        // set PC race
        else if (isPCType(cmd) && state == GameState::START_CURSOR) {
            dungeon.load(filename);
            dungeon.setPlayer(toPCType(cmd));
        }
        else if (state == GameState::START_CURSOR) {
            dungeon.load(filename);
            dungeon.setPlayer();
        }
        // move
        else if (isDirectionKey(cmd)) {
            try {
                dungeon.move(keyToDirection(cmd));
                if (dungeon.getState() == GameState::INGAME) {
                    dungeon.enemyTurn();
                }
            } catch (Invalid &e) {}
        }
        // use
        else if (cmd == 'k' && isDirectionKey(cmd2)) {
            try {
                dungeon.use(keyToDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
            catch (PlayerDead &e) {}
        }
        // attack
        else if (cmd == 'j' && isDirectionKey(cmd2)) {
            try {
                dungeon.attack(keyToDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
        }
        else if (cmd == 'm' && state == GameState::INGAME) {
            if (getch() == 'e' && getch() == 'o' && getch() == 'w') {
                cheatmode = !cheatmode;
                string msg = "WARNING! Cheating Mode has been ";
                msg += (cheatmode ? "ENABLED." : "DISABLED.");
                td.notify(msg);
            }
            else {
                td.notify("WARNING! Cheating Mode failed!");
            }
        }
        else if (cmd == 't' && state == GameState::INGAME && cheatmode) {
            if (getch() == 'p') {
                td.notify("WARNING! Warp Drive active!");
                dungeon.transport();
            }
            else {
                td.notify("WARNING! Warp Drive failed!");
            }
        }
        else {
            td.notify("ERROR: Invalid Command!");
        }
        
        printToCursor();
    }
    
    endwin();
}

void Game::playGraphics() {
    // setup Xwindow
    Xwindow w;
    w.setDungeon(&dungeon);

    repaint(w);
    
    while (true) {
        char cmd = nextChar(w);
        char cmd2 = cmd;
        
        GameState state = dungeon.getState();
        
        if ((state == GameState::WON ||
            state == GameState::LOST) &&
            cmd != 'r') {
            quitting = true;
            break;
        }
        
        if (cmd == 'j' || cmd == 'k') cmd2 = nextChar(w);
        
        
        
        if (cmd == 'q') {
            quitting = true;
            break;
        }
        else if (cmd == 'r') {
            dungeon.setState(GameState::START);
            break;
        }
        else if (cmd == '/' && state == GameState::START_GRAPHICS) {
            dungeon.load(filename);
            dungeon.setPlayer(toPCType('?'));
        }
        else if (isPCType(cmd) && state == GameState::START_GRAPHICS) {
            dungeon.load(filename);
            dungeon.setPlayer(toPCType(cmd));
        }
        else if (state == GameState::START_GRAPHICS) {
            dungeon.load(filename);
            dungeon.setPlayer();
        }
        else if (isDirectionKey(cmd)) {
            try {
                dungeon.move(keyToDirection(cmd));
                if (dungeon.getState() == GameState::INGAME) {
                    dungeon.enemyTurn();
                }
            } catch (Invalid &e) {}
        }
        else if (cmd == 'j' && isDirectionKey(cmd2)) {
            try {
                dungeon.attack(keyToDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
        }
        else if (cmd == 'k' && isDirectionKey(cmd2)) {
            try {
                dungeon.use(keyToDirection(cmd2));
                dungeon.enemyTurn();
            } catch (Invalid &e) {}
            catch (PlayerDead &e) {}
        }
        else if (cmd == 'm' && state == GameState::INGAME) {
            if (nextChar(w) == 'e' &&
                nextChar(w) == 'o' &&
                nextChar(w) == 'w') {
                
                cheatmode = !cheatmode;
                string msg = "WARNING! Cheating Mode has been ";
                msg += (cheatmode ? "ENABLED." : "DISABLED.");
                td.notify(msg);
            }
            else {
                td.notify("WARNING! Cheating Mode failed!");
            }
        }
        else if (cmd == 't' && state == GameState::INGAME && cheatmode) {
            if (nextChar(w) == 'p') {
                td.notify("WARNING! Warp Drive active!");
                dungeon.transport();
            }
            else {
                td.notify("WARNING! Warp Drive failed!");
            }
        }
        else {
            td.notify("ERROR: Invalid Command!");
        }
        
        repaint(w);
    } // while (true)
}

void Game::repaint(Xwindow &w) {
    stringstream ss;
    ss << td;
    string line;
    
    w.clear();
    
    GameState state = dungeon.getState();
    
    if (state == GameState::INGAME) {
        w.drawDungeon();
        // skip the dungeon
        for (int i = 0; i < 25; ++i) getline(ss, line);
        // draw race gold floor line
        getline(ss, line);
        w.drawString(toCoordsX(0), toCoordsY(26), line.substr(0, 70));
        w.drawString(toCoordsX(77), toCoordsY(26), line.substr(70));
        getline(ss, line);
        if (line.length() > 70) {
            w.drawString(toCoordsX(0), toCoordsY(27), line.substr(0, 70));
            w.drawString(toCoordsX(77), toCoordsY(27), line.substr(70));
        }
        else {
            w.drawString(toCoordsX(0), toCoordsY(27), line);
        }
        getline(ss, line);
        w.drawString(toCoordsX(0), toCoordsY(28), line);
        getline(ss, line);
        w.drawString(toCoordsX(0), toCoordsY(29), line);
        
        string action;
        while (getline(ss, line)) {
            if (line[0] == ' ') {
                action += line.substr(7);
            }
            else {
                action += line;
            }
        }
        w.drawString(toCoordsX(0), toCoordsY(30), action);
    }
    else if (state == GameState::START_GRAPHICS) {
        w.drawWelcome();
    }
    else if (state == GameState::WON) {
        w.drawWon();
    }
    else if (state == GameState::LOST) {
        w.drawLost();
    }
}

char Game::nextChar(Xwindow &w) {
    Display *d = w.getDisplay();
    XEvent event;
    KeySym key;
    char text[BUFFERSIZE];
    
    while (true) {
        if (XPending(d) > 0) {
            XNextEvent(d, &event);
            if (event.type == KeyPress) {
                if (XLookupString((XKeyEvent *)&event,
                                  text, BUFFERSIZE, &key, 0)
                    == 1) {
                    return text[0];
                }
            }
        }
        
        if (XPending(d) == 0) {
            usleep((unsigned int)(ONESEC / FPS));
        }
    }
}

Game::Game(int argc, char **argv) : filename{"default.txt"}, quitting{false} {
    td.setDungeon(&dungeon);
    dungeon.setObserver(&td);
    
    srand((unsigned int)time(NULL));
    
    if (argc == 3) {
        filename = argv[1];
        int seed = stoi(argv[2]);
        srand(seed);
    }
    else if (argc == 2) {
        try {
            int seed = stoi(argv[1]);
            srand(seed);
        }
        catch (invalid_argument &e) {
            filename = argv[1];
        }
    }
}

void Game::play() {
    // welcome page
    cout << td;
    char cmd = ' ';
    
    while (cin >> cmd) {
        GameState state = dungeon.getState();
        if (state == GameState::START) {
            if (cmd == 'c') {
                dungeon.setState(GameState::START_COMMANDLINE);
                playCommandline();
            }
            else if (cmd == 'e') {
                dungeon.setState(GameState::START_CURSOR);
                playCursor();
            }
            else if (cmd == 'g') {
                dungeon.setState(GameState::START_GRAPHICS);
                playGraphics();
            }
            else if (cmd == 'r') {
                dungeon.restart();
            }
            else {
                quitting = true;
            }
        }
        
        if (quitting) break;
        // game restarted, reprint welcome page
        if (dungeon.getState() == GameState::START) {
            dungeon.restart();
            cout << td;
        }
    }
}


