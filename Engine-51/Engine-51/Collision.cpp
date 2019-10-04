#include "Collision.h"

int checkCollision(Cube player, Cube toTest, int direction) {
	if (direction == 5 || direction == 0) {
		if (player.getY() - toTest.getY() < 1.0f &&
			player.getY() - toTest.getY() > 0.0f) {
			if (abs(player.getX() - toTest.getX()) < 1.0f &&
				abs(player.getZ() - toTest.getZ()) < 1.0f)
				return 2;
		}
		else if (player.getY() - toTest.getY() > -1.0f &&
			player.getY() - toTest.getY() < 0.0f) {
			if (abs(player.getX() - toTest.getX()) < 1.0f &&
				abs(player.getZ() - toTest.getZ()) < 1.0f)
				return -2;
		}
	}
	else if (direction == 4 || direction == 6) {
		if (player.getX() - toTest.getX() > -1.0f &&
			player.getX() - toTest.getX() < 0.0f) {
			if (abs(player.getY() - toTest.getY()) < 1.0f &&
				abs(player.getZ() - toTest.getZ()) < 1.0f)
				return -1;
		}
		else if (player.getX() - toTest.getX() < 1.0f &&
			player.getX() - toTest.getX() > 0.0f) {
			if (abs(player.getY() - toTest.getY()) < 1.0f &&
				abs(player.getZ() - toTest.getZ()) < 1.0f)
				return 1;
		}
	}
	else if (direction == 8 || direction == 2) {
		if (player.getZ() - toTest.getZ() < 1.0f &&
			player.getZ() - toTest.getZ() > 0.0f) {
			if (abs(player.getX() - toTest.getX()) < 1.0f &&
				abs(player.getY() - toTest.getY()) < 1.0f)
				return 3;
		}
		else if (player.getZ() - toTest.getZ() > -1.0f &&
			player.getZ() - toTest.getZ() < 0.0f) {
			if (abs(player.getX() - toTest.getX()) < 1.0f &&
				abs(player.getY() - toTest.getY()) < 1.0f)
				return -3;
		}
	}
	else {
		return 0;
	}
}
