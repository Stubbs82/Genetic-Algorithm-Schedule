// AIProgram2.cpp
// Matthew Stubblefield
// CS 461

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <utility>
#include <array>
#include <iomanip>
//#include <cstdlib>

//#include <sstream>
//#include <iomanip>

using namespace std;

//============================================= constants =============================================
const int numTimeSlots = 6;
const int numActivities = 9;
const int numRooms = 9;
const int numFacilitators = 10;

const vector<string> facilitators = { "Lock", "Glen", "Banks", "Richards", "Shaw", "Singer", "Uther", "Tyler", "Numen", "Zeldin" };
const vector<pair<string, int>> rooms = { {"Slater 003", 45}, {"Roman 216", 30}, {"Loft 206", 75}, {"Roman 201", 50}, {"Loft 301", 108}, {"Beach 201", 60}, {"Beach 301", 75}, {"Logos 325", 450}, {"Frank 119", 60} };
const vector<string> timeSlots = { "10 AM", "11 AM", "12 PM", "1 PM", "2 PM", "3 PM" };

//============================================= objects =============================================
class Activity {
private:
    string name;
    int expEnrollment;

    //string facilitator;
    //string time;
    //pair<string, int> room;

    vector<string> prefFacilitators;
    vector<string> othFacilitators;
public:
    Activity(string activityName, int expectedEnrollment, vector<string> preferredFacilitators, vector<string> otherFacilitators) {
        name = activityName;
        expEnrollment = expectedEnrollment;
        prefFacilitators = preferredFacilitators;
        othFacilitators = otherFacilitators;
    }
    
    string getName() {
        return name;
    }

    /*
    void setTime(string activityTime) {
        time = activityTime;
    }

    void setRoom(pair<string, int> activityRoom) {
        room = activityRoom;
    }

    void setFacilitator (string activityFacilitator) {
        facilitator = activityFacilitator;
    }
    */
};


struct Schedule {
    string activityNames[numActivities];
    string activityFacilitator[numActivities];
    pair<string, int> activityRoom[numActivities];
    string activityTime[numActivities];

};

//============================================= functions =============================================

//returns an array containing all of the activities
vector<Activity> getActivities() {
    vector<Activity> activityList;

    //SLA100AB
    vector<string> SLA100ABPrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA100ABOthFacilitators = { "Numen", "Richards" };
    Activity SLA100AB("SLA100AB", 50, SLA100ABPrefFacilitators, SLA100ABOthFacilitators);
    activityList.push_back(SLA100AB);

    //SLA191AB
    vector<string> SLA191ABPrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA191ABOthFacilitators = { "Numen", "Richards" };
    Activity SLA191AB("SLA191AB", 50, SLA191ABPrefFacilitators, SLA191ABOthFacilitators);
    activityList.push_back(SLA191AB);

    //SLA201
    vector<string> SLA201PrefFacilitators = { "Glen", "Banks", "Zeldin", "Shaw" };
    vector<string> SLA201OthFacilitators = { "Numen", "Richards", "Singer" };
    Activity SLA201("SLA201", 50, SLA201PrefFacilitators, SLA201OthFacilitators);
    activityList.push_back(SLA201);

    //SLA291
    vector<string> SLA291PrefFacilitators = { "Lock", "Banks", "Zeldin", "Singer" };
    vector<string> SLA291OthFacilitators = { "Numen", "Richards", "Shaw", "Tyler" };
    Activity SLA291("SLA291", 50, SLA291PrefFacilitators, SLA291OthFacilitators);
    activityList.push_back(SLA291);

    //SLA303
    vector<string> SLA303PrefFacilitators = { "Glen", "Zeldin", "Banks" };
    vector<string> SLA303OthFacilitators = { "Numen", "Singer", "Shaw" };
    Activity SLA303("SLA303", 60, SLA303PrefFacilitators, SLA303OthFacilitators);
    activityList.push_back(SLA303);

    //SLA304
    vector<string> SLA304PrefFacilitators = { "Glen", "Banks", "Tyler" };
    vector<string> SLA304OthFacilitators = { "Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin" };
    Activity SLA304("SLA304", 25, SLA304PrefFacilitators, SLA304OthFacilitators);
    activityList.push_back(SLA304);

    //SLA394
    vector<string> SLA394PrefFacilitators = { "Tyler", "Singer" };
    vector<string> SLA394OthFacilitators = { "Richards", "Zeldin" };
    Activity SLA394("SLA394", 20, SLA394PrefFacilitators, SLA394OthFacilitators);
    activityList.push_back(SLA394);

    //SLA449
    vector<string> SLA449PrefFacilitators = { "Tyler", "Singer", "Shaw" };
    vector<string> SLA449OthFacilitators = { "Zeldin", "Uther" };
    Activity SLA449("SLA449", 60, SLA449PrefFacilitators, SLA449OthFacilitators);
    activityList.push_back(SLA449);

    //SLA451
    vector<string> SLA451PrefFacilitators = { "Tyler", "Singer", "Shaw" };
    vector<string> SLA451OthFacilitators = { "Zeldin", "Uther", "Richards", "Banks" };
    Activity SLA451("SLA451", 100, SLA451PrefFacilitators, SLA451OthFacilitators);
    activityList.push_back(SLA451);

    return activityList;
}

vector<Activity> randomizeVec(vector<Activity> activityList) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(activityList.begin(), activityList.end(), gen);
    return activityList;
}

vector<string> randomizeVec(vector<string> inputVec) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(inputVec.begin(), inputVec.end(), gen);
    return inputVec;
}

vector<pair<string, int>> randomizeVec(vector<pair<string, int>> inputVec) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(inputVec.begin(), inputVec.end(), gen);
    return inputVec;
}

Schedule generateSchedule() {
    Schedule generatedSchedule;
    
    vector<Activity> activityList = randomizeVec(getActivities());
    //vector<string> randFacilitators = randomizeVec(facilitators);
    //vector<pair<string, int>> randRooms = randomizeVec(rooms);
    //vector<string> randTimeSlots = randomizeVec(timeSlots);

    //randomize placement of the activities
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activityNames[i] = activityList[i].getName();
    }
    //randomly select the facilitator
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activityFacilitator[i] = facilitators[rand()%numFacilitators];
    }
    //randomly select the room
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activityRoom[i] = rooms[rand()%numRooms];
    }
    //randomly select the time
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activityTime[i] = timeSlots[rand()%numTimeSlots];
    }

    return generatedSchedule;
}

void printSchedule(Schedule scheduleToPrint) {
    for (int i = 0; i < numActivities; i++) {
        cout << left << setw(10) << scheduleToPrint.activityNames[i] << " " << left << setw(10) << scheduleToPrint.activityFacilitator[i] << " " << left << setw(15) << scheduleToPrint.activityRoom[i].first << " " << left << setw(10) << scheduleToPrint.activityTime[i];
        cout << "\n";
    }

}

//generate the popSize number of random schedules
vector<Schedule> initializePopulation(int popSize) {
    vector<Schedule> population;
    for (int i = 0; i < popSize; i++) {
        Schedule newSchedule = generateSchedule();
        population.push_back(newSchedule);
    }
    return population;
}


void fitnessFunction() {

}



//============================================= main =============================================

int main()
{
    srand(time(0));
    int popSize = 10;
    vector<Schedule> population = initializePopulation(popSize);
    for (int i = 0; i < popSize; i++) {
        printSchedule(population[i]);
        cout << "\n\n";
    }
}
