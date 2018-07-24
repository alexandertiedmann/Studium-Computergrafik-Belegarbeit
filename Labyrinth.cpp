#include "Labyrinth.hpp"
#include "dummy.hpp"
#include <Windows.h>
#include <math.h>
#include <stdlib.h>




Labyrinth* lab;


Labyrinth::Labyrinth(ActualLevel al, ActualGame ag) {
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
void Labyrinth::loadLabyrinth(){

	// Hier werden die Indizes gesucht, auf denen sich das "s" im Vektor befindet, damit die Kamera-Variablen gesetzt werden koennen.
	// Die Kamera-Variablen werden dann der View uebergeben und so laesst sich die View dynamisch aendern
	if (level.getLevel()[game.yCoord][game.xCoord] == 'X') {
		int i = 0;
		int j = 0;
		for (const auto& inner : level.getLevel()) {
			for (const auto& position : inner) {

				if (position == 's') {
					cameraPos = glm::vec3(i, 0, j);
					cameraFront = glm::vec3(i, 0, j - 1);
					cameraUp = glm::vec3(0, 1, 0);
					cout << "Spieler bei " << j << " " << i << endl; // Spieler bei 4 1
					cout << "Level: " << game.level << endl;
					game.xCoord = i;
					game.yCoord = j;
					game.level;
					// View setzen je nach Startposition
					// View setzen je nach Startposition
					if (level.getLevel()[game.yCoord - 1][game.xCoord] == '0') {
						game.view = 1;
					}
					else if (level.getLevel()[game.yCoord][game.xCoord + 1] == '0') {
						game.view = 2;
						cameraFront += glm::vec3(1, 0, 1);
					}
					else if (level.getLevel()[game.yCoord + 1][game.xCoord] == '0') {
						game.view = 3;
						cameraFront += glm::vec3(0, 0, 2);
					}
					else if (level.getLevel()[game.yCoord][game.xCoord - 1] == '0') {
						game.view = 4;
						cameraFront += glm::vec3(-1, 0, 1);
					}

				}
				i++;
			}
			j++;
			i = 0;
		}
	}
	else if (level.getLevel()[game.yCoord][game.xCoord] == '0'){ // save wird geladen

		cout << "xcoord: " << game.xCoord << endl;
		cout << "ycoord: " << game.yCoord << endl;
		cameraPos.x = game.xCoord; 
		cameraPos.z = game.yCoord; 
		cameraUp = glm::vec3(0, 1, 0);
		cameraFront = glm::vec3(game.xCoord, 0, game.yCoord - 1);
		switch (game.view) {
			//case 1: cameraFront = glm::vec3(game.xCoord, 0, game.yCoord - 1);
			case 2: cameraFront += glm::vec3(1, 0, 1);
			case 3: cameraFront += glm::vec3(0, 0, 2);
			case 4: cameraFront += glm::vec3(-1, 0, 1);
		}
	}
	

	cout << "Labby" << endl;
 
	bool isGameFinished = false;


	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
	// Shader laden
	programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");

    // Shader benutzen
	glUseProgram(programID);

	
}

void Labyrinth::movePlayer(char keyPressed) {
	//cout << "Pos.: " << cameraPos.x << " " << cameraPos.z << "Cam.:" << cameraFront.y << " " << cameraFront.z << endl;
	// Drehmatrizen jeweils für Drehung um 1 Grad
	transformMatrixLeft = glm::mat3{ glm::vec3(0.9998476952f, 0.0f, 0.01745240644f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(-0.01745240644f, 0.0f, 0.9998476952f) };

	transformMatrixRight = glm::mat3{ glm::vec3(0.9998476952f, 0.0f, -0.01745240644f),
									glm::vec3(0.0f, 1.0f, 0.0f),
									glm::vec3(0.01745240644f, 0.0f, 0.9998476952f) };

	// Nach vorne laufen ("w")

	

	if (keyPressed == 'w') {
		if (game.view == 1) {
			if (level.getLevel()[game.yCoord-1][game.xCoord] == '0' || level.getLevel()[game.yCoord - 1][game.xCoord] == 's' || level.getLevel()[game.yCoord - 1][game.xCoord] == 'z') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0], 0, cameraPos[2] - 1);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);			
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 2) {
			if (level.getLevel()[game.yCoord][game.xCoord + 1] == '0' || level.getLevel()[game.yCoord][game.xCoord + 1] == 's' || level.getLevel()[game.yCoord][game.xCoord + 1] == 'z') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0] + 1, 0, cameraPos[2]);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 3) {
			if (level.getLevel()[game.yCoord + 1][game.xCoord] == '0' || level.getLevel()[game.yCoord +1][game.xCoord] == 's' || level.getLevel()[game.yCoord +1][game.xCoord] == 'z') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0], 0, cameraPos[2] + 1);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}
		else if (game.view == 4) {
			if (level.getLevel()[game.yCoord][game.xCoord - 1] == '0' || level.getLevel()[game.yCoord][game.xCoord - 1] == 's' || level.getLevel()[game.yCoord][game.xCoord - 1] == 'z') {
				cameraPos = cameraFront;
				cameraFront = glm::vec3(cameraPos[0] - 1, 0, cameraPos[2]);
				View = glm::lookAt(cameraPos, cameraFront, cameraUp);
				game.xCoord = cameraPos[0];
				game.yCoord = cameraPos[2];
			}
		}

		if (level.getLevel()[game.yCoord][game.xCoord] == 'z') {
			game.xCoord = 0;
			game.yCoord = 0;
			playerFinished = true;
		}
	}

	// Nach rechts drehen ("d")
	if (keyPressed == 'd') {
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

	// Nach links drehen ("a")
	if (keyPressed == 'a') {
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

	//cout << "Pos.: " << cameraPos.x << " " << cameraPos.z << "Cam.:" << cameraFront.y << " " << cameraFront.z << endl;
}
/*
*	\brief return the ActualGame
*/
ActualGame Labyrinth::getActualGame() {
	return game;
}
void Labyrinth::setActualGame(ActualGame g) {
	game = g;
}

/*
*	\brief return the ActualLevel
*/
ActualLevel Labyrinth::getActualLevel() {
	return level;
}
void Labyrinth::setActualLevel(ActualLevel l) {
	level = l;
}


//Experiment
bool Labyrinth::isPlayerFinished()
{
	if (level.getLevel()[cameraPos.z][cameraPos.x] == 'z') {
		return true;
	}
	else return false;

}

