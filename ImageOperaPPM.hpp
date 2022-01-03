//
// Created by brAiN on 12/29/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include "ImagePPM.h"

/*
 * P3           # "P3" means this is a RGB color image in ASCII
3 2          # "3 2" is the width and height of the image in pixels
255          # "255" is the maximum value for each color
# The part above is the header
# The part below is the image data: RGB triplets
255   0   0  # red
  0 255   0  # green
  0   0 255  # blue
255 255   0  # yellow
255 255 255  # white
  0   0   0  # black
 */

using namespace std;
const int SIZE2 = 3;

/**
 * Wczytuje plik o formacie ppm
 */
ImagePPM readImage2(char fileName[])
{
    int i, j;
    int fileRows = 0, fileCols = 0, fileRGBLevel = 0;
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

    if (inputLine.compare("P3") != 0 && inputLine.compare("P6") != 0)
    {
       cerr << "Version error!!" << endl;
    }

    //getline(inImage, inputLine); /*!< Czytanie drugiej linii obrazku | Read the second line of Image */


    ss << inImage.rdbuf(); /*!< Czytanie trzeciej linii obrazku (szerokosc i wysokosc) | Read the third line of Image (width and height) */
    ss >> fileCols >> fileRows;
    cout << fileCols << " columns and " << fileRows << " rows of Image" << endl;

    ss >> fileRGBLevel;
    ss.ignore();
    cout << fileRGBLevel << endl;

    ImagePPM image(fileRows, fileCols, fileRGBLevel);

    /*!< Odczytanie i zapisanie wartości pikseli w obiekcie obrazu | Read and save the pixel values into the image object */
    unsigned int pixel;


    for (i = 0; i < fileRows; i++) {
        for (j = 0; j < fileCols; j++) {
            ss >> pixel;
            image.setPixelValR(i, j, pixel);
            ss >> pixel;
            image.setPixelValB(i, j, pixel);
            ss >> pixel;
            image.setPixelValG(i, j, pixel);
        }
    }


    inImage.close();

    return image;
}

ImagePPM convolution(ImagePPM& im, double kernel[SIZE2][SIZE2], int kSize, int norm) {
    ImagePPM newImage = ImagePPM(im.rows, im.cols, im.rgb);

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

            val = val < 0 ? 0 : min(val, im.rgb);
            newImage.setPixelVal(i, j, (int) val);
            sum = 0;
        }
    }

    return newImage;
}

ImagePPM convo2D(ImagePPM& im, double kernel[2][2], int kSize, int norm) {
    ImagePPM newImage = ImagePPM(im.rows, im.cols, im.rgb);

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

            val = val < 0 ? 0 : min(val, im.rgb);
            newImage.setPixelVal(i, j, (int) val);
            sum = 0;
        }
    }

    return newImage;
}

ImagePPM gaussFilterPPM(ImagePPM& im) {
    double gaussBlur[3][3] = {
            {7, 7, 7},
            {2, 5, 2},
            {9, 2, 1}
    };
    return (convolution(im, gaussBlur, 3, 9));

}

ImagePPM robertFilterPPM(ImagePPM& im) {
    double kern1[2][2] = {
            {-1, 0},
            {0, -1}

    };
    double kern2[2][2] = {
            {0, 1},
            {-1,0}

    };


    ImagePPM temp = ImagePPM(convo2D(im, kern1, 2, 1));
    return (convo2D(temp, kern2, 2, 1));


}

ImagePPM sobelFilterPPM(ImagePPM &im)
{
    double kern1[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}};
    double kern2[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}};
    ImagePPM temp = ImagePPM(convolution(im, kern1, 3, 1));
    return (convolution(temp, kern2, 3, 1));
}

ImagePPM prewittFilterPPM(ImagePPM& im) {
    double kern1[3][3] = {
            {-1, -1, -1},
            {0, 0, 0},
            {1, 1, 1}
    };
    double kern2[3][3] = {
            {-1, 0, 1},
            {-1, 0, 1},
            {-1, 0, 1}
    };

    ImagePPM temp = ImagePPM(convolution(im, kern1, 3, 1));
    return (convolution(temp, kern2, 3, 1));

}

ImagePPM erosionPPM(ImagePPM& im) {
    ImagePPM binImage = ImagePPM(im.otsuBinarize());
    double kern[3][3] = {
            {1, -1, 1},
            {1, -1, 1},
            {1, -1, 1}
    };
    return (convolution(binImage, kern, 3, 3));

}

ImagePPM negative3(ImagePPM& im) {
    ImagePPM newImage = ImagePPM(im.rows, im.cols, im.rgb);
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

ImagePPM negativePPM(ImagePPM& im) {
    ImagePPM newImage = ImagePPM(im.rows, im.cols, im.rgb);
    int val = 0, pixel = 0;

    for (int i = 0; i < im.rows; i++) {
        for (int j = 0; j < im.cols; j++) {
            pixel = im.getPixelValR(i, j);
            val = 255 - pixel;
            newImage.setPixelValR(i, j, val);

            pixel = im.getPixelValB(i, j);
            val = 255 - pixel;
            newImage.setPixelValB(i, j, val);

            pixel = im.getPixelValG(i, j);
            val = 255 - pixel;
            newImage.setPixelValG(i, j, val);
        }
    }

    return newImage;
}
