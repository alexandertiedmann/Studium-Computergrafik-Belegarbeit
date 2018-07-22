#pragma once
#ifndef Menu_Header
#define Menu_Header

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "DateTime.hpp"
#include "File.hpp"
#include "ActualLevel.hpp"
#include "ActualGame.hpp"
#include "Labyrinth.hpp"

struct Mouse
{
	int x;		/*	the x coordinate of the mouse cursor	*/
	int y;		/*	the y coordinate of the mouse cursor	*/
	int lmb;	/*	is the left button pressed?		*/
	int mmb;	/*	is the middle button pressed?	*/
	int rmb;	/*	is the right button pressed?	*/

				/*
				*	These two variables are a bit odd. Basically I have added these to help replicate
				*	the way that most user interface systems work. When a button press occurs, if no
				*	other button is held down then the co-ordinates of where that click occured are stored.
				*	If other buttons are pressed when another button is pressed it will not update these
				*	values.
				*
				*	This allows us to "Set the Focus" to a specific portion of the screen. For example,
				*	in maya, clicking the Alt+LMB in a view allows you to move the mouse about and alter
				*	just that view. Essentually that viewport takes control of the mouse, therefore it is
				*	useful to know where the first click occured....
				*/
	int xpress; /*	stores the x-coord of when the first button press occurred	*/
	int ypress; /*	stores the y-coord of when the first button press occurred	*/
};
typedef struct Mouse Mouse;

typedef void(*ButtonCallback)();
struct Button
{
	int   x;							/* top left x coord of the button */
	int   y;							/* top left y coord of the button */
	int   w;							/* the width of the button */
	int   h;							/* the height of the button */
	int	  state;						/* the state, 1 if pressed, 0 otherwise */
	int	  highlighted;					/* is the mouse cursor over the control? */
	char* label;						/* the text label of the button */
	ButtonCallback callbackFunction;	/* A pointer to a function to call if the button is pressed */
};
typedef struct Button Button;

void Continue();
void Save();
void New();
void Load();
void High();
void Exit();
int calcW();
int calcH();
int calcX();
int calcY(int before);
void Font(void *font, char *text, int x, int y);
int ButtonClickTest(Button* b, int x, int y);
void ButtonRelease(Button *b, int x, int y);
void ButtonPress(Button *b, int x, int y);
void ButtonPassive(Button *b, int x, int y);
void ButtonDraw(Button *b);
void Draw3D();
void Draw2D();
void Draw();
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void MousePassiveMotion(int x, int y);
void renderScene(void);
bool closeMainMenu();
void callMenu();
ActualGame getActualGameFromLabyrinth();
ActualLevel getActualLevelFromLabyrinth();
void closeSubMenu();
bool callMainMenu();
void callLoadMenu();
void callSaveMenu();
void callHighscores();
void callFin();
void drawHighscores();
void drawFinish();
bool getLabbyOpen();
bool getMenuOpen();
void drawLabyrinth();
void setMenuOpen(bool openMain);
void loadLab(Labyrinth* labyrinth);
Labyrinth getLabyrinth();


#endif
