//Created by Nickolas Theodoulou 
//December 2016
#include "EasyBMP.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

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
	//Reads in the data for the functions from a text file
	std::ifstream e1file;
	e1file.open("IFS_Fern.txt", std::ifstream::in);

	std::string line;
	std::getline(e1file, line);
	//initialised the vectors that contain all the elements in the matrix equation
	std::vector<double> v_a_11, v_a_12, v_a_21, v_a_22, v_b_1, v_b_2, v_prob;
	//initialised the vectors that contain all the x and y elements that will be defined based on the values in the elements
	std::vector<double> v_x_n, v_y_n;

	while (std::getline(e1file, line))
	{
		std::stringstream linestream(line);
		double A_11, A_12, A_21, A_22, B_1, B_2, PROB;
		linestream >> A_11 >> A_12 >> A_21 >> A_22 >> B_1 >> B_2 >> PROB;
		v_a_11.push_back(A_11);//puts the first column into the vector v_a_11 as this contains n a_11 values where n is the number of transformations
		v_a_12.push_back(A_12);
		v_a_21.push_back(A_21);
		v_a_22.push_back(A_22);
		v_b_1.push_back(B_1);
		v_b_2.push_back(B_2);
		v_prob.push_back(PROB);//i added an extra row in the text file for the probability which is defined as an intiger value 

	}
	int number_of_iterations = 100000;//allows the user to select the number of iterations


	int sum_v_prob = 0;
	//simple loop to find the sum of all the probabilites so that the probability distribtuion can be found
	for (unsigned int i = 0; i < v_prob.size(); i++)
	{
		sum_v_prob += v_prob[i];
	}
	//initialise all the variables that will be used within the for loop to generate the new points
	double x_new = 0, y_new = 0, x_n = 0, y_n = 0, x_max = 0, y_max = 0, x_min = 0, y_min = 0, translation = 0, scalefactor = 0, x_translation = 0, y_translation = 0;
	int x_new_scaled = 0, y_new_scaled = 0;

	for (int i = 0; i < v_a_11.size(); i++)
	{
		//checks if the mappings are valid
		if (pow(v_a_11[i], 2) + pow(v_a_21[i], 2) <1 && pow(v_a_12[i], 2) + pow(v_a_22[i], 2) <1 &&
			pow(v_a_11[i], 2) + pow(v_a_12[i], 2) + pow(v_a_21[i], 2) + pow(v_a_22[i], 2) - pow((v_a_11[i] * v_a_22[i]) - (v_a_12[i] * v_a_21[i]), 2) <1)
		{
			continue;//if the values are all correct then carrys on the code
		}
		else
		{
			std::cout << "Can't run algorithm" << std::endl;//If mappings aren't valid, the algorithm won't run
			return 0;//terminates the programme at this point if the if condition is not met as an error would be met if the programme continued to ran
		}
	}
	std::cout << "Mappings are valid" << std::endl;

	for (int i = 0; i < number_of_iterations; i++)// Generate x and y points equal to the number_of_iterations
	{
		unsigned int dice_roll = rand() % sum_v_prob;//sets the random number dice roll to be any value from 0 to the sum of the vector v_prob
		int cumulative_prob = 0;
		for (int j = 0; j<v_a_11.size(); j++)//this loop finds the ith x and y coordinates 
										  //it loops up to the size of the vector that contains all the x-co-ordiantes as it is asumed there is an equal number of x and y coordinates
		{
			cumulative_prob += v_prob[j];//defines the cumulative probability in terms of the j'th element of the probability vector
			if (dice_roll < cumulative_prob)
			{
				x_new = (v_a_11[j] * x_n) + (v_a_12[j] * y_n) + v_b_1[j];//sets the x variable as described in the matrix equation in terms of the elements
				y_new = (v_a_21[j] * x_n) + (v_a_22[j] * y_n) + v_b_2[j];//sets the y variable as described in the matrix
				x_n = x_new;//for the next iteration, x_new is set as the new point 
				y_n = y_new;

				v_x_n.push_back(x_new);//puts the x coordinates into a vector so they can be scaled and translated
				v_y_n.push_back(y_new);
				break;
			}
		}

	}

	x_min = *std::min_element(v_x_n.begin(), v_x_n.end());//find the smallest value of x in the vector
	x_max = *std::max_element(v_x_n.begin(), v_x_n.end());//find the largest value of x in the vector
	y_min = *std::min_element(v_y_n.begin(), v_y_n.end());
	y_max = *std::max_element(v_y_n.begin(), v_y_n.end());
	//these values are found as they allow me to define an algorithm to translate and scale up all the values
	
	std::cout << "The smallest x value is " << x_min << std::endl;
	std::cout << "The largest x value is " << x_max << std::endl;
	std::cout << "The smallest y value is " << y_min << std::endl;
	std::cout << "The largest y value is " << y_max << std::endl;
	
	double delta_x = x_max - x_min;
	double delta_y = y_max - y_min;
	double s_f_x = (M / delta_x)*0.9999;
	double s_f_y = (N / delta_y)*0.9999;

	if (s_f_x < s_f_y)
	{
		double scalefactor = s_f_x;//makes the scale factor equal the smallest ratio so that the image isn't distorted
	}
	else
	{
		double scalefactor = s_f_y;
	}
	//generate the image by itereating through the two vectors containing the x and y co-ordinates and using the scale factor and translation to size up the image without distorting it
	for (int i = 0; i < number_of_iterations; i++)
	{
		//these four if loops check are more of a fail safe just incase any values that would throw an error pass through and terminate the programme if there is an error
		if (x_new_scaled >= M)
		{
			std::cout << x_new_scaled << " x too large" << std::endl;
			return 0;
		}
		if (x_new_scaled < 0)
		{
			std::cout << x_new_scaled << " x too small" << std::endl;
			return 0;
		}
		if (y_new_scaled >= N)
		{
			std::cout << y_new_scaled << " y too large" << std::endl;
			return 0;
		}
		if (y_new_scaled < 0)
		{
			std::cout << y_new_scaled << " y too small" << std::endl;
			return 0;
		}
		x_new = v_x_n[i];//same logic as before to define the new poins in the iteration
		y_new = v_y_n[i];
		x_n = x_new;
		y_n = y_new;
		x_new_scaled = ((x_new - x_min) * s_f_x);//scales up all the x and y co-ordinates (no need to scale down due to the conditions of a11,a12 etc)
		y_new_scaled = ((y_new - y_min) * s_f_y);//scales up all the x and y co-ordinates (no need to scale down due to the conditions of a11,a12 etc)
		data[x_new_scaled][y_new_scaled] = 1;//makes the values in the array equal to a black point on the screen

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
	Output.WriteToFile("leaf.bmp");

	std::cout << "check" << std::endl;
	//Remove data array from heap

	for (int i = 0; i < M; ++i)
	{
		delete[] data[i];
	}
	delete[] data;

}