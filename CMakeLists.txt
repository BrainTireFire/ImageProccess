cmake_minimum_required(VERSION 3.21)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcessing main.cpp Image.cpp Headers/Image.h ImageOperations.hpp ImageOperationsBMP.hpp ImageOperaBMP.cpp ImageOperaBMP.h ImagePPM.cpp ImagePPM.h ImageOperaPPM.hpp)
