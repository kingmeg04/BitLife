//
// Created by jbrui on 03.12.2024.
//

#ifndef CLASSES1_H
#define CLASSES1_H

#endif //CLASSES1_H

#include <array>
#include <utility>
#include <vector>
#include <string>

/*enum jobs{
  HOMELESS,
  JOBLESS,
  WORKLESS,
  JANITOR,
  TEACHER,
  ADMIN,
  PASSWORDMAKER,
  PASSWORDMANAGER,
};*/

int prisonTime();
void addCrime();

struct Crime{
  short sIllegalness; //range from 1 - 1000
  float fWitnessability;
  std::string sName;
  short sTimesCommitted = 0;

};

class Job {
    //enum jobs eJob;
    bool bIsAdmin = false;
    short sSalary; //paid weekly
    short sMentalInstability; //range from 1 - 1000


    public:
    std::string sName;
      Job(short Salary, short MentalInstability, std::string Name){
        this->sSalary = Salary;
        this->sMentalInstability = MentalInstability;
        this->sName = std::move(Name);
      };

      int getPaid(int iMoney){
        return iMoney += sSalary;
      }

};

class IllegalStuff : public Job {
  short sShadyness;
  short sIllegalness;

  public:
    IllegalStuff(short Salary, short MentalInstability, std::string Name, short Shadyness, short Illegalness)
    : Job(Salary, MentalInstability, std::move(Name)){
      this->sShadyness = Shadyness;
      this->sIllegalness = Illegalness;
    }

    bool isCaught(int lawStrength){

      if(true)
        {
        return false;
      }
      else
        {
          return true;
      }
    }




};