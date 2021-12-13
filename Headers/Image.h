//
// Created by brAiN on 12/6/2021.
//

#ifndef UNTITLED_IMAGE_H
#define UNTITLED_IMAGE_H

class Image {
public:
    Image();
    Image(int numRows, int numCols, int grayLevels);
    ~Image();
    Image(const Image& orig);
    //void setImageInfo(int numRows, int numCols, int maxVal);
    //void getImageInfo(int &numRows, int &numCols, int &maxVal);
    int getPixelVal(int row, int col);
    void setPixelVal(int row, int col, int value);
    bool inBounds(int row, int col);
    Image threshold(int threshold); //binarize a grayscale image

    int rows;       //number of rows
    int cols;       //number of columns
    int gray;       //number of gray levels
    int **pixelVal; //2D array containing pixel values
};


#endif //UNTITLED_IMAGE_H


/*
 * #include <vector>

struct Color {
    float  r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    Image();
    Image(int width, int heigt);
    ~Image();

    Color Getcolor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Copy(const char *path1, const char *path2);
    void Read(const char* path);
    void Export(const char* path);

    void BrigthnessUp(const char *path1, const char *path2, int brightness);

private:
    int m_width;
    int m_height;
    int fileSize;
    std::vector<Color> m_colors;

};
 *
 *
 *
 *
 */
