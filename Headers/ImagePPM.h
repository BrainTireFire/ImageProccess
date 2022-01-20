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
    /**
    * Pobiera row and col i z tego zwraca value danego pixela
    */
    int getPixelVal(int row, int col);
    /**
    * Pobiera row and col i z tego zwraca value danego pixela RED
    */
    int getPixelValR(int row, int col);
    /**
    * Pobiera row and col i z tego zwraca value danego pixela BLUE
    */
    int getPixelValB(int row, int col);
    /**
    * Pobiera row and col i z tego zwraca value danego pixela GREEN
    */
    int getPixelValG(int row, int col);
    /**
    * Ustawia wartosc danego pixela w 2 wymiarowej tablicy pixelval
    */
    void setPixelVal(int row, int col, int value);
    /**
    * Ustawia wartosc danego pixela w 2 wymiarowej tablicy pixelval RED
    */
    void setPixelValR(int row, int col, int value);
    /**
    * Ustawia wartosc danego pixela w 2 wymiarowej tablicy pixelval BLUE
    */
    void setPixelValB(int row, int col, int value);
    /**
    * Ustawia wartosc danego pixela w 2 wymiarowej tablicy pixelval GREEN
    */
    void setPixelValG(int row, int col, int value);
   // bool inBounds(int row, int col);
    /**
      * Przetwrza obraz na obraz binarny, zwraca obraz binarny jest uzwayny do gray scal image
      */
    ImagePPM threshold(int threshold); //binarize a grayscale image
    /**
    * Przetwrza obraz na obraz binarny, zwraca obraz binarny jest uzwayny do gray scal image
    */
    ImagePPM otsuBinarize();

    int rows;       //numer rows
    int cols;       //numer cols
    int rgb;       //numer color
    int **pixelVal; //2 wymiarowa tablica zawierajaca wartosc pixela
    int **pixelValRed; //2 wymiarowa tablica zawierajaca wartosc pixela red
    int **pixelValBlue; //2 wymiarowa tablica zawierajaca wartosc pixela blue
    int **pixelValGreen; //2 wymiarowa tablica zawierajaca wartosc pixela green
};


#endif //IMAGEPROCESSING_IMAGEPPM_H
