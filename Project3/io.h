#ifndef io_h
	#define io_h
	#include <iostream>

	using namespace std;

	class Image;
	class ImageLarge;
	class ImageDec;

	class inputoutput
	{
	public:
		Image readPPM(const char* file);	//readPPM for char
		ImageLarge readPPML(const char* file);	//readPPM for short
		ImageDec readPPMD(const char *file);	//readPPM for float
		void writePPM(Image &img, const char* file);	//writePPM for char
		void writePPML(ImageLarge &img, const char* file);	//writePPM for short
		void writePPMD(ImageDec &img, const char *file);	//writePPM for float
	};

#endif // !