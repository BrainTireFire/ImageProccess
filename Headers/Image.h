//
// Created by brAiN on 12/5/2021.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

#include <vector>

struct Color {
    float  r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    Image(int width, int heigt);
    ~Image();

    Color Getcolor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Export(const char* path);

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};


#endif //IMAGEPROCESSING_IMAGE_H
