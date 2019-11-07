#include "Cube.h"

void checkCollision(Cube player, Cube toTest) {
	
	if (player.getX() - toTest.getX() >= -1.0f) {
		std::cout << "collided from the left" << std::endl;
	}
	else if (player.getX() - toTest.getX() <= -1.0f) {
		std::cout << "collided from the right" << std::endl;
	}	
}