#include "Labyrinth.hpp"
#include "dummy.hpp"
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
Labyrinth::Labyrinth(ActualLevel al, ActualGame ag) : level(al), game(ag)
{
	level = al;
	game = ag;
}


Labyrinth::Labyrinth() { }

void Labyrinth::sendMVP()
{

	glm::mat4 MVP = Projection * View * Model;

	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);


	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);//Ergaenzt den oberen Befehl
}


/*
Erstellt das Labyrinth abhaengig von dem uebergebenen Array
*/
void Labyrinth::loadLabyrinth()
{
	// Hier werden die Indizes gesucht, auf denen sich das "s" im Vektor befindet, damit die Kamera-Variablen gesetzt werden koennen.
	// Die Kamera-Variablen werden dann der View uebergeben und so laesst sich die View dynamisch aendern
	int i = 0;
	int j = 0;
	for (const auto& inner : level.getLevel()) {
		for (const auto& position : inner) {
			
			if (position == 's') {
				cameraPos = glm::vec3(i, 0, j);
				cameraFront = glm::vec3(i, 0, j - 1);
				cameraUp = glm::vec3(0, 1, 0);
				cout << "Spieler bei " << j << " " << i << endl;
				game.xCoord = i;
				game.yCoord = j;
				game.view = 1;
				
			}
			i++;
		}
		j++;
		i = 0;
	}
	


		cout << "Labby" << endl;
	double xpos = 0.0;
	double zpos = 0.0;
	bool isGameFinished = false;


	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
	// Shader laden
	programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    // Shader benutzen
	glUseProgram(programID);

	while (!isGameFinished) // ToDo: Variable noch aendern, wenn Ziel erreicht
	{
		// Diese Schleife wird jetzt solange ausgefuehrt, bis der Spieler das Ziel erreicht hat
		// In der Schleife muessen immer und immer wieder alle Objekte im Labyrinth erstellt und texturiert werden
		// Auch muss die Bewegung des Spielers hier durchgefuehrt werden
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			cout << "Fehler" << endl;
		}

		glutMotionFunc(MouseMotionFunc);
		glutPassiveMotionFunc(MousePassiveMotionFunc);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Nicht aendern

		View = glm::lookAt(cameraPos, // Spieler steht da, wo das "S" auch ist
			cameraFront, // Blickrichtung abh�ngig vom Standort
			cameraUp);
										  // View eventuell aendern, um zu testen, um das Labyrinth anzuschauen
		Model = glm::mat4(1.0f);

		drawCube();
		sendMVP();

		//Boden
		glm::mat4 DefaultModel = Model;

		if (level.getLevelHeight() % 2 == 0) // gerade Laenge
		{
			Model = glm::translate(Model, glm::vec3(level.getLevelWidth() / 2 + 0.5, -0.6, level.getLevelHeight() / 2 + 0.5)); // Auf die Mitte des Labyrinths setzen und knapp drunter, y-Wert eventuell anpassen
		}
		else Model = glm::translate(Model, glm::vec3(level.getLevelWidth() / 2, -0.6, level.getLevelHeight() / 2)); // Ungerade Laenge

		Model = glm::scale(Model, glm::vec3(level.getLevelWidth(), 0.1, level.getLevelHeight())); // skalieren, um genauso gro� wie das Labyrinth zu sein	
		sendMVP();
		drawCube(); // erst sendMVP, dann drawCube

		// Default zuruecksetzen
		Model = DefaultModel;
		double xpos = 0.0;
		double zpos = 0.0;

		for (const auto& inner : level.getLevel()) {
			for (const auto& position : inner) {

				if (position == 'X') { // Wand zeichnen
					//cout << "Wand wird gezeichnet bei " << xpos << " " << zpos << endl;
					Model = glm::translate(Model, glm::vec3(xpos, 0.0, zpos)); // translate Koordinaten sind abhaengig von den Koordinaten des Models, es findet eine Addition statt...
					Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
					sendMVP();
					drawCube();
					//... Daher muss wieder auf das Default-Model gesetzt, damit Model wieder auf dem Ursprung sitzt
					Model = DefaultModel;
				}
				
				xpos++;
			}
			zpos++;
			xpos = 0;
		}

		glutSwapBuffers();
		glutPostRedisplay();
	}



}
// Leons Teil
void Labyrinth::movePlayer(ActualLevel al, char keyPressed) {

	// Drehmatrizen jeweils f�r Drehung um 1 Grad
	transformMatrixLeft = glm::mat3{ glm::vec3(0.9998476952f, 0.0f, 0.01745240644f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(-0.01745240644f, 0.0f, 0.9998476952f) };

	transformMatrixRight = glm::mat3{ glm::vec3(0.9998476952f, 0.0f, -0.01745240644f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.01745240644f, 0.0f, 0.9998476952f) };

	// Nach vorne laufen ("w")
	if (keyPressed == (char)"w") {
		if (game.view == 1) {
			if (level.getLevel()[game.yCoord-1][game.xCoord] == '0') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0], 0, cameraPos[2] - 1);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 2) {
			if (level.getLevel()[game.yCoord][game.xCoord + 1] == '0') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0] + 1, 0, cameraPos[2]);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 3) {
			if (level.getLevel()[game.yCoord + 1][game.xCoord] == '0') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0], 0, cameraPos[2] + 1);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 4) {
			if (level.getLevel()[game.yCoord][game.xCoord - 1] == '0') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0] - 1, 0, cameraPos[2]);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		
	}

	// Nach links drehen ("a")
	if (keyPressed == (char)"a") {
		if (game.view == 1) {
			cameraFront += glm::vec3(1, 0, 1);
			game.view = 2;
		}
		else if (game.view == 2) {
			cameraFront += glm::vec3(-1, 0, 1);
			game.view = 3;
		} 
		else if (game.view == 3) {
			cameraFront += glm::vec3(-1, 0, -1);
			game.view = 4;
		}
		else if (game.view == 4) {
			cameraFront += glm::vec3(1, 0, -1);
			game.view = 1;
		}
	}

	// Nach rechts drehen ("d")
	if (keyPressed == (char)"d") {
		if (game.view == 1) {
			cameraFront += glm::vec3(-1, 0, 1);
			game.view = 4;
		}
		else if (game.view == 4) {
			cameraFront += glm::vec3(1, 0, 1);
			game.view = 3;
		}
		else if (game.view == 3) {
			cameraFront += glm::vec3(1, 0, -1);
			game.view = 2;
		}
		else if (game.view == 2) {
			cameraFront += glm::vec3(-1, 0, -1);
			game.view = 1;
		}
	}
}
/*
*	\brief return the ActualGame
*/
ActualGame Labyrinth::getActualGame() {
	return game;
}
//Experiment
bool Labyrinth::isPlayerFinished()
{
	if (level.getLevel()[cameraPos.x][cameraPos.z] == 'z') {
		return true;
	}
	else return false;

}





