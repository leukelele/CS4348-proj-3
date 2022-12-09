/**
 * @file main.cpp
 * @brief Program simulates OS scheduling algorithms: Round Robin, Shortest Remaining
 * Time, and Feedback. Programm accepts two parameters upon execution:
 * - file: text file with jobs
 * - selected algorithm: RR, SRT, FB, or all algorithms
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>

#include "Job.hpp"
#include "RR.hpp"
#include "SRT.hpp"
#include "FB.hpp"

void fileToVector(std::string, std::vector<Job> &);
void displayJobNames(std::vector<Job>);
void roundRobin(std::vector<Job>);
void shortestRemainingTime(std::vector<Job>);
void feedBack(std::vector<Job>);

int main(int argc, char *argv[]) {
  
  /* read in file */
  std::vector<Job> jobList;
  fileToVector(argv[1], jobList);
  
  std::string selectedAlgo = argv[2]; // 2nd arguement selecting algo

  /* depending on cli argument, selects corresponding algo*/
  if (selectedAlgo.compare("RR") == 0) {roundRobin(jobList);}
  else if (selectedAlgo.compare("SRT") == 0) {shortestRemainingTime(jobList);}
  else if (selectedAlgo.compare("FB") == 0) {feedBack(jobList);}
  else if (selectedAlgo.compare("ALL") == 0) {
    roundRobin(jobList);
    std::cout << "\n" << std::endl;   // divider for visibility
    shortestRemainingTime(jobList);
    std::cout << "\n" << std::endl;
    feedBack(jobList);
  }
}   // end main()


// ==========================================================================================
// DON'T GO PAST THIS POINT, IT'S UGLY
//===========================================================================================
/**
 * @brief Reads from file and intiializes a Job class from the information. The class is then 
 * placed in a vector.
 * 
 * @param fileName 
 * @param jobList 
 */
void fileToVector(std::string fileName, std::vector<Job> &jobList) {

  std::ifstream inF;
  inF.open(fileName);
  
  /* error checking: file opened successfully */
  if (!inF) {
    std::cerr << "There was an error opening the file. Does the file exist?" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  /* initialization of variables to describe individual job */
  char name;
  unsigned int admitted;
  unsigned int length;
  unsigned int id = 0;

  /* reads from file, initializes the Job, and places the Job in vector */
  while (inF >> name >> admitted >> length) {
    Job admittingJob(name, admitted, length, id++);
    jobList.push_back(admittingJob);
  }

  //std::cout << "closing file..." << std::endl;
  inF.close();
}   // end readInputFile()

/**
 * @brief displays the job names
 * 
 * @param jobList 
 */
void displayJobNames(std::vector<Job> jobList) {
  
  /* iterates through the vector and calls getter for job name*/
  int listSize = jobList.size();
  for (int i = 0; i < listSize; i++) {
    if ((i + 1) != listSize) std::cout << jobList.at(i).getName() << " ";
    else std::cout << jobList.at(i).getName() << std::endl;
  }
} // end displayJobNames()

/**
 * @brief prompts for quantum size, processes information through Round Robin algorithm,
 * and displays result
 * 
 * @param jobList 
 */
void roundRobin(std::vector<Job> jobList) {
  RR rr(jobList);

  /* prompt for quantum size*/
  std::cout << "\nRR: Enter a nonnegative integer to set quantum size";
  std::cout << "(blank input defaults to 2): ";
  
  /* receives terminal input, and assigns quantum size */
  std::string input;
  std::getline(std::cin, input);
  if (!input.empty()) rr.requestQuantum(stoi(input));
  
  /* process and display */
  std::cout << "ROUND ROBIN:" << std::endl;
  displayJobNames(jobList);
  rr.circularQ();
} // end roundRobin()

/**
 * @brief prints heading specific to algorithm, then calls class, and subsequent functions
 * relating to Shortest Remaining Time algorithm
 * 
 * @param jobList 
 */
void shortestRemainingTime(std::vector<Job> jobList) {
  SRT srt(jobList);

  /* header for output*/
  std::cout << "\nSHORTEST REMAINING TIME:" << std::endl;
  displayJobNames(jobList);
  
  srt.shortestTimeQ();  // processing and output
} // end shortestRemainingTime()

void feedBack(std::vector<Job> jobList) {
  FB fb(jobList);

  /* prompt for quantum size*/
  std::cout << "\nFB: Enter a nonnegative integer to set quantum size ";
  std::cout << "(blank input defaults to 2): ";
  
  /* retrieves terminal input, and assigns quantum size */
  std::string input;
  std::getline(std::cin, input);
  if (!input.empty()) fb.requestQuantum(stoi(input));

  std::cout << "\nFEEDBACK:" << std::endl;
  displayJobNames(jobList);

  
    
} // end feedBack()