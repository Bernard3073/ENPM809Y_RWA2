#include <iostream>
#include <array>
#include "../include/mouse/mouse.h"
#include "../include/api/api.h"

// void log(const std::string& text) {
//     std::cerr << text << std::endl;
// }

int main() {
	/*
	initialize
	1. the maze
	2. boundary walls
	3. position of the mouse
	4. direction of the mouse
	*/
	rwa2::Mouse mouse;
	mouse.display_walls();
	while(1){
		// clear the color for all tiles
		API::clearAllColor();
		// set color and text for goal cell
		API::setColor(7, 7, 'G');
		API::setText(7, 7, "G1");
		// set mouse's goal position
		mouse.set_goal(7, 7);
		// get mouse's current position
		int m_x = std::get<0>(mouse.get_cur_status());
		int m_y = std::get<1>(mouse.get_cur_status());
		// update maze walls in the program
		// update maze walls in the simulator
		// mouse.update_maze_info();
		
		// generate a path from current position to goal
		std::stack<std::tuple<int, int, int>> st;
		std::vector<std::pair<int, int>> visited_node;
		
		if(mouse.search_maze(m_x, m_y, st, visited_node)){
			std::stack<std::tuple<int, int, int>> path;
			
			while(!st.empty()){
				path.push(st.top());
				st.pop();
			}
			// move the robot along the path
			while(!path.empty()){
				int move_command = std::get<2>(path.top());
				path.pop();
				switch(move_command){
					case 0: {
						int m_x = std::get<0>(mouse.get_cur_status());
						int m_y = std::get<1>(mouse.get_cur_status());
						std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
						// color path tiles in the simulator
						API::setColor(m_x, m_y, 'r');
						mouse.update_maze_info(m_x, m_y);
						mouse.move_forward(); 
						break;
					}
					case 1: mouse.turn_right(); break;
					case 2: mouse.move_forward(); break;
					case 3: mouse.turn_left(); break;
				}
				
			} 
		}
		else{
			std::cerr << "Path not found !!!" << '\n';
		}
	}

}

