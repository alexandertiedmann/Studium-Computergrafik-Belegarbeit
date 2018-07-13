#include "ActualLevel.hpp"

ActualLevel::ActualLevel(){
	
}

char** getSetArray(int height, int width) {
	char** array2D;
	array2D = new char*[height];

	for (int h = 0; h < height; h++)
	{
		array2D[h] = new char[width];

		for (int w = 0; w < width; w++)
		{
			// fill in some initial values
			// (filling in zeros would be more logic, but this is just for the example)
			array2D[h][w] = w + width * h;
		}
	}

	return array2D;
}
