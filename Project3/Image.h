#ifndef image_h
	#define image_h
	//*********************************************
	//Image class to hold and allow manipulation of images once read into the code
	//from https://www.scratchapixel.com/
	//*********************************************
	#include <cstdlib> 
	#include <cstdio> 
	#include <fstream>


	struct RgbChar
	{
	

		RgbChar() : r(0), g(0), b(0) {}
		RgbChar(unsigned char c) : r(c), g(c), b(c) {}
		RgbChar(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b) {}

	
		bool operator != (const RgbChar &c) const				
		{
			return c.r != r || c.g != g || c.b != b;
		}
		RgbChar& operator *= (const RgbChar &RgbChar)
		{
			r *= RgbChar.r, g *= RgbChar.g, b *= RgbChar.b; return *this;
		}
		RgbChar& operator += (const RgbChar &RgbChar)	
		{
			r += RgbChar.r, g += RgbChar.g, b += RgbChar.b; return *this;
		}
		friend unsigned char& operator += (unsigned char &f, const RgbChar RgbChar)
		{
			f += (RgbChar.r + RgbChar.g + RgbChar.b) / 3.f; return f;
		}

		unsigned char r, g, b;
	};

	class Image : public RgbChar
	{
	private:
		unsigned int w, h;
	
	public:

	
		Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }

		Image(const unsigned int &_w, const unsigned int &_h, const RgbChar &c = RgbChar(0)) : w(_w), h(_h), pixels(NULL)
		{
			pixels = new RgbChar[w * h];
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = c;
		}
	
		virtual void copyStruct(RgbChar *RgbCharStruct) {
			for (int x = 0; x < (this->h * this->w); x++) {
				this->pixels[x] = RgbCharStruct[x];
			}
		}

		virtual void resetStruct() {
			delete[] this->pixels;
			pixels = new RgbChar[w * h];
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = RgbChar(0);
		}

		virtual Image& operator=(const Image& other)
		{
			w = other.w;
			h = other.h;
			pixels = new RgbChar[other.w * other.h];
			for (unsigned int i = 0; i < other.w * other.h; ++i)
				pixels[i] = other.pixels[i];

			return *this;

		}

	
		virtual const RgbChar& operator [] (const unsigned int &i) const
		{
			return pixels[i];
		}
		virtual RgbChar& operator [] (const unsigned int &i)
		{
			return pixels[i];
		}

	
		~Image() {}

		RgbChar *pixels; 

		unsigned int getHeight() { return h; }
		unsigned int getWidth() { return w; }
		void setHeight(unsigned int _h) { this->h = _h; }
		void setWidth(unsigned int _w) { this->w = _w; }

		// ImageInfo
		const char *fileName = "fileName.ppm";
		void saveFileName(const char *s) { fileName = s; }
		int dataStoreRange() { return 255; }

		void outputData() {
			std::ofstream outfile;
			outfile.open("log.txt", std::ios_base::app);
			outfile << "FileName: " << fileName;
			outfile << "\n	Height: " << getHeight();
			outfile << "\n	Width: " << getWidth();
			outfile << "\n	DataStorageRange: " << dataStoreRange();
			outfile << "\n";
		}

	};
	class ImageZoom : public virtual Image
	{
	public:

		ImageZoom() : Image() {};
		ImageZoom(const unsigned int w, const unsigned int h) : Image(2*w, 2*h) {};

		~ImageZoom() {};

		unsigned int getHeight() { return Image::getHeight(); }
		unsigned int getWidth() { return Image::getWidth(); }
		void setHeight(unsigned int _h) { Image::setHeight(_h); }
		void setWidth(unsigned int _w) { Image::setWidth(_w); }


		const char *fileName = "fileName.ppm";
		void saveFileName(const char *s) { fileName = s; }
		int dataStoreRange() { return 255; }
		void outputData() {
			std::ofstream outfile;
			outfile.open("/log.txt", std::ios_base::app);

			outfile << "FileName: " << fileName;
			outfile << "\n	Height: " << getHeight();
			outfile << "\n	Width: " << getWidth();
			outfile << "\n	DataStorageRange: " << dataStoreRange();
			outfile << "\n";

			outfile.close();
		}
	};


	struct RbgShort
	{
		short r, g, b;
	
		RbgShort() : r(0), g(0), b(0) {}
		RbgShort(short c) : r(c), g(c), b(c) {}
		RbgShort(short _r, short _g, short _b) : r(_r), g(_g), b(_b) {}

	
		bool operator != (const RbgShort &c) const	
		{
			return c.r != r || c.g != g || c.b != b;
		}
		RbgShort& operator *= (const RbgShort &RbgShort)
		{
			r *= RbgShort.r, g *= RbgShort.g, b *= RbgShort.b; return *this;
		}
		RbgShort& operator += (const RbgShort &RbgShort)
		{
			r += RbgShort.r, g += RbgShort.g, b += RbgShort.b; return *this;
		}
		friend short& operator += (short &f, const RbgShort RbgShort)	
		{
			f += (RbgShort.r + RbgShort.g + RbgShort.b) / 3.f; return f;
		}
		~RbgShort() {}


	};
	class ImageLarge : public RbgShort
	{
	private:
		unsigned short w, h; 
	public:
	
		ImageLarge() : w(0), h(0), pixels(nullptr) { /* empty image */ }

		ImageLarge(const unsigned short &_w, const unsigned short &_h, const RbgShort &c = RbgShort(0)) :
			w(_w), h(_h), pixels(NULL)
		{
			pixels = new RbgShort[w * h];
			for (unsigned short i = 0; i < w * h; ++i)
				pixels[i] = c;
		}

		
		const RbgShort& operator [] (const unsigned short &i) const
		{
			return pixels[i];
		}

		
		RbgShort& operator [] (const unsigned short &i)
		{
			return pixels[i];
		}


	
		~ImageLarge() {}
	
		RbgShort *pixels;

		unsigned int getHeight() { return h; }
		unsigned int getWidth() { return w; }
		void setHeight(unsigned int _h) { this->h = _h; }
		void setWidth(unsigned int _w) { this->w = _w; }


		const char *fileName = "fileName.ppm";
		void saveFileName(const char *s) { fileName = s; }
		short dataStoreRange() { return 2147483647; }

		void outputData() {
			std::ofstream outfile;
			outfile.open("log.txt", std::ios_base::app);

			outfile << "FileName: " << fileName;
			outfile << "\n	Height: " << getHeight();
			outfile << "\n	Width: " << getWidth();
			outfile << "\n	DataStorageRange: " << dataStoreRange();
			outfile << "\n";
		}

	};


	struct RgbFloat
	{
		float r, g, b;

		RgbFloat() : r(0), g(0), b(0) {}
		RgbFloat(float c) : r(c), g(c), b(c) {}
		RgbFloat(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

	
		bool operator != (const RgbFloat &c) const
		{
			return c.r != r || c.g != g || c.b != b;
		}
		RgbFloat& operator *= (const RgbFloat &RgbFloat)
		{
			r *= RgbFloat.r, g *= RgbFloat.g, b *= RgbFloat.b; return *this;
		}
		RgbFloat& operator += (const RgbFloat &RgbFloat)
		{
			r += RgbFloat.r, g += RgbFloat.g, b += RgbFloat.b; return *this;
		}
		friend float& operator += (float &f, const RgbFloat RgbFloat)
		{
			f += (RgbFloat.r + RgbFloat.g + RgbFloat.b) / 3.f; return f;
		}
		~RgbFloat() {}


	};
	class ImageDec : public RgbFloat
	{
	private:
		unsigned short w, h;

	public:
	

		ImageDec() : w(0), h(0), pixels(nullptr) { /* empty image */ }

	
		ImageDec(const float &_w, const float &_h, const RgbFloat &c = RgbFloat(0)) :
			w(_w), h(_h), pixels(NULL)
		{
			pixels = new RgbFloat[w * h];
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = c;
		}

		
		const RgbFloat& operator [] (unsigned int  &i) const
		{
			return pixels[i];
		}

		
		RgbFloat& operator [] (unsigned int  &i)
		{
			return pixels[i];
		}


		~ImageDec() {}

	
		RgbFloat *pixels; 


		unsigned int getHeight() { return h; }
		unsigned int getWidth() { return w; }
		void setHeight(unsigned int _h) { this->h = _h; }
		void setWidth(unsigned int _w) { this->w = _w; }


		const char *fileName = "fileName.ppm";
		void saveFileName(const char *s) { fileName = s; }
		int dataStoreRange() { return  3.40282e+38; }

		void outputData() {
			std::ofstream outfile;
			outfile.open("log.txt", std::ios_base::app);

			outfile << "FileName: " << fileName;
			outfile << "\n	Height: " << getHeight();
			outfile << "\n	Width: " << getWidth();
			outfile << "\n	DataStorageRange: " << dataStoreRange();
			outfile << "\n";
		}

	};

#endif // !


