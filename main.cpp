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
    assert(rectangles[0].dx == 2);

    // Find the size of final picture
    int length, width;


    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
