#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"

class RR {
  
  private:
    std::queue<Job> admittance; // admits the job
    std::queue<Job> ready;      // ready queue for execution of process
    unsigned int quantum = 2;
    
  public:
    
    /* constructor when given jobList */
    RR(std::vector<Job> jobList) {
      acceptJobs(jobList);
    }

    /**
     * @brief places jobs from jobList into ready queue
     * 
     * @param jobList 
     */
    void acceptJobs(std::vector<Job> jobList) {
      for (int i = 0; i < jobList.size(); i++) 
        admittance.push(jobList.at(i));
    } // end acceptJobs()
    
    /**
     * @brief assigns quantum size
     * 
     */
    void requestQuantum(unsigned int size) {
      quantum = size;
    } // end requestQuantum()

    void circularQ() {
      unsigned int sysQuantum = quantum;
      
    }
};  // end RR