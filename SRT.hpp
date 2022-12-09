#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class SRT {
  private:
    std::queue<Job> admittance;

  public:
    
    /* constructor */
    SRT(std::vector<Job> jobList) {
      acceptJobs(jobList);
    } // end constructor

    /**
     * @brief admits jobs from jobList into storage
     * 
     * @param jobList 
     */
    void acceptJobs(std::vector<Job> jobList) {
      for (int i = 0; i < jobList.size(); i++) {
        admittance.push(jobList.at(i));
      }
    } // end acceptJobs()
    
    void shortestTimeQ() {
    } // end circularQ()
};