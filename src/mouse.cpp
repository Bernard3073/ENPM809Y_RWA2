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
    // API::setColor(cur_x, cur_y, 'g');
    
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

bool rwa2::Mouse::check_wall(direction moving_dir){
    char d;
    int d_int;
    switch(m_direction){
        // facing north
        case 0:{
            if(API::wallFront()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) break;
            }
            else if(API::wallRight()){
                d = 'e';
                d_int = 1;
            }
            else if(API::wallLeft()){
                d = 'w';
                d_int = 3;
            }
            
            
            break;
        }
        // facing east
        case 1:{
            if(API::wallFront()){
                d = 'e';
                d_int = 1;
            }
            else if(API::wallRight()){
                d = 's';
                d_int = 2;
            }
            else if(API::wallLeft()){
                d = 'n';
                d_int = 0;
            }
            m_maze.at(m_x).at(m_y).set_wall(d_int, true);
            API::setWall(m_x, m_y, d);
            break;
        }
        // facing south
        case 2:{
            if(API::wallFront()){
                d = 's';
                d_int = 2;
            }
            else if(API::wallRight()){
                d = 'w';
                d_int = 3;
            }
            else if(API::wallLeft()){
                d = 'e';
                d_int = 1;
            }  
            m_maze.at(m_x).at(m_y).set_wall(d_int, true);
            API::setWall(m_x, m_y, d);
            break;
        }
        // facing west
        case 3:{
            if(API::wallFront()){
                d = 'w';
                d_int = 1;
            }
            else if(API::wallRight()){
                d = 'n';
                d_int = 0;
            }
            else if(API::wallLeft()){
                d = 's';
                d_int = 2;
            }
            m_maze.at(m_x).at(m_y).set_wall(d_int, true);
            API::setWall(m_x, m_y, d);
            break;
        }
    }
    return true;
}

void rwa2::Mouse::mouse_run(direction moving_dir){
    char d;
    int d_int;
    switch(m_direction){
        // facing north
        case 0:{
            if(API::wallFront()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) break;
            }
            else if(API::wallRight()){
                d = 'e';
                d_int = 1;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == EAST) break;
            }
            else if(API::wallLeft()){
                d = 'w';
                d_int = 3;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == WEST) break;
            }
            switch(moving_dir){
                case direction::NORTH:{
                    move_forward();
                    break;
                }
                case direction::EAST:{
                    turn_right();
                    break;
                }
                case direction::SOUTH:{
                    turn_right();
                    turn_right();
                    break;
                }
                case direction::WEST:{
                    turn_left();
                    break;
                }
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
                if(moving_dir == EAST) break;
            }
            else if(API::wallRight()){
                d = 's';
                d_int = 2;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == SOUTH) break;
            }
            else if(API::wallLeft()){
                d = 'n';
                d_int = 0;
                m_maze.at(m_x).at(m_y).set_wall(d_int, true);
                API::setWall(m_x, m_y, d);
                if(moving_dir == NORTH) break;
            }

            switch(moving_dir){
                case direction::NORTH:{
                    turn_left();
                    break;
                }
                case direction::EAST:{
                    move_forward();
                    break;
                }
                case direction::SOUTH:{
                    turn_right();
                    break;
                }
                case direction::WEST:{
                    turn_right();
                    turn_right();
                    break;
                }
            }
        }
        // facing south
        case 2:{
            switch(dir){
                case direction::NORTH:{
                    turn_right();
                    turn_right();
                    break;
                }
                case direction::EAST:{
                    turn_left();
                    break;
                }
                case direction::SOUTH:{
                    move_forward();
                    break;
                }
                case direction::WEST:{
                    turn_right();
                    break;
                }
            }  
            break;
        }
        // facing west
        case 3:{
            switch(dir){
                case direction::NORTH:{
                    turn_right();
                    break;
                }
                case direction::EAST:{
                    turn_right();
                    break;
                }
                case direction::SOUTH:{
                    turn_left();
                    break;
                }
                case direction::WEST:{
                    move_forward();
                    break;
                }
            }
            break;
        }
    }
    // int m_d;
    // switch (d)
    // {
    // case 'n':
    //     m_d = 0;
    //     break;
    // case 'e':
    //     m_d = 1;
    //     break;
    // case 's':
    //     m_d = 2;
    //     break;
    // case 'w':
    //     m_d = 3;
    //     break;
    // default:
    //     break;
    // }
    // set_cur_status(x, y, m_d);
	// std::cerr <<  "Update position: " << std::to_string(x) << ", "  << std::to_string(y) << '\n';
    
}
