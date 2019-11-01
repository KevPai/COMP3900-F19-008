#pragma once
class TankAI
{
private:
	bool isPlayer = false;
	float x, z;

public:
	TankAI() {}
	TankAI(bool status);
	void move(float x, float z);

};

