#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class FB {
  private:
    std::queue<Job> admittance; // admits the job
    unsigned int quantum;       // interval for process before preemption, default is 2
    unsigned int numQ;
    
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
     * @brief assigns quantum size, default value is 1
     */
    void requestQuantum(unsigned int size = 1) {
      quantum = size;
    } // end requestQuantum()
    
    /**
     * @brief assigns quantum size, default value is 1
     */
    void requestNumQ(unsigned int num = 3) {
      numQ = num;
    } // end requestQuantum()

    /****************************
     *                          *
     *    FEEDBACK ALGORITHM    *
     *                          *
     ****************************/
    /**
     * @brief 
     */
    void QQQ() {
      
      /* initialize queue of varying levels of priority */
      typedef std::queue<Job> ready;
      std::vector<ready> q;
      for (unsigned int i = 0; i < numQ; i++) {
        q.push_back(ready());
      }

      unsigned int prioLvl = 0;
      unsigned int nextProc = admittance.front().getAdmitted();
      unsigned int sysQuantum = quantum;
      unsigned int counter = 0;

      do {
        if (counter == nextProc) {
          prioLvl = 0;
          popToQ(q.at(prioLvl), admittance);
          nextProc = admittance.front().getAdmitted();
        }
        
        if (sysQuantum == 0) {
          Job temp = q.at(prioLvl).front();
          q.at(prioLvl).pop();
          q.at(prioLvl).push(temp);
          sysQuantum = quantum;
        }
        
        if (!q.at(prioLvl).empty()) {
          q.at(prioLvl).front().processing();
          
          // display purposes, multiplies 2 to ID to find number of spaces for "X"
          int spacing = 2 * (q.at(prioLvl).front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }
        else prioLvl++;
        
        if (q.at(prioLvl).front().getLength() == 0) {
          q.at(prioLvl).pop();
          sysQuantum = quantum + 1;
        }
        
        counter++;
        sysQuantum--;
      } while (!q.at(0).empty() || !q.at(1).empty() 
               || !q.at(2).empty() || !admittance.empty());
    } // end QQQ();
};