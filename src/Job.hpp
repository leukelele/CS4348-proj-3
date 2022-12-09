#ifndef JOB_HPP
#define JOB_HPP

class Job {
  private:
    char name;                // name of the job
    unsigned int admitted;    // time the job was admitted
    unsigned int length;      // length of time required for the job
    unsigned int id;          // variable created to aid in display

  public:
    
    /* constructor */
    Job(char name, unsigned int admitted, unsigned int length, unsigned int id) {
      this->name = name;
      this->admitted = admitted;
      this->length = length;
      this->id = id;
    }
    
    /**
     * @brief simulates processing of a job
     * 
     * @return int
     */
    int processing() {

      /* decrements length but returns -1 if Job length is 0*/
      if (length == 0) {return -1;}
      length--;
      
      return 0;
    } // end processing()

    /**
     * @brief getter for private variables
     */
    char getName() {return name;}
    unsigned int getAdmitted() {return admitted;}
    unsigned int getLength() {return length;}
    unsigned int getID() {return id;}
};  // end Job

#endif 