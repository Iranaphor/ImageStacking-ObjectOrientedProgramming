#include "stackerBasic.h"
#include "io.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "common.h"

Image stackerBasic::meanRollingBlend() {
	inputoutput io;

	int imgItt = 1;
	
	std::string s = stackLocal + std::to_string(imgItt) + ".ppm"; const char *c = s.c_str(); imgItt++;		ImageLarge *mean = &io.readPPML(c);

	Image *imgN = new Image(0, 0);

	for (imgItt = 2; imgItt <= totalstackNum; imgItt++) {

		std::string s = stackLocal + std::to_string(imgItt) + ".ppm";
		const char *c = s.c_str();

		delete[] imgN->pixels;

		std::cout << std::endl;
		imgN = &io.readPPM(c);
		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << std::endl << "Incrementing Mean from img" << imgItt << "	:: ";
		for (unsigned int x = 0; x < (mean->getHeight() * mean->getWidth()); x++) {
			if (x % ((mean->getWidth()*mean->getHeight()) / 32) != 0) {}
			else { std::cout << (char)254u; }

			mean->pixels[x].r += imgN->pixels[x].r;
			mean->pixels[x].g += imgN->pixels[x].g;
			mean->pixels[x].b += imgN->pixels[x].b;

		}
		std::cout << (char)254u;

	}

	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Calculating Mean		:: ";
	for (unsigned int x = 0; x < (mean->getHeight() * mean->getWidth()); x++) {
		if (x % ((mean->getWidth()*mean->getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }

		imgN->pixels[x].r = mean->pixels[x].r / totalstackNum;
		imgN->pixels[x].g = mean->pixels[x].g / totalstackNum;
		imgN->pixels[x].b = mean->pixels[x].b / totalstackNum;
	}
	std::cout << (char)254u << std::endl;
	delete[] mean->pixels;

	return *imgN;
}

Image stackerBasic::medianBlend() {
	inputoutput io;

	std::string s;
	const char *c;
	int imgItt = 1;

	Image *images = new Image[totalstackNum];
	Image *temp = new Image(0, 0);
	for (int x = 0; x < totalstackNum; x++) {
		s = stackLocal + std::to_string(x + 1) + ".ppm"; c = s.c_str();
		delete[] temp->pixels;
		temp = &io.readPPM(c);
		images[x] = *temp;
	}
	delete[] temp->pixels;
	
	Image *medianBlend = new Image(images[1].getWidth(), images[1].getHeight());


	short *currSortR = new short[totalstackNum];
	short *currSortG = new short[totalstackNum];
	short *currSortB = new short[totalstackNum];


	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Sorting                  	:: ";
	for (unsigned int x = 0; x < (images[0].getWidth() * images[0].getHeight()); x++) {
		if (x % ((images[0].getWidth()*images[0].getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }

		for (int y = 0; y < totalstackNum; y++)
		{
			currSortR[y] = images[y].pixels[x].r;
			currSortG[y] = images[y].pixels[x].g;
			currSortB[y] = images[y].pixels[x].b;
		}
		
		short *LST2 = new short[totalstackNum];
		
		short l2itt;
		short tempstore = 0;

		LST2[0] = currSortR[0];	l2itt = 0;
		for (short x = 1; x < totalstackNum; x++) {
			if (currSortR[x] >= LST2[l2itt]) { l2itt++;	LST2[l2itt] = currSortR[x]; }
			else {
				for (short y = 0; y <= l2itt; y++) {
					if (currSortR[x] <= LST2[y]) {
						for (short z = l2itt; z >= y; z--) { LST2[z + 1] = LST2[z]; }
						LST2[y] = currSortR[x];	y = l2itt;
					}
				}	l2itt++;
			}
		}
		medianBlend->pixels[x].r = LST2[7];

		LST2[0] = currSortG[0];	l2itt = 0;
		for (short x = 1; x < totalstackNum; x++) {
			if (currSortG[x] >= LST2[l2itt]) { l2itt++;	LST2[l2itt] = currSortG[x]; }
			else {
				for (short y = 0; y <= l2itt; y++) {
					if (currSortG[x] <= LST2[y]) {
						for (short z = l2itt; z >= y; z--) { LST2[z + 1] = LST2[z]; }
						LST2[y] = currSortG[x];	y = l2itt;
					}
				}	l2itt++;
			}
		}
		medianBlend->pixels[x].g = LST2[7];

		LST2[0] = currSortB[0];	l2itt = 0;
		for (short x = 1; x < totalstackNum; x++) {
			if (currSortB[x] >= LST2[l2itt]) { l2itt++;	LST2[l2itt] = currSortB[x]; }
			else {
				for (short y = 0; y <= l2itt; y++) {
					if (currSortB[x] <= LST2[y]) {
						for (short z = l2itt; z >= y; z--) { LST2[z + 1] = LST2[z]; }
						LST2[y] = currSortB[x];	y = l2itt;
					}
				}	l2itt++;
			}
		}
		medianBlend->pixels[x].b = LST2[7];


	}
	std::cout << (char)254u << std::endl << std::endl;

	for (int y = 0; y < totalstackNum; y++)
	{
		delete[] images[y].pixels;
	}

	return *medianBlend;
}

Image stackerBasic::sigmaClippedMeanBlend(const float sigmaFactor){
	inputoutput io;

	Image *baseMean = new Image(0, 0);

	baseMean = &meanRollingBlend();
	
	Image *imgM = new Image(0, 0);
	*imgM = io.readPPM("Images/ImageStacker_set1/IMG_1.ppm");
	ImageDec *deviations = new ImageDec(imgM->getWidth(), imgM->getHeight());
	std::string s;
	const char *c;

	///take in each image and define it's variance
	for (unsigned int imgItt = 1; imgItt < totalstackNum; imgItt++) {
		s = "Images/ImageStacker_set1/IMG_" + std::to_string(imgItt) + ".ppm";
		c = s.c_str();
		delete[] imgM->pixels;
		imgM = &io.readPPM(c);

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << std::endl << "Calculate Deviation		:: ";
		for (unsigned int x = 0; x < (baseMean->getHeight() * baseMean->getWidth()); x++) {
			if (x % ((baseMean->getWidth()*baseMean->getHeight()) / 32) != 0) {}
			else { std::cout << (char)254u; }
			deviations->pixels[x].r += (imgM->pixels[x].r - baseMean->pixels[x].r) * (imgM->pixels[x].r - baseMean->pixels[x].r);
			deviations->pixels[x].g += (imgM->pixels[x].g - baseMean->pixels[x].g) * (imgM->pixels[x].g - baseMean->pixels[x].g);
			deviations->pixels[x].b += (imgM->pixels[x].b - baseMean->pixels[x].b) * (imgM->pixels[x].b - baseMean->pixels[x].b);
		}
		std::cout << (char)254u;

	
	}

///next, calculate the standard deviation from the mean (divide by 255 to store as float)

	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Calculate Deviation		:: ";
	for (unsigned int x = 0; x < (baseMean->getHeight() * baseMean->getWidth()); x++) {
		if (x % ((baseMean->getWidth()*baseMean->getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }
		deviations->pixels[x].r = sqrt(deviations->pixels[x].r / totalstackNum) / 255;
		deviations->pixels[x].g = sqrt(deviations->pixels[x].g / totalstackNum) / 255;
		deviations->pixels[x].b = sqrt(deviations->pixels[x].b / totalstackNum) / 255;
	}
	std::cout << (char)254u;
	
	ImageDec *sigmaClippy = new ImageDec(baseMean->getHeight(), baseMean->getWidth());
	Image *sigmaValidQuant = new Image(baseMean->getHeight(), baseMean->getWidth());

	short uB[] = { 0,0,0 };
	short lB[] = { 0,0,0 };

	///for each pixel in each image, clip outliers
	for (unsigned int imgItt = 1; imgItt < totalstackNum; imgItt++) {
		std::string s = "Images/ImageStacker_set1/IMG_" + std::to_string(imgItt) + ".ppm";
		const char *c = s.c_str();
		delete[] imgM->pixels;
		imgM = &io.readPPM(c);

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << std::endl << "Clip bounds for img" << (imgItt) << "		:: ";
		for (unsigned int x = 0; x < (baseMean->getHeight() * baseMean->getWidth()); x++) {
			if (x % ((baseMean->getWidth()*baseMean->getHeight()) / 32) != 0) {}
			else { std::cout << (char)254u; }

			//Calculate bounds
			uB[0] = baseMean->pixels[x].r + (sigmaFactor * 255 * deviations->pixels[x].r);
			lB[0] = baseMean->pixels[x].r - (sigmaFactor * 255 * deviations->pixels[x].r);

			uB[1] = baseMean->pixels[x].g + (sigmaFactor * 255 * deviations->pixels[x].g);
			lB[1] = baseMean->pixels[x].g - (sigmaFactor * 255 * deviations->pixels[x].g);

			uB[2] = baseMean->pixels[x].b + (sigmaFactor * 255 * deviations->pixels[x].b);
			lB[2] = baseMean->pixels[x].b - (sigmaFactor * 255 * deviations->pixels[x].b);

			if (imgM->pixels[x].r >= lB[0] && imgM->pixels[x].r <= uB[0]) {
				sigmaValidQuant->pixels[x].r++;
				sigmaClippy->pixels[x].r += imgM->pixels[x].r;
			}

			if (imgM->pixels[x].g >= lB[1] && imgM->pixels[x].g <= uB[1]) {
				sigmaValidQuant->pixels[x].g++;
				sigmaClippy->pixels[x].g += imgM->pixels[x].g;
			}

			if (imgM->pixels[x].b >= lB[2] && imgM->pixels[x].b <= uB[2]) {
				sigmaValidQuant->pixels[x].b++;
				sigmaClippy->pixels[x].b += imgM->pixels[x].b;
			}

		}
		std::cout << (char)254u;
	}

	delete[] deviations->pixels;
	
	delete[] imgM->pixels;
	
	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Calculate " << (char)236 << " clipped " << (char)230 << "		:: ";
	for (unsigned int x = 0; x < (baseMean->getHeight() * baseMean->getWidth()); x++) {
		if (x % ((baseMean->getWidth()*baseMean->getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }
		
		if (sigmaClippy->pixels[x].r / sigmaValidQuant->pixels[x].r == NAN || sigmaClippy->pixels[x].g / sigmaValidQuant->pixels[x].g == NAN || sigmaClippy->pixels[x].b / sigmaValidQuant->pixels[x].b == NAN) {
			sigmaClippy->pixels[x].r = baseMean->pixels[x].r / 255;
			sigmaClippy->pixels[x].g = baseMean->pixels[x].g / 255;
			sigmaClippy->pixels[x].b = baseMean->pixels[x].b / 255;
		}
		else {
			sigmaClippy->pixels[x].r /= sigmaValidQuant->pixels[x].r * 255;
			sigmaClippy->pixels[x].g /= sigmaValidQuant->pixels[x].g * 255;
			sigmaClippy->pixels[x].b /= sigmaValidQuant->pixels[x].b * 255;
		}
	}
	std::cout << (char)254u;

	delete[] sigmaValidQuant->pixels;
	
	for (int x = 0; x < (baseMean->getWidth() * baseMean->getHeight()); x++) {
		baseMean->pixels[x].r = sigmaClippy->pixels[x].r * 255;
		baseMean->pixels[x].g = sigmaClippy->pixels[x].g * 255;
		baseMean->pixels[x].b = sigmaClippy->pixels[x].b * 255;
	}
	

	delete[] sigmaClippy->pixels;
		
	return *baseMean;
}
