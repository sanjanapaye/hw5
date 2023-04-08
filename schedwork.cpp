#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool solveHelper(DailySchedule& sched,const AvailabilityMatrix& avail, size_t dailyNeed, size_t numdays, size_t numworkers, std::vector<size_t>& shiftcounts, int day, int worker, size_t maxShifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t numworkers = avail[0].size();

    size_t numdays = avail.size();
    
    std::vector<size_t> shiftcounts;
    int day=0;
    int worker = 0;
    for(int i = 0; i< numworkers; ++i){
        shiftcounts.push_back(0);
    } 
    sched.resize(numdays);
    for(int j = 0; j < numdays; ++j){
        sched[j].resize(dailyNeed);
    }

    return solveHelper(sched, avail, dailyNeed, numdays, numworkers, shiftcounts, day, worker, maxShifts);


}


bool solveHelper(DailySchedule& sched,const AvailabilityMatrix& avail, size_t dailyNeed, size_t numdays, size_t numworkers, std::vector<size_t>& shiftcounts, int day, int worker, size_t maxShifts){
    
    if (worker == dailyNeed){
        day ++;
        worker = 0;
    }
    if(day == numdays){
        return true;
    }
    
    for(size_t i = worker; i < numworkers; ++i){
        if(avail[day][i] == 1){
            if(shiftcounts[i]< maxShifts){
                sched[day][worker] = i;
                ++shiftcounts[i];
                if(solveHelper(sched, avail, dailyNeed, numdays, numworkers, shiftcounts, day, worker +1, maxShifts)){
                    return true;
                }
                sched[day][worker] = -1;
                shiftcounts[i]--;
                
            }
        }
    }
    return false;

    
}


