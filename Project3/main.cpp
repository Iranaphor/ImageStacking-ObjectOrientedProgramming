///TODO:
//	1.		Decrease time of median
//	1-1.		Remove vecotors entirely;
//	1-1-1.			Create std::system to pushback c-style array
//	1-1-2.			Create std::system to insert into c-style array
//	2.		Fix Image destructor
//	3.		Include some inheritance for ImageInfo
//	4.		Include some form of polymorphism
//	5.		Create new operator overloading
//	6.		Include ROI zoom class
//	6-1.		Include variable input

//main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Image.h"
#include "io.h"
#include "zoom.h"
#include "stackerBasic.h"
#include "stackerRolling.h"

#include <memory>	//Memory Management
#include <vector>	//Vector Use
#include <time.h>	//Time Management
#include <windows.h>	//AFK
#include <time.h>		//AFK - RandomNumber
#include <cstdlib>		//AFK - RandomNumber
#include <stdlib.h>		
#include <stdio.h>
#include <chrono>
#include <ctime>

#include <limits>

#include "common.h"		//Extern (global) variables

///Extern (global) variables
std::string zoomImgLocal = "Images/Zoom/zIMG_";
std::string stackLocal = "Images/ImageStacker_set1/IMG_";
int totalstackNum = 13;
int iWidth;
int iHeight;
int zWidth;
int zHeight;


using namespace std;
int AFK(int);
int position = 0; 
int randS;


int main()
{

	inputoutput io;
	zoom zm;
	stackerBasic sB;
	stackerRolling sR;

	std::system("Color B1");
	srand(time(NULL));	randS = rand() % 100;
	
	Image *out = new Image(0, 0);
	clock_t t;	t = clock();
	
	
	bool loop1;
	bool loop2;
	bool loop3;
	string option1 = "a";
	string option2 = "a";
	int totalStack = 0;

	bool sloop2;
	bool sloop3;
	bool sloop4;
	bool schoice1 = false;
	string soption2 = "a";
	string soption3 = "1.6";
	string soption4 = "a";

	bool zloop2;
	bool zloop3;
	bool zloop4;
	bool zloopR1;
	bool zloopR2;
	bool zloopR3;
	bool zloopR4;
	bool zloopR5;
	bool zchoice1 = false;
	string zoption2 = "a";
	string zoption3 = "1";
	string zoption4 = "a";
	string zoptionR1 = "a";
	int zoomFactor;
	bool zRloop;
	bool ROIc1 = false, ROIc2 = false, ROIc3 = false, ROIc4 = false, ROIc5 = false, ROIc6 = false;

	loop1 = true;
	while (loop1) {

		std::cout << "\n" << flush; std::system("CLS");
		std::cout << "What action would you like to perform:" << std::endl;
		std::cout << "	- For Image (S)tacking, enter \"S\"" << std::endl;
		std::cout << "	- For Image (Z)oom, enter \"Z\"" << std::endl;
		std::cout << "	- For Image (O)ptions, enter \"O\"" << std::endl;
		std::cout << std::endl;
		std::cout << "	- To Exit the application, enter \"E\"" << std::endl;
		std::cout << ":: ";
		std::cout << '\a'; std::cin >> option1;
		std::cout << std::endl;


		if (option1 == "o" || option1 == "O") 
		{
			loop2 = true;
			while (loop2)
			{
				std::cout << "\n" << flush; std::system("CLS");
				std::cout << "Options Menu:" << std::endl;
				std::cout << "Please select one of the following:" << std::endl;
				std::cout << "	- (1) Total Images to Stack" << std::endl;
				std::cout << "	- (2) Image Stacking Read Location" << std::endl;
				std::cout << "	- (3) Zoom Image Read Location" << std::endl;
				std::cout << std::endl;
				std::cout << "	- (E) Exit" << std::endl;
				std::cout << ":: ";
				std::cout << '\a'; std::cin >> option2;

				if (option2 == "1")
				{
					loop3 = true;
					while (loop3) {
						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Please Enter the total number of Images you wish to stack (min:5):" << std::endl;
						std::cout << "	- (E) Exit" << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> option2;

						try
						{

							if (option2 == "e" || option2 == "E") {
								std::cout << "Returning to Options Menu..." << std::endl;
								std::system("pause");
								loop3 = false;
							}
							else {

								totalStack = stoi(option2);

								if (totalStack < 5)
								{
									std::cout << "The value you entered is not valid;" << std::endl;
									std::cout << "	- Accepted values: Any whole number greater then 4" << std::endl;
									std::system("pause");
								}
								else {

									totalstackNum = totalStack;
									std::system("pause");
									loop3 = false;
								}


							}
						}
						catch (...) {
							std::cout << "The value you entered is not valid;" << std::endl;
							std::cout << "	- Accepted values: Any whole number greater then 4" << std::endl;
							std::system("pause");
						}
					}
				}
				else if (option2 == "2") 
				{
					loop3 = true;
					while (loop3) {

						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Please Enter the file location and name convention for the images to stack." << std::endl;
						std::cout << "Enter the file locatoin relative to the application." << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> option2;


						if (option2 == "e" || option2 == "E") {
							loop3 = false;
						}
						else {
							try {


								stackLocal = option2.c_str();
								std::string s = stackLocal + "1.ppm";
								const char *c = s.c_str();
								Image *stackLocalTest = &io.readPPM(c);

								iWidth = stackLocalTest->getWidth();
								iHeight = stackLocalTest->getHeight();

								loop3 = false;

							}
							catch (...) {

								std::cout << "The location you defined does not exist." << std::endl;
								std::cout << "	- Eg. Images/ImageStacker_set1/IMG_" << std::endl;
								std::system("pause");

							}
						}
					}
				}
				else if (option2 == "3") 
				{
					
					loop3 = true;
					while (loop3) {

						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Please Enter the file location and name for the image you may wish to zoom." << std::endl;
						std::cout << "Enter the file locatoin relative to the application." << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> option2;

						if (option2 == "e" || option2 == "E") {
							loop3 = false;
						}
						else {
							try {

								zoomImgLocal = option2.c_str();
								stackLocal = option2.c_str();
								std::string s = stackLocal + "1.ppm";
								const char *c = s.c_str();
								Image *stackLocalTest = &io.readPPM(c);

								iWidth = stackLocalTest->getWidth();
								iHeight = stackLocalTest->getHeight();

								loop3 = false;

							}
							catch (...) {

								std::cout << "The location you defined does not exist." << std::endl;
								std::cout << "	- Eg. Images/Zoom/zIMG_" << std::endl;
								std::system("pause");

							}
						}
					}



				
				}
				else if (option2 == "E" || option2 == "e") { loop2 = false; }
				else {}

			}
		}
		else if (option1 == "s" || option1 == "S") {
			sloop2 = true;
			while (sloop2) {
				schoice1 = false;
				std::cout << "\n" << flush; std::system("CLS");
				std::cout << "Welcome to the Image Stacking area." << std::endl;
				std::cout << "Please select one of the following:" << std::endl;
				std::cout << "	- (1) Mean Rolling Blend" << std::endl;
				std::cout << "	- (2) Range Rolling Blend" << std::endl;
				std::cout << "	- (3) Median Blend" << std::endl;
				std::cout << "	- (4) Median Custom Rolling Blend" << std::endl;
				std::cout << "	- (5) Sigma Clipped Mean Blend (Quick)" << std::endl;
				std::cout << "	- (6) Sigma Clipped Mean Blend (Custom)" << std::endl;
				std::cout << std::endl;
				std::cout << "	- (E) Exit" << std::endl;
				std::cout << ":: ";
				std::cout << '\a'; std::cin >> soption2;

				if (soption2 == "1") 
				{
					
					auto start = std::chrono::system_clock::now();

					out = &sB.meanRollingBlend();

					auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

					std::system("pause");

					schoice1 = true;
				
				}
				else if (soption2 == "2") 
				{
					
					auto start = std::chrono::system_clock::now();

					out = &sR.rangeRollingBlend(0, 0); 
					
					auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

					std::system("pause");

					schoice1 = true;
					
				}
				else if (soption2 == "3") 
				{ 

					auto start = std::chrono::system_clock::now();

					out = &sB.medianBlend();
					
					auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

					std::system("pause");

					schoice1 = true;

				}
				else if (soption2 == "4") 
				{
					auto start = std::chrono::system_clock::now();

					out = &sR.medianRollingBlend();

					auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

					std::system("pause");
					
					schoice1 = true;
				}
				else if (soption2 == "5") 
				{ 
					
					auto start = std::chrono::system_clock::now();

					out = &sB.sigmaClippedMeanBlend();

					auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
					std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

					std::system("pause");
					
					
					schoice1 = true; 
				
				
				}
				else if (soption2 == "6")
				{
					std::cout << "Enter your custom sigma factor:" << std::endl;
					std::cout << "	Reccomended value (1.6)" << std::endl;
					std::cout << ":: ";
					std::cout << '\a'; std::cin >> soption3;

					sloop3 = true;

					while (sloop3) {
						try {
							float temp = ::atof(soption3.c_str()); //https://stackoverflow.com/questions/1012571/stdstring-to-float-or-double


							auto start = std::chrono::system_clock::now();
							
							out = &sB.sigmaClippedMeanBlend(temp);
							
							auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
							std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

							std::system("pause");
							
							
							sloop3 = false;
						}
						catch (...) {
							std::cout << "The value you entered is not valid;";
							std::cout << "	- Example values: 1.4, 0.2, 0.01, 3.5";
							std::system("pause");
						}
					}
					schoice1 = true;
				}

				else if (soption2 == "E" || soption2 == "e") { sloop2 = false; }
				else {
					std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
					std::system("pause");
					schoice1 = false;
				}

				if (schoice1) {
					sloop4 = true;
					while (sloop4) {
						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Would you like to save the stacked image? (Y)/(N)" << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> soption4;
						if (soption4 == "Y" || soption4 == "y") {

							io.writePPM(*out, "result.ppm");
							std::cout << "\n" << flush; std::system("CLS");
							std::cout << "Your stacked image has been written." << std::endl;
							std::system("pause");
							sloop4 = false;
						}
						else if (soption4 == "N" || soption4 == "n") {
							std::cout << "Image not saved." << std::endl;
							std::system("pause");
							sloop4 = false;
						}
						else {
							std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
							std::system("pause");
						}
					}
					delete[] out->pixels;
				}
			}
		}
		else if (option1 == "z" || option1 == "Z") {
			zloop2 = true;
			std::cout << "Before we begin, please insure that the .ppm image you wish to zoom is in the correct folder." << std::endl;
			std::cout << "Press the enter key to continue when this is completed..." << std::endl;
			std::cin;
			std::cout << std::endl;
			while (zloop2) {
				zchoice1 = false;
				std::cout << "\n" << flush; std::system("CLS");
				std::cout << "Welcome to the Image Zoom area." << std::endl;
				std::cout << "Please select one of the following:" << std::endl;
				std::cout << "	- (1) Nearest Neighbor Zoom" << std::endl;
				std::cout << "	- (2) Image Interpolation Zoom" << std::endl;
				std::cout << "	- (3) Region of Interest Zoom" << std::endl;
				std::cout << std::endl;
				std::cout << "	- (E) Exit" << std::endl;
				std::cout << ":: ";
				std::cout << '\a'; std::cin >> zoption2;

				if (zoption2 == "1")
				{
					zloop3 = true;
					zchoice1 = false;

					while (zloop3) { //while not valid value

						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Please enter the power of 2 you wish to zoom by." << std::endl;
						std::cout << "	Reccomended value ( < 3 )" << std::endl;
						std::cout << ":: ";
						std::cin >> zoption3;
						try 
						{
							zoomFactor = stoi(zoption3);

							if (zoomFactor > 3 || zoomFactor < 0)
							{
								std::cout << "The value you entered is not valid;" << std::endl;
								std::cout << "	- Accepted values: 1, 2, 3" << std::endl;
								std::system("pause");
							}
							else {
								auto start = std::chrono::system_clock::now();
								
								out = &zm.doubleWidthHeightEx(zoomFactor);
								
								auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
								std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

								std::system("pause");
								zloop3 = false;
							}


						}
						catch (...) {
							std::cout << "The value you entered is not valid;" << std::endl;
							std::cout << "	- Accepted values: 1, 2, 3" << std::endl;
							std::system("pause");
						}

					}

					zchoice1 = true;
				}
				else if (zoption2 == "2")
				{
					zloop3 = true;
					zchoice1 = false;

					while (zloop3) { //while not valid value

						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Please enter the power of 2 you wish to zoom by." << std::endl;
						std::cout << "	Reccomended value ( < 3 )" << std::endl;
						std::cout << ":: ";
						std::cin >> zoption3;
						
						try
						{
							zoomFactor = stoi(zoption3);

							if (zoomFactor > 4)
							{
								std::cout << "The value you entered is not valid;" << std::endl;
								std::cout << "	- Accepted values: 1, 2, 3" << std::endl;
								std::system("pause");
							}
							else { 
								auto start = std::chrono::system_clock::now();

								out = &zm.doubleWidthHeightAvg(zoomFactor);

								auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
								std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

								std::system("pause");
								zloop3 = false;
							}

						}
						catch (...) {
							std::cout << std::endl;
							std::cout << "The value you entered is not valid;" << std::endl;
							std::cout << "	- Accepted values: 1, 2, 3" << std::endl;
							std::system("pause");
						}

					}

					zchoice1 = true;
				}
				else if (zoption2 == "3")
				{
					zRloop = true;
					Image *imgToZoom = new Image(0, 0);
					imgToZoom = &io.readPPM("Images/Zoom/zIMG_1.ppm");
					int topR = 0, topC = 0, selW = 0, selH = 0, zmF = 0;	

					ROIc1 = false, ROIc2 = false, ROIc3 = false, ROIc4 = false, ROIc5 = false, ROIc6 = false;
					while (zRloop) {

						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Welcome to the Image Zoom area." << std::endl;
						std::cout << "Image Width: " << imgToZoom->getWidth() << std::endl;
						std::cout << "Image Height: " << imgToZoom->getHeight() << std::endl;
						std::cout << "Your Image will be saved when you exit the ROI section." << std::endl;
						std::cout << "Please begin by selecting the image one of the following:" << std::endl;
						std::cout << "	- (1) Top Row";				if (ROIc1) { std::cout << "		~~Entered Successfully: " << topR; } std::cout << std::endl;
						std::cout << "	- (2) First Column";		if (ROIc2) { std::cout << "	~~Entered Successfully: " << topC; } std::cout << std::endl;
						std::cout << "	- (3) Selection Width";		if (ROIc3) { std::cout << "	~~Entered Successfully: " << selW; } std::cout << std::endl;
						std::cout << "	- (4) Selection Height";	if (ROIc4) { std::cout << "	~~Entered Successfully: " << selH; } std::cout << std::endl;
						std::cout << "	- (5) Zoom Factor";			if (ROIc5) { std::cout << "	~~Entered Successfully: " << zmF; } std::cout << std::endl;
						std::cout << std::endl;
						std::cout << "	- (6) Extract and Zoom" << std::endl;
						std::cout << std::endl;
						std::cout << "	- (E) Exit" << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> zoption3;

						
						if (zoption3 == "1")
						{
							zloopR1 = true; //GET top row
							while (zloopR1) {
								std::cout << "\n" << flush; std::system("CLS");
								std::cout << "Region of Interest Selection:" << std::endl;
								std::cout << "Please select the ROW number for the top of the selection." << std::endl;
								std::cout << ":: ";
								std::cout << '\a'; std::cin >> zoptionR1;
								try
								{
									topR = stoi(zoptionR1);

									if (topR < 2 || topR > imgToZoom->getHeight())
									{
										std::cout << "The value you entered is not a valid number;" << std::endl;
										std::system("pause");
									}
									else { zloopR1 = false; ROIc1 = true;}
								}
								catch (...) {
									std::cout << "The value you entered is not a valid number;" << std::endl;
									std::system("pause");
								}
							}
							
						}
						else if (zoption3 == "2")
						{
							zloopR1 = true; //GET left column
							while (zloopR1) {
								std::cout << "\n" << flush; std::system("CLS");
								std::cout << "Region of Interest Selection:" << std::endl;
								std::cout << "Please select the COLUMN number for the left side of the selection." << std::endl;
								std::cout << ":: ";
								std::cout << '\a'; std::cin >> zoptionR1;
								try
								{
									topC = stoi(zoptionR1);

									if (topC < 2 || topC > imgToZoom->getWidth())
									{
										std::cout << "The value you entered is not a valid number;" << std::endl;
										zloopR1 = false;
										std::system("pause");
									}
									else { zloopR1 = false; ROIc2 = true;}

								}
								catch (...) {
									std::cout << "The value you entered is not a valid number;" << std::endl;
									std::system("pause");
								}
							}
							
						}
						else if (zoption3 == "3")
						{
							if (!ROIc1) {
								std::cout << "You must first define a starting point for your region of interest." << std::endl;
								std::system("pause");
							}
							else {
								zloopR1 = true; //GET selection width (test for EoL)
								while (zloopR1) {
									std::cout << "\n" << flush; std::system("CLS");
									std::cout << "Region of Interest Selection:" << std::endl;
									std::cout << "Please select the WIDTH of the selection." << std::endl;
									std::cout << ":: ";
									std::cout << '\a'; std::cin >> zoptionR1;
									try
									{
										selW = stoi(zoptionR1);

										if (topC + selW > imgToZoom->getWidth())
										{
											std::cout << "The selection choices you have made exceed the size of the image." << std::endl;
											std::cout << "Please ensure your inputs: (left column + width) are smaller than image width." << std::endl;
											zloopR1 = false;
											std::system("pause");
										}
										else { zloopR1 = false; ROIc3 = true; }

									}
									catch (...) {
										std::cout << "The value you entered is not a valid number;" << std::endl;
										std::system("pause");
									}
								}
							}
						}
						else if (zoption3 == "4")
						{
							//GET selection height (test for EoL)
							if (!ROIc2) {
								std::cout << "You must first define a starting point for your region of interest." << std::endl;
								std::system("pause");
							}
							else {
								zloopR1 = true;
								while (zloopR1) {
									std::cout << "\n" << flush; std::system("CLS");
									std::cout << "Region of Interest Selection:" << std::endl;
									std::cout << "Please select the HEIGHT of the selection." << std::endl;
									std::cout << ":: ";
									std::cout << '\a'; std::cin >> zoptionR1;
									try
									{
										selH = stoi(zoptionR1);

										if (topR + selH > imgToZoom->getHeight())
										{
											std::cout << "The selection choices you have made exceed the size of the image." << std::endl;
											std::cout << "Please ensure your inputs: (top row + height) are smaller than image height." << std::endl;
											zloopR1 = false;
											std::system("pause");
										}
										else { zloopR1 = false; ROIc4 = true; }
									}
									catch (...) {
										std::cout << "The value you entered is not a valid number;" << std::endl;
										std::system("pause");
									}
								}
							}
						}
						else if (zoption3 == "5")
						{
							//GET zoom factor
							zloopR1 = true;
							while (zloopR1) {
								std::cout << "\n" << flush; std::system("CLS");
								std::cout << "Region of Interest Selection:" << std::endl;
								std::cout << "Please select the ZOOM FACTOR of the selection." << std::endl;
								std::cout << ":: ";
								std::cout << '\a'; std::cin >> zoptionR1;
								try
								{
									zmF = stoi(zoptionR1);

									if (zmF > 8)
									{
										std::cout << "The value you have entered is not within the acceptable bounds." << std::endl;
										std::cout << "	- Example values: 2, 3, 8" << std::endl;
										zloopR1 = false;
										std::system("pause");
									}
									else { zloopR1 = false; ROIc5 = true;}
								}
								catch (...) {
									std::cout << "The value you entered is not a valid number;" << std::endl;
									std::system("pause");
								}
							}
							
						}
						/*else if (zoption3 == "i" || zoption3 == "I")
						{
							//GET image inputted
							imgToZoom = &io.readPPM("Images/Zoom/zIMG_1.ppm");
							std::cout << "Image Width: " << imgToZoom->getWidth() << std::endl;
							std::cout << "Image Height: " << imgToZoom->getHeight() << std::endl;
							std::system("pause");
							ROIc6 = true;
						}*/
						else if (zoption3 == "e" || zoption3 == "E")
						{
							zRloop = false;
						}
						else if (zoption3 == "6") {
							if (ROIc1 && ROIc2 && ROIc3 && ROIc4 && ROIc5)
							{
								auto start = std::chrono::system_clock::now();
								out = &zm.zoomROI(topR, topC, selW, selH, zmF);
								auto end = std::chrono::system_clock::now();	std::chrono::duration<double> elapsed_seconds = end - start;
								std::cout << "\nTime taken: " << elapsed_seconds.count() << "s\n";

								std::system("pause");
								zchoice1 = true;

								topR = NULL, topC = NULL, selW = NULL, selH = NULL, zmF = NULL;
								ROIc1 = false, ROIc2 = false, ROIc3 = false, ROIc4 = false, ROIc5 = false, ROIc6 = false;

							}
							else {
								std::cout << "You must first fill in each setting." << std::endl;
								std::system("pause");
							}

						}
						else {
							std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
							std::system("pause");
						}
					}
				}
				else if (zoption2 == "E" || zoption2 == "e")
				{
					zchoice1 = false;
					zloop2 = false;
				}
				
				else {
					std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
					std::system("pause");
					zchoice1 = false;
				}

				if (zchoice1) {
					zloop4 = true;
					while (zloop4) {
						std::cout << "\n" << flush; std::system("CLS");
						std::cout << "Would you like to save the image? (Y)/(N)" << std::endl;
						std::cout << ":: ";
						std::cout << '\a'; std::cin >> zoption4;
						if (zoption4 == "Y" || zoption4 == "y") {
							io.writePPM(*out, "result.ppm");
							std::cout << "\n" << flush; std::system("CLS");
							std::cout << "Your stacked image has been written." << std::endl;
							std::cout << "Press the enter key to return to the zoom options." << std::endl;
							std::system("pause");
							zloop4 = false;
						}
						else if (zoption4 == "N" || zoption4 == "n") {
							std::cout << "Image not saved." << std::endl;
							std::system("pause");
							zloop4 = false;
						}
						else {
							std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
							std::system("pause");
						}
					}
					delete[] out->pixels;
				}
			}
		}
		else if (option1 == "e" || option1 == "E") { 
			std::cout << "\n" << flush; std::system("CLS");
			std::cout << "Thank you for using this aPplication." << std::endl;
			std::cout << "As our thanks, we have decided to include this little gift." << std::endl;
			std::cout << "We hope you like it." << std::endl;
			std::cout << std::endl;
			std::cout << "Dont forget to close the application when you are finished with the rave!" << std::endl;
			std::cout << "You can do this using the X in the top left corner, or by holding the Alt button, and pressing F4." << std::endl;
			while (position != -1) { position = AFK(position); }
		}
		else {
			std::cout << "\nYou have entered an incorrect option, please try again." << std::endl;
			std::system("pause");
		}
	}
	
	
	
	std::cin.get();
	return 0;
}


///*/
int AFK(int pos) {
	int x = rand() % 9;
		 if (x == 0) { std::system("Color 0B"); }
	else if (x == 1) { std::system("Color 01"); }
	else if (x == 2) { std::system("Color 02"); }
	else if (x == 2) { std::system("Color 03"); }
	else if (x == 4) { std::system("Color 04"); }
	else if (x == 5) { std::system("Color 05"); }
	else if (x == 6) { std::system("Color 06"); }
	else if (x == 8) { std::system("Color 08"); }
	
	vector <int> outS;
	if (randS < 20){
		outS = { 
			208,	150,	0,	247,	150,	0,	294,	300,	0,	370,	300,	0,	440,	300,	0,	330,	150,	0,	415,	150,	0,	494,	150,	0,	554,	200,	0,	185,	150,	0,	370,	150,	0,	370,	150,	0,	370,	300,	0,	370,	300,	0,	370,	150,	0,	185,	150,	0,	370,	150,	0,	370,	150,	0,	370,	300,	0,	370,	300,	0,	370,	150,	0,	185,	150,	0,	370,	150,	0,	370,	150,	0,	370,	300,	0,	370,	300,	0,	370,	150,	0,	185,	150,	0,	370,	150,	0,	370,	150,	0,	370,	300,	0,	370,	300,	0,	370,	150,	0,	165,	150,	0,	330,	150,	0,	330,	150,	0,	330,	300,	0,	330,	300,	0,	330,	150,	0,	165,	150,	0,	330,	150,	0,	330,	150,	0,	330,	300,	0,	330,	300,	0,	330,	150,	0,	175,	150,	0,	349,	150,	0,	349,	150,	0,	349,	300,	0,	349,	300,	0,	349,	150,	0,	175,	150,	0,	349,	150,	0,	349,	150,	0,	349,	300,	0,	349,	300,	0,	349,	300,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	247,	150,	0,	330,	150,	0,	370,	150,	0,	415,	450,	0,	247,	150,	0,	330,	150,	0,	370,	150,	0,	415,	1050,	0,	370,	150,	0,	415,	150,	0,	370,	150,	0,	349,	1950,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	247,	150,	0,	330,	150,	0,	370,	150,	0,	415,	450,	0,	247,	150,	0,	330,	150,	0,	370,	150,	0,	415,	1050,	0,	440,	150,	0,	494,	150,	0,	440,	150,	0,	415,	2100,	0,	277,	450,	0,	440,	450,	0,	415,	450,	0,	370,	450,	0,	277,	300,	0,	330,	600,	0,	330,	150,	0,	370,	150,	0,	330,	150,	0,	294,	1650,	0,	247,	450,	0,	415,	450,	0,	370,	450,	0,	330,	450,	0,	294,	300,	0,	277,	600,	0,	294,	150,	0,	330,	150,	0,	294,	150,	0,	277,	1650,	0,	277,	450,	0,	440,	450,	0,	415,	450,	0,	370,	450,	0,	277,	300,	0,	330,	600,	0,	330,	150,	0,	370,	150,	0,	330,	150,	0,	294,	1050,	0,	294,	300,	0,	208,	900,	0,	370,	300,	0,	330,	900,	0,	294,	300,	0,	277,	2700,	0,	440,	450,	0,	415,	450,	0,	440,	450,	0,	415,	450,	0,	277,	300,	0,	330,	750,	0,	294,	150,	0,	277,	150,	0,	294,	1650,	0,	415,	450,	0,	370,	450,	0,	415,	450,	0,	330,	450,	0,	294,	300,	0,	277,	600,	0,	294,	150,	0,	330,	150,	0,	294,	150,	0,	277,	1650,	0,	185,	150,	0,	208,	150,	0,	220,	150,	0,	277,	450,	0,	185,	150,	0,	208,	150,	0,	220,	150,	0,	277,	1050,	0,	185,	150,	0,	208,	150,	0,	220,	150,	0,	294,	450,	0,	185,	150,	0,	208,	150,	0,	220,	150,	0,	294,	450,	0,	294,	300,	0,	208,	900,	0,	415,	300,	0,	370,	900,	0,	208,	300,	0,	277,	2400,	0,	440,	150,	0,	415,	150,	0,	440,	1200,	0,	370,	150,	0,	415,	150,	0,	440,	150,	0,	494,	150,	0,	440,	150,	0,	415,	150,	0,	440,	150,	0,	415,	150,	0,	440,	2100,	0,	415,	150,	0,	370,	150,	0,	415,	1200,	0,	330,	150,	0,	370,	150,	0,	415,	150,	0,	440,	150,	0,	415,	150,	0,	370,	150,	0,	415,	150,	0,	370,	150,	0,	349,	2250,	0,	440,	300,	0,	440,	1050,	0,	370,	150,	0,	415,	300,	0,	440,	150,	0,	494,	150,	0,	440,	300,	0,	440,	300,	0,	440,	2100,	0,	494,	150,	0,	440,	150,	0,	494,	1050,	0,	415,	300,	0,	554,	150,	0,	587,	150,	0,	659,	150,	0,	554,	150,	0,	587,	150,	0,	554,	2400,	0,	370,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	370,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	294,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	294,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	330,	300,	0,	494,	150,	0,	466,	450,	0,	494,	300,	0,	330,	300,	0,	494,	150,	0,	466,	300,	0,	587,	150,	0,	659,	150,	0,	587,	150,	0,	554,	2550,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	900,	0,	247,	300,	0,	330,	150,	0,	370,	150,	0,	415,	300,	0,	247,	300,	0,	330,	150,	0,	370,	150,	0,	415,	1050,	0,	370,	150,	0,	415,	150,	0,	370,	150,	0,	349,	1950,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	1050,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	450,	0,	277,	150,	0,	370,	150,	0,	415,	150,	0,	440,	900,	0,	247,	300,	0,	330,	150,	0,	370,	150,	0,	415,	300,	0,	247,	300,	0,	330,	150,	0,	370,	150,	0,	415,	1050,	0,	440,	150,	0,	494,	150,	0,	440,	150,	0,	415,	2100,	0,	277,	450,	0,	440,	450,	0,	415,	450,	0,	370,	450,	0,	277,	300,	0,	330,	600,	0,	330,	150,	0,	370,	150,	0,	330,	150,	0,	294,	1500,	0,	247,	600,	0,	415,	450,	0,	370,	450,	0,	330,	450,	0,	294,	300,	0,	277,	600,	0,	294,	150,	0,	330,	150,	0,	294,	150,	0,	277,	1650,	0,	277,	450,	0,	440,	450,	0,	415,	450,	0,	370,	450,	0,	277,	300,	0,	330,	600,	0,	330,	150,	0,	370,	150,	0,	330,	150,	0,	294,	1050,	0,	294,	150,	0,	208,	1050,	0,	370,	300,	0,	330,	900,	0,	294,	300,	0,	277,	2700,	0,	440,	450,	0,	415,	450,	0,	440,	450,	0,	415,	450,	0,	277,	300,	0,	330,	750,	0,	294,	150,	0,	277,	150,	0,	294,	1650,	0,	415,	450,	0,	370,	450,	0,	415,	450,	0,	330,	450,	0,	294,	300,	0,	277,	600,	0,	294,	150,	0,	330,	150,	0,	294,	150,	0,	277,	1500,	0,	185,	150,	0,	208,	150,	0,	220,	300,	0,	277,	300,	0,	185,	150,	0,	208,	150,	0,	220,	300,	0,	277,	900,	0,	185,	150,	0,	208,	150,	0,	220,	300,	0,	294,	300,	0,	185,	150,	0,	208,	150,	0,	220,	300,	0,	294,	450,	0,	294,	150,	0,	208,	1050,	0,	415,	300,	0,	370,	750,	0,	208,	300,	0,	277,	2550,	0,	440,	150,	0,	415,	150,	0,	440,	1200,	0,	370,	150,	0,	415,	150,	0,	440,	150,	0,	494,	150,	0,	440,	150,	0,	415,	150,	0,	440,	150,	0,	415,	150,	0,	440,	2100,	0,	415,	150,	0,	370,	150,	0,	415,	1200,	0,	330,	150,	0,	370,	150,	0,	415,	150,	0,	415,	150,	0,	370,	150,	0,	415,	150,	0,	370,	150,	0,	349,	2250,	0,	440,	300,	0,	440,	1050,	0,	370,	150,	0,	415,	300,	0,	440,	150,	0,	494,	150,	0,	440,	300,	0,	440,	300,	0,	440,	2100,	0,	494,	150,	0,	440,	150,	0,	494,	1050,	0,	554,	150,	0,	587,	150,	0,	659,	150,	0,	554,	150,	0,	587,	150,	0,	554,	2700,	0,	370,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	370,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	294,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	294,	300,	0,	440,	150,	0,	415,	450,	0,	440,	300,	0,	330,	300,	0,	494,	150,	0,	466,	450,	0,	494,	300,	0,	330,	300,	0,	494,	150,	0,	587,	150,	0,	659,	150,	0,	587,	150,	0,	554,	150,	0
		};

	}
	else if (randS < 40){
		outS = { 
			277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	400,	0,	247,	200,	0,	247,	200,	0,	277,	400,	0,	277,	200,	0,	330,	200,	0,	311,	400,	0,	156,	600,	0,	415,	400,	0,	277,	200,	0,	370,	400,	0,	311,	200,	0,	277,	200,	0,	330,	400,	0,	277,	200,	0,	277,	200,	0,	311,	400,	0,	247,	200,	0,	247,	400,	0,	415,	400,	0,	277,	200,	0,	370,	400,	0,	277,	400,	0,	330,	400,	0,	311,	400,	0,	277,	400,	0,	185,	600,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	370,	200,	0,	330,	200,	0,	392,	400,	0,	330,	200,	0,	330,	200,	0,	370,	400,	0,	294,	200,	0,	294,	400,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	294,	400,	0,	440,	400,	0,	370,	400,	0,	330,	400,	0,	311,	600,	0,	165,	200,	0,	220,	200,	0,	294,	200,	0,	392,	200,	0,	311,	200,	0,	233,	200,	0,	349,	200,	0,	175,	200,	0,	311,	400,	0,	247,	200,	0,	277,	400,	0,	233,	400,	0,	830,	400,	0,	830,	400,	0,	185,	400,	0,	156,	600,	0,	311,	400,	0,	247,	200,	0,	277,	400,	0,	233,	400,	0,	830,	400,	0,	233,	400,	0,	156,	400,	0,	156,	600,	0,	311,	400,	0,	247,	200,	0,	277,	400,	0,	233,	400,	0,	830,	400,	0,	830,	400,	0,	185,	400,	0,	156,	600,	0,	311,	400,	0,	247,	200,	0,	277,	400,	0,	233,	400,	0,	830,	400,	0,	233,	400,	0,	156,	400,	0,	156,	600,	0,	311,	400,	0,	830,	200,	0,	277,	400,	0,	185,	400,	0,	830,	400,	0,	156,	400,	0,	185,	400,	0,	156,	600,	0,	311,	400,	0,	830,	200,	0,	277,	400,	0,	185,	400,	0,	830,	400,	0,	185,	400,	0,	156,	400,	0,	156,	600,	0,	311,	400,	0,	830,	200,	0,	277,	400,	0,	185,	400,	0,	830,	400,	0,	156,	400,	0,	185,	400,	0,	156,	600,	0,	311,	400,	0,	830,	200,	0,	277,	400,	0,	185,	400,	0,	830,	400,	0,	185,	400,	0,	156,	400,	0,	156,	600,	0,	165,	600,	0,	165,	200,	0,	165,	200,	0,	165,	200,	0,	233,	200,	0,	247,	200,	0,	196,	400,	0,	156,	800,	0,	156,	200,	0,	262,	100,	0,	196,	200,	0,	156,	200,	0,	156,	300,	0,	830,	200,	0,	185,	200,	0,	185,	300,	0,	233,	200,	0,	185,	200,	0,	185,	300,	0,	247,	400,	0,	262,	600,	0,	277,	400,	0,	277,	200,	0,	277,	100,	0,	165,	100,	0,	277,	600,	0,	277,	100,	0,	185,	200,	0,	185,	200,	0,	185,	200,	0,	156,	400,	0,	185,	700,	0,	277,	400,	0,	277,	200,	0,	277,	100,	0,	165,	100,	0,	277,	600,	0,	277,	200,	0,	277,	200,	0,	277,	800,	0,	262,	800,	0,	277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	247,	700,	0,	277,	400,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	156,	900,	0,	277,	400,	0,	330,	200,	0,	311,	400,	0,	277,	400,	0,	277,	300,	0,	247,	200,	0,	830,	400,	0,	156,	900,	0,	277,	400,	0,	330,	200,	0,	311,	100,	0,	247,	700,	0,	277,	400,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	156,	900,	0,	277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	400,	0,	330,	100,	0,	247,	100,	0,	370,	600,	0,	330,	600,	0,	311,	800,	0,	277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	247,	700,	0,	277,	400,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	156,	900,	0,	277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	400,	0,	277,	400,	0,	277,	300,	0,	247,	200,	0,	830,	400,	0,	156,	900,	0,	277,	200,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	247,	700,	0,	277,	400,	0,	277,	200,	0,	330,	200,	0,	311,	100,	0,	156,	400,	0,	247,	500,	0,	277,	400,	0,	330,	200,	0,	311,	300,	0,	247,	100,	0,	277,	400,	0,	277,	200,	0,	415,	400,	0,	277,	200,	0,	370,	400,	0,	311,	200,	0,	277,	200,	0,	330,	400,	0,	277,	200,	0,	277,	200,	0,	311,	100,	0,	247,	200,	0,	247,	700,	0,	415,	400,	0,	277,	200,	0,	370,	400,	0,	277,	400,	0,	330,	400,	0,	311,	400,	0,	277,	100,	0,	185,	900,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	370,	200,	0,	330,	200,	0,	392,	400,	0,	330,	200,	0,	330,	200,	0,	370,	400,	0,	294,	200,	0,	294,	400,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	294,	400,	0,	392,	400,	0,	370,	400,	0,	330,	400,	0,	294,	600,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	370,	200,	0,	330,	200,	0,	392,	400,	0,	330,	200,	0,	330,	200,	0,	370,	400,	0,	294,	200,	0,	294,	400,	0,	494,	400,	0,	330,	200,	0,	440,	400,	0,	294,	400,	0,	392,	400,	0,	370,	400,	0,	330,	400,	0,	294,	600,	0,	587,	400,	0,	392,	200,	0,	785,	400,	0,	440,	200,	0,	392,	200,	0,	466,	400,	0,	392,	200,	0,	392,	200,	0,	440,	400,	0,	349,	200,	0,	349,	400,	0,	587,	400,	0,	466,	200,	0,	523,	400,	0,	440,	200,	0,	392,	1200,	0,	294,	200,	0
		};
	}
	else if(randS < 60){
		outS = {
		330,  100, 100,		330,  100, 300,		330,  100, 300,		262,  100, 100,		330,  100, 300,		392,  100, 700,		196,  100, 700,		262,  300, 300,		196,  300, 300,		164,  300, 300,		220,  300, 100,		246,  100, 300,		233,  200, 000,		220,  100, 300,		196,  100, 150,		330,  100, 150,		392,  100, 150,		440,  100, 300,		349,  100, 100,		392,  100, 300,		330,  100, 300,		262,  100, 100,		294,  100, 100,	247,  100, 500,		262,  300, 300,		196,  300, 300,		164,  300, 300,		220,  300, 100,		246,  100, 300,	233,  200, 000,		220,  100, 300,		196,  100, 150,		330,  100, 150,		392,  100, 150,		440,  100, 300,		349,  100, 100,		392,  100, 300,		330,  100, 300,		262,  100, 100,		294,  100, 100,		247,  100, 900,		392,  100, 100,		370,  100, 100,		349,  100, 100,		311,  100, 300,		330,  100, 300,		207,  100, 100,		220,  100, 100,		262,  100, 300,		220,  100, 100,		262,  100, 100,		294,  100, 500,		392,  100, 100,		370,  100, 100,		349,  100, 100,		311,  100, 300,		330,  100, 300,		523,  100, 300,		523,  100, 100,		523,  100, 1100,		392,  100, 100,		370,  100, 100,		349,  100, 100,		311,  100, 300,		330,  100, 300,		207,  100, 100,		220,  100, 100,		262,  100, 300,		220,  100, 100,		262,  100, 100,		294,  100, 500,		311,  300, 300,		296,  300, 300,		262,  300, 1300,		262,  100, 100,		262,  100, 300,		262,  100, 300,		262,  100, 100,		294,  100, 300,		330,  200, 50,		262,  200, 50,		220,  200, 50,		196,  100, 700,		262,  100, 100,		262,  100, 300,		262,  100, 300,		262,  100, 100,		294,  100, 100,		330,  100, 700,		440,  100, 300,		392,  100, 500,		262,  100, 100,		262,  100, 300,		262,  100, 300,		262,  100, 100,		294,  100, 300,		330,  200, 50,		262,  200, 50,		220,  200, 50,		196,  100, 700,		330,  100, 100,		330,  100, 300,		330,  100, 300,		262,  100, 100,		330,  100, 300,		392,  100, 700,		196,  100, 700,		196,  100, 125,		262,  100, 125,		330,  100, 125,		392,  100, 125,		523,  100, 125,		660,  100, 125,		784,  100, 575,		660,  100, 575,		207,  100, 125,		262,  100, 125,		311,  100, 125,		415,  100, 125,		523,  100, 125,		622,  100, 125,		830,  100, 575,		622,  100, 575,		233,  100, 125,		294,  100, 125,		349,  100, 125,		466,  100, 125,		587,  100, 125,		698,  100, 125,		932,  100, 575,		932,  100, 125,		932,  100, 125,		932,  100, 125,			1046, 675, 000
		};
	}
	else if (randS < 80) {
		outS = {
			415, 500, 000, 555, 500, 000, 555, 300, 000, 623, 300, 000, 555, 300, 000, 523, 300, 000, 466, 500, 000, 466, 700, 000, 466, 500, 000, 623, 500, 000, 623, 300, 000, 699, 300, 000, 623, 300, 000, 555, 300, 000, 466, 500, 000, 415, 700, 000, 415, 500, 000, 699, 500, 000, 699, 300, 000, 740, 300, 000, 699, 300, 000, 623, 300, 000, 555, 500, 000, 466, 700, 000, 415, 300, 000, 415, 400, 000, 466, 500, 000, 623, 500, 000, 523, 500, 000, 555, 900, 000, 415, 500, 000, 555, 400, 000, 555, 400, 000, 555, 400, 000, 523, 900, 50, 523, 300, 000, 555, 300, 000, 523, 300, 000, 466, 500, 000, 415, 900, 100, 623, 500, 000, 699, 300, 000, 623, 400, 000, 555, 400, 000, 831, 400, 000, 415, 900, 100, 415, 300, 000, 415, 400, 000, 466, 500, 000, 623, 500, 000, 523, 500, 000, 555, 900, 000
		
		};
	}
	else {
		outS = {
			658, 125, 000,	 320, 500, 000,	 990, 250, 000,	 1056, 250, 000,	 1188, 250, 000,	 1320, 125, 000,	 1188, 125, 000,	 1056, 250, 000,	 990, 250, 000,	 880, 500, 000,	 880, 250, 000,	 1056, 250, 000,	 1320, 500, 000,	 1188, 250, 000,	 1056, 250, 000,	 990, 750, 000,	 1056, 250, 000,	 1188, 500, 000,	 1320, 500, 000,	 1056, 500, 000,	 880, 500, 000,	 880, 500, 250,	 1188, 500, 000,	 1408, 250, 000,	 1760, 500, 000,	 1584, 250, 000,	 1408, 250, 000,	 1320, 750, 000,	 1056, 250, 000,	 1320, 500, 000,	 1188, 250, 000,	 1056, 250, 000,	 990, 500, 000,	 990, 250, 000,	 1056, 250, 000,	 1188, 500, 000,	 1320, 500, 000,	 1056, 500, 000,	 880, 500, 000,	 880, 500, 500,	 1320, 500, 000,	 990, 250, 000,	 1056, 250, 000,	 1188, 250, 000,	 1320, 125, 000,	 1188, 125, 000,	 1056, 250, 000,	 990, 250, 000,	 880, 500, 000,	 880, 250, 000,	 1056, 250, 000,	 1320, 500, 000,	 1188, 250, 000,	 1056, 250, 000,	 990, 750, 000,	 1056, 250, 000,	 1188, 500, 000,	 1320, 500, 000,	 1056, 500, 000,	 880, 500, 000,	 880, 500, 250,	 1188, 500, 000,	 1408, 250, 000,	 1760, 500, 000,	 1584, 250, 000,	 1408, 250, 000,	 1320, 750, 000,	 1056, 250, 000,	 1320, 500, 000,	 1188, 250, 000,	 1056, 250, 000,	 990, 500, 000,	 990, 250, 000,	 1056, 250, 000,	 1188, 500, 000,	 1320, 500, 000,	 1056, 500, 000,	 880, 500, 000,	 880, 500, 500,	 660, 1000, 000,	 528, 1000, 000,	 594, 1000, 000,	 495, 1000, 000,	 528, 1000, 000,	 440, 1000, 000,	 419, 1000, 000,	 495, 1000, 000,	 660, 1000, 000,	 528, 1000, 000,	 594, 1000, 000,	 495, 1000, 000,	 528, 500, 000,	 660, 500, 000,	 880, 1000, 000,	 838, 2000, 000,	 660, 1000, 000,	 528, 1000, 000,	 594, 1000, 000,	 495, 1000, 000,	 528, 1000, 000,	 440, 1000, 000,	 419, 1000, 000,	 495, 1000, 000,	 660, 1000, 000,	 528, 1000, 000,	 594, 1000, 000,	 495, 1000, 000,	 528, 500, 000,	 660, 500, 000,	 880, 1000, 000,	 838, 2000, 000
		};
	}
	Beep(outS.at(3 * pos), outS.at((3 * pos) + 1)); Sleep(outS.at((3 * pos) + 2));	if ((3 * pos) + 3 == outS.size()) { pos = 0; }	return ++pos;
}

