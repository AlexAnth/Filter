#include <iostream>
#include "Image.h"
#include "Vec3.h"
using namespace imaging;
using namespace math;



class Filter
{

	public:
		virtual Image operator << (const Image& img)=0;

	//default constructor?
};

typedef Vec3<float> VecVal;
class filterLinear : public Filter
{
	protected:
		VecVal a, c;
	public:

		filterLinear(VecVal a, VecVal c);
		filterLinear();
		filterLinear(const filterLinear& src);

		Image operator << (const Image& image);
		
};
class filterGamma : public Filter
{
	protected:
		double pw;
	public:
		filterGamma(double pw);
		filterGamma();
		filterGamma(const filterGamma &src);

		Image operator << (const Image& image);
};
