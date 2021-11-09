#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <stack>
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
    // use binary search to check if current node is in the list of nodes
    int flag = 0;
    int start = 0, end = visited_node.size();
    while(start < end && !flag){
        int middle = start + (end - start)/2;
        if(visited_node[middle].first == x \
            && visited_node[middle].second == y) return true;
        else if(visited_node[middle].first > x) end = middle - 1;
        else start = middle + 1;
    }
    return false; 
}

bool rwa2::Mouse::search_maze(){ 
    
    // current node is not the goal
    // if (!(m_x == goal_x \
    //     && m_y == goal_y)){
    //     if(st.empty()){
    //         st.push(std::make_pair(m_x, m_y));
    //     }
    // }
    // // current node is the goal
    // else return true;

    if ((m_x == goal_x \
        && m_y == goal_y)){
        return true;
    }

    // check if current node is in visited list
    if(!is_in_visited_node(m_x, m_y, visited_node)) 
        visited_node.push_back(std::make_pair(m_x, m_y));
    // std::cout << m_maze.at(m_x).at(m_y).compute_number_of_walls() << '\n';
    
    // check North
    if(!m_maze.at(m_x).at(m_y).is_wall(direction::NORTH) && is_valid(m_x, m_y+1)){
        st.push(std::make_pair(m_x, m_y+1));
        // std::cout << m_y + 1 << '\n';
        m_y += 1;
    }
    // check East
    else if(!m_maze.at(m_x).at(m_y).is_wall(direction::EAST) && is_valid(m_x+1, m_y)){
        st.push(std::make_pair(m_x+1, m_y));
        m_x += 1;
    }
    // check South
    else if(!m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH) && is_valid(m_x, m_y-1)){
        st.push(std::make_pair(m_x, m_y-1));
        m_y -= 1;
    }
    // check West
    else if(!m_maze.at(m_x).at(m_y).is_wall(direction::WEST) && is_valid(m_x-1, m_y)){
        st.push(std::make_pair(m_x-1, m_y));
        m_x -= 1;
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
        m_x = st.top().first;
        m_y = st.top().second;
        std::cout << m_x << ' ' << m_y << '\n';
        search_maze(); 
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
