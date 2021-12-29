//
// Created by brAiN on 12/6/2021.
//

#include "Headers/Image.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

Image::Image() {
    rows = 0;
    cols = 0;
    gray = 0;
    pixelVal = NULL;
}

/**
 *
 */
Image::Image(int numRows, int numCols, int grayLevels) {
    rows = numRows;
    cols = numCols;
    gray = grayLevels;

    pixelVal = new int*[rows];
    for (int i = 0; i < rows; i++) {
        pixelVal[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            pixelVal[i][j] = 0;
        }
    }
}

Image::Image(const Image& oldImage) {
    rows = oldImage.rows;
    cols = oldImage.cols;
    gray = oldImage.gray;

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
Image::~Image() {
    rows = 0;
    cols = 0;
    gray = 0;

    for (int i = 0; i < rows; i++) {
        delete pixelVal[rows];
    }

    delete pixelVal;
}

/**
 * Pobiera row and col i z tego zwraca gray value danego pixela
 */
int Image::getPixelVal(int row, int col) {
    return pixelVal[row][col];
}

void Image::setPixelVal(int row, int col, int value) {
    pixelVal[row][col] = value;
}


/**
 * Sprawdzanie czy pisel jest w tym obrazie, adekwatnie zwraca jest true lub nie ma false
 */
bool Image::inBounds(int row, int col) {
    if (row >= rows || row < 0 || col >= cols || col < 0)
        return false;
    return true;
}

Image Image::threshold(int threshold) {
    int pixel = 0, val = 0;
    Image newImage(rows, cols, gray);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pixel = this->getPixelVal(i,j);
            val = pixel >= threshold ? gray : 0;

            newImage.setPixelVal(i,j, val);

        }
    }

    return newImage;
}

Image Image::otsuBinarize() {
    double histogram[gray + 1] = {0};
    int sum = 0;
    //Calculate image histogram
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixel =getPixelVal(i, j);
            histogram[pixel]++;

        }
    }
    //Calculate pixel sum
    for (int i = 0; i < gray + 1; i++) {

        sum += histogram[i];

    }
    //Find pixel probabilities
    for (int i = 0; i < gray + 1; i++) {

        histogram[i]=(double)histogram[i]/(double)sum;


    }
    //Begin Otsu's algorithmImage newImage =this->threshold(100);

    double probability[gray + 1], mean[gray + 1];
    double max_between, between[gray + 1];
    int threshold;

    /*
    probability = class probability
    mean = class mean
    between = between class variance
    */

    for(int i = 0; i < gray + 1; i++) {
        probability[i] = 0.0;
        mean[i] = 0.0;
        between[i] = 0.0;
    }

    probability[0] = histogram[0];

    for(int i = 1; i < gray + 1; i++) {
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
    Image newImage = this->threshold(threshold);
    return newImage;
}

/*
Color::Color()
    : r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b)
        : r(r), g(g), b(b)
{

}

Color::~Color() {

}

Image::Image(int width, int heigt)
    : m_width(width), m_height(heigt), m_colors(std::vector<Color>(width*heigt))
{

}

Image::Image() {

}


Image::~Image() {

}

Color Image::Getcolor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color &color, int x, int y)
{
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Read(const char* path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "File could not be opended" << std::endl;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
/*
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "The specified path is not a bitmap image" << std::endl;
        f.close();
        return;
    }
    */
/*
unsigned char infomationHeader[informationHeaderSize];
f.read(reinterpret_cast<char*>(infomationHeader), informationHeaderSize);

int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
m_width = infomationHeader[4] + (infomationHeader[5] << 8) + (infomationHeader[6] << 16) + (infomationHeader[7] << 24);
m_height = infomationHeader[8] + (infomationHeader[9] << 8) + (infomationHeader[10] << 16) + (infomationHeader[11] << 24);

m_colors.resize(m_width * m_height);

const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

for (int y = 0; y < m_height; ++y) {
for (int x = 0; x < m_width; ++x) {
unsigned char color[3];
f.read(reinterpret_cast<char*>(color), 3);

m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
m_colors[y * m_width + x].g = static_cast<float>(color[2]) / 255.0f;
m_colors[y * m_width + x].b = static_cast<float>(color[2]) / 255.0f;
}

f.ignore(paddingAmount);
}

f.close();

std::cout << "File read" << std::endl;
}

void Image::Export(const char *path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if(!f.is_open())
    {
        std::cout << "File could not be opened\n";
        return;
    }

    unsigned char bmpPad[3] = {0,0,0};
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

    unsigned  char fileHeader[fileHeaderSize];
    //file type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    //file size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    //Resreved 1 not used
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    //Resreved 2 not used
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    //Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    //Image width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;
    //Image heigth
    informationHeader[8] = m_width;
    informationHeader[9] = m_width >> 8;
    informationHeader[10] = m_width >> 16;
    informationHeader[11] = m_width >> 24;
    //Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    //Bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;
    //Compresion (no compresion)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    //Image size no compression
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    //X pixels per meter not specified
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    //Y pixels per meter not specified
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    //Total colors Color palette not used
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    //Important colors Generalyy Ignored
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char r =static_cast<unsigned char>(Getcolor(x, y).r * 300.0f);
            unsigned char g =static_cast<unsigned char>(Getcolor(x, y).g * 300.0f);
            unsigned char b =static_cast<unsigned char>(Getcolor(x, y).b * 300.0f);

            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout << "File created\n";
}

void Image::Copy(const char *path1, const char *path2)
{
    std::ifstream fin(path1, std::ios::binary);
    std::ofstream fout(path2, std::ios::binary);

    char byte;

    while (fin.get(byte) )
    {
        fout.put(byte);
    }
}

void Image::BrigthnessUp(const char *path1, const char *path2, int brightness) {
    std::ifstream fin(path1, std::ios::binary);
    std::ofstream fout(path2, std::ios::binary);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    fin.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
/*
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "The specified path is not a bitmap image" << std::endl;
        f.close();
        return;
    }


    unsigned char infomationHeader[informationHeaderSize];
    fin.read(reinterpret_cast<char*>(infomationHeader), informationHeaderSize);

    fileSize =  fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = infomationHeader[4] + (infomationHeader[5] << 8) + (infomationHeader[6] << 16) + (infomationHeader[7] << 24);
    m_height = infomationHeader[8] + (infomationHeader[9] << 8) + (infomationHeader[10] << 16) + (infomationHeader[11] << 24);


    for(int i =0;i<fileSize;i++)
    {
        int temp = fin.binary+ brightness;
        fout.binary =  (temp > 255)? 255 :temp;
    }
}
*/






