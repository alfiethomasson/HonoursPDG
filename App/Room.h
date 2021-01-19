#pragma once

class Room {
protected:
	int xSize;
	int ySize;
public:
	Room(int x, int y) { xSize = x; ySize = y; };
	virtual ~Room() = default;

	virtual void Update();
	//virtual void Render() {};
	//virtual void Load();

};