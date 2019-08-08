cmake_minimum_required(VERSION 3.13)
project(Flower_Pollination_ALGORITHM)

set(CMAKE_CXX_STANDARD 14)

include_directories(C++)
include_directories("C++/Neural Network Training")

add_executable(Flower_Pollination_ALGORITHM
        "C++/Neural Network Training/dblib.hpp"
        "C++/Neural Network Training/neuralNetwork.cpp"
        "C++/Neural Network Training/neuralNetworkWithFPA.cpp"
        C++/fpa.cpp
        C++/Levy.hpp
        C++/randn.hpp
        C++/vectorMath.hpp)
