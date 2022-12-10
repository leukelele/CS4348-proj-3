/**
 * @brief contains functions that pops the element of a queue and pushes it into another
 * in hindsight, a simpler approach might have been to implement templates
 */
#include <queue>
#include <vector>

#include "Job.hpp"

#ifndef POP_TO_QUEUE_HPP
#define POP_TO_QUEUE_HPP

/**
 * QUEUE TO VECTOR
 * @brief pushs the front of "lose" queue into "gain" queue and removes
 * the front element of "lose" queue
 * 
 * @param gain
 * @param lose
 */
inline void popToQ(std::vector<Job> &gain, std::queue<Job> &lose) {
  Job temp = lose.front();
  lose.pop();
  gain.push_back(temp);
}

/**
 * QUEUE TO QUEUE
 * @brief pushs the front of "lose" queue into "gain" queue and removes
 * the front element of "lose" queue
 * 
 * @param gain
 * @param lose
 */
inline void popToQ(std::queue<Job> &gain, std::queue<Job> &lose) {
  Job temp = lose.front();
  lose.pop();
  gain.push(temp);
} // end moveToRQ()

#endif