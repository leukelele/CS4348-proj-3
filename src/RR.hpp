#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class RR {
  private:
    
    std::queue<Job> admittance; // admits the job
    unsigned int quantum;       // interval for process before preemption, default is 1
    
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
      int listSize = jobList.size();
      for (int i = 0; i < listSize; i++) {
        admittance.push(jobList.at(i));
      }
    } // end acceptJobs()
    
    /**
     * @brief assigns quantum size, default value is 1
     */
    void requestQuantum(unsigned int size = 1) {
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
        
        // if there is a process in ready queue, execute process
        if (!ready.empty()) {
          ready.front().processing();   // execution of process

          // display purposes, multiplies 2 to ID to find number of spaces for "X"
          int spacing = 2 * (ready.front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }

        // process is removed once completed
        if (ready.front().getLength() == 0) {
          ready.pop();
          
          /**
           * I was stuck here; though, it has been fixed. Whenever the quantum counter decrements to 0,
           * the execution of a process is paused for the next process in ready queue. The issue, however,
           * was that if a process were to complete while the duration of the quantum has yet to expire,
           * the process would swap to the process next in queue without resetting the quantum counter.
           * 
           * I then wondered if this was actually how Round Robin was supposed to work, but ultimately 
           * some internet researching suggested otherwise.
           * 
           * TLDR: Issue with quantum counter where it did not reset after when process is determined
           * complete and resulted in processes sharing quantum interval.
           **/
          sysQuantum = quantum + 1;
        }

        counter++;
        sysQuantum--;
      } while (!ready.empty() || !admittance.empty());
    } // end circularQ()
};  // end RR