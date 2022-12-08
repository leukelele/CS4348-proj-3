#ifndef JOB_HPP
#define JOB_HPP

class Job {
  private:
    char name;                  // name of the job
    unsigned short admitted;    // time the job was admitted
    unsigned short length;      // length of time required for the job

  public:
    
    /* constructor */
    Job(char name, unsigned short admitted, unsigned short length){
      this->name = name;
      this->admitted = admitted;
      this->length = length;
    }
    
    /**
     * @brief simulates processing of a job
     * 
     * @return short 
     */
    short processing() {

      /* decrements length but returns -1 if Job length is 0*/
      if (length == 0) {return -1;}
      length--;
      
      return 0;
    } // end processing()

    /**
     * @brief getter for private variables
     */
    char getName() {return name;}
    unsigned short getAdmitted() {return admitted;}
    unsigned short getLength() {return length;}
};  // end Job

#endif 