#include "ActualLevel.hpp"

/*
*	\brief	sets the level from teh given array
*	\param	2D Array with level
*/
<<<<<<< HEAD
ActualLevel::ActualLevel()
{
}
=======
ActualLevel::ActualLevel() {
	level = readLevel(1);
	height = level.size();
	width = level[0].size();
}

/*
*	\brief	sets the level from teh given array
*	\param	2D Array with level
*/
>>>>>>> 1ef9a7359d96e57e666e2e2639e69d02f45d4029
ActualLevel::ActualLevel(vector<vector<char>> lvl){
	level = lvl;
	height = level.size();
	width = level[0].size();
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
