#include <iostream>
#include <vector>
#include <queue>

#include "Job.hpp"
#include "popToQ.hpp"

class SRT {
  private:
    std::queue<Job> admittance;  // admits jobs from job list

  public:
    
    /* constructor */
    SRT(std::vector<Job> jobList) {
      acceptJobs(jobList);
    } // end constructor

    /*****************
     *               *
     *    MODIFER    *
     *               *
     *****************/
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
    
    /*******************************************
     *                                         *
     *    SHORTEST REMAINING TIME ALGORITHM    *
     *                                         *
     *******************************************/
    /**
     * @brief shortest remaining time algorithm, which is a scheduling algorithm
     * that prioritizes the exectuion of the process that takes the least amount of 
     * time; every admittance of a process into the ready queue requires reranking
     * of shortest algorithm which is implemented with a selection sort algorithm
     */
    void shortestTimeQ() {
      std::vector<Job> ready;                                     // ready "queue"
      unsigned int nextProc = admittance.front().getAdmitted();   // time of next process
      unsigned int counter = 0;                                   // system counter
      
      /* travereses through queue, that will is rearanged with each addition of a 
         process, and executes the process with the shortest length*/
      do {
        
        /* places admitting process into ready queue at the time it is admitted */
        if (counter == nextProc) {
          popToQ(ready, admittance);
          selectionSort(ready);
          nextProc = admittance.front().getAdmitted();
        }
        
        /* decrements the time remaining for a process */
        if (!ready.empty()) {
          ready.front().processing();
          
          // display purposes, multiplies 2 to ID to find number of spaces for "X"
          int spacing = 2 * (ready.front().getID());
          for (int i = 0; i < spacing; i++) std::cout << " ";
          std::cout << "X" << std::endl;
        }
        
        /* removes the element at the front of the queue if completed */
        if (ready.front().getLength() == 0) {
          ready.erase(ready.begin());
        }
        
        counter++;
      } while(!ready.empty() || !admittance.empty());
    } // end shortestTimeQ()
    
    /**
     * @brief sorts the algorithm smallest to greatest by comparing each
     * element with subsequent elements
     * 
     * @param input 
     */
    void selectionSort(std::vector<Job> &input) {
      int temp;
      for (int i = 0; i < input.size() - 1; i++) {  // boundary that moves along vector
        int min = input.at(i).getLength();        // assumed min until proven otherwise
        
        /* compares subsequent elemnts*/
        temp = i;
        for (int j = (i + 1); j < input.size(); j++) {
          if (min > input.at(j).getLength()) {
            min = input.at(j).getLength();  
            temp = j;
          }
        }  
        std::swap(input.at(i), input.at(temp)); // swap for the min val
      }
    } // end selectionSort()
};