#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "QInteract.hpp"

class RR {
  
  private:
    std::queue<Job> admittance; // admits the job
    std::queue<Job> ready;      // ready queue for execution of process
    unsigned int quantum;       // interval for process before preemption, default is 2
    
  public:
    
    /* constructor when given jobList */
    RR(std::vector<Job> jobList) {
      acceptJobs(jobList);
      requestQuantum();
    }

    /******************
     *                *
     *    MODIFERS    *
     *                *
     ******************/
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
     * @brief assigns quantum size, default value is 2
     * 
     */
    void requestQuantum(unsigned int size = 2) {
      quantum = size;
    } // end requestQuantum()

    /*******************************
     *                             *
     *    ROUND ROBIN ALGORITHM    *
     *                             * 
     *******************************/
    /**
     * @brief 
     * 
     */
    void circularQ() {
      unsigned int sysQuantum = quantum;                          // interval for job until preemption
      unsigned int counter = 0;                                   // system counter
      unsigned int nextProc = admittance.front().getAdmitted();   // time of the next process
      Job *currentJob;                                            // pointer for current process
      
      do {
        
        /* places admitting process into ready queue at time admitted */
        if (counter == nextProc) {
          popToQ(ready, admittance);
          nextProc = admittance.front().getAdmitted();
        }
        
        /* moves process at the front of queue to the back and resets quantum counter*/
        if (sysQuantum == 0) {
          Job temp = ready.front();
          ready.pop();
          ready.push(temp);
          sysQuantum = quantum;
        }
        
        if (!ready.empty()) ready.front().processing();   // execution of process
        if (ready.front().getLength() == 0) ready.pop();  // process removed if completed

        counter++;
        sysQuantum--;
      } while (!ready.empty() || !admittance.empty());
    } // end circularQ()
};  // end RR