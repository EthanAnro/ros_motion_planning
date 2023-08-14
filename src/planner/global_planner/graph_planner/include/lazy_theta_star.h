/***********************************************************
 *
 * @file: lazy_theta_star.h
 * @breif: Contains the lazy Theta* planner class
 * @author: Wu Maojia
 * @update: 2023-8-14
 * @version: 1.0
 *
 * Copyright (c) 2023， Wu Maojia
 * All rights reserved.
 * --------------------------------------------------------
 *
 **********************************************************/
#ifndef LAZY_THETA_STAR_H
#define LAZY_THETA_STAR_H

#include <vector>
#include <queue>
#include "global_planner.h"

namespace global_planner
{
/**
 * @brief Class for objects that plan using the lazy Theta* algorithm
 */
class LazyThetaStar : public GlobalPlanner
{
public:
  /**
   * @brief Construct a new LaztThetaStar object
   * @param nx          pixel number in costmap x direction
   * @param ny          pixel number in costmap y direction
   * @param resolution  costmap resolution
   */
  LazyThetaStar(int nx, int ny, double resolution);

  /**
   * @brief Lazy Theta* implementation
   * @param global_costmap global costmap
   * @param start         start node
   * @param goal          goal node
   * @param path          optimal path consists of Node
   * @param expand        containing the node been search during the process
   * @return  true if path found, else false
   */
  bool plan(const unsigned char* global_costmap, const Node& start, const Node& goal, std::vector<Node>& path,
            std::vector<Node>& expand);

protected:
  /**
   * @brief update the g value of child node
   * @param parent
   * @param child
   */
  void _updateVertex(const Node& parent, Node& child);

  /**
   * @brief check if the parent of vertex need to be updated. if so, update it
   * @param node
  */
  void _setVertex(Node& node);

  /**
   * @brief Bresenham algorithm to check if there is any obstacle between parent and child
   * @param parent
   * @param child
   * @return true if no obstacle, else false
   */
  bool _lineOfSight(const Node& parent, const Node& child);

  /**
   * @brief Get the Euclidean distance between two nodes
   * @param node  current node
   * @param goal  goal node
   * @return  Euclidean distance
  */
  double _getDistance(const Node& node, const Node& goal);

private:
  const unsigned char* costs_;              // costmap copy
  std::vector<Node> open_list_;             // open list
  std::unordered_set<Node, NodeIdAsHash, compare_coordinates> closed_list_; // closed list
  std::vector<Node> motion_;          // possible motions
};
}  // namespace global_planner
#endif
