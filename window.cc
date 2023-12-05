#include "window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void Xwindow::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                           int colour) {
    XSetForeground(d, gc, colours[colour]);

    XPoint points[3];
    points[0].x = x1;
    points[0].y = y1;
    points[1].x = x2;
    points[1].y = y2;
    points[2].x = x3;
    points[2].y = y3;

    XFillPolygon(d, w, gc, points, 3, Convex, CoordModeOrigin);

    XSetForeground(d, gc, colours[Black]);  // Reset to default color if needed
}

void Xwindow::fillRoundedRectangle(int x, int y, int width, int height,
                                   int arcSize, int colour) {
    // Set the color
    XSetForeground(d, gc, colours[colour]);

    // Draw rectangles for top and bottom parts
    XFillRectangle(d, w, gc, x + arcSize, y, width - 2 * arcSize, height);
    XFillRectangle(d, w, gc, x, y + arcSize, width, height - 2 * arcSize);

    // Draw filled arcs for the corners
    XFillArc(d, w, gc, x, y, 2 * arcSize, 2 * arcSize, 90 * 64,
             90 * 64);  // Top-left corner
    XFillArc(d, w, gc, x + width - 2 * arcSize, y, 2 * arcSize, 2 * arcSize, 0,
             90 * 64);  // Top-right corner
    XFillArc(d, w, gc, x, y + height - 2 * arcSize, 2 * arcSize, 2 * arcSize,
             180 * 64, 90 * 64);  // Bottom-left corner
    XFillArc(d, w, gc, x + width - 2 * arcSize, y + height - 2 * arcSize,
             2 * arcSize, 2 * arcSize, 270 * 64,
             90 * 64);  // Bottom-right corner
}

void Xwindow::drawFilledRoundedRectangle(int x, int y, int width, int height,
                                   int arcSize, int fillColour,
                                   int outlineColour) {
    // Draw the filled rounded rectangle
    fillRoundedRectangle(x, y, width, height, arcSize, fillColour);

    // Set the color for the outline
    XSetForeground(d, gc, colours[outlineColour]);

    // Draw the outline
    // Top and bottom lines
    XDrawLine(d, w, gc, x + arcSize, y, x + width - arcSize, y);  // Top
    XDrawLine(d, w, gc, x + arcSize, y + height, x + width - arcSize,
              y + height);  // Bottom

    // Left and right lines
    XDrawLine(d, w, gc, x, y + arcSize, x, y + height - arcSize);  // Left
    XDrawLine(d, w, gc, x + width, y + arcSize, x + width,
              y + height - arcSize);  // Right

    // Corner arcs
    XDrawArc(d, w, gc, x, y, 2 * arcSize, 2 * arcSize, 90 * 64,
             90 * 64);  // Top-left
    XDrawArc(d, w, gc, x + width - 2 * arcSize, y, 2 * arcSize, 2 * arcSize, 0,
             90 * 64);  // Top-right
    XDrawArc(d, w, gc, x, y + height - 2 * arcSize, 2 * arcSize, 2 * arcSize,
             180 * 64, 90 * 64);  // Bottom-left
    XDrawArc(d, w, gc, x + width - 2 * arcSize, y + height - 2 * arcSize,
             2 * arcSize, 2 * arcSize, 270 * 64, 90 * 64);  // Bottom-right
}

void Xwindow::drawRoundedRectangle(int x, int y, int width, int height,
                                         int arcSize,
                                         int outlineColour) {

    // Set the color for the outline
    XSetForeground(d, gc, colours[outlineColour]);

    // Draw the outline
    // Top and bottom lines
    XDrawLine(d, w, gc, x + arcSize, y, x + width - arcSize, y);  // Top
    XDrawLine(d, w, gc, x + arcSize, y + height, x + width - arcSize,
              y + height);  // Bottom

    // Left and right lines
    XDrawLine(d, w, gc, x, y + arcSize, x, y + height - arcSize);  // Left
    XDrawLine(d, w, gc, x + width, y + arcSize, x + width,
              y + height - arcSize);  // Right

    // Corner arcs
    XDrawArc(d, w, gc, x, y, 2 * arcSize, 2 * arcSize, 90 * 64,
             90 * 64);  // Top-left
    XDrawArc(d, w, gc, x + width - 2 * arcSize, y, 2 * arcSize, 2 * arcSize, 0,
             90 * 64);  // Top-right
    XDrawArc(d, w, gc, x, y + height - 2 * arcSize, 2 * arcSize, 2 * arcSize,
             180 * 64, 90 * 64);  // Bottom-left
    XDrawArc(d, w, gc, x + width - 2 * arcSize, y + height - 2 * arcSize,
             2 * arcSize, 2 * arcSize, 270 * 64, 90 * 64);  // Bottom-right
}

void Xwindow::setLargerFont(const std::string& inFont) {
    string fontName;
    if (inFont == "courier34r") {
        fontName = "-*-courier-*-r-*-*-34-*-*-*-*-*-*-*";
    }
    else if (inFont == "courier25o") {
        fontName = "-*-courier-*-o-*-*-25-*-*-*-*-*-*-*";
    } else if (inFont == "courier20r") {
        fontName = "-*-courier-*-r-*-*-20-*-*-*-*-*-*-*";
    } else if (inFont == "courier17r") {
        fontName = "-*-courier-*-r-*-*-17-*-*-*-*-*-*-*";
    }
    XFontStruct *font =
        XLoadQueryFont(d, fontName.c_str());  // 'd' is a member of Xwindow
    if (font) {
        XSetFont(d, gc, font->fid);  // 'gc' is a member of Xwindow
    } else {
        // cerr << "failed to load font: " << fontName << endl;
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
    static const int NumColors = 23;
    char color_vals[NumColors][20] = {
        "white",       "black",   "red",       "green",    "blue",
        "#FFD800",     "cyan",    "magenta",   "SkyBlue1", "RoyalBlue1",
        "chartreuse1", "DarkRed", "DarkGreen", "#000C2F",  "#00CAC3",
        "#E87B2B",     "#32B000", "#3C005B",   "#AC0000",  "#B0B0B0",
        "#001260",     "#D234FF",    "#651F00"};

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

    usleep(20000);
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
