

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper( size_t row,
    size_t col,
    std::vector<size_t>& daysWorked, 
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched) {

        // if we made it through last row, return true
        if(row == avail.size()) {
            return true;
        }
        // if made it through all workers in day
        else if(col == dailyNeed) {
            return schedHelper(row+1, 0, daysWorked, avail, dailyNeed, maxShifts, sched);
        }
        // if within bounds, work needs to be done
        else {
            // iterate through each worker
            for(size_t worker = 0; worker <  avail[0].size(); worker++) {
                if((avail[row][worker] == 1) && (daysWorked[worker] < maxShifts)) {
                    // add worker to schedule if they're free
                    sched[row].push_back(worker);
                    // set their availability on current day to 0 since already assigned
                    avail[row][worker] = 0;
                    // record that given worker has worked one more day
                    daysWorked[worker]++;
                    // iterate to next assignment
                    if(schedHelper(row, col+1, daysWorked, avail, dailyNeed, maxShifts, sched) == true) {
                        return true;
                    }

                    // if it didn't work (we didn't return), revert changes
                    daysWorked[worker]--;
                    avail[row][worker] = 1;
                    sched[row].pop_back();
                }
            }
            // if we never returned, false
            return false;
        }

    }

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
    if(dailyNeed > avail[0].size()) {
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<size_t> daysWorked;
    for(size_t i = 0; i < avail[0].size(); i++) {
        daysWorked.push_back(0);
    }
    

    for(size_t i = 0; i < avail.size(); i++) {
        std::vector<Worker_T> workers1;
        sched.push_back(workers1);
    }
    AvailabilityMatrix temp_avail = avail;
    return schedHelper(0, 0, daysWorked, temp_avail, dailyNeed, maxShifts, sched);
}

