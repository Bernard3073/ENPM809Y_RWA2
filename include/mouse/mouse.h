/**
 * @file Mouse.h
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief The file contains the Mouse class
 * @version 0.1
 * @date 2021-10-24
 *
 * @copyright Copyright (c) 2021
 *
 */

 /*! \mainpage Maze search algorithm
  *
  * This project consists of searching a path in a maze
  * and then task a Mouse (Mouse) to follow the path.
  * - \subpage searchingPathPage "Searching a path"
  *
  * - \subpage followingPathPage "Following a path"
  *
  */

  /*! \page searchingPathPage Searching a path
   *
   * The search algorithm used for searching a path in a maze relies on
   * the depth-first search (DFS) approach. This algorithm is implemented in rwa2::Mouse::search_maze()
   *
   */

   /*! \page followingPathPage Following a path
    *
    * To follow a path generated by DFS, methods from the class API (api/api.h) must be used to interact
    * with the microMouse simulator.
    * - Methods of the API class are documented <a href="https://github.com/mackorone/mms#summary">here</a>.
    */


#ifndef MICROMouse_H
#define MICROMouse_H

#include "../node/node.h"
#include "../util/util.h"
#include <array>
#include <vector>
#include <utility>
#include <tuple>
#include <stack>
#include <iostream>

namespace rwa2 {
    /**
     * @brief This class is used to compute a path and execute the path.
     *
     */
    class Mouse {
        public:

        /**
         * @brief Construct a new MicroMouse object
         *
         * The robot is always at (0,0) and facing NORTH when the simulator starts
         */
        Mouse() :m_x{ 0 }, m_y{ 0 }, m_direction{ direction::NORTH } {
            //initialize the maze by placing around the perimeter of the maze
            for (int x = 0; x < m_maze_width; x += 1) {
                for (int y = 0; y < m_maze_height; y += 1) {
                    m_maze.at(x).at(y).set_wall(direction::NORTH, (y == m_maze_height - 1));
                    m_maze.at(x).at(y).set_wall(direction::EAST, (x == m_maze_width - 1));
                    m_maze.at(x).at(y).set_wall(direction::SOUTH, (y == 0));
                    m_maze.at(x).at(y).set_wall(direction::WEST, (x == 0));
                }
            }
        }
        // this method visually sets the walls in the simulator
        void display_walls();
        //IMPLEMENT THE METHODS BELOW
        //Note: Come up with your own parameters and implementations
        /**
         * @brief Implement DFS to compute a path between 2 nodes in a maze
         *
         * @return true A path is found
         * @return false A path is not found
         */
        bool search_maze(int x, int y, std::stack<std::pair<int, int>> &st, std::vector<std::pair<int, int>> &visited_node);
        /**
         * @brief Make the Mouse move forward
         *
         */
        void move_forward();
        /**
         * @brief Make the Mouse rotate 90 deg CCW
         *
         */
        void turn_left();
        /**
         * @brief Make the Mouse rotate 90 deg CW
         *
         */
        void turn_right();
        /**
         * @brief setter for goal x, y position of the Mouse
         * 
         */
        void set_goal(int x, int y){
             goal_x = x;
             goal_y = y;
        }
        /**
         * @brief getter for goal x, y position of the Mouse
         * 
         */
        std::pair<int, int> get_goal(){
            return std::make_pair(goal_x, goal_y);
        }
        /**
         * @brief getter for current x, y position and direction of the Mouse
         * 
         */
        std::tuple<int, int, int> get_cur_status(){
            return std::make_tuple(m_x, m_y, m_direction);
        }
        /**
         * @brief setter for current x, y position and direction of the Mouse
         * 
         */
        void set_cur_status(int x, int y, int dir){
            m_x = x; 
            m_y = y; 
            m_direction = dir;
        }


        bool is_valid(int x, int y){
            if(x >= 0 && x < m_maze_width && y >= 0 && y < m_maze_height) return true;
            return false;
        }

        bool mouse_run(int &x, int &y, direction d);
        void check_wall();
        private:
        static const int m_maze_width{ 16 }; //width of the maze
        static const int m_maze_height{ 16 };//height of the maze
        int m_x; //x position of the Mouse in the maze
        int m_y; //y position of the Mouse in the maze
        int m_direction; //direction of the Mouse in the maze
        int goal_x; // goal x position
        int goal_y; // goal y position
        std::array<std::array<Node, m_maze_width>, m_maze_height> m_maze; //2D array maze object
    };
}
#endif