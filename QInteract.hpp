#include <queue>

#include "Job.hpp"

#ifndef Q_INTERACT_HPP
#define Q_INTERACT_HPP

/**
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