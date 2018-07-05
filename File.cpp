#include "File.h"

/*
*	\brief	reads the given level to a array
*	\param	levelnum	-	number of the level
*/
char* readLevel(string levelnum) {
	string levelfile = "lvl" + levelnum;
	ofstream file;
	file.open(levelfile);
	char level[] = { '1', '2', '3' };

	//TODO: read the file and extract to array level

	file.close();
	return level;
}


/*
*	\brief	reads the given savefile and returns the savedate
*	\param	savenum	-	number of the savefile
*/
time_t readSavedate(string savenum) {
	string levelfile = "lvl" + savenum;
	ofstream file;
	file.open(levelfile);
	time_t date = time(nullptr);

	//TODO: read the file and extract the savedate

	file.close();
	return date;
}