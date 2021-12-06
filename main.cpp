#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Headers/Image.h"

int main() {
    const int width = 512;
    const int height = 512;

    Image image(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image.SetColor(Color((float)j / (float)width, 1.0f - ((float)j / (float)width), (float)i / (float)height),j,i );
        }
    }

    image.Export("image.bmp");

    return 0;
}
