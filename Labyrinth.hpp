class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	GLuint programID;
	ActualLevel level;
	ActualGame game;
	


public:
	Labyrinth(ActualLevel al, ActualGame ag);
	

	void sendMVP();

	void loadLabyrinth(ActualLevel al);
	
	void movePlayer();

	


};