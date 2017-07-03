#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

int main() {
    // Opening files and reading metadata
    ifstream inputFile("U2.txt");
    ofstream outputFile("U2rez.txt");
    int rectCount;
    inputFile >> rectCount;
    assert(rectCount == 3);//d



    // Closing the program
    inputFile.close();
    outputFile.close();
    return 0;
}
