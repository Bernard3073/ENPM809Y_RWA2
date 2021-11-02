#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <stack>
#include <utility>

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

bool is_in_node_list(std::pair<int, int> &cur_node, std::vector<std::pair<int, int>> &node_list){
    // use binary search to check if current node is in the list of nodes
    int flag = 0;
    int start = 0, end = node_list.size();
    while(start < end && !flag){
        int middle = start + (end - start)/2;
        if(node_list[middle].first == cur_node.first \
            && node_list[middle].second == cur_node.second) return true;
        else if(node_list[middle].first > cur_node.first) end = middle - 1;
        else start = middle + 1;
    }
    return false; 
}

bool rwa2::Mouse::search_maze(){
    // current node
    std::pair<int, int> cur_node = rwa2::Mouse::get_cur(); 
    // goal node
    std::pair<int, int> goal_node = rwa2::Mouse::get_goal();

    // stack of nodes
    std::stack<std::pair<int, int>> st;
    // list of nodes
    std::vector<std::pair<int, int>> node_list;
    // current node is not the goal
    if (!(cur_node.first == goal_node.first \
        && cur_node.second == goal_node.second)){
        if(!st.empty()) st.push(cur_node);
    }
    // current node is the goal
    else return true;
    if(!is_in_node_list(cur_node, node_list)) 
        node_list.push_back(cur_node);
    // check North
    if(m_maze.at(cur_node.first).at(cur_node.second).is_wall(direction::NORTH)){
        st.push(cur_node);
        cur_node.second += 1;
    }
    // check East
    else if(m_maze.at(cur_node.first).at(cur_node.second).is_wall(direction::EAST)){
        st.push(cur_node);
        cur_node.first += 1;
    }
    // check South
    else if(m_maze.at(cur_node.first).at(cur_node.second).is_wall(direction::SOUTH)){
        st.push(cur_node);
        cur_node.second -= 1;
    }
    // check West
    else if(m_maze.at(cur_node.first).at(cur_node.second).is_wall(direction::WEST)){
        st.push(cur_node);
        cur_node.first -= 1;
    }
    // no valid nodes: backtrack
    else{
        // remove current node from stack
        if(!st.empty()) st.pop();
        // empty stack = goal not found
        else return false;
    }
    if(!st.empty()){
        // current node is now the one at the top of stack
        m_x = st.top().first;
        m_y = st.top().second;
        search_maze(); 
    }
    // empty stack = goal not found
    else return false;
}