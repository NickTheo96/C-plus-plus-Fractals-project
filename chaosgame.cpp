//Created by Nickolas Theodoulou 
//December 2016
#include "EasyBMP.h"
#include <iostream>
#include <vector>
#include <numeric>

int main()
{

	//Create a 2D array with MxN pixels on the heap
	int M = 1920;
	int N = 1200;
	double **data = new double*[M];

	for (int i = 0; i < M; ++i)
	{
		data[i] = new double[N];
	}
	//Initialise pixel array
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			data[i][j] = 0;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Initialise the vectors seperately so that an n sided shape can be build by adding 1 more value to the end of the vector
	//v_x contains all the x-coordiantes
	std::vector<double> v_x = { 910,   0.25 * 600 * pow(10 + 2 * pow(5,0.5),0.5) + 910,   0.25 * 600 * pow(10 - 2 * pow(5,0.5),0.5) + 910,  -0.25 * 600 * pow(10 - 2 * pow(5,0.5),0.5) + 910,  -0.25 * 600 * pow(10 + 2 * pow(5,0.5),0.5) + 910 };
	//v_y contains all the y coordinates
	std::vector<double> v_y = { 1200,  (0.25 * 600 * (pow(5,0.5) - 1)) + 600,  -(0.25 * 600 * (pow(5,0.5) + 1)) + 600,  -(0.25 * 600 * (pow(5,0.5) + 1)) + 600,   (0.25 * 600 * (pow(5,0.5) - 1)) + 600 };
	//v_prob contains the probability of each x and y cordinate to be selected as a percentage, the probability of selecting a x and y coordinate is equal to the ith value
	//in this vector divided by the sum of all the ith values in the vector so the probability will always be calculated correctly no matter how many values
	//are contained here
	std::vector<double> v_prob = { 20, 20,20,20,20 };
	//v_factor allows the user to decide the factor by which to move the ith coordinate to the new point
	std::vector<double> v_factor = { 2.5,2.5,2.5,2.5,2.5 };

	//simple loop to find the sum of all the probabilites so that the probability distribtuion can be found
	int sum_v_prob = 0;
	for (int i = 0; i < v_prob.size(); i++)
	{
		sum_v_prob += v_prob[i];
	}
	
	//initialise all the variables that will be used within the for loop to generate the new points
	int x_random = 0, y_random = 0, x_vertices = 0, y_vertices = 0, x_distance = 0, y_distance = 0, x_new = 0, y_new = 0, a = 0, b = 0;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//I attemped to generate the  random point within the triangle so that the user wouldn't have to input a point within the triangle using arrays.
	//I decided to leave it in anyway, but i found it dificult to generalise as an algorithnm for a n sided shape was difficult to implement
	
	/*
	x_random = rand() % M;
	y_random = rand() % N;

	a = ( (x_random*vertices3[1]) - (y_random*vertices3[0]) - (vertices1[0] * vertices3[1]) + (vertices1[1] * vertices3[0])) / (vertices2[1] * vertices3[0]) - (vertices2[0] * vertices3[1]);
	b = ((x_random*vertices2[1]) - (y_random*vertices2[0]) - (vertices1[0] * vertices2[1]) + (vertices1[1] * vertices2[0])) / (vertices2[1] * vertices3[0]) - (vertices2[0] * vertices3[1]);

	if (a > 0 && b > 0 && a + b < 1)
	{
	x_random = x_random;
	y_random = y_random;
	}
	else
	{
	x_random = rand() % M;
	y_random = rand() % N;

	}

	std::cout << "The random co-ordinate is (" << x_random << "," << y_random << ")" << std::endl;
	*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//i set the first random x and y co-ordinate to be the middle of the NxM pixels
	x_random = 910;
	y_random = 600;
	int n = 1000000;
	for (int i = 0; i < n; i++)// iterate the loop to generate n new points
	{
		data[x_new][y_new] = 1;//makes the values in the array equal to a black dot on the screen for every iteration

		unsigned int dice_roll = rand() % sum_v_prob;//sets the random number dice roll to be any value from 0 to the sum of the vector v_prob
		int cumulative_prob = 0;
		for (int j = 0; j<v_x.size(); j++)//this loop finds the ith x and y coordinates 
		//it loops up to the size of the vector that contains all the x-co-ordiantes as it is asumed there is an equal number of x and y coordinates
		{
			cumulative_prob += v_prob[j];//defines the cumulative probability in terms of the j'th element of the probability vector
			if (dice_roll < cumulative_prob)
			{
				x_vertices = v_x[j];//defines the vertex as a random one that is selected
				y_vertices = v_y[j];
				x_distance = x_random - x_vertices;//the distance of the random point to the vertex is found
				x_new = (x_distance / v_factor[j]) + x_vertices;//the new point is set to the distance divided by the scale factor also adding the selected vertex
				x_random = x_new;//for the next iteration, x_random is set as the current new point
				y_distance = y_random - y_vertices;
				y_new = (y_distance / v_factor[j]) + y_vertices;
				y_random = y_new;
				break;
			}

		}



	}
	//Work out max and min pixel values to rescale pixel max/min for easy visualisation
	double min = 9e9;
	double max = -9e9;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j <N; j++)
		{
			if (data[i][j] < min)
			{
				min = data[i][j];
			}
			if (data[i][j] > max)
			{
				max = data[i][j];
			}
		}
	}

	std::cout << "Detected Cell Minimum: " << min << std::endl;
	std::cout << "Detected Cell Maximum: " << max << std::endl;

	//Create output bmp container
	BMP Output;
	Output.SetSize(M, N);
	Output.SetBitDepth(32);

	// plot the pixels
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double scaled_value = 1 - (data[i][j] - min) / (max - min + 1e-16);
			ebmpBYTE pixel_value = (ebmpBYTE)(scaled_value * 255.0);
			Output(i, j)->Red = pixel_value;   //
			Output(i, j)->Green = pixel_value; //for more interesting colours you can play around with these
			Output(i, j)->Blue = pixel_value;  //
		}
	}

	//Save output
	Output.WriteToFile("test.bmp");

	//Remove data array from heap

	for (int i = 0; i < M; ++i)
	{
		delete[] data[i];
	}
	delete[] data;

}