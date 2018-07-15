#include "ActualLevel.hpp"

/*
*	\brief	sets the level from teh given array
*	\param	2D Array with level
*/
ActualLevel::ActualLevel(vector<vector<char>> lvl){
	level = lvl;
	height = level.size();
	width = level[0].size();
	//cout << height << " " << width << endl;
}

/*
*	\brief	returns the vector of the actual level
*/
vector<vector<char>> ActualLevel::getLevel() {
	return level;
}

/*
*	\brief	returns the height of the actual level
*/
int ActualLevel::getLevelHeight() {
	return height;
}

/*
*	\brief	returns the width of the actual level
*/
int ActualLevel::getLevelWidth() {
	return width;
}

/*
*	\brief	gives the level as a string
*/
string ActualLevel::toString() {
	ostringstream levelstream;
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			levelstream << level[i][k] << " ";
		}
		levelstream << endl;
	}
	return levelstream.str();
}
