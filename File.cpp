#include "File.hpp"

/*
*	\brief	reads the given savefile and returns the savedate
*	\param	savenum	-	number of the savefile
*/
DateTime readSavedate(int savenum) {
	//Savefile suchen
	string num = to_string(savenum);
	string savefile = "saves\\00" + num + ".sav";
	//cout << savefile << endl;
	string savedate;
	int count = 0;
	ifstream infile(savefile);

	//Fehlermeldung bei nicht vorhandenem File
	if (!infile) {
		cout << "File not found." << endl;
		DateTime fail("0000-00-00 00-00");
		return fail;
	}

	//Datei auslesen
	string line;
	while (getline(infile, line))
	{
		count++;
		if (count == 6) { //line 6
			savedate = line;
		}
	}
	infile.close();

	//cout << "From File: " << savedate << endl;
	DateTime date(savedate);
	return date;
}

/*
*	\brief	reads the given savefile
*	\param	savenum	-	number of the savefile
*/
ActualGame readSave(int savenum) {
	
	//Savefile suchen
	string num = to_string(savenum);
	string savefile = "saves\\00" + num + ".sav";
	int count = 0;
	ifstream infile(savefile);

	//Fehlermeldung bei nicht vorhandenem File
	if (!infile) {
		cout << "File not found." << endl;
		ActualGame fail;
		return fail;
	}

	int level, xCoord, yCoord, view;
	double playtime;
	string datesa, datest;

	//Datei auslesen
	string line;
	while (getline(infile, line))
	{
		count++;
		switch (count) {
			case 1: //level
				level = stoi(line);
				break;
			case 2: //xCoord
				xCoord = stoi(line);
				break;
			case 3: //yCoord
				yCoord = stoi(line);
				break;
			case 4: //view
				view = stoi(line);
				break;
			case 5: //playtime
				playtime = stoi(line);
				break;
			case 6: //savedate
				datesa = line;
				break;
			case 7: //startdate
				datest = line;
				break;
		}
	}
	infile.close();

	DateTime savedate(datesa);
	DateTime startdate(datest);

	ActualGame game(xCoord, yCoord, level, view, playtime, savedate, startdate);
	return game;
}

/*
*	\brief	reads the given level
*	\param	levelnum	-	number of the levelfile
*/
ActualLevel readLevel(int levelnum) {
	if (levelnum < 1) {
		cout << "Levelnum can not be < 1 !" << endl;
	}
	//get height and width
		//read file
	string num = to_string(levelnum);
	string savefile = "level\\00" + num + ".lvl";
	int height = 0;
	int width = 0;
	ifstream infile(savefile);

	//Failure
	if (!infile) {
		cout << "File not found." << endl;
		return readLevel(levelnum-1);
	}

	//Datei auslesen
	string line;
	while (getline(infile, line))
	{
		height++;
		width = line.length();
	}
	infile.close();

	//Create Vector
	vector<vector<char>> levelVec(height, vector<char>(width));

	//fill Vector
	line = "";
	ifstream file(savefile);
	int countline = 0;
	while (getline(file, line))
	{
		for (int w = 0; w < levelVec[0].size(); w++) {
			levelVec[countline][w] = line[w];
		}
		countline++;
	}
	infile.close();

	//create and fill level
	ActualLevel level(levelVec);
	return level;
}