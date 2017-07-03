// Only one file is allowed in the exam so it is not split

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

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

typedef vector<Rectangle> Rectangles;

class Image {
    vector<vector<Pixel>> matrix;
    static Vector getNeededImageSize(Rectangles rectangles);
public:
    Vector size;
    Image(Vector size);

    static Image getEmptyImage(Rectangles rectangles);

    Pixel &at(int x, int y);

    void addRectangle(Rectangle rect);

    void addRectangles(Rectangles rectangles);
};

class FilesIO {
    ifstream inputFile;
    ofstream outputFile;
public:
    FilesIO(string inputFilePath, string outputFilePath);

    Rectangles readRectangleData();

    void outputImage(Image image);

    void closeAll();
};

int main() {
    // Data input
    FilesIO filesIO("U2.txt", "U2rez.txt");
    Rectangles rectangles = filesIO.readRectangleData();
    Image image = Image::getEmptyImage(rectangles);

    // Processing
    image.addRectangles(rectangles);

    // Data output
    filesIO.outputImage(image);
    filesIO.closeAll();

    return 0;
}

void Image::addRectangle(Rectangle rect) {
    for (int yi = rect.start.y; yi < rect.start.y + rect.size.y; ++yi) {
        for (int xi = rect.start.x; xi < rect.start.x + rect.size.x; ++xi) {
            at(xi, yi) = rect.color;
        }
    }
}

void Image::addRectangles(Rectangles rectangles) {
    for (int i = 0; i < rectangles.size(); ++i) {
        Rectangle rect = rectangles[i];
        this->addRectangle(rect);
    }
}

Image::Image(Vector size) {
    assert(size.x > 0);
    assert(size.y > 0);
    this->size = size;

    vector<vector<Pixel>> matrix;
    for (int yi = 0; yi < size.y; ++yi) {
        vector<Pixel> row;
        for (int xi = 0; xi < size.x; ++xi) {
            row.push_back(Pixel());
        }
        matrix.push_back(row);
    }

    this->matrix = matrix;
}

Pixel &Image::at(int x, int y) {
    return matrix.at((unsigned long) y).at((unsigned long) x);
}

Vector Image::getNeededImageSize(Rectangles rectangles) {
    Vector imageSize = {0, 0};
    for (int i = 0; i < rectangles.size(); ++i) { // Greedy search for the smallest possible image size
        Rectangle rect = rectangles[i];

        int xNeeded = rect.start.x + rect.size.x; // x of needed image size to fit this one rectangle
        if (imageSize.x < xNeeded)
            imageSize.x = xNeeded;
        int yNeeded = rect.start.y + rect.size.y; // y of needed image size to fit this one rectangle
        if (imageSize.y < yNeeded)
            imageSize.y = yNeeded;
    }
    return imageSize;
}

Image Image::getEmptyImage(Rectangles rectangles) {
    const Vector neededImageSize = getNeededImageSize(rectangles);
    return Image(neededImageSize);
}

void FilesIO::closeAll() {
    inputFile.close();
    outputFile.close();
}

Rectangles FilesIO::readRectangleData() {
    int rectCount;
    inputFile >> rectCount;

    Rectangles rectangles;
    for (int i = 0; i < rectCount; ++i) {
        Rectangle rect;
        inputFile >> rect.start.x >> rect.start.y
                  >> rect.size.x >> rect.size.y
                  >> rect.color.r >> rect.color.g >> rect.color.b;
        rectangles.push_back(rect);
    }
    return rectangles;
}

FilesIO::FilesIO(string inputFilePath, string outputFilePath) {
    inputFile.open(inputFilePath, fstream::in);
    outputFile.open(outputFilePath, fstream::out);
}

void FilesIO::outputImage(Image image) {
    outputFile << image.size.y << " " << image.size.x << endl;
    for (int yi = 0; yi < image.size.y; ++yi) {
        for (int xi = 0; xi < image.size.x; ++xi) {
            Pixel pixel = image.at(xi, yi);
            outputFile << pixel.r << " " << pixel.g << " " << pixel.b << endl;
        }
    }
}
