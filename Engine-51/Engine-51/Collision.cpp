#include "Collision.h"

int checkCollision(Cube player, Cube toTest, int direction) {
	if (direction == 5 || direction == 0) {
		if (boundary(player.getX() - toTest.getX(), 
					(player.getZ() - toTest.getZ()))) {
			if (between(player.getY() - toTest.getY(), 0.0f, 1.0f)) {
				return 2;
			} else if (between(player.getY() - toTest.getY(), -1.0f, 0.0f)) {
				return -2;
			}
		}
	} else if (direction == 4 || direction == 6) {		
		if (boundary(player.getY() - toTest.getY(),
					(player.getZ() - toTest.getZ()))) {
			if (between(player.getX() - toTest.getX(), -1.0f, 0.0f)) {
				return -1;
			} else if (between(player.getX() - toTest.getX(), 0.0f, 1.0f)) {
				return 1;
			}
		}
	} else if (direction == 8 || direction == 2) {
		if (boundary(player.getX() - toTest.getX(), 
					(player.getY() - toTest.getY()))) {
			if (between(player.getZ() - toTest.getZ(), 0.0f, 0.1f)) {
				return 3;
			} else if (between(player.getZ() - toTest.getZ(), -1.0f, 0.0f)) {
				return -3;
			}
		}						
	} else {
		return 0;
	}
}

bool boundary(float d1, float d2) {
	return abs(d1) < 1.0f && abs(d2) < 1.0f;
}
bool between(float curCoord, float min, float max) {
	return curCoord > min && curCoord < max;
}