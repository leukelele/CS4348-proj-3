#include <vector>
#include <queue>

#include "Job.hpp"

class RR {
  
  private:
    std::queue<Job> ready;
    
  public:
    
    /* constructor */
    RR(std::vector<Job> jobList) {}
};  // end RR