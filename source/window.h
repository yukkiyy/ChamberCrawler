#ifndef __WINDOW_H__
#define __WINDOW_H__
#include "observer.h"
#include "constants.h"

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>

class Dungeon;

class Xwindow {
    Dungeon *dungeon;
    
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
    
    std::vector<Pixmap> icons;
    Pixmap won;
    Pixmap lost;
    
    XImage *welcome;
    
    std::vector<std::vector<char>> background;
    std::vector<std::vector<char>> foreground;
    
    int symbolToIndex(char c) const;
    int symbolToIndex(char f, char b) const;
    
    void checkPixmapError(int rc, int i);

public:
	Xwindow(int width=WIDTH, int height=HEIGHT);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	Xwindow(const Xwindow&) = delete;
	Xwindow &operator=(const Xwindow&) = delete;

	enum {White=0, Black, Red, Green, Blue}; // Available colours.

    void setDungeon(Dungeon *dungeon);
    
	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	// Draws a string
	void drawString(int x, int y, std::string msg);
    
    void drawDungeon();
    
    void drawWelcome();
    void drawWon();
    void drawLost();

    Display *getDisplay() const;
    
    void setForeground(int colour=Black);
    void setBackground(int colour=Black);
    
    void clear();
    

};

#endif
