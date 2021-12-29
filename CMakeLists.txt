cmake_minimum_required(VERSION 3.21)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcessing main.cpp Image.cpp Headers/Image.h ImageOperaPGM.hpp ImagePPM.cpp ImagePPM.h ImageOperaPPM.hpp)
