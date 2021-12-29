#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Headers/Image.h"
#include "ImageOperations.hpp"
#include "ImageOperationsBMP.hpp"
#include "ImageOperaBMP.h"
#include "ImageOperaPPM.hpp"
#include "ImagePPM.h"
#include <algorithm>
#include <cstring>

#include <crtdbg.h>

double PI = 3.141592653589793238462643383279;


struct File {
    string fileNameIn;
};

ImageOperaBMP fileCreateBMP(string fileNameIn, string fileNameOut);
void fileColsAndRows(Image imageOut, string fileOut);
void menuPGM(string flag, string fileOut);
void menuPPM(string flag, string fileOut);
void setFileName(string fileName);
void fileColsAndRowsPPM(ImagePPM imageOut, string fileOut);


int main() {
    int rows = 0, cols = 0, grayscale = 0;
    int val;
    bool type;
    string flagOut = "";
    string flag = "";

    cout << "Wpisz flage i nazwe pliku" << endl;
    getline(cin, flag);
    if (flag.find("-i") != std::string::npos) {

        cout << "Wpisz flage -o i podaj sciezke z nazwa do pliku koncowego" << endl;
        getline(cin, flagOut);

        if (flagOut.find("-o") != std::string::npos) {
            if (flag.find(".pgm") != std::string::npos && flagOut.find(".pgm") != std::string::npos) {
                cout << flag;
                flagOut = flagOut.erase(0,3);
                menuPGM(flag, flagOut);
            }else if (flag.find(".ppm") != std::string::npos && flagOut.find(".ppm") != std::string::npos) {
                flagOut = flagOut.erase(0,3);
                menuPPM(flag, flagOut);
            } else {
                cout << "Ten format jest nie wspierany!" << endl;
            }
        }
    }

    //BMP image = readBMP(fileName);
    //image = rotate(image,180);
    //image = negatyw(image);
    //writeBMP("girlface2_Output.bmp", image);

    //Image imageIn = readImage("../images/lena.pgm");
    //Image imageIn2 = readImage("../images/man.pgm");
    //Image imageIn3 = readImage("../images/aya.pgm");


    //Image imageOut = mirror(imageIn);


   // BMP image2 = readBMP("../images/lena.bmp");
    //image2 = rotate180Degree(image2, 180);
    //image2 = rotate(image2,180);
   // writeBMP("Out2.bmp", image2);


    //Image imageOut = rotateImage(imageIn, 180);

    //Image imageOut=linearFilter(imageIn,100,200);

    return 0;
}

void menuPGM(string flag, string fileOut) {
    string fileName = "";
    string flag2 = "";

    fileName = flag.erase(0,3);
    int n = fileName.length();
    char char_array[n + 1];
    Image imageIn = readImage(strcpy(char_array, fileName.c_str()));

    cout << endl;
    cout << "Wpisz kolejna flage" << endl;
    getline(cin, flag2);

    cout << flag2;

    if (flag2.find("-n") != std::string::npos) {
        cout << "Negatyw" << endl;;
        Image imageOut = negative(imageIn);
        fileColsAndRows(imageOut, fileOut);

    } else if (flag2.find("-g") != std::string::npos) {
        if (flag2.find("1") != std::string::npos){
            cout << "Sobel" << endl;
            Image imageOut = sobelFilter(imageIn);
            fileColsAndRows(imageOut, fileOut);
        } else if (flag2.find("2") != std::string::npos) {
            cout << "Prewitt" << endl;
            Image imageOut = prewittFilter(imageIn);
            fileColsAndRows(imageOut, fileOut);
        } else if (flag2.find("3") != std::string::npos) {
            cout << "Robert" << endl;
            Image imageOut = robertFilter(imageIn);
            fileColsAndRows(imageOut, fileOut);
        }

    } else if (flag2.find("-rs") != std::string::npos) {
        cout << "Zmiana rozdzielczonsci" << endl;

    } else if (flag2.find("-b") != std::string::npos) {
        cout << "Rozmycie obrazu" << endl;
        Image imageOut = gaussFilter(imageIn);
        fileColsAndRows(imageOut, fileOut);

    } else if (flag2.find("-dn") != std::string::npos) {
        cout << "Odszumianie obrazu" << endl;

    } else if (flag2.find("-ib") != std::string::npos) {
        cout << "Odszumianie obrazu" << endl;

    } else if (flag2.find("-e") != std::string::npos) {
        cout << "Erozja obrazu" << endl;
        Image imageOut=erosion(imageIn);
        fileColsAndRows(imageOut, fileOut);

    } else if (flag2.find("-d") != std::string::npos) {
        cout << "Dylatacja obrazu" << endl;


    } else if (flag2.find("-r") != std::string::npos) {
        cout << "Obracanie obrazu" << endl;

    }  else if (flag2.find("-h") != std::string::npos) {
        cout << "Pomoc" << endl;


    }  else {
        cout << "Pomoc" << endl;

    }
}


void menuPPM(string flag, string fileOut) {
    string fileName = "";
    string flag2 = "";

    fileName = flag.erase(0,3);
    int n = fileName.length();
    char char_array[n + 1];
    ImagePPM imageIn = readImage2(strcpy(char_array, fileName.c_str()));

    cout << endl;
    cout << "Wpisz kolejna flage" << endl;
    getline(cin, flag2);

    if (flag2.find("-n") != std::string::npos) {
        cout << "Negatyw" << endl;;
        ImagePPM imageOut = negativePPM(imageIn);
        fileColsAndRowsPPM(imageOut, fileOut);

    } else if (flag2.find("-g") != std::string::npos) {
        if (flag2.find("1") != std::string::npos){
            cout << "Sobel" << endl;
            ImagePPM imageOut = sobelFilterPPM(imageIn);
            fileColsAndRowsPPM(imageOut, fileOut);
        } else if (flag2.find("2") != std::string::npos) {
            cout << "Prewitt" << endl;
            ImagePPM imageOut = prewittFilterPPM(imageIn);
            fileColsAndRowsPPM(imageOut, fileOut);
        } else if (flag2.find("3") != std::string::npos) {
            cout << "Robert" << endl;
            ImagePPM imageOut = robertFilterPPM(imageIn);
            fileColsAndRowsPPM(imageOut, fileOut);
        }

    } else if (flag2.find("-rs") != std::string::npos) {
        cout << "Zmiana rozdzielczonsci" << endl;

    } else if (flag2.find("-b") != std::string::npos) {
        cout << "Rozmycie obrazu" << endl;
        ImagePPM imageOut = gaussFilterPPM(imageIn);
        fileColsAndRowsPPM(imageOut, fileOut);

    } else if (flag2.find("-dn") != std::string::npos) {
        cout << "Odszumianie obrazu" << endl;

    } else if (flag2.find("-ib") != std::string::npos) {
        cout << "Odszumianie obrazu" << endl;

    } else if (flag2.find("-e") != std::string::npos) {
        cout << "Erozja obrazu" << endl;
        ImagePPM imageOut = erosionPPM(imageIn);
        fileColsAndRowsPPM(imageOut, fileOut);

    } else if (flag2.find("-d") != std::string::npos) {
        cout << "Dylatacja obrazu" << endl;


    } else if (flag2.find("-r") != std::string::npos) {
        cout << "Obracanie obrazu" << endl;

    }  else if (flag2.find("-h") != std::string::npos) {
        cout << "Pomoc" << endl;

    }  else {
        cout << "Pomoc" << endl;

    }
}

void fileColsAndRows(Image imageOut, string fileOut) {
    ofstream ofile(fileOut, std::ios::out);

    ofile << "P2\n" << imageOut.cols << " " << imageOut.rows << "\n255\n";
    for (int i = 0; i < imageOut.rows; i++) {
        for (int j = 0; j < imageOut.cols; j++) {
            ofile << imageOut.getPixelVal(i, j) << endl;
        }
    }
}

void fileColsAndRowsPPM(ImagePPM imageOut, string fileOut) {
    ofstream ofilePPM(fileOut, std::ios::out);

    ofilePPM << "P3\n" << imageOut.cols << " " << imageOut.rows << "\n255\n";
    for (int i = 0; i < imageOut.rows; i++) {
        for (int j = 0; j < imageOut.cols; j++) {
            ofilePPM << imageOut.getPixelValR(i, j) << " " << imageOut.getPixelValB(i, j) << " " << imageOut.getPixelValG(i, j) << endl;
        }
    }
}

/*
 *
 * void writeBMP2(string filename, BMP image) {
    string fileName = filename;
    FILE *out = fopen(fileName.c_str(), "wb");
    fwrite(image.header, sizeof(unsigned char), 54, out);

    unsigned char tmp;
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width * 3; j += 3) {
            //Convert(B, G, R) to(R, G, B)
            tmp = image.pixels[j];
            image.pixels[j] = image.pixels[j + 2];
            image.pixels[j + 2] = tmp;
        }
    }
    fwrite(image.pixels, sizeof(unsigned char), image.size_padded, out);
    fclose(out);
}

BMP readBMP2(string filename) {
    BMP image;
    string fileName = filename;
    FILE *in = fopen(fileName.c_str(), "rb");

    if (in == NULL)
        throw "Argument Exception";

    fread(image.header, sizeof(unsigned char), 54, in); // read the 54-byte header

    // extract image height and width from header
    image.width = *(int *) &image.header[18];
    image.height = *(int *) &image.header[22];

    image.row_padded = (image.width * 3 + 3) & (~3);     // ok size of a single row rounded up to multiple of 4
    image.size_padded = image.row_padded * image.height;  // padded full size
    image.pixels = new unsigned char[image.size_padded];  // yeah !

    if (fread(image.pixels, sizeof(unsigned char), image.size_padded, in) == image.size_padded) {
        unsigned char tmp;
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width * 3; j += 3) {
                // Convert (B, G, R) to (R, G, B)
                tmp = image.pixels[j];
                image.pixels[j] = image.pixels[j + 2];
                image.pixels[j + 2] = tmp;
            }
        }
    } else {
        cout << "Error: all bytes couldn't be read" << endl;
    }

    fclose(in);
    return image;
}

BMP rotate180Degree(BMP image, double degree) {
    _ASSERTE(degree == 180.0);

    BMP newImage = image;
    unsigned char *pixels = new unsigned char[image.size_padded];

    int H = image.height, W = image.width;
    for (int x = 0; x < H; x++) {
        for (int y = 0; y < W;y ++) {
            pixels[(x * W + y) * 3 + 0] = image.pixels[((H - 1 - x) * W + (W - 1 - y)) * 3 + 0];
            pixels[(x * W + y) * 3 + 1] = image.pixels[((H - 1 - x) * W + (W - 1 - y)) * 3 + 1];
            pixels[(x * W + y) * 3 + 2] = image.pixels[((H - 1 - x) * W + (W - 1 - y)) * 3 + 2];
        }
        newImage.pixels[x] = pixels[x];
    }

   // newImage.pixels = pixels;
    return newImage;
}

BMP readBMP3(string filename) {
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

void writeBMP3(string filename, BMP image) {
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

BMP negatyw3(BMP image) {
    BMP newImage = image;
    unsigned char *pixels = new unsigned char[image.size];

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            //pixels[i] = 255 - i*image.width;
            //newImage.pixels[i*j] = 255 - image.width;
            //newImage.pixels[i] = pixels[i];
            pixels[i*newImage.width+j] = 255 - image.pixels[i*image.width+j];
            newImage.pixels[i] = pixels[i];
        }
    }

    return newImage;
}

BMP rotate(BMP image, double degree) {
    BMP newImage = image;
    unsigned char *pixels = new unsigned char[image.size];

    double radians = (degree * M_PI) / 180;
    int sinf = (int) sin(radians);
    int cosf = (int) cos(radians);

    double x0 = 0.5 * (image.width - 1);     // point to rotate about
    double y0 = 0.5 * (image.height - 1);     // center of image

    // rotation
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            long double a = x - x0;
            long double b = y - y0;
            int xx = (int) (+a * cosf - b * sinf + x0);
            int yy = (int) (+a * sinf + b * cosf + y0);

            if (xx >= 0 && xx < image.width && yy >= 0 && yy < image.height) {
                pixels[(y * image.height + x) * 3 + 0] = image.pixels[(yy * image.height + xx) * 3 + 0];
                pixels[(y * image.height + x) * 3 + 1] = image.pixels[(yy * image.height + xx) * 3 + 1];
                pixels[(y * image.height + x) * 3 + 2] = image.pixels[(yy * image.height + xx) * 3 + 2];
            }
            newImage.pixels[x] = pixels[y];
        }
    }

    return newImage;
}

 */