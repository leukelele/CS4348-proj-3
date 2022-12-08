#include <iostream>
#include <fstream>
#include <queue>

#include "Job.hpp"
#include "RR.hpp"


void fileToQ(std::string, std::queue<Job> &);

int main(int argc, char *argv[]) {

  std::queue<Job> jobList;
  fileToQ(argv[1], jobList);
  
  std::string selectedAlgo = argv[2];
  if (selectedAlgo.compare("RR")) {}
  else if (selectedAlgo.compare("SRT")) {}
  else if (selectedAlgo.compare("FB")) {}
  else if (selectedAlgo.compare("ALL")) {}
  else {}
  
}   // end main()


/**
 * @brief Reads from file and intiializes a Job class from the information. The class is then placed in 
 * a queue.
 * 
 * @param fileName 
 * @param jobList 
 */
void fileToQ(std::string fileName, std::queue<Job> &jobList) {

  std::ifstream inF;
  inF.open(fileName);
  
  /* error checking: file opened successfully */
  if (!inF) {
    std::cerr << "There was an error opening the file. Does the file exist?" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  /* initialization of variables to describe individual job */
  char name;
  unsigned short admitted;
  unsigned short length;
  
  // std::cout << "reading file..." << std::endl;
  /* reads from file, initializes the Job, and places the Job in queue*/
  while (inF >> name >> admitted >> length) {
    Job admittingJob(name, admitted, length);
    jobList.push(admittingJob);
  }

  //std::cout << "closing file..." << std::endl;
  inF.close();
}   // end readInputFile()