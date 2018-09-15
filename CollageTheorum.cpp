//Created by Nickolas Theodoulou 
//December 2016
#include "EasyBMP.h"
#include <vector>

int main()
{
	BMP maple_leaf_image;
	maple_leaf_image.ReadFromFile("maple_leaf.bmp");
	int x_new_0 = 0, y_new_0 = 0,x_new_1,y_new_1, x_new_2, y_new_2, x_new_3, y_new_3, x_new_4, y_new_4, x_new_5, y_new_5;
	for (int i = 0; i < maple_leaf_image.TellWidth(); i++)
	{
		for (int j = 0; j < maple_leaf_image.TellHeight(); j++)
			{
				RGBApixel Temp = maple_leaf_image.GetPixel(i, j);
				if (Temp.Red < 240 || Temp.Green < 240 || Temp.Blue < 240)
				{
				Temp.Red = 192; Temp.Green = 50; Temp.Blue = 50; Temp.Alpha = 0;
				
				x_new_0 = ((i *0.525) + (j *0.8509))*0.4 +100;
				y_new_0 = ((i*-0.8509) + (j *0.525))*0.4 + 700;
				x_new_1 = (i *0.6) + (j * 0) + 600;
				y_new_1 = (i * 0) + (j *0.6) + 500;
				x_new_2 = (i *0.6) + (j * 0.35) - 100;
				y_new_2 = (i * -0.35) + (j *0.6) + 750;
				x_new_3 = ((i *0.175) + (j * -0.2836))*1.0 + 1600;
				y_new_3 = ((i *0.2836) + (j *0.175))*1.0 + 100;
				x_new_4 = ((i *0.35) + (j * 0))*1.0 + 650;
				y_new_4 = ((i *0) + (j *0.35))*1.0 + 0;
				x_new_5 = (-i *0.7) + (j * 0) + 1700;
				y_new_5 = (i * 0) + (-j *0.7) + 1400;
				
				maple_leaf_image.SetPixel(x_new_0, y_new_0, Temp);
				maple_leaf_image.SetPixel(x_new_1, y_new_1, Temp);
				maple_leaf_image.SetPixel(x_new_2, y_new_2, Temp);
				maple_leaf_image.SetPixel(x_new_3, y_new_3, Temp);
				maple_leaf_image.SetPixel(x_new_4, y_new_4, Temp);
				maple_leaf_image.SetPixel(x_new_5, y_new_5, Temp);
			}
		}
	}
	maple_leaf_image.WriteToFile("copied.bmp");
}