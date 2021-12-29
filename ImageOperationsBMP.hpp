//
// Created by brAiN on 12/29/2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

using namespace std;
const int SIZEBMP = 3;

struct BMP {
public:
    int width;
    int height;
    unsigned char header[54];
    unsigned char *pixels;
    int **pixelVal;
    int row_padded;
    long long int size_padded;
    int size;
};

BMP readBMP(string filename) {
    BMP image;
    int i;
    string fileName = filename;
    FILE *f = fopen(fileName.c_str(), "rb");
    fread(image.header, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    image.width = *(int *) &image.header[18];
    image.height = *(int *) &image.header[22];


    image.size = 3 * image.width * image.height;
    image.pixels = new unsigned char[image.size]; // allocate 3 bytes per pixel
    fread(image.pixels, sizeof(unsigned char), image.size, f); // read the rest of the data at once
    fclose(f);

    for (i = 0; i < image.size; i += 3) {
        unsigned char tmp = image.pixels[i];
        image.pixels[i] = image.pixels[i + 2];
        image.pixels[i + 2] = tmp;
    }
    return image;
}

void writeBMP(string filename, BMP image) {
    string fileName = filename;
    FILE *out = fopen(fileName.c_str(), "wb");
    fwrite(image.header, sizeof(unsigned char), 54, out);
    int i;
    unsigned char tmp;
    for (i = 0; i < image.size; i += 3) {
        tmp = image.pixels[i];
        image.pixels[i] = image.pixels[i + 2];
        image.pixels[i + 2] = tmp;
    }
    fwrite(image.pixels, sizeof(unsigned char), image.size, out); // read the rest of the data at once
    fclose(out);
}

BMP negatyw(BMP image) {
    BMP newImage = image;
    unsigned char *pixels = new unsigned char[image.size];

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            //pixels[i] = 255 - i*image.width;
            //newImage.pixels[i*j] = 255 - image.width;
            //newImage.pixels[i] = pixels[i];
            pixels[i * newImage.width + j] = 255 - image.pixels[i * image.width + j];
            newImage.pixels[i] = pixels[i];
        }
    }

    return newImage;
}
