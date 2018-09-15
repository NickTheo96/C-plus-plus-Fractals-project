//Created by Nickolas Theodoulou 
//December 2016
#include "EasyBMP.h"
#include <vector>

int main()
{
	BMP maple_leaf_image;
	maple_leaf_image.ReadFromFile("maple_leaf.bmp");

	std::vector<double> v_x = { 0,1920,910 };
	std::vector<double> v_y = { 1200,1200,0 };
	std::vector<double> v_x_n, v_y_n;

	int x_random = 0, y_random = 0, x_vertices = 0, y_vertices = 0, x_distance = 0, y_distance = 0, x_new = 0, y_new = 0, a = 0, b = 0;
	x_random = 910;
	y_random = 600;
	int n = 1000000;
	for (int i = 0; i < n; i++)
	{
		unsigned int dice_roll = rand() % 3;
		for (int j = 0; j<v_x.size(); j++)
		{
			if (dice_roll == j)
			{
				x_vertices = v_x[j];
				y_vertices = v_y[j];
				x_distance = x_random - x_vertices;
				x_new = (x_distance / 2.0) + x_vertices;
				x_random = x_new;
				y_distance = y_random - y_vertices;
				y_new = (y_distance / 2.0) + y_vertices;
				y_random = y_new;
				v_x_n.push_back(x_new);
				v_y_n.push_back(y_new);
			}
		}
	}
	int x_n = 0, y_n = 0, x_new_scaled = 0, y, y_new_scaled = 0;
	for (int i = 0; i < n; i++)
	{
		x_new = v_x_n[i];
		y_new = v_y_n[i];
		x_n = x_new;
		y_n = y_new;

		x_new_scaled = x_new;
		y_new_scaled = y_new;

		RGBApixel Temp = maple_leaf_image.GetPixel(x_new_scaled, y_new_scaled);
		if (Temp.Red < 240 || Temp.Green < 240 || Temp.Blue < 240)
		{
			Temp.Red = 192; Temp.Green = 50; Temp.Blue = 50; Temp.Alpha = 0;
			maple_leaf_image.SetPixel(x_new_scaled, y_new_scaled, Temp);
		}

	}
	maple_leaf_image.WriteToFile("triangle_on_leaf.bmp");
}