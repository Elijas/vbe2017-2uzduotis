#include <iostream>
#include <fstream>

using namespace std;

struct Pixel {
    int r, g, b;

    Pixel() { // New images will be filled with white color because of this constructor
        r = 255;
        g = 255;
        b = 255;
    }

    Pixel(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

struct Vector {
    int x, y;

    Vector operator+(const Vector b) { // Improves readability
        return Vector {x = this->x + b.x, y = this->y + b.y};
    }
};

struct Rectangle {
    Vector start, size;
    Pixel color;
};

void addRectToImage(Pixel **image, Rectangle rect) {
    for (int ix = rect.size.x; ix < rect.start.x + rect.size.x; ++ix) {
        for (int iy = rect.size.y; iy < rect.start.y + rect.size.y; ++iy) {
            image[ix][iy] = {4,4,4};
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
    Rectangle rectangles[rectCount];
    for (int i = 0; i < rectCount; ++i) {
        Rectangle rect;
        inputFile >> rect.start.x >> rect.start.y
                  >> rect.size.x >> rect.size.y
                  >> rect.color.r >> rect.color.g >> rect.color.b;
        rectangles[i] = rect;
    }

    // Find the size of final picture
    Vector imageSize = {0, 0};
    for (int i = 0; i < rectCount; ++i) { // Greedy search for the greatest needed image size
        Rectangle rect = rectangles[i];
        Vector neededImageSize = rect.start + rect.size; // Size of needed image size to fit this one rectangle
        if (neededImageSize.x > imageSize.x) imageSize.x = neededImageSize.x;
        if (neededImageSize.y > imageSize.y) imageSize.y = neededImageSize.y;
    }

    // Create the picture
    Pixel **image;
    image = new Pixel *[imageSize.x];
    for (int i = 0; i < imageSize.x; ++i) {
        image[i] = new Pixel[imageSize.y];
    }

    // Color the picture
    for (int i = 0; i < rectCount; ++i) {
        Rectangle rect = rectangles[i];
        for (int ix = rect.size.x; ix < rect.start.x + rect.size.x; ++ix) {
            for (int iy = rect.size.y; iy < rect.start.y + rect.size.y; ++iy) {
                image[ix][iy] = {4,4,4};
            }
        }

        for (int iy = 0; iy < imageSize.y; ++iy) {
            for (int ix = 0; ix < imageSize.x; ++ix) {
                Pixel pixel = image[ix][iy];
                cout << pixel.r << " " << pixel.g << " " << pixel.b << endl;
            }
        }
        cout << endl;
    }

    // Output data
    outputFile << imageSize.y << " " << imageSize.x << endl;
    for (int iy = 0; iy < imageSize.y; ++iy) {
        for (int ix = 0; ix < imageSize.x; ++ix) {
            Pixel pixel = image[ix][iy];
            outputFile << pixel.r << " " << pixel.g << " " << pixel.b << endl;
        }
    }

    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
