
# C++ Fractals project #
## Outline of Project ##
This repositry contains a 3 week project completed in December 2016. The goal of the project was to produce a C++ programme making use of EasyBMP - a visualisation library which is capable of analysing and prodcing geometries on demand. The first part of the project involved creating an algorithm to produce a Sierpinski Triangle. The algorithm was then generalised by implementing Affine transformations. This made it possible to generate a snowflake like pattern as seen in Fig.1 in the [pdf report](myLib/report.pdf). Barnsley's Fern was then created by inputting the variables stored in a text file.

## How to run the file ##
Unfortunately, I can't get the code to compile as it as designed to however, for it to compile correctly, EasyBMP.cpp, EasyBMP.h and main.cpp need to be set as source files. To run the code created by myslef, the code in main.cpp must be replaced by either one of: advancedchaosgame.cpp, chaosegame.cpp, triangleonleaf.cpp or CollegeTheorem.cpp and should compile correctly.

## Description of the file structure ##

* The folder EasyBMP library contains the library
* Main files where main.cpp must be replaced are: advancedchaosgame.cpp, chaosegame.cpp, triangleonleaf.cpp and CollegeTheorem.cpp
* Report summarising the project included in report.pdf
* maple_leaf.bmp is imported in the example code
* IFSFern.txt contains the parameters needed to generate a Barnsley's Fern

## Library Required: ##
* EasyBMP - details of the linbrary can be found [here](http://easybmp.sourceforge.net)

## Examples ##
An example of the EasyBMP libary working correctly is possible by running main.cpp along with EasyBMP.cpp and EasyBMP.h as source files. this takes in maple_leaf.bmp and outputs a black and white image as image.bmp.
