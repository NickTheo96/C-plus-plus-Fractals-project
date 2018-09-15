#include "EasyBMP.h"

int main(){

    BMP ImageIn;
    ImageIn.ReadFromFile("maple_leaf.bmp");
    const unsigned int widthPixels = ImageIn.TellWidth();
    const unsigned int heightPixels = ImageIn.TellHeight();

    double **data = new double*[widthPixels];

    for (unsigned int xPixel = 0; xPixel < widthPixels; ++xPixel){

        data[xPixel] = new double[heightPixels];

        for (unsigned int yPixel = 0; yPixel < heightPixels; ++yPixel){
            // convert each pixel to greyscale
            double Temp = 0.30*(ImageIn(xPixel, yPixel)->Red) + 0.59*(ImageIn(xPixel, yPixel)->Green) + 0.11*(ImageIn(xPixel, yPixel)->Blue);
            if (Temp != 255){
                data[xPixel][yPixel] = (Temp);
            }
            else{
                data[xPixel][yPixel] = 0;
            }
        }
    }

    double min = 9e9;
    double max = -9e9;
    for( unsigned int i=0 ; i < widthPixels ;i++ )
    {
        for( unsigned int j=0; j <heightPixels ; j++ )
        {
            if( data[i][j] < min )
            { min = data[i][j]; }
            if( data[i][j] > max )
            { max = data[i][j]; }
        }
    }

    std::cout << "Detected Cell Minimum: " << min << std::endl;
    std::cout << "Detected Cell Maximum: " << max << std::endl;

    //Create output bmp container
    BMP Output;
    Output.SetSize(widthPixels,heightPixels);
    Output.SetBitDepth(32);

    // plot the pixels
    for( unsigned int i=0 ; i < widthPixels ; i++ )
    {
        for( unsigned int j=0; j < heightPixels ; j++ )
        {
            double scaled_value = 1 - ( data[i][j] - min )/( max-min + 1e-16 );
            ebmpBYTE pixel_value = (ebmpBYTE) ( scaled_value * 255.0 );
            Output(i,j)->Red = pixel_value;   //
            Output(i,j)->Green = pixel_value; //for more interesting colours you can play around with these
            Output(i,j)->Blue = pixel_value;  //
        }
    }

    Output.WriteToFile( "image.bmp" );

}