/**
 * @file FB.hpp
 * @brief collects preliminary information, then processes the information to produce a graphic
 * that reflects the shortest remaining time scheduler algorithm
 */
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
      int listSize = jobList.size();
      for (int i = 0; i < listSize; i++) {
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
          selectionSort(ready);                   // reorganize so shortest process executes first
          nextProc = admittance.front().getAdmitted();
        }
        
        /* decrements the time remaining for a process */
        if (!ready.empty()) {
          ready.front().processing();
          
          // display purposes, multiplies 2 to ID to find number of spaces before placing "X"
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
      int temp;                                  // temporary variable to contain index of min
      int inputSize = input.size();              // size of vector for traversal
      for (int i = 0; i < inputSize - 1; i++) {  // boundary that moves along vector
        int min = input.at(i).getLength();    // assumed min until proven otherwise
        
        /* compares subsequent elemnts*/
        temp = i;
        for (int j = (i + 1); j < inputSize; j++) {

          /* comparison between minimums */
          int newMin = input.at(j).getLength();
          if (min > newMin) {
            min = newMin;
            temp = j;
          }
        }  
        std::swap(input.at(i), input.at(temp)); // swap for the min val
      }
    } // end selectionSort()
};