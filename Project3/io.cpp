#include "io.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "common.h"


using namespace std;


Image inputoutput::readPPM(const char *filename)
{
	///*		UI
	//Remove this std::cout to prevent multiple outputs
	//std::cout << "Reading image ..." << std::endl;


	///*		File assigned to ifs and opened in binary mode
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);


	//std::cout << "bi" << std::endl;
	///*		Empty image object created
	Image *src = new Image(0, 0);

	try {
		///*		test if file is present
		if (ifs.fail()) {
			std::cout << filename << std::endl;
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}

		///*		extract the file dimensions (the first few numbers) and add to variable "header",
		///*		add dimensions "w", "h", "b" to image object src
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;

		///*		assign width and height of import to Empty image object
		src->setWidth(w);
		src->setHeight(h);

		///*		create an array of the width and height in pixels of the image

		///std::cout << filename << std::endl;
		src->pixels = new Image::RgbChar[w * h]; // this will throw an exception if bad_alloc

											 ///*		remove all new-line chars from the file
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 

							   ///*		go through each pixel and add its r, g and b binary values to the array pix
							   ///*		
							   ///*		to their respective locations in src as shorts
		unsigned char pix[3]; // read each pixel one by one and convert bytes to shorts 

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Importing Image			:: ";
		for (int i = 0; i < (w * h); i++) {
			if (i % ((w*h) / 32) != 0) {}	else { cout << (char)254u; }

			ifs.read(reinterpret_cast<char *>(pix), 3); ///read in 3 values and save as type char
			src->pixels[i].r = pix[0];
			src->pixels[i].g = pix[1];
			src->pixels[i].b = pix[2];

		}
		std::cout << (char)254u;
		///*		close the input file
		ifs.close();
	}


	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}

	//std::cout << "ti" << std::endl;

	//Confirm image read
	//Delete this to prevent multiple lines output
	//std::cout << "Image read" << std::endl;

	src->saveFileName(filename);
	src->outputData();
	return *src;
}

ImageLarge inputoutput::readPPML(const char *filename)
{
	///*		UI
	//Remove this std::cout to prevent multiple outputs
	//std::cout << "Reading image ..." << std::endl;


	///*		File assigned to ifs and opened in binary mode
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);


	//std::cout << "bi" << std::endl;
	///*		Empty image object created
	ImageLarge *src = new ImageLarge(0, 0);
	try {
		///*		test if file is present
		if (ifs.fail()) {
			std::cout << filename << std::endl;
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}

		///*		extract the file dimensions (the first few numbers) and add to variable "header",
		///*		add dimensions "w", "h", "b" to image object src
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;

		///*		assign width and height of import to Empty image object
		src->setWidth(w);
		src->setHeight(h);

		///*		create an array of the width and height in pixels of the image

		///std::cout << filename << std::endl;
		src->pixels = new ImageLarge::RbgShort[w * h]; // this will throw an exception if bad_alloc

												  ///*		remove all new-line chars from the file
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 

							   ///*		go through each pixel and add its r, g and b binary values to the array pix
							   ///*		
							   ///*		to their respective locations in src as shorts
		unsigned char pix[3]; // read each pixel one by one and convert bytes to shorts 

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Importing Image			:: ";
		for (int i = 0; i < (w * h); i++) {
			if (i % ((w*h) / 32) != 0) {} else { cout << (char)254u; }
			ifs.read(reinterpret_cast<char *>(pix), 3); ///read in 3 values and save as type char
			src->pixels[i].r = pix[0];
			src->pixels[i].g = pix[1];
			src->pixels[i].b = pix[2];
		}
		std::cout << (char)254u;

		///*		close the input file
		ifs.close();
	}


	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}


	//std::cout << "ti" << std::endl;

	//Confirm image read
	//Delete this to prevent multiple lines output
	//std::cout << "Image read" << std::endl;

	src->saveFileName(filename);
	src->outputData();
	return *src;
}

ImageDec inputoutput::readPPMD(const char *filename)
{
	///*		UI
	//Remove this std::cout to prevent multiple outputs
	//std::cout << "Reading image ..." << std::endl;


	///*		File assigned to ifs and opened in binary mode
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);


	//std::cout << "bi" << std::endl;
	///*		Empty image object created
	ImageDec *src = new ImageDec(0, 0);
	try {
		///*		test if file is present
		if (ifs.fail()) {
			std::cout << filename << std::endl;
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}

		///*		extract the file dimensions (the first few numbers) and add to variable "header",
		///*		add dimensions "w", "h", "b" to image object src
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;

		///*		assign width and height of import to Empty image object
		src->setWidth(w);
		src->setHeight(h);

		///*		create an array of the width and height in pixels of the image

		///std::cout << filename << std::endl;
		src->pixels = new ImageDec::RgbFloat[w * h]; // this will throw an exception if bad_alloc

											///*		remove all new-line chars from the file
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 

							   ///*		go through each pixel and add its r, g and b binary values to the array pix
							   ///*		
							   ///*		to their respective locations in src as floats
		unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Importing Image			:: ";
		for (int i = 0; i < (w * h); i++) {
			if (i % ((w*h) / 32) != 0) {} else { cout << (char)254u; }
			ifs.read(reinterpret_cast<char *>(pix), 3); ///read in 3 values and save as type char
			src->pixels[i].r = pix[0] / 255.f;
			src->pixels[i].g = pix[1] / 255.f;
			src->pixels[i].b = pix[2] / 255.f;
		}
		std::cout << (char)254u;

		///*		close the input file
		ifs.close();
	}


	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}


	//std::cout << "ti" << std::endl;

	//Confirm image read
	//Delete this to prevent multiple lines output
	//std::cout << "Image read" << std::endl;

	src->saveFileName(filename);
	src->outputData();

	return *src;
}

void inputoutput::writePPM(Image &img, const char *filename)
{
	///*		UI
	//std::cout << filename << std::endl;
	//std::cout << "Writing image ..." << std::endl;

	///*		test if error will occur with save
	if (img.getWidth() == 0 || img.getHeight() == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
	std::ofstream ofs;
	try {

		///*		open the filename as ofs, to export in binary mode
		ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 

											  ///*		if it cannot open, throw an error to catch at the end
		if (ofs.fail()) throw("Can't open output file");

		///*		output the image details and setup variables to output the pixel colours
		ofs << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		//std::cout << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		unsigned char r, g, b;

		///*		export all the data from the 2d array of pointers of size (width * height)
		///*		note that the /n does not require adding. this is because it is not realy
		///*		in the document, but is added automatically by cin, which is why it 
		///*		needs to be removed.
		// loop over each pixel in the image, clamp and convert to byte format
		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Exporting Image			:: ";
		for (unsigned int i = 0; i < (img.getWidth() * img.getHeight()); ++i) {
			if (((img.getWidth()*img.getHeight()) / 32) != 0){
				if (i % ((img.getWidth()*img.getHeight()) / 32) != 0) {}
				else {
					cout << (char)254u;
				}
			}
			
			
			r = static_cast<unsigned char>(img.pixels[i].r);
			g = static_cast<unsigned char>(img.pixels[i].g);
			b = static_cast<unsigned char>(img.pixels[i].b);

			ofs << r << g << b;
		}
		std::cout << (char)254u << (char)254u;

		///*		close file
		ofs.close();

		///*		UI
		//Confirm image write
		//std::cout << "Image written" << std::endl;
	}

	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ofs.close();
	}
}

void inputoutput::writePPML(ImageLarge &img, const char *filename)
{
	///*		UI
	//std::cout << filename << std::endl;
	//std::cout << "Writing image ..." << std::endl;

	///*		test if error will occur with save
	if (img.getWidth() == 0 || img.getHeight() == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
	std::ofstream ofs;
	try {

		///*		open the filename as ofs, to export in binary mode
		ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 

											  ///*		if it cannot open, throw an error to catch at the end
		if (ofs.fail()) throw("Can't open output file");

		///*		output the image details and setup variables to output the pixel colours
		ofs << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		//std::cout << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		unsigned char r, g, b;

		///*		export all the data from the 2d array of pointers of size (width * height)
		///*		note that the /n does not require adding. this is because it is not realy
		///*		in the document, but is added automatically by cin, which is why it 
		///*		needs to be removed.
		// loop over each pixel in the image, clamp and convert to byte format
		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Exporting Image			:: ";
		for (unsigned int i = 0; i < (img.getWidth() * img.getHeight()); ++i) {
			if (i % ((img.getWidth()*img.getHeight()) / 32) != 0) {} else { cout << (char)254u; }
			r = static_cast<unsigned char>(img.pixels[i].r);
			g = static_cast<unsigned char>(img.pixels[i].g);
			b = static_cast<unsigned char>(img.pixels[i].b);

			ofs << r << g << b;
		}
		std::cout << (char)254u << (char)254u;

		///*		close file
		ofs.close();

		///*		UI
		//Confirm image write
		//std::cout << "Image written" << std::endl;
	}

	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ofs.close();
	}
}

void inputoutput::writePPMD(ImageDec &img, const char *filename)
{
	///*		UI
	//std::cout << filename << std::endl;
	//std::cout << "Writing image ..." << std::endl;

	///*		test if error will occur with save
	if (img.getWidth() == 0 || img.getHeight() == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
	std::ofstream ofs;
	try {

		///*		open the filename as ofs, to export in binary mode
		ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 

											  ///*		if it cannot open, throw an error to catch at the end
		if (ofs.fail()) throw("Can't open output file");

		///*		output the image details and setup variables to output the pixel colours
		ofs << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		//std::cout << "P6\n" << img.getWidth() << " " << img.getHeight() << "\n255\n";
		unsigned char r, g, b;

		///*		export all the data from the 2d array of pointers of size (width * height)
		///*		note that the /n does not require adding. this is because it is not realy
		///*		in the document, but is added automatically by cin, which is why it 
		///*		needs to be removed.
		// loop over each pixel in the image, clamp and convert to byte format
		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << endl << "Exporting Image			:: ";
		for (unsigned int i = 0; i < (img.getWidth() * img.getHeight()); ++i) {
			if (i % ((img.getWidth() * img.getHeight()) / 32) != 0) {} else { cout << (char)254u; }
			r = static_cast<unsigned char>(min(1.f, img.pixels[i].r) * 255);
			g = static_cast<unsigned char>(min(1.f, img.pixels[i].g) * 255);
			b = static_cast<unsigned char>(min(1.f, img.pixels[i].b) * 255);
			ofs << r << g << b;
		}
		std::cout << (char)254u << (char)254u;

		///*		close file
		ofs.close();

		///*		UI
		//Confirm image write
		//std::cout << "Image written" << std::endl;
	}

	///*		Output error details
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ofs.close();
	}
}
