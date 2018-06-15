#include "MenuButton.h"

/*
* default contruktur
*
MenuButton::MenuButton() {
	ButtonCallback exitButton;
	x = nScreenWidth / 2;
	y = ((nScreenWidth / 100) * 5) + 10;
	w = (nScreenWidth / 100) * 5;
	h = (nScreenHeight / 100) * 5;
	state = 0;
	highlighted = 0;
	label = (char*)"Fehler";
	callbackFunction = exitButton;
}*/

/*
*	Construktor for MenuButton
*/
MenuButton::MenuButton(int baseheigt, char* buttonName, int before, ButtonCallback buttonClickFunction) {
	x = nScreenWidth / 2;
	y = ((nScreenWidth / 100) * 5) + baseheigt + before;
	w = (nScreenWidth / 100) * 5;
	h = (nScreenHeight / 100) * 5;
	state = 0;
	highlighted = 0;
	label = buttonName;
	callbackFunction = buttonClickFunction;
}

MenuButton MenuButton::operator=(const MenuButton &rhs) {
	// destroy m_items
	// alloc m_items
	// copy from rhs
	return *this;
}%

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

	/*----------------------------------------------------------------------------------------
	*	\brief	This function draws a text string to the screen using glut bitmap fonts.
	*	\param	font	-	the font to use. it can be one of the following :
	*
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
	void MenuButton::Font(void *font, char *text, int x, int y) {
		glRasterPos2i(x, y);

		while (*text != '\0') {
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
	int MenuButton::ButtonClickTest(int x, int y) {
		MenuButton *b = this;
		if (b) {
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
	*	\param xpress	-	the 
	*/
	void MenuButton::ButtonRelease(int x, int y, int xpress, int ypress) {
		MenuButton *b = this;
		if (b) {
			/*
			*	If the mouse button was pressed within the button area
			*	as well as being released on the button.....
			*/
			if (ButtonClickTest(xpress, ypress) &&
				ButtonClickTest(x, y)) {
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
	void MenuButton::ButtonPress(int x, int y) {
		MenuButton *b = this;
		if (b) {
			/*
			*	if the mouse click was within the buttons client area,
			*	set the state to true.
			*/
			if (ButtonClickTest(x, y)) {
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
	void MenuButton::ButtonPassive(int x, int y) {
		MenuButton *b = this;
		if (b) {
			/*
			*	if the mouse moved over the control
			*/
			if (ButtonClickTest(x, y)) {
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
				if (b->highlighted == 1) {
					b->highlighted = 0;
					glutPostRedisplay();
				}
		}
	}

	/*----------------------------------------------------------------------------------------
	*	\brief	This function draws the specified button.
	*	\param	b	-	a pointer to the button to draw.
	*/
	void MenuButton::ButtonDraw() {
		MenuButton *b = this;
		int fontx;
		int fonty;

		if (b) {
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
			fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10, (const unsigned char *)b->label)) / 2;
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
			if (b->highlighted) {
				glColor3f(0, 0, 0);
				Font(GLUT_BITMAP_HELVETICA_10, b->label, fontx, fonty);
				fontx--;
				fonty--;
			}

			glColor3f(1, 1, 1);
			Font(GLUT_BITMAP_HELVETICA_10, b->label, fontx, fonty);
		}
	}