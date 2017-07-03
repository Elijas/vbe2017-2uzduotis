#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

struct Rect {
    int x, y, dx, dy, r, g, b;
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
        inputFile >> rect.x >> rect.y >> rect.dx >> rect.dy >> rect.r >> rect.g >> rect.b;
        rectangles[i] = rect;
    }

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
    assert(length == 2);
    assert(width == 3);

    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
