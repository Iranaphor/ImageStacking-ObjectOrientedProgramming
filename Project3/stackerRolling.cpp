#include "stackerRolling.h"
#include "io.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "common.h"


Image stackerRolling::rangeRollingBlend(int w, int h) {
	inputoutput io;

	//int totImgNum = 3;
	//const int totalstackNum = 13;

	Image *low = new Image(w, h);
	for (unsigned int x = 0; x < (w * h); x++) {
		low->pixels[x].r = 255;
		low->pixels[x].g = 255;
		low->pixels[x].b = 255;
	}
	///

	Image *high = new Image(w, h);
	///

	Image *imgN = new Image(0, 0);
	///





	for (int imgItt = 1; imgItt <= totalstackNum; imgItt++) {
		///
		std::string s = "Images/ImageStacker_set1/IMG_" + std::to_string(imgItt) + ".ppm";
		const char *c = s.c_str();
		delete[] imgN->pixels; ///LBL1:
		imgN = &io.readPPM(c);	//assign an img
								///
		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << std::endl << "Updating low:high for img" << (imgItt) << "	:: ";
		for (unsigned int x = 0; x < (w * h); x++) { //	.: for each pixel
			if (x % ((imgN->getWidth()*imgN->getHeight()) / 32) != 0) {}
			else { std::cout << (char)254u; }
			///
			//tests for her royal highness
			if (imgN->pixels[x].r > high->pixels[x].r) { high->pixels[x].r = imgN->pixels[x].r; }
			if (imgN->pixels[x].g > high->pixels[x].g) { high->pixels[x].g = imgN->pixels[x].g; }
			if (imgN->pixels[x].b > high->pixels[x].b) { high->pixels[x].b = imgN->pixels[x].b; }
			///
			//tests for low self esteem
			if (imgN->pixels[x].r < low->pixels[x].r) { low->pixels[x].r = imgN->pixels[x].r; }
			if (imgN->pixels[x].g < low->pixels[x].g) { low->pixels[x].g = imgN->pixels[x].g; }
			if (imgN->pixels[x].b < low->pixels[x].b) { low->pixels[x].b = imgN->pixels[x].b; }
		}
		std::cout << (char)254u << std::endl;
		///
	}

	///


	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Calculating Range		:: ";
	for (unsigned int x = 0; x < (w * h); x++) { //	.: for each pixel
		if (x % ((imgN->getWidth()*imgN->getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }
		imgN->pixels[x].r = ((high->pixels[x].r + low->pixels[x].r) / 2);
		imgN->pixels[x].g = ((high->pixels[x].g + low->pixels[x].g) / 2);
		imgN->pixels[x].b = ((high->pixels[x].b + low->pixels[x].b) / 2);
	} //work the middle
	std::cout << (char)254u << std::endl;
	///

	delete[] low->pixels;
	///
	delete[] high->pixels;
	///
	return *imgN;


}

Image stackerRolling::medianRollingBlend() {
	inputoutput io;

	int nL = 0;
	int nH = 0;

	//const int totalstackNum = 13;

	unsigned char tempHold;

	unsigned char swapArrR[] = { 0, 0, 0, 0 };
	unsigned char swapArrG[] = { 0, 0, 0, 0 };
	unsigned char  swapArrB[] = { 0, 0, 0, 0 };


	Image *I = new Image(0, 0); //input
	Image *L = new Image(0, 0); //low
	L = &io.readPPM("Images/ImageStacker_set1/IMG_1.ppm");

	Image *M = new Image(0, 0); //median
	Image *H = new Image(0, 0); //high
	
	H = &io.readPPM("Images/ImageStacker_set1/IMG_2.ppm");
	M = &io.readPPM("Images/ImageStacker_set1/IMG_3.ppm");

	bool switchMedian = true;

	//std::cout << "Reading Images:" << std::endl;

	//	L, M, H = sort(L, H, I)
	//std::cout << "Sorting first 3 images:" << std::endl;

	std::cout << "\n" << flush; system("CLS");
	std::cout << "				   __________________________________" << std::endl << "Sorting: img1, img2, img3	:: ";
	for (unsigned int x = 0; x < (L->getWidth() * L->getHeight()); x++) {
		if (x % ((L->getWidth()*L->getHeight()) / 32) != 0) {}
		else { std::cout << (char)254u; }
		//swapArrR = { L->pixels[x].r, H->pixels[x].r, M->pixels[x].r, 0 };
		swapArrR[0] = L->pixels[x].r;
		swapArrR[1] = H->pixels[x].r;
		swapArrR[2] = M->pixels[x].r;
		if (swapArrR[0] > swapArrR[1]) { tempHold = swapArrR[1];		swapArrR[1] = swapArrR[0];		swapArrR[0] = tempHold; }
		if (swapArrR[1] > swapArrR[2]) { tempHold = swapArrR[2];		swapArrR[2] = swapArrR[1];		swapArrR[1] = tempHold; }
		if (swapArrR[0] > swapArrR[1]) { tempHold = swapArrR[1];		swapArrR[1] = swapArrR[0];		swapArrR[0] = tempHold; }
		L->pixels[x].r = swapArrR[0];	H->pixels[x].r = swapArrR[2];	M->pixels[x].r = swapArrR[1];

		//swapArrG = { L->pixels[x].g, H->pixels[x].g, M->pixels[x].g, 0 };
		swapArrG[0] = L->pixels[x].g;
		swapArrG[1] = H->pixels[x].g;
		swapArrG[2] = M->pixels[x].g;
		if (swapArrG[0] > swapArrG[1]) { tempHold = swapArrG[1];		swapArrG[1] = swapArrG[0];		swapArrG[0] = tempHold; }
		if (swapArrG[1] > swapArrG[2]) { tempHold = swapArrG[2];		swapArrG[2] = swapArrG[1];		swapArrG[1] = tempHold; }
		if (swapArrG[0] > swapArrG[1]) { tempHold = swapArrG[1];		swapArrG[1] = swapArrG[0];		swapArrG[0] = tempHold; }
		L->pixels[x].g = swapArrG[0];	H->pixels[x].g = swapArrG[2];	M->pixels[x].g = swapArrG[1];

		//swapArrB = { L->pixels[x].b, H->pixels[x].b, M->pixels[x].b, 0 };
		swapArrB[0] = L->pixels[x].b;
		swapArrB[1] = H->pixels[x].b;
		swapArrB[2] = M->pixels[x].b;
		if (swapArrB[0] > swapArrB[1]) { tempHold = swapArrB[1];		swapArrB[1] = swapArrB[0];		swapArrB[0] = tempHold; }
		if (swapArrB[1] > swapArrB[2]) { tempHold = swapArrB[2];		swapArrB[2] = swapArrB[1];		swapArrB[1] = tempHold; }
		if (swapArrB[0] > swapArrB[1]) { tempHold = swapArrB[1];		swapArrB[1] = swapArrB[0];		swapArrB[0] = tempHold; }
		L->pixels[x].b = swapArrB[0];	H->pixels[x].b = swapArrB[2];	M->pixels[x].b = swapArrB[1];
	}
	std::cout << (char)254u << std::endl << std::endl;

	std::string s;
	const char *c;

	//std::cout << "Number of Images to sort: " << totImg << std::endl;

	for (int imgItt = 4; imgItt <= totalstackNum; imgItt++) {
		s = "Images/ImageStacker_set1/IMG_" + std::to_string(imgItt) + ".ppm";
		c = s.c_str();
		delete[] I->pixels;
		I = &io.readPPM(c);

		//std::cout << "Sorting images: L, M, H, and img" << imgItt << std::endl;

		//*		L, M, I, H = sort(Lpix, Mpix, Ipix, Hpix)

		std::cout << "\n" << flush; system("CLS");
		std::cout << "				   __________________________________" << std::endl << "Sorting with img" << (imgItt) << "		:: ";
		for (unsigned int x = 0; x < (L->getWidth() * L->getHeight()); x++) {
			if (x % ((L->getWidth()*L->getHeight()) / 32) != 0) {}
			else { std::cout << (char)254u; }

		
			//swapArrR = { L->pixels[x].r, H->pixels[x].r, M->pixels[x].r, I->pixels[x].r };
			swapArrR[0] = L->pixels[x].r;
			swapArrR[1] = H->pixels[x].r;
			swapArrR[2] = M->pixels[x].r;
			swapArrR[3] = I->pixels[x].r;
			if (swapArrR[0] > swapArrR[1]) { tempHold = swapArrR[1];		swapArrR[1] = swapArrR[0];		swapArrR[0] = tempHold; }
			if (swapArrR[1] > swapArrR[2]) { tempHold = swapArrR[2];		swapArrR[2] = swapArrR[1];		swapArrR[1] = tempHold; }
			if (swapArrR[2] > swapArrR[3]) { tempHold = swapArrR[3];		swapArrR[3] = swapArrR[3];		swapArrR[3] = tempHold; }
			if (swapArrR[0] > swapArrR[1]) { tempHold = swapArrR[1];		swapArrR[1] = swapArrR[0];		swapArrR[0] = tempHold; }
			if (swapArrR[1] > swapArrR[2]) { tempHold = swapArrR[2];		swapArrR[2] = swapArrR[1];		swapArrR[1] = tempHold; }
			if (swapArrR[0] > swapArrR[1]) { tempHold = swapArrR[1];		swapArrR[1] = swapArrR[0];		swapArrR[0] = tempHold; }
			L->pixels[x].r = swapArrR[0];	H->pixels[x].r = swapArrR[3];	M->pixels[x].r = swapArrR[2];	I->pixels[x].r = swapArrR[1];

			//swapArrG = { L->pixels[x].g, H->pixels[x].g, M->pixels[x].g, I->pixels[x].g };
			swapArrG[0] = L->pixels[x].g;
			swapArrG[1] = H->pixels[x].g;
			swapArrG[2] = M->pixels[x].g;
			swapArrG[3] = I->pixels[x].g;
			if (swapArrG[0] > swapArrG[1]) { tempHold = swapArrG[1];		swapArrG[1] = swapArrG[0];		swapArrG[0] = tempHold; }
			if (swapArrG[1] > swapArrG[2]) { tempHold = swapArrG[2];		swapArrG[2] = swapArrG[1];		swapArrG[1] = tempHold; }
			if (swapArrG[2] > swapArrG[3]) { tempHold = swapArrG[3];		swapArrG[3] = swapArrG[3];		swapArrG[3] = tempHold; }
			if (swapArrG[0] > swapArrG[1]) { tempHold = swapArrG[1];		swapArrG[1] = swapArrG[0];		swapArrG[0] = tempHold; }
			if (swapArrG[1] > swapArrG[2]) { tempHold = swapArrG[2];		swapArrG[2] = swapArrG[1];		swapArrG[1] = tempHold; }
			if (swapArrG[0] > swapArrG[1]) { tempHold = swapArrG[1];		swapArrG[1] = swapArrG[0];		swapArrG[0] = tempHold; }
			L->pixels[x].g = swapArrG[0];	H->pixels[x].g = swapArrG[3];	M->pixels[x].g = swapArrG[2];	I->pixels[x].g = swapArrG[1];

			//swapArrB = { L->pixels[x].b, H->pixels[x].b, M->pixels[x].b, I->pixels[x].b };
			swapArrB[0] = L->pixels[x].b;
			swapArrB[1] = H->pixels[x].b;
			swapArrB[2] = M->pixels[x].b;
			swapArrB[3] = I->pixels[x].b;
			if (swapArrB[0] > swapArrB[1]) { tempHold = swapArrB[1];		swapArrB[1] = swapArrB[0];		swapArrB[0] = tempHold; }
			if (swapArrB[1] > swapArrB[2]) { tempHold = swapArrB[2];		swapArrB[2] = swapArrB[1];		swapArrB[1] = tempHold; }
			if (swapArrB[2] > swapArrB[3]) { tempHold = swapArrB[3];		swapArrB[3] = swapArrB[3];		swapArrB[3] = tempHold; }
			if (swapArrB[0] > swapArrB[1]) { tempHold = swapArrB[1];		swapArrB[1] = swapArrB[0];		swapArrB[0] = tempHold; }
			if (swapArrB[1] > swapArrB[2]) { tempHold = swapArrB[2];		swapArrB[2] = swapArrB[1];		swapArrB[1] = tempHold; }
			if (swapArrB[0] > swapArrB[1]) { tempHold = swapArrB[1];		swapArrB[1] = swapArrB[0];		swapArrB[0] = tempHold; }
			L->pixels[x].b = swapArrB[0];	H->pixels[x].b = swapArrB[3];	M->pixels[x].b = swapArrB[2];	I->pixels[x].b = swapArrB[1];
			

		}
		//*/
		std::cout << (char)254u << std::endl << std::endl;



		if (nL == nH) {
			if (switchMedian) {
				delete[] H->pixels;
				*H = *I;
				nH++;
				//std::cout << "Image H removed, new value for nH is " << nH << std::endl;
				switchMedian = false;
			}
			else {
				delete[] L->pixels;
				*L = *M;
				delete[] M->pixels;
				*M = *I;
				nL++;
				//std::cout << "Image L removed, new value for nL is " << nL << std::endl;
				switchMedian = true;
			}
		}

		else if (nL < nH) {
			delete[] L->pixels;
			*L = *M;
			delete[] M->pixels;
			*M = *I;
			nL++;
			//std::cout << "Image L removed, new value for nL is " << nL << std::endl;
		}

		else if (nH < nL) {
			delete[] H->pixels;
			*H = *I;
			
			nH++;
			//std::cout << "Image H removed, new value for nH is " << nH << std::endl;
		}
		std::cout << std::endl;


	}

	if (nL == nH) {
		delete I->pixels;
		*I = *M;
	}

	if (nL < nH) {
		delete I->pixels;
		I = &meanOf2(*M, *H, M->getWidth(), M->getHeight());
	}

	if (nH < nL) {
		delete I->pixels;
		I = &meanOf2(*L, *M, M->getWidth(), M->getHeight());
	}

	if (L->pixels != NULL) { delete[] L->pixels; }
	if (M->pixels != NULL) { delete[] M->pixels; }
	if (H->pixels != NULL) { delete[] H->pixels; }
	

	system("pause");

	return *I;

	///17m 35s

}

Image stackerRolling::meanOf2(const Image &img, const Image &img2, int w, int h) {

	Image *Q = new Image(w, h); 	*Q = img;
	Image *R = new Image(w, h); 	*R = img2;


	for (unsigned int x = 0; x < (Q->getHeight() * Q->getWidth()); x++) {
		Q->pixels[x].r += R->pixels[x].r;
		Q->pixels[x].r /= 2;
		Q->pixels[x].g += R->pixels[x].g;
		Q->pixels[x].g /= 2;
		Q->pixels[x].b += R->pixels[x].b;
		Q->pixels[x].b /= 2;
	}
	delete R->pixels;
	return *Q;

}
