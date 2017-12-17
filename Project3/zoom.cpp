#include "zoom.h"
#include "io.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "common.h"

Image zoom::doubleWidthHeightEx(int choice, const Image &img) {
	inputoutput io;

	Image *imgResize = new Image(0, 0);
	imgResize = (choice < 1) ? &io.readPPM("Images/Zoom/zIMG_1.ppm") : &doubleWidthHeightEx(choice - 1, *imgResize);

	ImageZoom *imgEx = new ImageZoom(imgResize->getWidth(), imgResize->getHeight());

	std::cout << "\n" << flush; system("CLS");
	std::cout << "				__________________________________" << std::endl << "Incrementing Total Value ::	";
	for (unsigned int N = 0; N < imgResize->getHeight() - 1; N++) {
		if (N % ((((imgResize->getHeight() - 1) + (imgResize->getHeight() - 1)) / 96)) != 0) {} else { std::cout << (char)254u; }

		for (unsigned int P = 0; P < imgResize->getWidth(); P++) {
			int x = (2 * N * imgEx->getWidth()) + (2 * P);		//the position in the imgEx we wish to change (every second row of imgEx) + (current pixel)
			int y = (N * imgResize->getWidth()) + P;						//the position in the imgN we want to copy
			int z = (2 * N * imgEx->getWidth()) + (2 * P) + 1;	//the extrapolated column position in imgEx to fill
			
			imgEx->pixels[x].r = imgResize->pixels[y].r;
			imgEx->pixels[x].g = imgResize->pixels[y].g;
			imgEx->pixels[x].b = imgResize->pixels[y].b;

			imgEx->pixels[z].r = imgResize->pixels[y].r;
			imgEx->pixels[z].g = imgResize->pixels[y].g;
			imgEx->pixels[z].b = imgResize->pixels[y].b;
		}
	}
	
	//loop extrapolated image: copy right all values by 1 column
	for (unsigned int N = 1; N < imgEx->getHeight(); N += 2) {

		for (unsigned int P = 0; P < imgEx->getWidth(); P++) {

			int y = (N * imgEx->getWidth()) + P;					//the position in the imgEx pixel to copy to
			int w = ((N - 1) * imgEx->getWidth()) + P;			//the in the previous row to copy from
		
			imgEx->pixels[y].r = imgEx->pixels[w].r;
			imgEx->pixels[y].g = imgEx->pixels[w].g;
			imgEx->pixels[y].b = imgEx->pixels[w].b;
			
		}
	}
	std::cout << (char)254u;
	delete[] imgResize->pixels;

	return *imgEx;
}

Image zoom::doubleWidthHeightAvg(int choice, const Image &img) {
	inputoutput io;

	Image *imgScale = new Image(0, 0);
	imgScale = (choice < 1) ? &io.readPPM("Images/Zoom/zIMG_1.ppm") : &doubleWidthHeightAvg(choice - 1, *imgScale);

	ImageZoom *imgEx = new ImageZoom(imgScale->getWidth(), imgScale->getHeight());

	for (unsigned int P = 0; P < imgScale->getWidth(); P++) {
		int x = (2 * P);		//the position in the imgEx we wish to change
		int y = P;				//the position in the imgN we want to copy
		imgEx->pixels[x].r = imgScale->pixels[y].r;
		imgEx->pixels[x].g = imgScale->pixels[y].g;
		imgEx->pixels[x].b = imgScale->pixels[y].b;
	}

	//Fill gaps for row 0
	for (unsigned int P = 1; P < imgScale->getWidth(); P++) {
		int x = (2 * P);		//the position in the imgEx we wish to change
		int y = P;					//the position in the imgN we want to copy

		imgEx->pixels[x - 1].r = (imgEx->pixels[x - 2].r + imgEx->pixels[x].r) / 2;
		imgEx->pixels[x - 1].g = (imgEx->pixels[x - 2].g + imgEx->pixels[x].g) / 2;
		imgEx->pixels[x - 1].b = (imgEx->pixels[x - 2].b + imgEx->pixels[x].b) / 2;
	}

	//Fill rows with existing values
	for (unsigned int N = 1; N < imgScale->getHeight() - 1; N++) {
		for (unsigned int P = 0; P < imgScale->getWidth(); P++) {
			int x = (2 * N * imgScale->getWidth() * 2) + (2 * P);		//the position in the imgEx we wish to change
			int y = (N * imgScale->getWidth()) + P;						//the position in the imgN we want to copy

			imgEx->pixels[x].r = imgScale->pixels[y].r;
			imgEx->pixels[x].g = imgScale->pixels[y].g;
			imgEx->pixels[x].b = imgScale->pixels[y].b;
		}
	}

	//Fill gaps for rows 1+
	for (unsigned int N = 1; N < imgScale->getHeight() - 1; N++) {
		for (unsigned int P = 1; P < imgScale->getWidth(); P++) {
			int x = (2 * N * imgScale->getWidth() * 2) + (2 * P);		//the position in the imgEx we wish to change
			int y = (N * imgScale->getWidth()) + P;						//the position in the imgN we want to copy

			imgEx->pixels[x - 1].r = (imgEx->pixels[x - 2].r + imgEx->pixels[x].r) / 2;
			imgEx->pixels[x - 1].g = (imgEx->pixels[x - 2].g + imgEx->pixels[x].g) / 2;
			imgEx->pixels[x - 1].b = (imgEx->pixels[x - 2].b + imgEx->pixels[x].b) / 2;

		}
	}

	//Fill empty rows
	for (unsigned int N = 1; N < imgEx->getHeight() - 1; N += 2) {
		for (unsigned int P = 0; P < imgEx->getWidth(); P++) {
			int x = ((N + 0) * imgEx->getWidth()) + P;			//the position in the imgEx we wish to change

			int w = ((N - 1) * imgEx->getWidth()) + P;			//the same column in the prior row
			int z = ((N + 1) * imgEx->getWidth()) + P;			//the same column in the next row

			imgEx->pixels[x].r = (imgEx->pixels[w].r + imgEx->pixels[z].r) / 2;
			imgEx->pixels[x].g = (imgEx->pixels[w].g + imgEx->pixels[z].g) / 2;
			imgEx->pixels[x].b = (imgEx->pixels[w].b + imgEx->pixels[z].b) / 2;

		}
	}

	delete[] imgScale->pixels;


	return *imgEx;


}

Image zoom::doubleWidthHeightAvg(Image &img, int itt) {
	inputoutput io;

	Image *imgScale = new Image(0, 0);
	
	imgScale = (itt <= 1) ? &img : &doubleWidthHeightAvg(img, itt - 1);


	ImageZoom *imgEx = new ImageZoom(imgScale->getWidth(), imgScale->getHeight());

	//Input row 0
	for (unsigned int P = 0; P < imgScale->getWidth(); P++) {
		int x = (2 * P);		//the position in the imgEx we wish to change
		int y = P;				//the position in the imgN we want to copy
		imgEx->pixels[x].r = imgScale->pixels[y].r;
		imgEx->pixels[x].g = imgScale->pixels[y].g;
		imgEx->pixels[x].b = imgScale->pixels[y].b;
	}

	//Fill gaps for row 0
	for (unsigned int P = 1; P < imgScale->getWidth(); P++) {
		int x = (2 * P);		//the position in the imgEx we wish to change
		int y = P;					//the position in the imgN we want to copy

		imgEx->pixels[x - 1].r = (imgEx->pixels[x - 2].r + imgEx->pixels[x].r) / 2;
		imgEx->pixels[x - 1].g = (imgEx->pixels[x - 2].g + imgEx->pixels[x].g) / 2;
		imgEx->pixels[x - 1].b = (imgEx->pixels[x - 2].b + imgEx->pixels[x].b) / 2;
	}

	//Fill rows with existing values
	for (unsigned int N = 1; N < imgScale->getHeight() - 1; N++) {
		for (unsigned int P = 0; P < imgScale->getWidth(); P++) {
			int x = (2 * N * imgScale->getWidth() * 2) + (2 * P);		//the position in the imgEx we wish to change
			int y = (N * imgScale->getWidth()) + P;						//the position in the imgN we want to copy

			imgEx->pixels[x].r = imgScale->pixels[y].r;
			imgEx->pixels[x].g = imgScale->pixels[y].g;
			imgEx->pixels[x].b = imgScale->pixels[y].b;
		}
	}

	//Fill gaps for rows 1+
	for (unsigned int N = 1; N < imgScale->getHeight() - 1; N++) {
		for (unsigned int P = 1; P < imgScale->getWidth(); P++) {
			int x = (2 * N * imgScale->getWidth() * 2) + (2 * P);		//the position in the imgEx we wish to change
			int y = (N * imgScale->getWidth()) + P;						//the position in the imgN we want to copy

			imgEx->pixels[x - 1].r = (imgEx->pixels[x - 2].r + imgEx->pixels[x].r) / 2;
			imgEx->pixels[x - 1].g = (imgEx->pixels[x - 2].g + imgEx->pixels[x].g) / 2;
			imgEx->pixels[x - 1].b = (imgEx->pixels[x - 2].b + imgEx->pixels[x].b) / 2;

		}
	}

	//Fill empty rows
	for (unsigned int N = 1; N < imgEx->getHeight() - 1; N += 2) {
		for (unsigned int P = 0; P < imgEx->getWidth(); P++) {
			int x = ((N + 0) * imgEx->getWidth()) + P;			//the position in the imgEx we wish to change

			int w = ((N - 1) * imgEx->getWidth()) + P;			//the same column in the prior row
			int z = ((N + 1) * imgEx->getWidth()) + P;			//the same column in the next row

			imgEx->pixels[x].r = (imgEx->pixels[w].r + imgEx->pixels[z].r) / 2;
			imgEx->pixels[x].g = (imgEx->pixels[w].g + imgEx->pixels[z].g) / 2;
			imgEx->pixels[x].b = (imgEx->pixels[w].b + imgEx->pixels[z].b) / 2;

		}
	}//*/

	delete[] imgScale->pixels;

	//io.writePPM(*imgEx, "Results/imgExAvg.ppm");

	return *imgEx;


}

Image zoom::zoomROI(int tLx, int tLy, int selW, int selH, int zoomF) {
	inputoutput io;

	Image *img = new Image(0, 0);
	img = &io.readPPM("Images/Zoom/zIMG_1.ppm");

	int fR = tLx;
	int fC = tLy;

	int sH = selH;
	int sW = selW;

	int lR = fR + sH;
	int lC = fC + sW;

	Image *selection = new Image(sW, sH);

	//copy data to new image

	int P = 0;
	for (int x = fR; x < lR; x++) {					//loop through ech column in selection
		for (int y = fC; y < lC; y++) {				//loop through each row in selection
			int T = (img->getWidth() * x) + y;			//pixel location to copy from

			selection->pixels[P].r = img->pixels[T].r;
			selection->pixels[P].g = img->pixels[T].g;
			selection->pixels[P].b = img->pixels[T].b;

			P++;
		}
	}

	io.writePPM(*selection, "selection.ppm");

	
	selection = &zoom::doubleWidthHeightAvg(*selection, zoomF);
	
	
	return *selection;
}

long int zoom::floorSig(long int number, int significance) {
	return round(number / significance)*significance;
}
