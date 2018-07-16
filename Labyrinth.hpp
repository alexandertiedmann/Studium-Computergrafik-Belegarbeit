class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	glm::vec3 cameraPos; // Camera Position
	glm::vec3 cameraFront; // Camera Direction
	glm::vec3 cameraUp;
	GLuint programID;
	ActualLevel level;
	ActualGame game;
	


public:
	Labyrinth(ActualLevel al, ActualGame ag);
	

	void sendMVP();

	void loadLabyrinth();
	
	void movePlayer(ActualLevel al, char keyPressed);

	bool isPlayerFinished();


};