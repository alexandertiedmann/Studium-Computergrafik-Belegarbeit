#include "Menu.hpp"

//get Screen Resolution
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

bool menuOpen = getMenuOpen();
bool labyOpen = false;

/*----------------------------------------------------------------------------------------
*	\brief	This function is called to initialise opengl.
*/
void Init(){
	glEnable(GL_LIGHT0);
}

void getOpenLabyrinth() {
	labyOpen = getLabbyOpen();
}

void keys(unsigned char key, int xmouse, int ymouse) {
	getOpenLabyrinth();
	Labyrinth lab = getLabyrinth();

	if (labyOpen) {
		switch (key) {
		case 27:
			cout << "esc Key was pressed" << endl;
			setMenuOpen(callMainMenu());
			break;
		case 'w':
			cout << "w Key was pressed" << endl;
			lab.movePlayer('w');
			setLabyrinth(lab);
			break;
		case 'a':
			cout << "a Key was pressed" << endl;
			lab.movePlayer('a');
			setLabyrinth(lab);
			break;
		case 'd':
			cout << "d Key was pressed" << endl;
			lab.movePlayer('d');
			setLabyrinth(lab);
			break;
		default:
			break;
		}
	}	
	else {
		if (!getFirstStart()) {
			switch (key) {
			case 27:
				setMenuOpen(closeMainMenu());
				break;
			default:
				break;
			}
			
		}
		
	}
}
 
int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_BORDERLESS | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(nScreenWidth, nScreenHeight);
	glutCreateWindow("CG-Labyrinth");

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);

	glutKeyboardFunc(keys);

	menuOpen = true;
	setMenuOpen(callMainMenu());

	glutMainLoop();
	
	return 0;
}