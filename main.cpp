#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

struct Pixel {
    int r, g, b;

    Pixel() {
        r = 255;
        g = 255;
        b = 255;
    }
};

struct Rect {
    int x, y, dx, dy;
    Pixel color;
};

int main() {
    // Opening files and reading metadata
    ifstream inputFile("U2.txt");
    ofstream outputFile("U2rez.txt");
    int rectCount;
    inputFile >> rectCount;

    // Reading data
    Rect rectangles[rectCount];
    for (int i = 0; i < rectCount; ++i) {
        Rect rect;
        inputFile >> rect.x >> rect.y >> rect.dx >> rect.dy >> rect.color.r >> rect.color.g >> rect.color.b;
        rectangles[i] = rect;
    }
    assert(rectangles[0].color.g == 128);
    assert(false);

    // Find the size of final picture
    int length = 0, width = 0;
    for (int i = 0; i < rectCount; ++i) {
        Rect rect = rectangles[i];

        int xdx = rect.x + rect.dx; // x of lower left corner of rectangle
        if (xdx > width)
            width = xdx;

        int ydy = rect.y + rect.dy; // y of lower left corner of rectangle
        if (ydy > length)
            length = ydy;
    }

    // Create and fill the picture


    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
