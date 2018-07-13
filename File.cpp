#include "File.hpp"

/*
*	\brief	reads the given savefile and returns the savedate
*	\param	savenum	-	number of the savefile
*/
DateTime readSavedate(int savenum) {
	//Savefile suchen
	string num = std::to_string(savenum);
	string savefile = "saves\\00" + num + ".sav";
	//cout << savefile << endl;
	string savedate;
	int count = 0;
	std::ifstream infile(savefile);

	//Fehlermeldung bei nicht vorhandenem File
	if (!infile) {
		std::cout << "File not found." << std::endl;
		DateTime fail("0000-00-00 00-00");
		return fail;
	}

	//Datei auslesen
	std::string line;
	while (std::getline(infile, line))
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
	string num = std::to_string(savenum);
	string savefile = "saves\\00" + num + ".sav";
	int count = 0;
	std::ifstream infile(savefile);

	//Fehlermeldung bei nicht vorhandenem File
	if (!infile) {
		std::cout << "File not found." << std::endl;
		ActualGame fail;
		return fail;
	}

	int level, xCoord, yCoord, view;
	double playtime;
	string datesa, datest;

	//Datei auslesen
	std::string line;
	while (std::getline(infile, line))
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