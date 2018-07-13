#include "Labyrinth.hpp"
#include "glm.hpp"
#include <string>
#include "matrix_transform.hpp"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "objects.hpp"
using namespace std;
using namespace glm;



	


	Labyrinth::Labyrinth(string walls[]) {

		drawLabyrinth(walls);
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
	void Labyrinth::drawLabyrinth(string walls[]) 
	{
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Nicht aendern
		View = glm::lookAt(glm::vec3(0, 0, -5), // wo der Spieler steht    
			glm::vec3(0, 0, 0),  // Wo der Spieler hinguckt
			glm::vec3(0, 1, 0)); // so lassen
		// View eventuell aendern, um zu testen, um das Labyrinth anzuschauen
		Model = glm::mat4(1.0f);
		
		
		double xpos = 0.0;
		double zpos = 0.0;
		 
		int rootArray = std::sqrt(sizeof(walls)); // Die Laenge des Arrays, da das Labyrinth quadratisch ist, Wurzel ziehen
		//Boden
		glm::mat4 DefaultModel = Model;

		if (rootArray % 2 == 0) // gerade Laenge
		{
			Model = glm::translate(Model, glm::vec3(rootArray / 2 + 0.5, -0.6, -rootArray / 2 + 0.5)); // Auf die Mitte des Labyrinths setzen und knapp drunter, y-Wert eventuell anpassen
		}
		else Model = glm::translate(Model, glm::vec3(rootArray / 2, -0.6, -rootArray / 2)); // Ungerade Laenge
		
		Model = glm::scale(Model, glm::vec3(rootArray, 0.1, rootArray)); // skalieren, um genauso groﬂ wie das Labyrinth zu sein	
		sendMVP();
		drawCube(); // erst sendMVP, dann drawCube

		// Default zuruecksetzen
		Model = DefaultModel;


		for (int i = 0; i < sizeof(walls); i++) {
			if (i + 1 % rootArray == 0) { 
				zpos++;
				xpos = 0;
			}
			if (walls[i] == "X") {
				Model = glm::translate(Model, glm::vec3(xpos, 0.0, zpos)); // translate Koordinaten sind abhaengig von den Koordinaten des Models, es findet eine Addition statt...
				sendMVP();
				drawCube();
				//... Daher muss wieder auf das Default-Model gesetzt, damit Model wieder auf dem Ursprung sitzt
				Model = DefaultModel;
			}
			if (walls[i] == "S") {
				// Spieler platzieren
				View = glm::lookAt(glm::vec3(xpos, 0, zpos), // Spieler steht da, wo das "S" auch ist
					glm::vec3(xpos,0,zpos-1), // Blickrichtung abh‰ngig vom Standort
					glm::vec3(0, 1, 0)); 
			}
			xpos++;
			
		}
	}
	// Leons Teil
	void Labyrinth::movePlayer() {

	}

	



