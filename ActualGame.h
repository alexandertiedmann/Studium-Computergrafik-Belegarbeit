#include <ctime>
class ActualGame
{
public:
	//Variables:
	int xCoord;
	int yCoord;
	int level;
	int view;
	int playtime;
	time_t savedate;
	time_t startdate;
	//Methods:
	ActualGame();
	ActualGame(int x, int y, int lvl, int perspective, int time, std::time_t savedate);
	double diffTime(time_t startTime, time_t endTime);
};

