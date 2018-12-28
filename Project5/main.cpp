/*
	Trikalis Christos - 3140205

 	Alexandros Anthis - 3140012
*/


#include "Filter.h"
#include <iostream>
#include <string>
#include "Image.h"
#include "Vec3.h"

using namespace std;
using namespace imaging;
using namespace math; 

void first_assignment(bool loaded, Image image, string filename);
void second_assignment(bool loaded, Image image, string filename,char**argv,int argc);
typedef Vec3<float> Value;

int main(int argc, char **argv)
{
	
	string filename;
	Image image;

	if (argc == 1)
	{
		string input;
		string pow, aR, aG, aB, cR, cG, cB;
		cout << "set filters > ";
		cin >> input;
		filename = input;
		bool load = image.load(filename, "ppm");
		cout << filename << endl;
		cin >> input;
		while (input != (string)("filter"))
		{

			if (input == (string)("gamma"))
			{
				cin >> pow;
				float p = stof(pow);
				filterGamma gamma(p);
				image = gamma << image;
			}
			else if (input == (string)("linear"))
			{
				cin >> aR;
				cin >> aG;
				cin >> aB;
				cin >> cR;
				cin >> cG;
				cin >> cB;
				Value a = (stof(aR), stof(aG), stof(aB));
				Value c = (stof(cR), stof(cG), stof(cB));
				filterLinear linear(a, c);
				image = linear << image;
			}
			cin >> input;
		}

		image.save("filtered_" + filename, "ppm");

	}
	else if (argc >= 2)
	{
		filename = argv[argc - 1];



		bool loaded = image.load(filename, "ppm");


		second_assignment(loaded, image, filename, argv, argc);


	}
	//first_assignment(loaded, image, filename);


	system("PAUSE");
	return 0;
}


void first_assignment(bool loaded,Image image,string filename)
{
	if (loaded) {
		for (unsigned int j = 0; j < image.getHeight(); j++)
		{
			for (unsigned int i = 0; i < image.getWidth(); i++)
			{
				Color temporary = image.getColor(i, j);
				Color color = Color(1, 1, 1) - temporary;
				image.setColor(i, j, color);
			}
		}
		filename = filename.substr(0, filename.length() - 4);
		image.save(filename + "_neg.ppm", "ppm");
	}
}

void second_assignment(bool loaded, Image image, string filename,char **argv,int argc) 
{
	int linearcounter = 0;
	int gammacounter = 0;
	if (loaded)
	{
		if (strcmp(argv[1], "filter") == 0)
		{
			for (int i = 2; i < argc - 1; i++)
			{
				if (strcmp(argv[i], "gamma") == 0)
				{
					gammacounter++;
					float power = atof(argv[i + 1]);
					filterGamma gamma(power);
					image = gamma << image;
					i = i + 2;
				}
				else if (strcmp(argv[i], "linear") == 0)
				{
					linearcounter++;
					Value a = (atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
					Value c = (atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
					filterLinear linear(a, c);
					image = linear << image;
					i = i + 7;
				}
			}

			size_t i = filename.find_last_of('\\');
			image.save(filename.substr(0, i + 1) + "filtered_" + filename.substr(i + 1), "ppm");
			cout << "image has been " << linearcounter << " times linear filtered and " << gammacounter << " times gamma filtered." << endl;
		}
		else
		{
			cout << "must have filter" << endl;
		}
	}
}