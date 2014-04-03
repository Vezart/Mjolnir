#pragma once

class Sentinel {
    public:
		enum Direction { Up, Down, Left, Right };
		Sentinel();
		void update();
		void drawSentinel();
		Direction direction;
    private:
		//Image up;
		//Image down;
		//Image left;
		//Image right;
};
