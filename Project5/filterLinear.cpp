#include <iostream>
#include "Image.h"
#include "Vec3.h"
#include "Filter.h"
using namespace imaging;
using namespace math;
typedef Vec3<float> VecVal;


filterLinear::filterLinear(VecVal aV, VecVal cV)
{
	this->a = aV;
	this->c = cV;
	
}

filterLinear::filterLinear()
{
	this->a = VecVal(1, 1, 1);
	this->c = VecVal(0, 0, 0);
}

filterLinear::filterLinear(const filterLinear& src)
{
	this->a = src.a;
	this->c = src.c;
}




Image filterLinear :: operator<<(const Image &image)
{
	Image newimg(image);

	for (int i = 0; i < image.getWidth(); i++)
	{
		for (int j = 0; j < image.getHeight(); j++)
		{
			VecVal item = newimg.getItem(i, j);
			VecVal newItem = a*item + c;
			if (newItem.r < 0) {
				newItem.r = 0;
			}
			if (newItem.r > 1.0) {
				newItem.r = 1.0;
			}

			if (newItem.g < 0) {
				newItem.g = 0;
			}
			if (newItem.g > 1.0) {
				newItem.g = 1.0;
			}

			if (newItem.b < 0) {
				newItem.b = 0;
			}
			if (newItem.b > 1.0) {
				newItem.b = 1.0;
			}
			newimg.setItem(i, j, newItem);
		}
	}

	return newimg;
}
