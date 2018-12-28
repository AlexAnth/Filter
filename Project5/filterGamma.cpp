#include <iostream>
#include "Image.h"
#include "Vec3.h"
#include "Filter.h"
using namespace imaging;
using namespace math;
typedef Vec3<float> VecVal;

filterGamma::filterGamma() {
	this->pw = 1;
}

filterGamma::filterGamma(double pw) 
{
	if(pw>=0.5 && pw<=2.0)
		this->pw = pw;
	else
	{
		if (pw < 0.5)
			this->pw = 0.5;
		else if (pw > 2.0)
			this->pw = 2.0;
	}

	
}

Image filterGamma:: operator <<(const Image &image)
{
	Image newimg(image);
	for (int i = 0; i < image.getWidth(); i++)
	{
		for (int j = 0; j < image.getHeight(); j++) {
			Vec3<float> item = newimg.getItem(i, j);
			Vec3<float>newItem;
			newItem.r = pow(item.r, pw);
			newItem.g = pow(item.g, pw);
			newItem.b = pow(item.b, pw);

			newimg.setItem(i, j, newItem);

		}
	}
	return newimg;
}


