/*
Author: Kenneth Lamb
Date: 10/24/2019
Filename: Triangles
Purpose: To calculate 3 values given from files to see if they make a triangle and if so what type of triangles as well as the perimeter and area of them.
Error Yes to see if there is a valid file inputed from the user.
Assumptions: That this will be able to calculate if the 3 values are indeed a triangle and if so what type and calculate the area and perimeter.
Input/ Output: Output is sent to the output file results.out and Input is taken care of by the user to select a file.
*/


#include <iostream> //Handles the input output stream
#include <fstream> //this handles the file stream
#include <string> //This handles all string functions
#include <cmath> //This is used for mathmatical equations
#include <iomanip> //This is used to manipulate the output

using namespace std;

//These are the functions we have below///////////////////////////////////////////////////////////////
bool IsTriangle(int num1, int num2, int num3);
bool IsRight(int num1, int num2, int num3);
bool IsScalene(int num1, int num2, int num3);
bool IsIsosceles(int num1, int num2, int num3);
bool IsEquilateral(int num1, int num2, int num3);

//Float Functions to calculate area, perim and the averages of both
float TriangleArea(int num1, int num2, int num3);
float TrianglePerim(int num1, int num2, int num3);
float CalcAverages(int &total, float &totalPerim, float &totalArea, string name);

//Variable to print the file headings
void PrintHeading(string name, ofstream& cout);

//Functions to get and print the statistics for both files
void PrintErrorLog(int side1, int side2, int side3, ofstream& file);
void PrintStatistics(int right, int scale, int equil, int isco, int total, float totalPerim, float totalArea, ofstream &results);
void GetStatistics(int side1, int side2, int side3, int& countRight, int& countScale, int& countEquil, int& countIsco, int& total);


int main()
{
	ifstream din; //This is the input file stream
	ofstream dout; //This is the output file stream for the results.out
	ofstream errorLog;//This is the output for the error.log
	string inputFileName; //This will hold the file name that will be inputed by the user

	int side1; //This will hold the first integer value from the input file
	int side2; //This will hold the second integer value from the input file
	int side3; //This will hold the third integer value from the input file
	bool error;//This will hold the boolean of the file error to use in the do while loop

	//Variables to hold how many triangles and what types
	int countRight = 0;
	int countScale = 0;
	int countEquil = 0;
	int countIsco = 0;
	int total = 0; //Holds how many triangles their are

	//Holds the variables for the averages of Area and Perimeters of the triangles
	float totalArea=0;
	float totalPerim=0;


	dout << fixed << showpoint << setprecision(2); //This will set the decimal to show in the float numbers and set the decimal to show 2 places.

	do //Error checking the file name.
	{
		cout << "Please enter a file name " << endl;
		cin >> inputFileName;

		din.open(inputFileName);

		dout.open("results.out");
		errorLog.open("error.log");

		if (!din)
		{
			cout << "File " << inputFileName << " not found. Please try again." << endl;
			din.clear();
			error = true;
		}
		else
		{
			error = false;
		}
	} while (error);

	//Print the headings to each output file
	PrintHeading("results", dout);
	PrintHeading("errorlog", errorLog);

	//Priming Read
	din >> side1; //sets side 1 to the first integer in the input file.
	din >> side2; //sets side 2 to the second integer in the input file.
	din >> side3; //sets side 3 to the third integer in the input file.

	while (din)//Loop Test
	{
		//If the above sides do not calculate a triangle the below code will not run. 
	//Checks to see if it is a Right triangle
		if (IsTriangle(side1, side2, side3))
		{
			GetStatistics(side1, side2, side3, countRight, countScale, countEquil, countIsco, total);//run the function getStatistics to see how many of each triangle there is.

			totalArea = TriangleArea(side1, side2, side3) + totalArea;
			totalPerim = TrianglePerim(side1, side2, side3) + totalPerim;

		}
		else
		{
			PrintErrorLog(side1, side2, side3, errorLog); //Run all of the non triangle through the printErrorLog function to see why they are not triangles
		}
		//Modify LCV
		din >> side1; //sets side 1 to the first integer in the input file.
		din >> side2; //sets side 2 to the second integer in the input file.
		din >> side3; //sets side 3 to the third integer in the input file.
	}


	//Here we are outputting to the results file
	PrintStatistics(countRight, countScale, countEquil, countIsco, total, totalPerim, totalArea, dout);
	
	
	//Close the file streams
	din.close();
	dout.close();
	errorLog.close();

	system("pause");
	return 0;
}

bool IsTriangle(int num1, int num2, int num3) //This is the function that will calculate if it is a valid triangle
{
		//*********************************************************************
		//	IsTriangle
		//
		//	task: This function will calculate if the sides are a triangle
		//	data in: num1, num2, num3
		//	data out: true or false
		//
		//********************************************************************

	//Pre:Needs to have the values num1 - 3 initialized before it can check the calculation
	//Post:checks the values and will return true or false depending on the outcome.
	//Purpose:To check if 3 given values are a triangle
	// check for negative numbers.
	if ((num1 >= 0) && (num2 >= 0) && (num3 >= 0)) //This formula calculates if the numbers are negative or not
	{
		//check if the sides equal a triangle.
		if ((num1 + num2 > num3) && (num2 + num3 > num1) && (num1 + num3 > num2)) //This calculates the Triangle Inequality Theorem to see if the 3 values make a triangle
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

bool IsRight(int num1, int num2, int num3) //This function will check if the triangle given with the three values make up a right triangle
{
		//*********************************************************************
		//	IsRight
		//
		//	task: This function will calculate if the triangle is an Right
		//	data in: num1, num2, num3
		//	data out: true or false
		//
		//********************************************************************

	//Pre:Needs to have the values num1 - 3 initialized before it can check the calculation
	//Post:checks the values and will return true or false depending on the outcome.
	//Purpose:To check if 3 given values are a right triangle
	//The below statement will calculate if the triangle is a right triangle
	if ((pow(num1, 2)) + (pow(num2, 2)) == (pow(num3, 2)) || (pow(num1, 2)) + (pow(num3, 2)) == (pow(num2, 2)) || (pow(num2, 2)) + (pow(num3, 2)) == (pow(num1, 2)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsScalene(int num1, int num2, int num3) //This function will check to see if the triangle is Scalene
{
		//*********************************************************************
		//	IsScalene
		//
		//	task: This function will calculate if the triangle is an Scalene
		//	data in: num1, num2, num3
		//	data out: true or false
		//
		//********************************************************************

	//Pre:Needs to have the values num1 - 3 initialized before it can check the calculation
	//Post:checks the values and will return true or false depending on the outcome.
	//Purpose:To check if 3 given values are a scalene triangle
	if (num1 != num2 && num2 != num3 && num1 != num3) //This is the formula to calculate if the triangle is Scalene
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsIsosceles(int num1, int num2, int num3) //This function will check to see if the triangle is an iscosceles
{
		//*********************************************************************
		//	IsIsosceles
		//
		//	task: This function will calculate if the triangle is an Isosceles
		//	data in: num1, num2, num3
		//	data out: true or false
		//
		//********************************************************************

	//Pre:Needs to have the values num1 - 3 initialized before it can check the calculation
	//Post:checks the values and will return true or false depending on the outcome.
	//Purpose:To check if 3 given values are a isosceles triangle
	if (num1 == num2 || num1 == num3 || num2 == num3) //This formula calculates if the triangle is Isosceles
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsEquilateral(int num1, int num2, int num3) //This function will check to see if the triangle is an Equilateral triangle
{
		//*********************************************************************
		//	IsEquilateral
		//
		//	task: This function will calculate if the triangle is an equilateral
		//	data in: num1, num2, num3
		//	data out: true or false
		//
		//********************************************************************

	//Pre:Needs to have the values num1 - 3 initialized before it can check the calculation
	//Post:checks the values and will return true or false depending on the outcome.
	//Purpose:To check if 3 given values are a equilateral triangle
	if (num1 == num2 && num2 == num3) //This is the formula to calculate if the triangle is Equilateral
	{
		return true;
	}
	else
	{
		return false;
	}
}

float TriangleArea(int num1, int num2, int num3) //This function will first calculate the half of the perimeter then it will calculate the area of the triangle
{
		//*********************************************************************
		//	TriangleArea
		//
		//	task:	  This function will calculate the area of the triangles
		//	data in: num1, num2, num3
		//	data out: area
		//
		//********************************************************************

	//Pre:Needs to have num1-3 initialized before it can do its calculations
	//Post:Calculates the are of the triangle then returns the area value
	//Purpose:To calculate the area of a triangle
	float halfPerim; //this will hold the value of half of the perimeter
	float area; //this will hold the value of the area

	halfPerim = (float)(num1 + num2 + num3) / 2.0f; //This will calculate half of the perimeter

	area = (float)(sqrt(halfPerim * (float)(halfPerim - num1) * (float)(halfPerim - num2) * (float)(halfPerim - num3))); //This will take the halfPerim value and calculate the area

	return area;
}

float TrianglePerim(int num1, int num2, int num3) // This function will calculate the perimeter of the triangle
{

		//*********************************************************************
		//	TrianglePerim
		//
		//	task:	  This function will calculate the perimeter of the triangles
		//	data in: num1, num2, num3
		//	data out: perim
		//
		//********************************************************************

	//Pre:Needs to have num1-3 initialized before it can do its calculations
	//Post:Calculates the perimeter of the triangle then returns the perimeter value
	//Purpose:To calculate the perimeter of the triangle
	float perim; //this will hold the value of the perimeter

	perim = (float)num1 + (float)num2 + (float)num3; //This will calculate the perimeter

	return perim;
}

//Print Heading for either 
void PrintHeading(string name, ofstream& dout)
{

		//*********************************************************************
		//	PrintHeading
		//
		//	task:	  This function will print headings to the results and error log file
		//	data in:  name, file dout
		//	data out: 
		//
		//********************************************************************

		//Pre:Needs to have name and dout initialized
		//Post:Print out the heading for each file
		//Purpose:To print out the heading for the output files

	if (name == "results")
	{
		//This is the header to the file telling them what this program is about as well as what file is being used
		dout << "*******************************************************************" << endl;
		dout << endl;
		dout << "*                                                                 *" << endl;
		dout << endl;
		dout << "*                    Triangle Statistics                          *" << endl;
		dout << endl;
		dout << "*                    Output file name: results.out                *" << endl;
		dout << endl;
		dout << "*                                                                 *" << endl;
		dout << endl;
		dout << "*******************************************************************" << endl;

		dout << endl;
		dout << "The file has the following statistics:" << endl;
	}
	else
	{
		//This is the header to the file telling them what this program is about as well as what file is being used
		dout << "*******************************************************************" << endl;
		dout << endl;
		dout << "*                                                                 *" << endl;
		dout << endl;
		dout << "*                    Triangle Statistics                          *" << endl;
		dout << endl;
		dout << "*                    Output file name: error.log                  *" << endl;
		dout << endl;
		dout << "*                                                                 *" << endl;
		dout << endl;
		dout << "*******************************************************************" << endl;

		dout << endl;
		dout << "The following sides are invalid:" << endl;
	}
	
}

//prints errors to the error log
void PrintErrorLog(int side1, int side2, int side3, ofstream& error)
{

	//*********************************************************************
	//	PrintErrorLog
	//
	//	task:	  This function prints out the errors of the sides that do not make triangles
	//	data in:  side1, side2, side3, error.log file
	//	data out: 
	//
	//********************************************************************

	//Pre:Needs to have side1, side2, side3, error.log file initialized
	//Post:Calculate why the sides do not make a triangle and print out the information to error.log file
	//Purpose:To print out the errors of the file of the sides that do not form a triangle

	if ((side1 >= 0) && (side2 >= 0) && (side3 >= 0)) //This formula calculates if the numbers are negative or not
	{
		if (side1 == 0 || side2 == 0 || side3 == 0)
		{
			error << setw(9);
			error << side1 << " " << side2 << " " << side3 << " " << "- Side(s) can not be zero" << endl;
		}
		else
		{
			error << setw(9);
			error << side1 << " " << side2 << " " << side3 << " " << "- Can not form a triangle" << endl;
		}

	}
	else
	{
		error << setw(9);
		error << side1 << " " << side2 << " " << side3 << " " << "- Side(s) can not be negative" << endl;
	}

}

//prints the statistics to the results.out
void PrintStatistics(int right, int scale, int equil, int isco, int total, float totalPerim, float totalArea, ofstream &results)
{

	//*********************************************************************
	//	PrintStatistics
	//
	//	task:	  This function prints out the statistics to the results table of the input file
	//	data in:  right, scale, equil, isco, total, totalPerim, totalArea, results output file
	//	data out: 
	//
	//********************************************************************

	//Pre:Needs to have right, scale, equil, isco, total, totalPerim, totalArea, results output file initialized
	//Post:Prints out the statistics to the results.out output file
	//Purpose:To print out the statistics of the triangles from the input file to the results output file.

	results << setw(6) << total << setw(26) << " total # of triangle(s)" << endl;

	results << setw(6) << isco << setw(25) << " isosceles triangle(s)" << endl;

	results << setw(6) << equil << setw(27) << " equilateral triangle(s)" << endl;

	results << setw(6) << scale << setw(23) << " scalene triangle(s)" << endl;

	results << setw(6) << right << setw(21) << " right triangle(s)" << endl;

	results << setw(9) << CalcAverages(total, totalPerim, totalArea, "Area") << " is the average area of all triangles." << endl;

	results << setw(9) <<  CalcAverages(total, totalPerim, totalArea, "Perim") << " is the average perimeter of all triangles." << endl;
}

//calculates how many of each type of triangle
void GetStatistics(int side1, int side2, int side3, int& countRight, int& countScale, int& countEquil, int& countIsco, int& total)
{

//*********************************************************************
//	GetStatistics
//
//	task:	  This function counts the number of each triangle as well as counts the number of passes of the function
//	data in:  side1, side2, side3, countRight, countScale, countEquil, countIsco, total
//	data out: 
//
//********************************************************************
	//Pre:Needs side1, side2, side3, countRight, countScale, countEquil, countIsco, total to be initialized
	//Post:Counts each function and returns the number to the countRight, countScale, countEquil, countIsco, total variables.
	//Purpose:To calculate the number of each triangle in the file as well as total triangles

	if (IsRight(side1, side2, side3))//Checks to see if it is a right triangle
	{
		countRight++;
	}

	if (IsScalene(side1, side2, side3))//Checks to see if it is a Scalene triangle
	{
		countScale++;
	}

	if (IsIsosceles(side1, side2, side3))//Checks to see if it is an Isosceles triangle
	{
		countIsco++;
	}

	if (IsEquilateral(side1, side2, side3))//Checks to see if it is an Equilateral triangle
	{
		countEquil++;
	}

	total++;
}


float CalcAverages(int &total, float &totalPerim, float &totalArea, string name)
{

//*********************************************************************
//	CalcAverages
//
//	task:	  This function calculates total averages for Perimeter and Area
//	data in:  Total, TotalPerim, Total Area, Name
//	data out: areaAve and perimAve are returned based on name inputed
//
//********************************************************************

	//Pre:Needs to have total, totalperim, totalarea, and name initialized to run.
	//Post:Calculates the area average and perimeter average and returns them based on the name given in the parameter.
	//Purpose:To calculate the average of the area and perimeters of the triangles

	float areaAve;
	float perimAve;
	if (name == "Area")
	{
		areaAve = totalArea / (float)total;
		return areaAve;
	}
	else
	{
		perimAve = totalPerim / (float)total;
		return perimAve;
	}
}