//
// Created by brAiN on 12/29/2021.
//

#include "ImagePPM.h"

#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

ImagePPM::ImagePPM() {
    rows = 0;
    cols = 0;
    rgb = 0;
    pixelVal = NULL;
}

/**
 *
 */
ImagePPM::ImagePPM(int numRows, int numCols, int grayLevels) {
    rows = numRows;
    cols = numCols;
    rgb = grayLevels;

    pixelVal = new int*[rows];
    for (int i = 0; i < rows; i++) {
        pixelVal[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            pixelVal[i][j] = 0;
        }
    }
}

ImagePPM::ImagePPM(const ImagePPM& oldImage) {
    rows = oldImage.rows;
    cols = oldImage.cols;
    rgb = oldImage.rgb;

    pixelVal = new int* [rows];
    for (int i = 0; i < rows; i++) {
        pixelVal[i] = new int [cols];
        for (int j = 0; j < cols; j++)
            pixelVal[i][j] = oldImage.pixelVal[i][j];
    }
}

/**
 * Destruktor :) innym slowem pozbywa sie zmiennych z pamieci
 */
ImagePPM::~ImagePPM() {
    rows = 0;
    cols = 0;
    rgb = 0;

    for (int i = 0; i < rows; i++) {
        delete pixelVal[rows];
    }

    delete pixelVal;
}

/**
 * Pobiera row and col i z tego zwraca gray value danego pixela
 */
int ImagePPM::getPixelVal(int row, int col) {
    return pixelVal[row][col];
}

int ImagePPM::getPixelValR(int row, int col) {
    return pixelVal[row][col];
}

int ImagePPM::getPixelValG(int row, int col) {
    return pixelVal[row][col];
}

int ImagePPM::getPixelValB(int row, int col) {
    return pixelVal[row][col];
}

void ImagePPM::setPixelVal(int row, int col, int value) {
    pixelVal[row][col] = value;
}

void ImagePPM::setPixelValR(int row, int col, int value) {
    pixelVal[row][col] = value;
}

void ImagePPM::setPixelValG(int row, int col, int value) {
    pixelVal[row][col] = value;
}

void ImagePPM::setPixelValB(int row, int col, int value) {
    pixelVal[row][col] = value;
}

ImagePPM ImagePPM::threshold(int threshold) {
    int pixel = 0, val = 0;
    ImagePPM newImage(rows, cols, rgb);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pixel = this->getPixelVal(i,j);
            val = pixel >= threshold ? rgb : 0;

            newImage.setPixelValR(i,j, val);
            newImage.setPixelValB(i,j, val);
            newImage.setPixelValG(i,j, val);
        }
    }

    return newImage;
}

ImagePPM ImagePPM::otsuBinarize() {
    double histogram[rgb + 1] = {0};
    int sum = 0;
    //Calculate image histogram
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixel =getPixelVal(i, j);
            histogram[pixel]++;

        }
    }
    //Calculate pixel sum
    for (int i = 0; i < rgb + 1; i++) {

        sum += histogram[i];

    }
    //Find pixel probabilities
    for (int i = 0; i < rgb + 1; i++) {

        histogram[i]=(double)histogram[i]/(double)sum;


    }
    //Begin Otsu's algorithmImage newImage =this->threshold(100);

    double probability[rgb + 1], mean[rgb + 1];
    double max_between, between[rgb + 1];
    int threshold;

    /*
    probability = class probability
    mean = class mean
    between = between class variance
    */

    for(int i = 0; i < rgb + 1; i++) {
        probability[i] = 0.0;
        mean[i] = 0.0;
        between[i] = 0.0;
    }

    probability[0] = histogram[0];

    for(int i = 1; i < rgb + 1; i++) {
        probability[i] = probability[i - 1] + histogram[i];
        mean[i] = mean[i - 1] + i * histogram[i];
    }

    threshold = 0;
    max_between = 0.0;

    for(int i = 0; i < 255; i++) {
        if(probability[i] != 0.0 && probability[i] != 1.0)
            between[i] = pow(mean[255] * probability[i] - mean[i], 2) / (probability[i] * (1.0 - probability[i]));
        else
            between[i] = 0.0;
        if(between[i] > max_between) {
            max_between = between[i];
            threshold = i;
        }
    }

    //Apply thresholding algorithm using Otsu's threshold value
    cout << "Otso Threshold Value: "<<threshold<< endl;
    ImagePPM newImage = this->threshold(threshold);
    return newImage;
}
