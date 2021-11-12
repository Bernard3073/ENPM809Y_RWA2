#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <stack>
#include <tuple>
#include <utility>
#include <iostream>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

bool is_in_visited_node(int x, int y, std::vector<std::pair<int, int>> &visited_node){
    for(auto it = visited_node.begin(); it!= visited_node.end(); it++){
        if(it->first == x && it->second == y) return true;
    }
    return false; 
}

bool rwa2::Mouse::search_maze(int cur_x, int cur_y, std::stack<std::pair<int, int>> &st, std::vector<std::pair<int, int>> &visited_node){ 
    // current node is not the goal
    if (!(cur_x == goal_x \
        && cur_y == goal_y)){
        if(st.empty()){
            st.push(std::make_pair(cur_x, cur_y));
        }
    }
    // current node is the goal
    else return true;

    // check if current node is in visited list
    if(!is_in_visited_node(cur_x, cur_y, visited_node)) 
        visited_node.push_back(std::make_pair(cur_x, cur_y));

    // check North
    if((!m_maze.at(cur_x).at(cur_y).is_wall(direction::NORTH)) && (!is_in_visited_node(cur_x, cur_y+1, visited_node)))
    {
        st.push(std::make_pair(cur_x, cur_y+1));
        cur_y += 1;
    }
    // check East
    else if((!m_maze.at(cur_x).at(cur_y).is_wall(direction::EAST)) && (!is_in_visited_node(cur_x+1, cur_y, visited_node)))
    {
        st.push(std::make_pair(cur_x+1, cur_y));
        cur_x += 1;
    }
    // check South
    else if(!m_maze.at(cur_x).at(cur_y).is_wall(direction::SOUTH) && (!is_in_visited_node(cur_x, cur_y-1, visited_node))){
        st.push(std::make_pair(cur_x, cur_y-1));
        cur_y -= 1;
    }
    // check West
    else if(!m_maze.at(cur_x).at(cur_y).is_wall(direction::WEST) && (!is_in_visited_node(cur_x-1, cur_y, visited_node))){
        st.push(std::make_pair(cur_x-1, cur_y));
        cur_x -= 1;
    }
    // no valid nodes: backtrack
    else{
        // remove current node from stack
        if(!st.empty()){
            st.pop();
        }
        // empty stack = goal not found
        else return false;
    }
    API::setColor(cur_x, cur_y, 'g');
    
    if(!st.empty()){
        // current node is now the one at the top of stack
        cur_x = std::get<0>(st.top());
        cur_y = std::get<1>(st.top());
        search_maze(cur_x, cur_y, st, visited_node); 
    }
    // empty stack = goal not found
    else return false;
}

void rwa2::Mouse::move_forward(){
    API::moveForward();
}
void rwa2::Mouse::turn_left(){
    API::turnLeft();
}
void rwa2::Mouse::turn_right(){
    API::turnRight();
}

void rwa2::Mouse::check_wall(){
    char d;
    int d_int;
    std::cerr << "CHECK_WALL: "<<std::to_string(m_x) << ", "  << std::to_string(m_y) << ", d:" << m_direction << '\n';
    switch(m_direction){
        // facing north
        case 0:{
            if(API::wallFront()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallRight()){
                d = 'e';
                d_int = 1;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallLeft()){
                d = 'w';
                d_int = 3;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            
            break;
        }
        // facing east
        case 1:{
            if(API::wallFront()){
                d = 'e';
                d_int = 1;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallRight()){
                d = 's';
                d_int = 2;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallLeft()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            break;
        }
        // facing south
        case 2:{
            if(API::wallFront()){
                d = 's';
                d_int = 2;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallRight()){
                d = 'w';
                d_int = 3;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallLeft()){
                d = 'e';
                d_int = 1;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }  
            
            break;
        }
        // facing west
        case 3:{
            if(API::wallFront()){
                d = 'w';
                d_int = 3;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallRight()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            if(API::wallLeft()){
                d = 's';
                d_int = 2;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
            }
            
            break;
        }
    }
    //display the number of walls surrounding the current node
    API::setText(m_x, m_y, std::to_string(m_maze.at(m_x).at(m_y).compute_number_of_walls()));
    std::cerr << "WALL: "<<std::to_string(m_x) << ", "  << std::to_string(m_y) << ", w:" << d << '\n';

}

bool rwa2::Mouse::mouse_run(int &delta_x, int &delta_y, direction moving_dir){
    char d;
    int d_int;
    std::cerr << "f_D: " << std::to_string(m_direction) << '\n';
    check_wall();
    switch(m_direction){
        // facing north
        case 0:{
            if(API::wallFront()){
                // d = 'n';
                // d_int = 0;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) return false;
            }
            if(API::wallRight()){
                // d = 'e';
                // d_int = 1;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == EAST) return false;
            }
            if(API::wallLeft()){
                // d = 'w';
                // d_int = 3;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == WEST) return false;
            }
            // set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            
            switch(moving_dir){
                case direction::NORTH:{
                    move_forward();
                    break;
                }
                case direction::EAST:{
                    turn_right();
                    move_forward();
                    break;
                }
                case direction::SOUTH:{
                    turn_right();
                    turn_right();
                    move_forward();
                    break;
                }
                case direction::WEST:{
                    turn_left();
                    move_forward();
                    break;
                }
            }
            set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            
            break;
        }
        // facing east
        case 1:{
            std::cerr << "Facing East !!!!" << '\n';
            if(API::wallFront()){
                // d = 'e';
                // d_int = 1;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == EAST) return false;
            }
            if(API::wallRight()){
                // d = 's';
                // d_int = 2;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == SOUTH) return false;
            }
            if(API::wallLeft()){
                // d = 'n';
                // d_int = 0;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) return false;
            }
            
            
            switch(moving_dir){
                case direction::NORTH:{
                    turn_left();
                    move_forward();
                    std::cerr << "LEFT East !!!" << '\n';
                    break;
                }
                case direction::EAST:{
                    move_forward();
                    std::cerr << "FORWARD East !!!" << '\n';
                    
                    break;
                }
                case direction::SOUTH:{
                    turn_right();
                    move_forward();
                    std::cerr << "RIGHT East !!!" << '\n';
                    break;
                }
                case direction::WEST:{
                    turn_right();
                    turn_right();
                    move_forward();
                    std::cerr << "RIGHT RIGHT East !!!" << '\n';
                    break;
                }
            }
            set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir); 
            break;
        }
        // facing south
        case 2:{
            if(API::wallFront()){
                // d = 's';
                // d_int = 2;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == SOUTH) return false;
            }
            if(API::wallRight()){
                // d = 'w';
                // d_int = 3;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == WEST) return false;
            }
            if(API::wallLeft()){
                // d = 'e';
                // d_int = 1;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == EAST) return false;
            }  
            // set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            
            switch(moving_dir){
                case direction::NORTH:{
                    turn_right();
                    turn_right();
                    move_forward();
                    break;
                }
                case direction::EAST:{
                    turn_left();
                    move_forward();
                    break;
                }
                case direction::SOUTH:{
                    move_forward();
                    break;
                }
                case direction::WEST:{
                    turn_right();
                    move_forward();

                    break;
                }
            }  
            set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            break;
        }
        // facing west
        case 3:{
            if(API::wallFront()){
                // d = 'w';
                // d_int = 1;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == WEST) return false;
            }
            if(API::wallRight()){
                // d = 'n';
                // d_int = 0;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) return false;
            }
            if(API::wallLeft()){
                // d = 's';
                // d_int = 2;
                // m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                // API::setWall(m_x, m_y, d);
                if(moving_dir == SOUTH) return false;
            }
            // set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            
            switch(moving_dir){
                case direction::NORTH:{
                    
                    turn_right();
                    move_forward();

                    break;
                }
                case direction::EAST:{
                    turn_right();
                    turn_right();
                    move_forward();

                    break;
                }
                case direction::SOUTH:{
                    turn_left();                    
                    move_forward();

                    break;
                }
                case direction::WEST:{
                    move_forward();
                    break;
                }
            }
            set_cur_status(m_x + delta_x, m_y + delta_y, moving_dir);
            break;
        }
    }
    std::cerr << "***************" << '\n';	
    std::cerr << std::to_string(m_x) << ", "  << std::to_string(m_y) << ", f_D: " << std::to_string(m_direction)<< '\n';
    std::cerr << "^^^^^^^^^^^^^^^" << '\n';
    
    return true;
}
