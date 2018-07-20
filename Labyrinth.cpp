#include "Labyrinth.hpp"

Labyrinth::Labyrinth(ActualLevel al, ActualGame ag) : level(al), game(ag)
{
	level = al;
	game = ag;
}

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


	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Nicht aendern
	View = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), // wo der Spieler steht    
		glm::vec3(0.0f, 0.0f, 0.0f),  // Wo der Spieler hinguckt
		glm::vec3(0.0f, 1.0f, 0.0f)); // so lassen
	// View eventuell aendern, um zu testen, um das Labyrinth anzuschauen
	Model = glm::mat4(1.0f);


	double xpos = 0.0;
	double zpos = 0.0;


	//Boden
	glm::mat4 DefaultModel = Model;

	if (level.getLevelHeight % 2 == 0) // gerade Laenge
	{
		Model = glm::translate(Model, glm::vec3(level.getLevelWidth / 2 + 0.5, -0.6, level.getLevelHeight / 2 + 0.5)); // Auf die Mitte des Labyrinths setzen und knapp drunter, y-Wert eventuell anpassen
	}
	else Model = glm::translate(Model, glm::vec3(level.getLevelWidth / 2, -0.6, level.getLevelHeight / 2)); // Ungerade Laenge

	Model = glm::scale(Model, glm::vec3(level.getLevelWidth, 0.1, level.getLevelHeight)); // skalieren, um genauso groﬂ wie das Labyrinth zu sein	
	sendMVP();
	drawCube(); // erst sendMVP, dann drawCube

	// Default zuruecksetzen
	Model = DefaultModel;


	for (const auto& inner : level.getLevel) {
		for (const auto& position : inner) {
			if (position == "X") { // Wand zeichnen
				Model = glm::translate(Model, glm::vec3(xpos, 0.0, zpos)); // translate Koordinaten sind abhaengig von den Koordinaten des Models, es findet eine Addition statt...
				sendMVP();
				drawCube();
				//... Daher muss wieder auf das Default-Model gesetzt, damit Model wieder auf dem Ursprung sitzt
				Model = DefaultModel;
			}
			if (position == "S") {
				// Spieler platzieren
				cameraPos = glm::vec3(xpos, 0, zpos);
				cameraFront = glm::vec3(xpos, 0, zpos - 1);
				cameraUp = glm::vec3(0, 1, 0);
				View = glm::lookAt(cameraPos, // Spieler steht da, wo das "S" auch ist
					cameraFront, // Blickrichtung abh‰ngig vom Standort
					cameraUp);
			}
			xpos++;
		}
		zpos++;
		xpos = 0;
	}
}
// Leons Teil
void Labyrinth::movePlayer(ActualLevel al, char keyPressed) {

	// Nach vorne laufen ("w")
	if (keyPressed == (char)"w") {
		if (al.getLevel[cameraFront[2]][cameraFront[0]] == "0") {
			cameraPos = cameraPos + cameraFront;
			View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
	}

	// Nach links drehen ("a")
	if (keyPressed == (char)"a") {
		//nach links drehen
	}

	// Nach rechts drehen ("d")
	if (keyPressed == (char)"a") {
		//nach rechts drehen
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
	if (level.getLevel[cameraPos.x][cameraPos.z] == "Z") {
		return true;
	}
	else return false;

}





