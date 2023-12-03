#include "window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void Xwindow::setLargerFont(const std::string& inFont) {
    string fontName;
    if (inFont == "courier34r") {
        fontName = "-*-courier-*-r-*-*-34-*-*-*-*-*-*-*";
    }
    else if (inFont == "courier25o") {
        fontName = "-*-courier-*-o-*-*-25-*-*-*-*-*-*-*";
    } else if (inFont == "courier20r") {
        fontName = "-*-courier-*-r-*-*-20-*-*-*-*-*-*-*";
    }
    XFontStruct *font =
        XLoadQueryFont(d, fontName.c_str());  // 'd' is a member of Xwindow
    if (font) {
        XSetFont(d, gc, font->fid);  // 'gc' is a member of Xwindow
    } else {
        cerr << "failed to load font: " << fontName << endl;
    }
}

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix =
        XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0, (XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap = DefaultColormap(d, DefaultScreen(d));
    static const int NumColors = 12;
    char color_vals[NumColors][20] = {
        "white", "black",   "red",      "green",      "blue",        "yellow",
        "cyan",  "magenta", "SkyBlue1", "RoyalBlue1", "chartreuse1", "DarkRed"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < NumColors; ++i) {
        if (!XParseColor(d, cmap, color_vals[i], &xcolour)) {
            cerr << "Failed to parse color " << color_vals[i] << endl;
        } else if (!XAllocColor(d, cmap, &xcolour)) {
            cerr << "Failed to allocate color " << color_vals[i] << endl;
        } else {
            colours[i] = xcolour.pixel;
        }
    }

    XSetForeground(d, gc, colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height =
        height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);

    usleep(1000);
}



Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);  // Set the color
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, colours[Black]);  // Reset to default color if needed
}

void Xwindow::fillCircle(int x, int y, int radius, int colour) {
    XSetForeground(d, gc, colours[colour]);
    // Draw a full circle
    XFillArc(d, w, gc, x - radius, y - radius, 2 * radius, 2 * radius, 0,
             360 * 64);
    XSetForeground(d, gc,
                   colours[Black]);  // Reset color to default if necessary
}
