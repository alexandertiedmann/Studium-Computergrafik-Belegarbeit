#include "ActualGame.h"


/*
*	\brief	Default construktor for new game
*/
ActualGame::ActualGame(){
	xCoord = 0;
	yCoord = 0;
	level = 1;
	view = 1;
	playtime = 0;
	savedate = time(nullptr);
	startdate = time(nullptr);
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
ActualGame::ActualGame(int x, int y, int lvl, int perspective, int time, time_t date){
	xCoord = x;
	yCoord = y;
	level = lvl;
	view = perspective;
	playtime = time;
	savedate = date;
}

/*
*	\brief	Returns the difference for the time in seconds
*	\param	startTime	-	start time
*	\param	endTime		-	stop time
*/
double ActualGame::diffTime(time_t startTime, time_t endTime) {
	return difftime(endTime, startTime);
}