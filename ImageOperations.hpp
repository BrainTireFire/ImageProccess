//
// Created by brAiN on 12/13/2021.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include "Headers/Image.h"

/* PGM IMAGE
 * P5
#WPI-ME/CHSLT generated image Ver.1.0 (0)
10 10
255
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
26 27 28 28 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70
71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93
255 255 255 255 255 255
 */


using namespace std;
const int SIZE = 3;


Image readImage(char fileName[])
{
    int i, j;
    int fileRows = 0, fileCols = 0, fileGrayLevel = 0;
    unsigned char *charImage;

    char header[100], *ptr;

    ifstream inImage(fileName, ios::in | ios::binary);

    stringstream ss;
    string inputLine = "";


    if (!inImage)
    {
        cout << "Cannot read image:" << fileName << endl;
        exit(1);
    }

    getline(inImage, inputLine); /*!< Czytanie pierwszej linii obrazku | Read the first line of Image*/

    if (inputLine.compare("P5") != 0 && inputLine.compare("P2") != 0)
    {
        cerr << "Version error!!" << endl;
    }

    cout << "Version : " << inputLine << endl;

    getline(inImage, inputLine); /*!< Czytanie drugiej linii obrazku | Read the second line of Image */
    cout << "Comment : " << inputLine << endl;

    ss << inImage.rdbuf(); /*!< Czytanie trzeciej linii obrazku (szerokosc i wysokosc) | Read the third line of Image (width and height) */
    ss >> fileCols >> fileRows;
    cout << fileCols << " columns and " << fileRows << " rows of Image" << endl;

    ss >> fileGrayLevel;
    ss.ignore();
    cout << fileGrayLevel << endl;

    Image image(fileRows, fileCols, fileGrayLevel);

    /*!< Odczytanie i zapisanie wartości pikseli w obiekcie obrazu | Read and save the pixel values into the image object */
    unsigned int pixel;

    for (i = 0; i < fileRows; i++) {
        for (j = 0; j < fileCols; j++) {
            ss >> pixel;

            image.setPixelVal(i, j, pixel);
        }
    }

    inImage.close();

    return image;
}

template <typename T>
T clamp(T value, T lower_bound, T upper_bound) {
    value = std::min(std::max(value, lower_bound), upper_bound);
}

Image rotateImage(Image& image, double ang) {
    Image newImage = Image(image.rows, image.cols, image.gray);
    int pixel = 0;

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols  ;j++) {
            pixel = image.getPixelVal(i, j);
            newImage.setPixelVal((cos(-ang), -sin(-ang), newImage.cols/2 - image.cols*cos(-ang)/2)
                    , (sin(-ang),  cos(-ang), newImage.rows/2 - image.rows*cos(-ang)/2), pixel);
        }
    }

    return newImage;

}


Image mirror(Image& image) {
    Image newImage = Image(image.rows, image.cols, image.gray);
    int pixel =0;

    for (int i = 0; i < image.rows; i++) {
        for (int lx = 0, rx = image.cols - 1; lx < image.cols; lx++, rx--) {
            pixel = image.getPixelVal(i, lx);
            newImage.setPixelVal(i, rx, pixel);
        }
    }

    return newImage;
}

Image subtraction(Image& im1, Image& im2) {//im1-im2
    if (!im1.gray == im2.gray) {
        cout << "Images must have same maximum gray values" << endl;
        exit(1);
    }
    int Max = im1.gray;
    int pixel = 0, val = 0;
    Image newImage = Image(im1.rows, im1.cols, im1.gray);
    for (int i = 0; i < im1.rows; i++) {
        for (int j = 0; j < im1.cols; j++) {
            pixel = im1.getPixelVal(i, j) - im2.getPixelVal(i, j);
            val = (int) max(pixel, 0);
            newImage.setPixelVal(i, j, val);

        }

    }

    return newImage;

}

double min(double a, double b) {
    return ((a <= b) ? a : b);
}

Image convolution(Image& im, double kernel[SIZE][SIZE], int kSize, int norm) {
    Image newImage = Image(im.rows, im.cols, im.gray);

    // find center position of kernel (half of kernel size)
    int kCenter = kSize / 2;
    //int mm = 0, nn = 0, ii = 0, jj = 0;
    double sum = 0;

    for (int i = 0; i < im.rows; ++i) // rows
    {
        for (int j = 0; j < im.cols; ++j) // columns
        {
            for (int m = 0; m < kSize; ++m) // kernel rows
            {
                int mm = kSize - 1 - m;

                for (int n = 0; n < kSize; ++n) // kernel columns
                {
                    int nn = kSize - 1 - n;
                    // ignore input samples which are out of bound
                    int ii = i + (m - kCenter);
                    int jj = j + (n - kCenter);
                    if (ii < 0)
                        ii = ii + 1;
                    if (jj < 0)
                        jj = jj + 1;
                    if (ii >= im.rows)
                        ii = ii - 1;
                    if (jj >= im.cols)
                        jj = jj - 1;
                    if (ii >= 0 && ii < im.rows && jj >= 0 && jj < im.cols)
                        sum += im.getPixelVal(ii, jj) * kernel[mm][nn];
                }
            }

            double val = sum / norm;

            val = val < 0 ? 0 : min(val, im.gray);
            newImage.setPixelVal(i, j, (int) val);
            sum = 0;
        }
    }

    return newImage;
}

Image gaussFilter(Image& im) {
    double gaussBlur[3][3] = {
            {7, 7, 7},
            {2, 5, 2},
            {9, 2, 1}
    };
    return (convolution(im, gaussBlur, 3, 9));

}

int maxPixel(Image &im) {
    int maxi = 0, pixel = 0;
    int val = 0;

    for (int i = 0; i < im.rows; i++) {
        for (int j = 0; j < im.cols; j++) {
            pixel = im.getPixelVal(i, j);
            maxi = (int) max(pixel, maxi);
        }

    }
    return maxi;
}

int minPixel(Image &im) {
    int mini = im.gray, pixel = 0;
    int val = 0;

    for (int i = 0; i < im.rows; i++) {
        for (int j = 0; j < im.cols; j++) {
            pixel = im.getPixelVal(i, j);
            mini = (int) min(pixel, mini);

        }

    }
    return mini;
}

Image linearContrastSaturation(Image& im, double sMin, double sMax) {
    //Amelioration de contrast par transformation lineaire avec saturation

    if ((sMin > sMax) || (sMin < minPixel(im)) || (sMax > maxPixel(im))) {
        //Test simples pour niveaux de saturation
        cout << "Valeurs de saturation invalides" << endl;
        exit(1);
    }
    Image newImage = Image(im.rows, im.cols, im.gray);
    int val = 0, pixel = 0;

    for (int i = 0; i < im.rows; i++) {
        for (int j = 0; j < im.cols; j++) {
            pixel = im.getPixelVal(i, j);
            val = im.gray * (pixel - sMin) / (sMax - sMin);
            val = val < 0 ? 0 : val;
            val = val > im.gray ? im.gray : val;
            newImage.setPixelVal(i, j, val);
        }

    }

    return newImage;
}

Image negative(Image& im) {
    Image newImage = Image(im.rows, im.cols, im.gray);
    int val = 0, pixel = 0;

    for (int i = 0; i < im.rows; i++) {
        for (int j = 0; j < im.cols; j++) {
            pixel = im.getPixelVal(i, j);
            val = 255 - pixel;
            newImage.setPixelVal(i, j, val);
        }

    }

    return newImage;
}

Image sobelFilter(Image &im)
{
    double kern1[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}};
    double kern2[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}};
    Image temp = Image(convolution(im, kern1, 3, 1));
    return (convolution(temp, kern2, 3, 1));
}












/*
#ifndef IMAGEPROCESSING_IMAGEOPERATIONS_HPP
#define IMAGEPROCESSING_IMAGEOPERATIONS_HPP


class ImageOperations {

};


#endif //IMAGEPROCESSING_IMAGEOPERATIONS_HPP

 */