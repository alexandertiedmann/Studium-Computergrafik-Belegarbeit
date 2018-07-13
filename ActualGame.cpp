#include "ActualGame.hpp"

/*
*	\brief	Default construktor for new game
*/
ActualGame::ActualGame(){
	xCoord = 0;
	yCoord = 0;
	level = 1;
	view = 1; //Blickrichtung
	playtime = 0; //wie lange in Level verbracht
	DateTime savedate; //vergleich fuer Continue
	DateTime startdate; //im Menue anzeigen lassen
}

/*
*	\brief	Construktor to load a game from a save
*	\param	xCoord	-	x-ccord in labyrinth
*	\param	yCoord	-	y-coord in labyrinth
*	\param	lvl		-	actual level
*	\param	view	-	perspective
*	\param	time	-	playtime
*	\param	date	-	Date and time of the savegame
*/
ActualGame::ActualGame(int x, int y, int lvl, int perspective, double time, DateTime date, DateTime start){
	xCoord = x;
	yCoord = y;
	level = lvl;
	view = perspective;
	playtime = time;
	savedate = date;
	startdate = start;
}

/*
*	\brief	saves the time to start a game
*/
void ActualGame::startTimer() {
	starttime = time(nullptr);
}

/*
*	\brief	adds the played seconds to playtime
*/
void ActualGame::stopTimer() {
	playtime = playtime + difftime(starttime, time(nullptr));
}

/*
*	\brief	Returns the difference for the time in seconds
*	\param	startTime	-	start time
*	\param	endTime		-	stop time
*/
double ActualGame::diffTime(time_t startTime, time_t endTime) {
	return difftime(endTime, startTime);
}

/*
*	\brief	Returns the String of the object
*/
string ActualGame::toString() {
	string line;
	line += "Level: " + to_string(level) + "\n";
	line += "xCoord: " + to_string(xCoord) + "\n";
	line += "yCoord: " + to_string(yCoord) + "\n";
	line += "View: " + to_string(view) + "\n";
	line += "Playtime: " + to_string(playtime) + "\n";
	line += "Savedate: " + savedate.toString() + "\n";
	line += "Startdate: " + startdate.toString() + "\n";
	return line;
}