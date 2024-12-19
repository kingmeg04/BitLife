//
// Created by jbrui on 17.12.2024.
//

#include "PlayerStuff.h"

using namespace std;

void player::newJob(job newJob) {
    this->vPrevJobs.push_back(this->jCurrentJob);
    for(int i; i < this->vPrevJobs.size(); i++){
        if(this->vPrevJobs[i].sName == newJob.sName){
            this->vPrevJobs.pop_back();
            break;
        }
    }
    this->jCurrentJob = newJob;
}

void player::useItem(item itemUsed, int amountUsed) {
    for(int items = 0; items < this->vItems.size(); items++) {
        if(this->vItems[items].first.sItemName == itemUsed.sItemName){
            if(this->vItems[items].second -= amountUsed >= 0) {
                this->vItems[items].second -= amountUsed;
            }
            else {
                cout << "You don't have enough of the item " << itemUsed.sItemName << " to perform this action." << endl;
            }
            break;
        }
    }
    cout << "You don't have enough of the item " << itemUsed.sItemName << " to perform this action." << endl;
}

