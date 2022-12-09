/**
 * @brief in hindsight, a simpler approach might have been to implement templates
 */

#include <queue>
#include <vector>

#include "Job.hpp"

#ifndef POP_TO_QUEUE_HPP
#define POP_TO_QUEUE_HPP

/**
 * VECTOR
 * @brief pushs the front of "lose" queue into "gain" queue and removes
 * the front element of "lose" queue
 * 
 * @param gain
 * @param lose
 */
inline void popToQ(std::vector<Job> &gain, std::vector<Job> &lose) {
  gain.push_back(lose.front());
  lose.erase(lose.begin());  
}

/**
 * QUEUE
 * @brief pushs the front of "lose" queue into "gain" queue and removes
 * the front element of "lose" queue
 * 
 * @param gain
 * @param lose
 */
inline void popToQ(std::queue<Job> &gain, std::queue<Job> &lose) {
  gain.push(lose.front());
  lose.pop();
} // end moveToRQ()

#endif