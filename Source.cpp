//Components
struct Position {
	float x;
	float y;
	float z;
};

struct Velocity {

};

struct Model {

};

struct Texture {

};

struct Rotation {

};

struct Collider {};

//Entities
struct Tank {
	Position pos;
	Velocity vel;
	Rotation rot;
	Model mod;
	Texture text;
};

struct Bullet {
	Velocity speed;
	Position startpos;
};

struct Wall {
	//Mesh mesh;
	Position pos;
	//Direction dir;
};

struct Player {
	Tank tank;
};



