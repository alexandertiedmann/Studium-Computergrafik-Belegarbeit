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
	cout << "Check: " << check << endl;

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
	while (getline(infile, line))
	{
		count++;
		switch (count) {
			case 1: //level
				level = stoi(line);
				break;
			case 2: //yCoord
				yCoord = stoi(line);
				break;
			case 3: //xCoord
				xCoord = stoi(line);
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

	outfile << game.level << "\n";
	outfile << game.yCoord << "\n";
	outfile << game.xCoord << "\n";
	outfile << game.view << "\n";
	outfile << game.playtime << "\n";
	outfile << game.savedate.toString() << "\n";
	outfile << game.startdate.toString() << endl;

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

	//Failure
	if (!file) {
		cout << "File not found." << endl;
		ofstream outfile(scorefile);
		outfile << highscore << endl;
		outfile.close();
	}
	file.close();

	ofstream outfile(scorefile, ios::app);
	outfile << endl;
	outfile << highscore;
	outfile.close();
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
	if (scores.size() > 1) {
		sort(scores.begin(), scores.end());

		vector<int> highscores(numScores);
		for (int i = 0; i < highscores.size(); i++) {
			highscores[i] = scores[i];
		}

		return highscores;
	}
	else {
		vector<int> highscores(1);
		return highscores;
	}
}