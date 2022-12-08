#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class RR {
  
  private:
    std::queue<Job> admittance; // admits the job
    std::queue<int> ID;         // help for displaying execution of processes
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
      for (int i = 0; i < jobList.size(); i++) {
        admittance.push(jobList.at(i));
      }
    } // end acceptJobs()
    
    /**
     * @brief assigns quantum size, default value is 2
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
     * @brief round robing algorithm, similar in concept to the first come first algorithm except all 
     * have a set time limit before the process is moved to the back of the queue
     */
    void circularQ() {
      std::queue<Job> ready;                                      // ready queue for execution of processes
      std::queue<int> identifier;                                 // keep track of elements as they moved through ready queue
      unsigned int sysQuantum = quantum;                          // interval for job until preemption
      unsigned int nextProc = admittance.front().getAdmitted();   // time of the next process
      unsigned int counter = 0;                                   // system counter
      
      /* iterates through queue, remaning on an element for the duration of the quantum, and breaks
         when ready queue and admittance queue are empty */
      do {
        
        /* places admitting process into ready queue at time admitted */
        if (counter == nextProc) {
          popToQ(ready, admittance);
          nextProc = admittance.front().getAdmitted();
        }
        
        /* moves process at the front of queue to the back and resets quantum counter */
        if (sysQuantum == 0) {
          Job temp = ready.front();
          ready.pop();
          ready.push(temp);
          sysQuantum = quantum;
        }
        
        if (!ready.empty()) {
          ready.front().processing();   // execution of process

          // display purposes, multiples 2 to ID to find number of spaces
          int spacing = 2 * (ready.front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }

        // process is removed if completed
        if (ready.front().getLength() == 0) {
          ready.pop();
          sysQuantum = quantum + 1;
        }

        counter++;
        sysQuantum--;
      } while (!ready.empty() || !admittance.empty());
    } // end circularQ()
};  // end RR