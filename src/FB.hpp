#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class FB {
  private:

    typedef std::queue<Job> priority;
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
     * @brief emulates the feedback algorithm by placing processes into lower priority
     * queues in addition to limiting processes to some interval defined by the quantum
     */
    void QQQ() {
      
      /* initialize queue of varying levels of priority */
      std::vector<priority> q;
      for (unsigned int i = 0; i < numQ; i++) {
        q.push_back(priority());
      }

      unsigned int prioLvl = 0;                                   // priority lvl to access queues
      unsigned int nextProc = admittance.front().getAdmitted();   // time next process will be admitted
      unsigned int sysQuantum = quantum;                          // quamtum counter
      unsigned int counter = 0;                                   // system counter

      /* iterates through queue, until all queus are empty */
      do {
        
        /* places admitting process into ready queue at time admitted and resets 
          priority level to 0 (highest priority) */
        if (counter == nextProc) {
          prioLvl = 0;
          popToQ(q.at(prioLvl), admittance);
          nextProc = admittance.front().getAdmitted();

          std::cout << "\nadmittance:" << std::endl;
          display(q);
        }
        
        int numInQ = 0;
        
        /* at expiration of quantum, places the process in a lower prio queue*/
        if (sysQuantum == 0) {
          Job temp = q.at(prioLvl).front();     // temporary container for process
          q.at(prioLvl).pop();                  // removes process in current queue

          /* check that prioLvl isn't already at the lowest priority */
          unsigned int numPrio = q.size() - 1;
          if (prioLvl < numPrio) q.at((prioLvl + 1)).push(temp);
          sysQuantum = quantum;

          std::cout << "\nquantum reset:" << std::endl;
          display(q);

        }
        
        // int tempNumQ = numQ;
        // for (int i = 0; i < tempNumQ; i++) {
        //   if (!q.at(prioLvl).empty()) {
        //     q.at(prioLvl).front().processing();
        //     break;
        //   }
        // }

        /* execution of process and display on graph; increments priority level if 
           current level is empty */
        if (!q.at(prioLvl).empty()) {
          q.at(prioLvl).front().processing();
          
          // display purposes, multiplies 2 to ID to find number of spaces for "X"
          int spacing = 2 * (q.at(prioLvl).front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }
        else {
          prioLvl++;
          
          unsigned int qSize = q.size();
          if (prioLvl == qSize) {
            prioLvl = 0;
          }
        }
        
        /* exe process in high prio q*/
        if (q.at(prioLvl).front().getLength() == 0) {
          q.at(prioLvl).pop();
          sysQuantum = quantum + 1;
        }
        
        counter++;
        sysQuantum--;
      } while (!q.at(0).empty() || !q.at(1).empty() 
               || !q.at(2).empty() || !admittance.empty());
    } // end QQQ();
    
    void display(std::vector<priority> q) {
      int prioSize = q.size();
      for (int i = 0; i < prioSize; i++) {
        std::cout << "Priority Queue " << i << ": ";

        int queueSize = q.at(i).size();
        for (int j = 0; j < queueSize; j++) {
          std::cout << q.at(i).front().getName();
          std::cout << q.at(i).front().getLength();
          q.at(i).pop();
          std::cout << " ";
        }
        
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
};