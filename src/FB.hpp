#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class FB {
  private:
    std::queue<Job> admittance; // admits the job
    unsigned int quantum;       // interval for process before preemption, default is 2
    
  public:
    
    /* constructor when given jobList */
    FB(std::vector<Job> jobList) {
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
     * @brief assigns quantum size, default value is 2
     */
    void requestQuantum(unsigned int size = 2) {
      quantum = size;
    } // end requestQuantum()

    /**
     * @brief 
     */
    void QQQ() {
      std::queue<Job> prio1;
      std::queue<Job> prio2;
      std::queue<Job> prio3;
      unsigned int nextProc = admittance.front().getAdmitted();
      unsigned int sysQuantum = quantum;
      unsigned int counter = 0;

      do {
        if (counter == nextProc) {
          popToQ(prio1, admittance);
          nextProc = admittance.front().getAdmitted();
        }
        
        if (sysQuantum == 0) {

        }

        counter++;
      } while (!prio1.empty() || !prio2.empty() || prio3.empty() 
               || !admittance.empty());
    } // end QQQ();
};