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

bool rwa2::Mouse::search_maze(int cur_x, int cur_y, std::stack<std::tuple<int, int, int>> &st, std::vector<std::pair<int, int>> &visited_node){ 
    
    // current node is not the goal
    if (!(cur_x == goal_x \
        && cur_y == goal_y)){
        if(st.empty()){
            st.push(std::make_tuple(cur_x, cur_y, m_direction));
        }
    }
    // current node is the goal
    else return true;

    // if ((cur_x == goal_x \
    //     && cur_y == goal_y)){
    //     return true;
    // }

    // check if current node is in visited list
    if(!is_in_visited_node(cur_x, cur_y, visited_node)) 
        visited_node.push_back(std::make_pair(cur_x, cur_y));

    // check North
    if((!m_maze.at(cur_x).at(cur_y).is_wall(direction::NORTH)) && (!is_in_visited_node(cur_x, cur_y+1, visited_node)))
    {
        st.push(std::make_tuple(cur_x, cur_y+1, 0));
        // API::setWall(cur_x, cur_y, 'n');
        cur_y += 1;
        
    }
    // check East
    else if((!m_maze.at(cur_x).at(cur_y).is_wall(direction::EAST)) && (!is_in_visited_node(cur_x+1, cur_y, visited_node)))
    {
        st.push(std::make_tuple(cur_x+1, cur_y, 1));
        // API::setWall(cur_x, cur_y, 'e');
        cur_x += 1;
    }
    // check South
    else if(!m_maze.at(cur_x).at(cur_y).is_wall(direction::SOUTH) && (!is_in_visited_node(cur_x, cur_y-1, visited_node))){
        st.push(std::make_tuple(cur_x, cur_y-1, 2));
        // API::setWall(cur_x, cur_y, 's');
        cur_y -= 1;
    }
    // check West
    else if(!m_maze.at(cur_x).at(cur_y).is_wall(direction::WEST) && (!is_in_visited_node(cur_x-1, cur_y, visited_node))){
        st.push(std::make_tuple(cur_x-1, cur_y, 3));
        // API::setWall(cur_x, cur_y, 'w');
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

void rwa2::Mouse::update_maze_info(int cur_x, int cur_y){
    switch(m_direction){
        // facing north
        case 0:{
            char d;
            if(API::wallFront()){
                std::cerr << "Wall front" << '\n';
                d = 'n';                
                m_maze.at(cur_x).at(cur_y).set_wall(0, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallRight()){
                d = 'e';
                m_maze.at(cur_x).at(cur_y).set_wall(1, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallLeft()){
                d = 'w';
                m_maze.at(cur_x).at(cur_y).set_wall(3, true);
                API::setWall(cur_x, cur_y, d);
            }
            break;
        }
        // facing east
        case 1:{
            char d;
            if(API::wallFront()){
                d = 'e';
                m_maze.at(cur_x).at(cur_y).set_wall(1, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallRight()){
                d = 's';
                m_maze.at(cur_x).at(cur_y).set_wall(2, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallLeft()){
                d = 'n';
                m_maze.at(cur_x).at(cur_y).set_wall(0, true);
                API::setWall(cur_x, cur_y, d);
            }
            break;
        }
        // facing south
        case 2:{
            char d;
            if(API::wallFront()){
                d = 's';
                m_maze.at(cur_x).at(cur_y).set_wall(2, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallRight()){
                d = 'w';
                m_maze.at(cur_x).at(cur_y).set_wall(3, true);
                API::setWall(cur_x, cur_y, d);
            }
            else if(API::wallLeft()){
                d = 'e';
                m_maze.at(cur_x).at(cur_y).set_wall(1, true);
                API::setWall(cur_x, cur_y, d);
            }
            
            
            break;
        }
        // facing west
        case 3:{
            char d;
            if(API::wallFront()){
                d = 'w';
                API::setWall(cur_x, cur_y, d);
                m_maze.at(cur_x).at(cur_y).set_wall(3, true);
            }
            else if(API::wallRight()){
                d = 'n';
                API::setWall(cur_x, cur_y, d);
                m_maze.at(cur_x).at(cur_y).set_wall(0, true);
            }
            else if(API::wallLeft()){
                d = 's';
                API::setWall(cur_x, cur_y, d);
                m_maze.at(cur_x).at(cur_y).set_wall(2, true);
            }
            
            break;
        }
    }
}
