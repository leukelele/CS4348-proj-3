#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class FB {
  private:

    typedef std::queue<Job> priority; // typedef to create number of queues to be stored in a vector
    std::queue<Job> admittance;       // admits the job
    unsigned int quantum;             // interval for process before preemption, default is 2
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

      unsigned int prioLvl = 0;                                   // current priority lvl to access queues
      unsigned int numPrioLvl = numQ;                             // number of priority lvls
      unsigned int numProc = 0;                                   // keeps track of number of process in sys
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
          numProc++;
          nextProc = admittance.front().getAdmitted();

          std::cout << "\nadmittance:" << std::endl;
          displayContent(q);
        }

        /* inc prioLvl, if current queue is empty and not already on the lowest prio queue*/
        if ((q.at(prioLvl).empty()) && (prioLvl < numPrioLvl)) prioLvl++;
        
        /* at expiration of quantum, does either
           - continue with current process
           - places the current process into the next level of prio  */
        if (sysQuantum == 0) {
          
          /* if there is no other process in the system, place the only process
             back into the highest priority and reset prioLvl to 0 (highest prio)*/
          if (numProc < 2) {
            popToQ(q.at(0), q.at(prioLvl));
            prioLvl = 0;
            
            std::cout << "\nquantum reset:" << std::endl;
            displayContent(q);
          }

          /* places the process in a lower prio queue */
          else {

           /* check that prioLvl isn't already at the lowest priority; places process in
           the next lowest priority */
            if (prioLvl < numPrioLvl) popToQ(q.at((prioLvl + 1)), q.at(prioLvl));
                      
            sysQuantum = quantum;   // resets quantum

            std::cout << "\nquantum reset:" << std::endl;
            displayContent(q);
          }
        }
        
        /* execution of process and display on graph; increments priority level if 
           current level is empty */
        if (!q.at(prioLvl).empty()) {
          q.at(prioLvl).front().processing();
          
          // display purposes, multiplies 2 to ID to find number of spaces for "X"
          int spacing = 2 * (q.at(prioLvl).front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }
        
        /* exe process in high prio q*/
        if (q.at(prioLvl).front().getLength() == 0) {
          q.at(prioLvl).pop();
          numProc--;
          sysQuantum = quantum + 1;
        }
        
        counter++;
        sysQuantum--;
      } while (!q.at(0).empty() || !q.at(1).empty() 
               || !q.at(2).empty() || !admittance.empty());
    } // end QQQ();
    
    
    /**
     * @brief displays the contents of all the queues in provided vector
     * 
     * @param q 
     */
    void displayContent(std::vector<priority> q) {

      int prioSize = q.size();                      // size of vector
      for (int i = 0; i < prioSize; i++) {          // traveres through elements of vector
        std::cout << "Queue " << i << ": ";

        int queueSize = q.at(i).size();          // size of queue at position i in vector
        for (int j = 0; j < queueSize; j++) {       // traverses queue and prints content
          std::cout << q.at(i).front().getName();
          std::cout << q.at(i).front().getLength();
          q.at(i).pop();
          std::cout << " ";
        }
        
        std::cout << std::endl;
      }
      std::cout << std::endl;
    } // end display()
};