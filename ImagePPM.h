//
// Created by brAiN on 12/29/2021.
//

#ifndef IMAGEPROCESSING_IMAGEPPM_H
#define IMAGEPROCESSING_IMAGEPPM_H


class ImagePPM {
public:
    ImagePPM();
    ImagePPM(int numRows, int numCols, int grayLevels);
    ~ImagePPM();
    ImagePPM(const ImagePPM& orig);
    int getPixelVal(int row, int col);
    int getPixelValR(int row, int col);
    int getPixelValB(int row, int col);
    int getPixelValG(int row, int col);
    void setPixelVal(int row, int col, int value);
    void setPixelValR(int row, int col, int value);
    void setPixelValB(int row, int col, int value);
    void setPixelValG(int row, int col, int value);
   // bool inBounds(int row, int col);
    ImagePPM threshold(int threshold); //binarize a grayscale image
    ImagePPM otsuBinarize();

    int rows;       //number of rows
    int cols;       //number of columns
    int rgb;       //number of gray levels
    int **pixelVal; //2D array containing pixel values
    int **pixelValRed;
    int **pixelValBlue;
    int **pixelValGreen;
};


#endif //IMAGEPROCESSING_IMAGEPPM_H
