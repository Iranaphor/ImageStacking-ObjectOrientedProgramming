#ifndef stackerBasic_h
	#define stackerBasic_h

	#include <iostream>
	#include "Image.h"

	using namespace std;

	class Image;
	class ImageLarge;

	class stackerBasic
	{
	public:
		Image meanRollingBlend();	//mean blending algorithm
		Image medianBlend();		//median blending algorithm
		Image sigmaClippedMeanBlend(const float sigmaFactor = 1.6);	//sigma Clipped mean blending algorithm
	};

#endif // !