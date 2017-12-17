#pragma once
//*********************************************
//Image class to hold and allow manipulation of images once read into the code
//from https://www.scratchapixel.com/
//*********************************************
#include <cstdlib> 
#include <cstdio> 

/*

This is not needed if i can find a way to actually delete the data being stored...?

//This class is used to take a section of the image
class Image_Section
{
public:
	//we do this by taking in the image, then selecting the area of the image we want (the row) and returning that
	void section(int sectionRow) 
	{
		*img1 = readPPM("Images/ImageStacker_set1/IMG_1.ppm");
	};

};
*/

//http://en.cppreference.com/w/cpp/memory/weak_ptr
//https://stackoverflow.com/questions/11281909/why-i-cant-cast-nullptr-to-weak-ptr

class Image
{
public:
	// Rgb structure, i.e. a pixel 
///*	 	This is the Image:Rgb class(-ish) 
	struct Rgb
	{
	///*		if rgb is called without attributes pixel is set to black
	///*		if rgb is called with 1 short, r, g, and b are equal (shade of grey)
	///*		if rgb is called with 3 shorts, r, g, and b are asigned respectively
		Rgb() : r(0), g(0), b(0) {}
		Rgb(short c) : r(c), g(c), b(c) {}
		Rgb(short _r, short _g, short _b) : r(_r), g(_g), b(_b) {}

///*	Overloaded Operator Initialisation
		bool operator != (const Rgb &c) const					///	this would be the test for cross-pixel perfection
		{
			return c.r != r || c.g != g || c.b != b;
		}
		Rgb& operator *= (const Rgb &rgb)						///	in code: 
		{
			r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this;
		}
		Rgb& operator += (const Rgb &rgb)						///	in main: "mean->pixels += imgN->pixels"  will call this overloaded operator
		{
			r += rgb.r, g += rgb.g, b += rgb.b; return *this;
		}	
		friend short& operator += (short &f, const Rgb rgb)		///	in main: "short  meanVal += imgN->pixels"  will call this overloaded operator
		{
			f += (rgb.r + rgb.g + rgb.b) / 3.f; return f;
		}
		~Rgb(){}

		short r, g, b;
	};
	
///*		Empty input constructor creates null image available for editing
///*			THIS IS USED FOR IMPORTING
	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	 
///*		Image constructor, defining width, height and default colour
///*			USED FOR MAIN() IMAGE CONTAINER CREATION
///*			width, height are defined
///*			each pixels in list defined as default rgb colour
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) : 
		w(_w), h(_h), pixels(NULL)
	{
		pixels = new Rgb[w * h];
		for (unsigned int i = 0; i < w * h; ++i)
			pixels[i] = c;
	}
	
///*		
	const Rgb& operator [] (const unsigned int &i) const
	{
		return pixels[i];
	}

///*		
	Rgb& operator [] (const unsigned int &i)
	{
		return pixels[i];
	}


///*		Reset image pixels all to smallest value (konstant black)
	void reset(int resetColour) {		
		if (resetColour == 0) {
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = kBlack;
		}
		else if (resetColour == 1) {
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = kWhite;
		}
	}

///*		Deconstructor deletes the pixels data is not empty already
	~Image()
	{
		//if (pixels != nullptr) {	delete[] pixels; }
	}

///*		Variable declartation
	unsigned int w, h; // Image resolution 
	Rgb *pixels; // 1D array of pixels 
	static const Rgb kBlack, kWhite; // Preset colors 
};




/*
class Store : public Image
{

};
*/



const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
//const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
//const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
//const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);


/*




cout << "                            _________________" << endl << "Incrementing Total Value :: ";
for (int x = 0; x < (mean->h * mean->w); x++) { //	.: for each pixel
if (x % 500000 != 0) {}	else { cout << (char)254u; }



cout << (char)254u << endl;




*/