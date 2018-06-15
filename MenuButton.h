#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

class MenuButton {
private:
	//get Screen Resolution
	const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
	int	  highlighted;					/* is the mouse cursor over the control? */
	int	  state;						/* the state, 1 if pressed, 0 otherwise */

	/*
	* Functions
	*/
	void Font(void *font, char *text, int x, int y);
	int ButtonClickTest(int x, int y);

public:
	//Button Variables
	int   x;							/* top left x coord of the button */
	int   y;							/* top left y coord of the button */
	int   w;							/* the width of the button */
	int   h;							/* the height of the button */
	char* label;						/* the text label of the button */
	typedef void(*ButtonCallback)();
	ButtonCallback callbackFunction;	/* A pointer to a function to call if the button is pressed */
	typedef struct Button Button;

	/*
	* Functions
	*/
	//MenuButton();
	MenuButton(int baseheigt, char* buttonName, int before, ButtonCallback buttonClickFunction); //Construktor
	MenuButton operator=(const MenuButton &rhs);
	void ButtonDraw();
	void ButtonRelease(int x, int y, int xpress, int ypress);
	void ButtonPress(int x, int y);
	void ButtonPassive(int x, int y);
};