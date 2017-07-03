#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

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

void addRectToImage(Pixel **image, Rect rect) {
    for (int ix = rect.x; ix < rect.x + rect.dx; ++ix) {
        for (int iy = rect.y; iy < rect.y + rect.dy; ++iy) {
            image[ix][iy] = rect.color;
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

    // Create the picture
    Pixel **image;
    image = new Pixel *[width];
    for (int i = 0; i < width; ++i) {
        image[i] = new Pixel[length];
    }

    // Color the picture
    for (int i = 0; i < rectCount; ++i) {
        Rect rect = rectangles[i];
        addRectToImage(image, rect);
    }

    // Output data
    outputFile << length << " " << width << endl;
    for (int il = 0; il < length; ++il) {
        for (int iw = 0; iw < width; ++iw) {
            Pixel pixel = image[iw][il];
            outputFile << pixel.r << " " << pixel.g << " " << pixel.b << endl;
        }
    }

    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
