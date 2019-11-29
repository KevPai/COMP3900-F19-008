#pragma once

class GridCell {
private:

	int realX;
	int realZ;
	int status = 1; // status initially set to 1 marking a "free" cell

public:

	GridCell() {
		realX = 0;
		realZ = 0;
	}
	~GridCell() {};

	// for testing purposes
	friend std::ostream& operator << (std::ostream& os, const GridCell& gc) {
		os << "" << gc.getRealX() << "," << gc.getRealZ() << "";
		return os;
	}
	
	void setRealX(int x) { realX = x; }
	void setRealZ(int z) { realZ = z; }
	int getRealX() const { return realX; }
	int getRealZ() const { return realZ; }

	void setStatus(int status) { this->status = status; }
	int getStatus() const { return status; }

};