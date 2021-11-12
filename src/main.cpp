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
		API::setColor(7, 7, 'R');
		API::setText(7, 7, "Goal");
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
			int flag = 0;
			// move the robot along the path
			while(!path.empty() && flag == 0){
				m_x = std::get<0>(mouse.get_cur_status());
				m_y = std::get<1>(mouse.get_cur_status());
				m_d = std::get<2>(mouse.get_cur_status());
				std::cerr << std::to_string(m_d) << '\n';
				
				int delta_x = path.top().first - m_x;
				int delta_y = path.top().second - m_y;
				int dir;
				// mouse.set_cur_status(m_x, m_y, m_d);
				
				// std::cerr << "CUR: "<<std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
				std::cerr << "NEXT: "<<std::to_string(path.top().first) << ", "  << std::to_string(path.top().second) << '\n';
				// std::cerr << "DEL: "<<std::to_string(delta_x) << ", "  << std::to_string(delta_y) << '\n';
				mouse.check_wall();
				
				// moving north
				if(delta_x == 0 && delta_y == 1){
					dir = 0;
					std::cerr << "Move North !!!" << '\n';
					if(!mouse.mouse_run(delta_x, delta_y, direction::NORTH)){
						std::cerr << "Wall Encountered (NORTH)!!!" << '\n';
						flag = 1;
						// mouse.set_cur_status(m_x, m_y, m_d);
						std::cerr << "STOP_BY_WALL: "<<std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
						break;
					}
					else flag = 0;
				}
				// moving east
				else if(delta_x == 1 && delta_y == 0){
					// mouse.turn_right();
					dir = 1;
					std::cerr << "Move East !!!" << '\n';
					if(!mouse.mouse_run(delta_x, delta_y, direction::EAST)){
						std::cerr << "Wall Encountered (EAST)!!!" << '\n';
						flag = 1;
						// mouse.set_cur_status(m_x, m_y, m_d);
						
						break;
					}
					else flag = 0;
				}
				// moving south
				else if(delta_x == 0 && delta_y == -1){
					// mouse.turn_right();
					// mouse.turn_right();
					dir = 2;
					std::cerr << "Move South !!!" << '\n';
					if(!mouse.mouse_run(delta_x, delta_y, direction::SOUTH)){
						std::cerr << "Wall Encountered (SOUTH)!!!" << '\n';
						flag = 1;
						// mouse.set_cur_status(m_x, m_y, m_d);
						
						break;
					}
					else flag = 0;
				}
				// moving west
				else if(delta_x == -1 && delta_y == 0){
					// mouse.turn_left();
					dir = 3;
					std::cerr << "Move West !!!" << '\n';
					if(!mouse.mouse_run(delta_x, delta_y, direction::WEST)){
						std::cerr << "Wall Encountered (WEST)!!!" << '\n';
						flag = 1;
						// mouse.set_cur_status(m_x, m_y, m_d);
						
						break;
					}
					else flag = 0;
				}
				// std::cerr << "***************" << '\n';	
				// // std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
				// mouse.set_cur_status(path.top().first, path.top().second, dir);
				// std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << '\n';
				// std::cerr << "^^^^^^^^^^^^^^^" << '\n';	

				path.pop();
			}
		}
		else{
			std::cerr << "Unable to find path !!!" << '\n';
			break;
		}
		
	}

}

