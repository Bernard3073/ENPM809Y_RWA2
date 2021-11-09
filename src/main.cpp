#include <iostream>
#include <array>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"

int main() {
	/*
	initialize
	1. the maze
	2. boundary walls
	3. position of the mouse
	4. direction of the mouse
	*/
	rwa2::Mouse mouse;
	while(1){
		// clear the color for all tiles
		API::clearAllColor();
		// set color and text for goal cell
		API::setColor(7, 7, 'G');
		API::setText(7, 7, "G1");
		// set mouse's goal position
		mouse.set_goal(7, 7);
		// get mouse's current position
		// update maze walls in the program
		// update maze walls in the simulator
		// mouse.display_walls();
		// no path found: maze unsolvable
		if(!mouse.search_maze()){
			std::cout << "Maze unsolvable !!!!" << '\n';
			break;
		}
		// generate a path from current position to goal
		else{
			std::stack<std::pair<int, int>> st;
			std::stack<std::pair<int, int>> path;
			// color path tiles in the simulator
			while(!st.empty()){
				path.push(st.top());
				st.pop();
			}
			// move the robot along the path 
		}
	}

}

