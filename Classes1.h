//
// Created by jbrui on 03.12.2024.
//

#ifndef CLASSES1_H
#define CLASSES1_H

#endif //CLASSES1_H

#include <array>
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
    bool bIsAdmin;
    short sSalary;
    short sMentalInstability;

    public:
      Job(bool IsAdmin, unsigned short Salary, short MentalInstability){
      this->bIsAdmin = IsAdmin;
      this->sSalary = Salary;
      this->sMentalInstability = MentalInstability;
      };

      int getPaid(int iMoney){
        return iMoney += sSalary;
      }

};

class IllegalStuff : public Job {
  short sShadyness;
  short sIllegalness;

  public:
    IllegalStuff(bool IsAdmin, unsigned short Salary, short MentalInstability, unsigned short Shadyness, unsigned short Illegalness)
    : Job(IsAdmin, Salary, MentalInstability){
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