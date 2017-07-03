#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

struct Pixel {
    int r, g, b;

    Pixel() { // New images will be filled with white color because of this constructor
        r = 255;
        g = 255;
        b = 255;
    }
};

struct Rect {
    int x, y, dx, dy;
    Pixel color;
};

void addRectToImage(vector<vector<Pixel>> &image, Rect rect) {
    for (int ix = rect.x; ix < rect.x + rect.dx; ++ix) {
        for (int iy = rect.y; iy < rect.y + rect.dy; ++iy) {
            image.at(iy).at(ix) = rect.color;
        }
    }
}

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

    // Find the size of final picture
    int ySize = 0, xSize = 0;
    for (int i = 0; i < rectCount; ++i) {
        Rect rect = rectangles[i];

        int xdx = rect.x + rect.dx; // x of lower left corner of rectangle
        if (xdx > xSize)
            xSize = xdx;

        int ydy = rect.y + rect.dy; // y of lower left corner of rectangle
        if (ydy > ySize)
            ySize = ydy;
    }

    // Create the picture
    vector<vector<Pixel>> image;
    for (int ix = 0; ix < ySize; ++ix) {
        vector<Pixel> row;
        for (int iy = 0; iy < xSize; ++iy) {
            row.push_back(Pixel());
        }
        image.push_back(row);
    }

    // Color the picture
    for (int i = 0; i < rectCount; ++i) {
        Rect rect = rectangles[i];
        addRectToImage(image, rect);
    }

    // Output data
    outputFile << ySize << " " << xSize << endl;
    for (int iiy = 0; iiy < ySize; ++iiy) {
        for (int iix = 0; iix < xSize; ++iix) {
            Pixel pixel = image.at(iiy).at(iix);
            outputFile << pixel.r << " " << pixel.g << " " << pixel.b << endl;
        }
    }

    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
