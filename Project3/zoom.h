#ifndef zoom_h
	#define zoom_h

	#include <iostream>
	#include "Image.h"

	using namespace std;

	class Image;

	class zoom : public Image
	{
	public:

		Image doubleWidthHeightEx(int choice, const Image &img = Image(0, 0)); //nearest neighbour zoom
		Image doubleWidthHeightAvg(int choice, const Image &img = Image(0, 0)); //bilinear interpolation recursively

		Image doubleWidthHeightAvg(Image &img = Image(0, 0), int itt = 0); //bilinear interpolation of defined zoom factor

		Image zoomROI(int tLx, int tLy, int sW, int sH, int zF = 1); //zooms bilinear defined section to power or 2

		long int floorSig(long int number, int significance); //rounds number down to nearest multuple of significance 
	};


#endif // !