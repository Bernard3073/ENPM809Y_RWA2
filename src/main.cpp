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
	// mouse.display_walls();
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
		int m_d = std::get<2>(mouse.get_cur_status());
		std::cerr << "Start Searching !!!" << '\n';
		// std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
		// update maze walls in the program
		// update maze walls in the simulator
		mouse.check_wall();
		// generate a path from current position to goal
		std::stack<std::pair<int, int>> st;
		std::vector<std::pair<int, int>> visited_node;
		if(mouse.search_maze(m_x, m_y, st, visited_node)){
			std::stack<std::pair<int, int>> path;
			if(m_x == mouse.get_goal().first && m_y == mouse.get_goal().second) break;
			while(!st.empty()){
				path.push(st.top());
				st.pop();
			}
			// move the robot along the path
			while(!path.empty()){
				// std::cerr << "Start moving !!!" << '\n';
				m_x = std::get<0>(mouse.get_cur_status());
				m_y = std::get<1>(mouse.get_cur_status());
				m_d = std::get<2>(mouse.get_cur_status());
				int new_x = path.top().first - m_x;
				int new_y = path.top().second - m_y;
				int dir;
				// moving north
				if(new_x == 0 && new_y == 1){
					dir = 0;
					std::cerr << "Move North !!!" << '\n';
					mouse.mouse_run(direction::NORTH);
				}
				// moving east
				else if(new_x == 1 && new_y == 0){
					// mouse.turn_right();
					dir = 1;
					std::cerr << "Move East !!!" << '\n';
					mouse.mouse_run(direction::EAST);
				}
				// moving south
				else if(new_x == 0 && new_y == -1){
					// mouse.turn_right();
					// mouse.turn_right();
					dir = 2;
					std::cerr << "Move South !!!" << '\n';
					mouse.mouse_run(direction::SOUTH);
				}
				// moving west
				else if(new_x == -1 && new_y == 0){
					// mouse.turn_left();
					dir = 3;
					std::cerr << "Move West !!!" << '\n';
					mouse.mouse_run(direction::WEST);
				}
				std::cerr << "***************" << '\n';	
				// std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
				mouse.set_cur_status(path.top().first, path.top().second, dir);
				std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
				std::cerr << "^^^^^^^^^^^^^^^" << '\n';	
				path.pop();
			} 
		}
		
	}

}

