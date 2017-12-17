#ifndef stackerRolling_h
	#define stackerRolling_h

	#include <iostream>
	#include "Image.h"

	using namespace std;

	class Image;
	class ImageLarge;

	class stackerRolling
	{
	public:
		Image rangeRollingBlend(int w, int h); //stacks images using range (largest value + smallest value)/2
		Image medianRollingBlend(); //stacks using custom-made median algorithm
		Image meanOf2(const Image &img, const Image &img2, int w, int h); //calculated the mean of 2 sets of images
	};

#endif // !