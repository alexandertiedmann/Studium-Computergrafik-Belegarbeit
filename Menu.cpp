#include "Menu.hpp"

/*----------------------------------------------------------------------------------------
*	Global Variables
*/

/*
*	rename the structure from "struct Mouse" to just "Mouse"
*/
typedef struct Mouse Mouse;
bool openMenu = false;

/*
*	Create a global mouse structure to hold the mouse information.
*/
Mouse TheMouse = { 0,0,0,0,0 };

/*
*	Variables to hold the current size of the window.
*/
int winw = ::GetSystemMetrics(SM_CXSCREEN);
int winh = ::GetSystemMetrics(SM_CYSCREEN);

/*----------------------------------------------------------------------------------------
*	Button Stuff
*/

/*
*	We will define a function pointer type. ButtonCallback is a pointer to a function that
*	looks a bit like this :
*
*	void func() {
*	}
*/
typedef void(*ButtonCallback)();
typedef struct Button Button;



/*----------------------------------------------------------------------------------------
*	Calls the continue-method to load the last played game
*/
void Continue()
{
	printf("Continue the game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the method-to save the actual game.
*	Do nothing if no game loaded.
*/
void Save()
{
	printf("Save the game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the method to choose a posible Save-Game and starts a new game.
*/
void New()
{
	printf("New game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the mehtod to choose one of the Save-Games and loads it
*/
void Load()
{
	printf("Load the game\n");
}

/*----------------------------------------------------------------------------------------
*	Calls the method to show the Highscores
*/
void High()
{
	printf("Show the Highscore\n");
}

/*----------------------------------------------------------------------------------------
*	Quits the Game. No save before!
*/
void Exit()
{
	glutDestroyWindow(glutGetWindow());
	exit(0);
}

/*----------------------------------------------------------------------------------------
*	Cancels the action and calls the mainmenu
*/
void BackToMainMenu()
{
	printf("Main Menu");
}

/*
*	Calculates the width of the Button
*/
int calcW() {
	return ((winw / 100) * 10);
}

/*
*	Calculates the hight of the Button
*/
int calcH() {
	return ((winh / 100) * 10);
}

/*
*	Calculates the X-Coord for the Button
*/
int calcX() {
	return ((winw / 2) - (calcW() / 2));
}

/*
*	Calculates the Y-Coord for the Button
*	\param before		-	the y-coord of the button before
*/
int calcY(int before) {
	int basehight = 10;
	return ((winh / 100) * 10) + basehight + before;
}

/*----------------------------------------------------------------------------------------
*	Buttons for the Main-Menu
*/
Button ContinueBtn = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button NewBtn = { calcX(), calcY(ContinueBtn.y), calcW(), calcH(), 0,0, (char*)"New", New };
Button SaveBtn = { calcX(), calcY(NewBtn.y), calcW(), calcH(), 0,0, (char*)"Save", Save };
Button LoadBtn = { calcX(), calcY(SaveBtn.y), calcW(), calcH(), 0,0, (char*)"Load", Load };
Button HighBtn = { calcX(), calcY(LoadBtn.y), calcW(), calcH(), 0,0, (char*)"Highscore", High };
Button ExitBtn = { calcX(), calcY(HighBtn.y), calcW(), calcH(), 0,0, (char*)"Exit", Exit };

/*----------------------------------------------------------------------------------------
*	Buttons for the Save-Menu
*/
Button Save1 = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button Save2 = { calcX(), calcY(Save1.y), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button Save3 = { calcX(), calcY(Save2.y), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button CancelSave = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Cancel", BackToMainMenu };

/*----------------------------------------------------------------------------------------
*	Buttons for the Load-Menu
*/
Button Load1 = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button Load2 = { calcX(), calcY(Load1.y), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button Load3 = { calcX(), calcY(Load2.y), calcW(), calcH(), 0,0, (char*)"Continue", Continue };
Button CancelLoad = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Cancel", BackToMainMenu };

/*----------------------------------------------------------------------------------------
*	Buttons for the Highscore-Menu
*/
Button CancelHighscore = { calcX(), calcY(0), calcW(), calcH(), 0,0, (char*)"Back", BackToMainMenu };


/*----------------------------------------------------------------------------------------
*	\brief	This function draws a text string to the screen using glut bitmap fonts.
*	\param	font	-	the font to use. it can be one of the following :
*					GLUT_BITMAP_9_BY_15
*					GLUT_BITMAP_8_BY_13
*					GLUT_BITMAP_TIMES_ROMAN_10
*					GLUT_BITMAP_TIMES_ROMAN_24
*					GLUT_BITMAP_HELVETICA_10
*					GLUT_BITMAP_HELVETICA_12
*					GLUT_BITMAP_HELVETICA_18
*
*	\param	text	-	the text string to output
*	\param	x		-	the x co-ordinate
*	\param	y		-	the y co-ordinate
*/
void Font(void *font, char *text, int x, int y)
{
	glRasterPos2i(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}


/*----------------------------------------------------------------------------------------
*	\brief	This function is used to see if a mouse click or event is within a button
*			client area.
*	\param	b	-	a pointer to the button to test
*	\param	x	-	the x coord to test
*	\param	y	-	the y-coord to test
*/
int ButtonClickTest(Button* b, int x, int y)
{
	if (b)
	{
		/*
		*	If clicked within button area, then return true
		*/
		if (x > b->x      &&
			x < b->x + b->w &&
			y > b->y      &&
			y < b->y + b->h) {
			return 1;
		}
	}

	/*
	*	otherwise false.
	*/
	return 0;
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonRelease(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	If the mouse button was pressed within the button area
		*	as well as being released on the button.....
		*/
		if (ButtonClickTest(b, x, y))
			//&& ButtonClickTest(b, TheMouse.xpress, TheMouse.ypress))	<-- funktioniert nicht immer
		{
			/*
			*	Then if a callback function has been set, call it.
			*/
			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}

		/*
		*	Set state back to zero.
		*/
		b->state = 0;
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonPress(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	if the mouse click was within the buttons client area,
		*	set the state to true.
		*/
		if (ButtonClickTest(b, x, y))
		{
			b->state = 1;
		}
	}
}


/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void ButtonPassive(Button *b, int x, int y)
{
	if (b)
	{
		/*
		*	if the mouse moved over the control
		*/
		if (ButtonClickTest(b, x, y))
		{
			/*
			*	If the cursor has just arrived over the control, set the highlighted flag
			*	and force a redraw. The screen will not be redrawn again until the mouse
			*	is no longer over this control
			*/
			if (b->highlighted == 0) {
				b->highlighted = 1;
				glutPostRedisplay();
			}
		}
		else

			/*
			*	If the cursor is no longer over the control, then if the control
			*	is highlighted (ie, the mouse has JUST moved off the control) then
			*	we set the highlighting back to false, and force a redraw.
			*/
			if (b->highlighted == 1)
			{
				b->highlighted = 0;
				glutPostRedisplay();
			}
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to draw.
*/
void ButtonDraw(Button *b)
{
	int fontx;
	int fonty;

	if (b)
	{
		/*
		*	We will indicate that the mouse cursor is over the button by changing its
		*	colour.
		*/
		if (b->highlighted)
			glColor3f(0.7f, 0.7f, 0.8f);
		else
			glColor3f(0.6f, 0.6f, 0.6f);

		/*
		*	draw background for the button.
		*/
		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		/*
		*	Draw an outline around the button with width 3
		*/
		glLineWidth(3);

		/*
		*	The colours for the outline are reversed when the button.
		*/
		if (b->state)
			glColor3f(0.4f, 0.4f, 0.4f);
		else
			glColor3f(0.8f, 0.8f, 0.8f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glEnd();

		if (b->state)
			glColor3f(0.8f, 0.8f, 0.8f);
		else
			glColor3f(0.4f, 0.4f, 0.4f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(1);


		/*
		*	Calculate the x and y coords for the text string in order to center it.
		*/
		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char *)b->label)) / 2;
		fonty = b->y + (b->h + 10) / 2;

		/*
		*	if the button is pressed, make it look as though the string has been pushed
		*	down. It's just a visual thing to help with the overall look....
		*/
		if (b->state) {
			fontx += 2;
			fonty += 2;
		}

		/*
		*	If the cursor is currently over the button we offset the text string and draw a shadow
		*/
		if (b->highlighted)
		{
			glColor3f(0, 0, 0);
			Font(GLUT_BITMAP_HELVETICA_12, b->label, fontx, fonty);
			fontx--;
			fonty--;
		}

		glColor3f(1, 1, 1);
		Font(GLUT_BITMAP_HELVETICA_12, b->label, fontx, fonty);
	}
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw the 3D scene
*/
void Draw3D()
{
	gluLookAt(0, 1, 5, 0, 0, 0, 0, 1, 0);
	glutSolidTeapot(1);
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw an overlay over the 3D scene.
*	This will be used to draw our fonts, buttons etc......
*/
void Draw2D()
{
	ButtonDraw(&ContinueBtn);
	ButtonDraw(&NewBtn);
	ButtonDraw(&SaveBtn);
	ButtonDraw(&LoadBtn);
	ButtonDraw(&HighBtn);
	ButtonDraw(&ExitBtn);
}

/*----------------------------------------------------------------------------------------
*	This is the main display callback function. It sets up the drawing for
*	The 3D scene first then calls the Draw3D() function. After that it switches to
*	an orthographic projection and calls Draw2D().
*/
void Draw()
{
	/*
	*	Clear the background
	*/
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	/*
	*	Enable lighting and the z-buffer
	*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	/*
	*	Set perspective viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (winh == 0) ? (1) : ((float)winw / winh), 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	*	Draw the 3D elements in the scene
	*/
	//Draw3D();

	/*
	*	Disable depth test and lighting for 2D elements
	*/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	/*
	*	Set the orthographic viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winw, winh, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	*	Draw the 2D overlay
	*/
	Draw2D();

	/*
	*	Bring the back buffer to the front and vice-versa.
	*/
	glutSwapBuffers();
}


/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever a mouse button is pressed or released
*	\param	button	-	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
*	\param	state	-	GLUT_UP or GLUT_DOWN depending on whether the mouse was released
*						or pressed respectivly.
*	\param	x		-	the x-coord of the mouse cursor.
*	\param	y		-	the y-coord of the mouse cursor.
*/
void MouseButton(int button, int state, int x, int y)
{
	if (openMenu) {
		/*
		*	update the mouse position
		*/
		TheMouse.x = x;
		TheMouse.y = y;

		/*
		*	has the button been pressed or released?
		*/
		if (state == GLUT_DOWN)
		{
			/*
			*	This holds the location of the first mouse click
			*/
			if (!(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb)) {
				TheMouse.xpress = x;
				TheMouse.ypress = y;
			}

			/*
			*	Which button was pressed?
			*/
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				TheMouse.lmb = 1;
				ButtonPress(&ContinueBtn, x, y);
				ButtonPress(&NewBtn, x, y);
				ButtonPress(&SaveBtn, x, y);
				ButtonPress(&LoadBtn, x, y);
				ButtonPress(&HighBtn, x, y);
				ButtonPress(&ExitBtn, x, y);
			case GLUT_MIDDLE_BUTTON:
				TheMouse.mmb = 1;
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rmb = 1;
				break;
			}
		}
		else
		{
			/*
			*	Which button was released?
			*/
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				TheMouse.lmb = 0;
				ButtonRelease(&ContinueBtn, x, y);
				ButtonRelease(&NewBtn, x, y);
				ButtonRelease(&SaveBtn, x, y);
				ButtonRelease(&LoadBtn, x, y);
				ButtonRelease(&HighBtn, x, y);
				ButtonRelease(&ExitBtn, x, y);
				break;
			case GLUT_MIDDLE_BUTTON:
				TheMouse.mmb = 0;
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rmb = 0;
				break;
			}
		}
	}
	
	/*
	*	Force a redraw of the screen. If we later want interactions with the mouse
	*	and the 3D scene, we will need to redraw the changes.
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND A BUTTON IS HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MouseMotion(int x, int y)
{
	/*
	*	Calculate how much the mouse actually moved
	*/
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	/*
	*	update the mouse position
	*/
	TheMouse.x = x;
	TheMouse.y = y;


	/*
	*	Check MyButton to see if we should highlight it cos the mouse is over it
	*/
	ButtonPassive(&ContinueBtn, x, y);
	ButtonPassive(&NewBtn, x, y);
	ButtonPassive(&SaveBtn, x, y);
	ButtonPassive(&LoadBtn, x, y);
	ButtonPassive(&HighBtn, x, y);
	ButtonPassive(&ExitBtn, x, y);

	/*
	*	Force a redraw of the screen
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND NO BUTTONS ARE HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MousePassiveMotion(int x, int y)
{
	/*
	*	Calculate how much the mouse actually moved
	*/
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	/*
	*	update the mouse position
	*/
	TheMouse.x = x;
	TheMouse.y = y;

	/*
	*	Check MyButton to see if we should highlight it cos the mouse is over it
	*/
	ButtonPassive(&ContinueBtn, x, y);
	ButtonPassive(&NewBtn, x, y);
	ButtonPassive(&SaveBtn, x, y);
	ButtonPassive(&LoadBtn, x, y);
	ButtonPassive(&HighBtn, x, y);
	ButtonPassive(&ExitBtn, x, y);

	/*
	*	Note that I'm not using a glutPostRedisplay() call here. The passive motion function
	*	is called at a very high frequency. We really don't want much processing to occur here.
	*	Redrawing the screen every time the mouse moves is a bit excessive. Later on we
	*	will look at a way to solve this problem and force a redraw only when needed.
	*/
}

/*----------------------------------------------------------------------------------------
*
*/
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
	glutSwapBuffers();
}

void closeMenu() {
	openMenu = false;
	glewInit();
	glutDisplayFunc(renderScene);
	glutPostRedisplay();
}

void callMenu() {
	openMenu = true;
	glutDisplayFunc(Draw);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
}








