#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <unistd.h>         /* sleep(), etc.  */
#include <iostream>
#include <string>
#include <unistd.h>
#include "window.h"
#include "dungeon.h"
#include "utility.h"

using namespace std;

Xwindow::Xwindow(int width, int height)
: dungeon{nullptr}, icons(iconNums, 0),
background(25, vector<char>(79, ' ')), foreground(25, vector<char>(79, ' ')) {
      
    d = XOpenDisplay(NULL);
	if (d == NULL) {
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(
		d, RootWindow(d, s), 10, 10, width, height, 
		1, BlackPixel(d, s), BlackPixel(d, s)
	);
    
    XStoreName(d, w, "CC3K+");

	XSelectInput(d, w, ExposureMask | KeyPressMask);

	Pixmap pix = XCreatePixmap(
		d, w, width, height, 
		DefaultDepth(d, DefaultScreen(d))
	);

	gc = XCreateGC(d, pix, 0, 0);

	// Set up colours.
	XColor xcolour;
	Colormap cmap;

	const size_t numColours = 5;
	char color_vals[numColours][10] = {
		"white", "black", "red", 
		"green", "blue"
	};

	cmap = DefaultColormap(d, DefaultScreen(d));
	
	for(unsigned int i = 0; i < numColours; ++i) {
		XParseColor(d, cmap, color_vals[i], &xcolour);
		XAllocColor(d, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(d, gc, colours[Black]);

	 // Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

    for (int i = 0; i < iconNums; ++i) {
        int rc = XpmReadFileToPixmap(d, w, (iconPath + iconFiles[i]).c_str(), &icons[i], NULL, NULL);
        /* check for failure or success. */
        checkPixmapError(rc, i);
    }
    
    int rc = XpmReadFileToImage(d, (iconPath + "welcome1920.xpm").c_str(), &welcome, NULL, NULL);
    checkPixmapError(rc, 0);
    
    rc = XpmReadFileToPixmap(d, w, (iconPath + "won1920.xpm").c_str(), &won, NULL, NULL);
    checkPixmapError(rc, 0);
    
    rc = XpmReadFileToPixmap(d, w, (iconPath + "lost1920.xpm").c_str(), &lost, NULL, NULL);
    checkPixmapError(rc, 0);
    

    
    
	// map window and flush
	XMapRaised(d, w);
	XFlush(d);
    
	// wait 1 second for setup
	sleep(1);
}

Xwindow::~Xwindow() {
    for (Pixmap &icon: icons) {
        XFreePixmap(d, icon);
    }
    
    XFreePixmap(d, won);
    XFreePixmap(d, lost);
    
    XDestroyImage(welcome);
    
    icons.clear();
    
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void Xwindow::drawString(int x, int y, string msg) {
    setForeground(White);
	XDrawString(d, w, gc, x, y, msg.c_str(), (int)msg.length());
	XFlush(d);
}

Display *Xwindow::getDisplay() const {
    return d;
}


void Xwindow::setForeground(int colour) {
    XSetForeground(d, gc, colours[colour]);
}

void Xwindow::setBackground(int colour) {
    XSetBackground(d, gc, colours[colour]);
}

void Xwindow::clear() {
    XClearWindow(d, w);
}

void Xwindow::setDungeon(Dungeon *dungeon) {
    this->dungeon = dungeon;
}

void Xwindow::drawDungeon() {
    for (int r = 0; r < 25; ++r) {
        for (int c = 0; c < 79; ++c) {
            background[r][c] = dungeon->getBackground(r, c);
            foreground[r][c] = dungeon->getForeground(r, c);
        }
    }
    
    
    for (int r = 0; r < 25; ++r) {
        for (int c = 0; c < 79; ++c) {
            int i = symbolToIndex(background[r][c]);
            if (i >= 0) {
                // XPutImage(d, w, gc, img, 0, 0, toCoordsX(c), toCoordsY(r), DIAMETER, DIAMETER);
                
                XCopyArea(d, icons[i], w, gc, 0, 0, DIAMETER, DIAMETER, toCoordsX(c), toCoordsY(r));
                
            }
            
            if (background[r][c] != foreground[r][c]) {
                int i;
                if (foreground[r][c] == '@') {
                    i = symbolToIndex(foreground[r][c], background[r][c]);
                }
                else {
                    i = symbolToIndex(foreground[r][c]);
                }

                if (i >= 0) {
                    // XPutImage(d, w, gc, img, 0, 0, toCoordsX(c), toCoordsY(r), DIAMETER, DIAMETER);
                    
                    XCopyArea(d, icons[i], w, gc, 0, 0, DIAMETER, DIAMETER, toCoordsX(c), toCoordsY(r));
                }
            }
        }
    }
    
    XFlush(d);
}

int Xwindow::symbolToIndex(char c) const {
    switch (c) {
        case '+':
            return 0;
            break;
        case '.':
            return 1;
            break;
        case '#':
            return 2;
            break;
        case '\\':
            return 3;
            break;
        case '-':
        case '|':
            return 4;
            break;
        case 'D':
            return 5;
            break;
        case 'N':
            return 6;
            break;
        case 'M':
            return 7;
            break;
        case 'X':
            return 8;
            break;
        case 'T':
            return 9;
            break;
        case 'V':
            return 10;
            break;
        case 'W':
            return 11;
            break;
        case 'B':
            return 12;
            break;
        case 'C':
            return 13;
            break;
        case 'P':
            return 14;
            break;
        case 'G':
            return 15;
            break;
            
        default:
            break;
    }
    return -1;
}

int Xwindow::symbolToIndex(char f, char b) const {
    if (f == '@') {
        switch (b) {
            case '.':
                return 16;
                break;
            case '+':
                return 17;
                break;
            case '#':
                return 18;
                break;
                
            default:
                break;
        }
    }
    return -1;
}

void Xwindow::checkPixmapError(int rc, int i) {
    switch (rc) {
        case PixmapOpenFailed:
            cerr << "XReadPixmapFile - could not open file '" << iconFiles[i] << "'." << endl;
            exit(1);
            break;
        case PixmapFileInvalid:
            cerr << "XReadPixmapFile - file '" << iconFiles[i] << "' doesn't contain a valid bitmap." << endl;
            exit(1);
            break;
        case PixmapNoMemory:
            cerr << "XReadPixmapFile - not enough memory." << endl;
            exit(1);
            break;
    }
}

void Xwindow::drawWelcome() {
    // XCopyArea(d, welcome, w, gc, 0, 0, WIDTH, HEIGHT, 0, 0);
    XPutImage(d, w, gc, welcome, 0, 0, 0, 0, WIDTH, HEIGHT);
    XFlush(d);
    sleep(1);
    
}

void Xwindow::drawWon() {
    XCopyArea(d, won, w, gc, 0, 0, WIDTH, HEIGHT, 0, 0);
    XFlush(d);
    sleep(1);
}

void Xwindow::drawLost() {
    XCopyArea(d, lost, w, gc, 0, 0, WIDTH, HEIGHT, 0, 0);
    XFlush(d);
    sleep(1);
}
