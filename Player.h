//
// Created by jbrui on 10.12.2024.
//
#include "Classes1.h"
#include <vector>

#ifndef PLAYER_H
#define PLAYER_H

#endif //PLAYER_H

class player{
  Job jCurrentJob;
  std::vector<Job> vPrevJobs;

  public:
    player();

    void newJob(Job newJob){
      vPrevJobs.push_back(jCurrentJob);
      for(int i; i < vPrevJobs.size(); i++){
        if(vPrevJobs[i].sName == newJob.sName){
          vPrevJobs.pop_back();
          break;
        };
      };
      jCurrentJob = newJob;
    };


};