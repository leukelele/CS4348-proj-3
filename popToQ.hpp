/**
 * @brief in hindsight, a simpler approach might have been to implement templates
 */

#include <queue>

#include "Job.hpp"

#ifndef POP_TO_QUEUE_HPP
#define POP_TO_QUEUE_HPP

/**
 * INT
 * @brief pushs the front of "lose" queue into "gain" queue and removes
 * the front element of "lose" queue
 * 
 * @param gain
 * @param lose
 */
inline void popToQ(std::queue<int> &gain, std::queue<int> &lose) {
  gain.push(lose.front());
  lose.pop();  
}

/**
 * CLASS JOB
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