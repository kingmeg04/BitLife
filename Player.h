//
// Created by jbrui on 10.12.2024.
//

#ifndef PLAYER_H
#define PLAYER_H



#include <vector>
#include "WorkLife.h"



class player{

  std::vector<Job> vPrevJobs;

  public:

  Job currentJob;
  long balance = 0;
  short saturation = 100;         // Hunger in %
  short mentalHealth = 100;   // Mental Health in %


    player(Job CurrentJob): currentJob(CurrentJob){

  } ;

    void newJob(Job newJob){
      vPrevJobs.push_back(currentJob);
      for(int i; i < vPrevJobs.size(); i++){
        if(vPrevJobs[i].sName == newJob.sName){
          vPrevJobs.pop_back();
          break;
        };
      };
      currentJob = newJob;
    };

};

#endif //PLAYER_H
