#include "File.hpp"

/*
*	\brief checks if a path is a directory
*	returns 0 if somithing is wrong
*	returns 1 if it is a directory
*	returns 2 if it is no directory but exists
*/
int dirExists(const string& dirName) {
	DWORD ftyp = GetFileAttributesA(dirName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return 0;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return 1;   // this is a directory!

	return 2;    // this is not a directory!
}

/*
*	\brief checks if a directory exists and create it if not
*	\param path of directory
*/
void checkDirectory(string directory) {
	int check = dirExists(directory);
	const char * dir = directory.c_str();

	if (check == 1 || check == 0) {
		CreateDirectory(dir, NULL);
	}
}

/*
*	\brief	reads the given savefile and returns the savedate
*	\param	savenum	-	number of the savefile
*/
DateTime readSavedate(int savenum) {
	//Savefile suchen
	string num = to_string(savenum);
	string dir = "saves";
	checkDirectory(dir);
	string savefile = dir + "\\00" + num + ".sav";
	//cout << savefile << endl;
	string savedate;
	int count = 0;
	ifstream infile(savefile);

	//Fehlermeldung bei nicht vorhandenem File
	if (!infile) {
		cout << "File not found." << endl;
		DateTime fail("0000-00-00 00:00");
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
	string dir = "saves";
	checkDirectory(dir);
	string savefile = dir + "\\00" + num + ".sav";
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
	cout << "Read Save: ";
	while (getline(infile, line))
	{
		count++;
		switch (count) {
			case 1: //level
				level = stoi(line);
				cout << "Level: " << level << " | ";
				break;
			case 2: //yCoord
				yCoord = stoi(line);
				cout << "yCoord: " << yCoord << " | ";
				break;
			case 3: //xCoord
				xCoord = stoi(line);
				cout << "xCoord: " << xCoord << " | ";
				break;
			case 4: //view
				view = stoi(line);
				cout << "view: " << view << " | ";
				break;
			case 5: //playtime
				playtime = stoi(line);
				cout << "playtime: " << playtime << " | ";
				break;
			case 6: //savedate
				datesa = line;
				cout << "savedate: " << datesa << " | ";
				break;
			case 7: //startdate
				datest = line;
				cout << "startdate: " << datest << " | ";
				break;
		}
	}
	cout << endl;
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
	//get height and width
	//read file
	string num = to_string(levelnum);
	string levelfile;

	string dir = "level";
	checkDirectory(dir);

	if (levelnum < 10) {
		levelfile = dir + "\\00" + num + ".lvl";
	}
	else {
		levelfile = dir + "\\0" + num + ".lvl";
	}
	int height = 0;
	int width = 0;
	ifstream infile(levelfile);

	//Failure
	if (!infile) {
		cout << "Level-File not found." << endl;
		if (levelnum == 1) {
			cout << "No Level found" << endl;
			exit(-1);
		}
		else {
			return readLevel(levelnum - 1);
		}
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
	ifstream file(levelfile);
	int countline = 0;
	while (getline(file, line)){
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

/*
*	\brief	write the ActualGame to the save
*	\param	levelnum	-	number of the savefile
*	\param	game		-	The Object of the actualGame
*/
void writeGame(int savenum, ActualGame game) {
	string num = to_string(savenum);
	string dir = "saves";
	checkDirectory(dir);
	string savefile = dir + "\\00" + num + ".sav";
	ifstream infile(savefile);

	//new and overwrite
	std::ofstream outfile(savefile);
	cout << "Write Save: ";
	cout << "level: " << game.level << " | ";
	outfile << game.level << endl;
	cout << "yCoord: " << game.yCoord << " | ";
	outfile << game.yCoord << endl;
	cout << "xCoord: " << game.xCoord << " | ";
	outfile << game.xCoord << endl;
	cout << "view: " << game.view << " | ";
	outfile << game.view << endl;
	cout << "playtime: " << game.playtime << " | ";
	outfile << game.playtime << endl;
	cout << "savedate: " << game.savedate.toString() << " | ";
	outfile << game.savedate.toString() << endl;
	cout << "startdate: " << game.startdate.toString() << " | ";
	outfile << game.startdate.toString();
	cout << endl;
	outfile.close();
}

/*
*	\brief	writes a new highscore to the highscore file
*	\param	highscore	-	new highscore to write
*/
void addHighscore(int highscore) {
	string dir = "saves";
	checkDirectory(dir);
	string scorefile = dir + "\\highscores.scores";

	ifstream file(scorefile);

	string highscorestring(to_string(highscore));

	//check new file
	string line;
	ifstream readfile(scorefile);
	int linecounter = 0;
	int linelength = 0;
	while (getline(readfile, line)) {
		linecounter++;
		if (linecounter == 1) {
			if (line.length() > 1) {
				linelength = line.length();
			}
		}
	}
	readfile.close();

	if (highscorestring.length() < 2) {
		cout << "You damn Cheater" << endl;
	}
	else {
		//check new file
		if (linecounter != 1 && linelength < 2) {
			ofstream outfile(scorefile, ios::app);
			outfile << highscore;
			outfile.close();
		}
		else {
			ofstream outfile(scorefile, ios::app);
			outfile << endl;
			outfile << highscore;
			outfile.close();
		}
	}
}

/*
*	\brief	reads and returns the hihscore from the file
*	\param	numScores	-	number of highscores to return
*/
vector<int> readScores(int numScores) {
	vector<int> scores;
	string dir = "saves";
	checkDirectory(dir);
	string scorefile = dir + "\\highscores.scores";
	ifstream infile(scorefile);

	//Failure
	if (!infile) {
		cout << "File not found." << endl;
		std::ofstream outfile(scorefile);
		outfile << "";
		outfile.close();
	}
	infile.close();
	
	//Datei auslesen
	string line;
	ifstream readfile(scorefile);
	while (getline(readfile, line)){
		if (line.length() > 1) {
			int score = atoi(line.c_str());
			scores.push_back(score);
		}
	}
	readfile.close();

	//sort vec
	if (scores.size() > 0) {
		if (scores.size() > 1) {
			sort(scores.begin(), scores.end());
		}
		vector<int> highscores;
		for (int i = 0; i < scores.size(); i++) {
			if (i > numScores) {
				break;
			}
			highscores.push_back(scores[i]);
		}
		while (highscores.size() < numScores) {
			highscores.push_back(0);
		}
		return highscores;
	}
	else {
		vector<int> highscores(0);
		return highscores;
	}
}