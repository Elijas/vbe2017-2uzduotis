#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Pixel {
    int r, g, b;

    Pixel() {
        r = 255;
        g = 255;
        b = 255;
    }  // New images will be filled with white color because of this constructor
};

struct Vector {
    int x, y;
};

struct Rectangle {
    Vector start; // upper left corner coordinates
    Vector size; // length and width
    Pixel color;
};

void addRectToImage(vector<vector<Pixel>> &image, Rectangle rect);

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
    for (int i = 0; i < rectCount; ++i) { // Greedy search for the smallest possible image size
        Rectangle rect = rectangles[i];

        int xNeeded = rect.start.x + rect.size.x; // x of needed image size to fit this one rectangle
        if (imageSize.x < xNeeded)
            imageSize.x = xNeeded;
        int yNeeded = rect.start.y + rect.size.y; // y of needed image size to fit this one rectangle
        if (imageSize.y < yNeeded)
            imageSize.y = yNeeded;
    }

    // Create the picture
    vector<vector<Pixel>> image;
    for (int yi = 0; yi < imageSize.y; ++yi) {
        vector<Pixel> row;
        for (int xi = 0; xi < imageSize.x; ++xi) {
            row.push_back(Pixel());
        }
        image.push_back(row);
    }

    // Color the picture
    for (int i = 0; i < rectCount; ++i) {
        Rectangle rect = rectangles[i];
        addRectToImage(image, rect);
    }

    // Output data
    outputFile << imageSize.y << " " << imageSize.x << endl;
    for (int yi = 0; yi < imageSize.y; ++yi) {
        for (int xi = 0; xi < imageSize.x; ++xi) {
            Pixel pixel = image.at(yi).at(xi);
            outputFile << pixel.r << " " << pixel.g << " " << pixel.b << endl;
        }
    }

    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}

void addRectToImage(vector<vector<Pixel>> &image, Rectangle rect) {
    for (int yi = rect.start.y; yi < rect.start.y + rect.size.y; ++yi) {
        for (int xi = rect.start.x; xi < rect.start.x + rect.size.x; ++xi) {
            image.at(yi).at(xi) = rect.color;
        }
    }
}
