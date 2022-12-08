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

void fileToVector(std::string, std::vector<Job> &);
void displayJobNames(std::vector<Job>);
void roundRobin(std::vector<Job>);

int main(int argc, char *argv[]) {
  
  /* read in file */
  std::vector<Job> jobList;
  fileToVector(argv[1], jobList);
  
  std::string selectedAlgo = argv[2]; // 2nd arguement selecting algo

  /* depending on cli argument, selections algo*/
  if (selectedAlgo.compare("RR") == 0) {roundRobin(jobList);}
  else if (selectedAlgo.compare("SRT")) {}
  else if (selectedAlgo.compare("FB")) {}
  else if (selectedAlgo.compare("ALL")) {}
  else {}
}   // end main()


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
  
  // std::cout << "reading file..." << std::endl;

  /* reads from file, initializes the Job, and places the Job in vector */
  while (inF >> name >> admitted >> length) {
    Job admittingJob(name, admitted, length);
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
  for (int i = 0; i < jobList.size(); i++) {
    if ((i + 1) != jobList.size()) std::cout << jobList.at(i).getName() << " ";
    else std::cout << jobList.at(i).getName() << std::endl;
  }
} // end displayJobNames()


void roundRobin(std::vector<Job> jobList) {
    RR rr(jobList);

    /* prompt for quantum size*/
    std::cout << "Enter a nonnegative integer to set quantum ";
    std::cout << "(entering nothing defaults to 2): ";
    
    /* receives terminal input, and assigns quantum size*/
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) rr.requestQuantum(stoi(input));
    
    displayJobNames(jobList);
}