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
#include <set>
#include <map>

//#include <cmath>
//#include <algorithm>
//#include <cstdlib>

//#include <sstream>
//#include <iomanip>

using namespace std;

//============================================= constants =============================================
const int numTimeSlots = 6;
const int numActivities = 11;
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
    int getExpectedEnrollment() {
        return expEnrollment;
    }
    vector<string> getPreferredFacilitators() {
        return prefFacilitators;
    }
    vector<string> getOtherFacilitators() {
        return othFacilitators;
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
    double score;
    vector<Activity> activities;
    string activityNames[numActivities];
    string activityFacilitator[numActivities];
    pair<string, int> activityRoom[numActivities];
    string activityTime[numActivities];

};

//============================================= functions =============================================

//returns an array containing all of the activities
vector<Activity> getActivities() {
    vector<Activity> activityList;

    //SLA100A
    vector<string> SLA100APrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA100AOthFacilitators = { "Numen", "Richards" };
    Activity SLA100A("SLA100A", 50, SLA100APrefFacilitators, SLA100AOthFacilitators);
    activityList.push_back(SLA100A);

    //SLA100B
    vector<string> SLA100BPrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA100BOthFacilitators = { "Numen", "Richards" };
    Activity SLA100B("SLA100B", 50, SLA100BPrefFacilitators, SLA100BOthFacilitators);
    activityList.push_back(SLA100B);

    //SLA191A
    vector<string> SLA191APrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA191AOthFacilitators = { "Numen", "Richards" };
    Activity SLA191A("SLA191A", 50, SLA191APrefFacilitators, SLA191AOthFacilitators);
    activityList.push_back(SLA191A);

    //SLA191B
    vector<string> SLA191BPrefFacilitators = { "Glen", "Lock", "Banks", "Zeldin" };
    vector<string> SLA191BOthFacilitators = { "Numen", "Richards" };
    Activity SLA191B("SLA191B", 50, SLA191BPrefFacilitators, SLA191BOthFacilitators);
    activityList.push_back(SLA191B);

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

//generate a schedule with completely random values
Schedule generateSchedule() {
    Schedule generatedSchedule;
    
    vector<Activity> activityList = getActivities();

    //randomize placement of the activities
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activities.push_back(activityList[i]);
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

//prints out all the information about a schedule.
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

//determines the fitness score of a schedule.
double fitnessFunction(Schedule schedule) {

    /*
    For each activity, fitness starts at 0.
    - Activity is scheduled at the same time in the same room as another of the activities : -0.5
    %- Room size :
    %    + Activities is in a room too small for its expected enrollment : -0.5
    %    + Activities is in a room with capacity > 3 times expected enrollment : -0.2
    %    + Activities is in a room with capacity > 6 times expected enrollment : -0.4
    %    + Otherwise + 0.3
    %- Activities is overseen by a preferred facilitator : +0.5
    %- Activities is overseen by another facilitator listed for that activity : +0.2
    %- Activities is overseen by some other facilitator : -0.1
    - Facilitator load :
    TOFIX    + Activity facilitator is scheduled for only 1 activity in this time slot : +0.2
    %    + Activity facilitator is scheduled for more than one activity at the same time : -0.2
    %    + Facilitator is scheduled to oversee more than 4 activities total : -0.5
    %    + Facilitator is scheduled to oversee 1 or 2 activities * : -0.4
    TODO        Exception: Dr. Tyler is committee chair and has other demands on his time.
    TODO        *No penalty if he’s only required to oversee < 2 activities.
    TODO    + If any facilitator scheduled for consecutive time slots: Same rules as for SLA 191 and SLA
    TODO      101 in consecutive time slots—see below
    */

    double fitness = 0.0;

    set<pair<string, string>> seenFacilitators;
    map<string, int> frequencyMap;

    for (int i = 0; i < numActivities; i++) {
        //-------------------Overlapping Room time------------------------
        //TO DO!!!!!!!!!!!
        //--------------------------Room Size-----------------------------
        

        if (schedule.activityRoom[i].second < schedule.activities[i].getExpectedEnrollment()) {
            fitness -= 0.5;
        }
        else if (schedule.activityRoom[i].second > (6 * schedule.activities[i].getExpectedEnrollment())) {
            fitness -= 0.4;
        }
        else if (schedule.activityRoom[i].second > (3 * schedule.activities[i].getExpectedEnrollment())) {
            fitness -= 0.2;
        }
        else {
            fitness += 0.3;
        }
        //--------------------Facilitator Preferences---------------------
        vector<string> preferredFacilitators = schedule.activities[i].getPreferredFacilitators();
        vector<string> otherFacilitators = schedule.activities[i].getOtherFacilitators();

        if (find(preferredFacilitators.begin(), preferredFacilitators.end(), schedule.activityFacilitator[i]) != preferredFacilitators.end()) {
            fitness += 0.5;
        }
        else if (find(otherFacilitators.begin(), otherFacilitators.end(), schedule.activityFacilitator[i]) != otherFacilitators.end()) {
            fitness += 0.2;
        }
        else {
            fitness -= 0.1;
        }
        //-----------------------Facilitator Load-------------------------
        

        if (seenFacilitators.count({ schedule.activityFacilitator[i], schedule.activityTime[i]})) {
            fitness -= 0.2;
        }
        else {                 //
            fitness += 0.;    // THIS ELSE STATEMENT IS A MAKESHIFT WAY OF IMPLEMENTING ACTIVITY FACILITATOR IS SCHEDULED FOR ONLY 1 ACTIVITY IN THIS TIME SLOT. IT IS NOT CORRECT.
        }                      //
        seenFacilitators.insert({ schedule.activityFacilitator[i], schedule.activityTime[i] });



        // ACTIVITY SPECIFIC ADJUSTMENTS ALSO NEEDED!!!!!!!!!!!!!!
    }

    // activity facilitator is scheduled to oversee more than 4, or 1 or 2
    for (auto const& pair : seenFacilitators) {
        frequencyMap[pair.first]++;
    }

    for (auto const& entry : frequencyMap) {
        if (entry.second > 4) {
            fitness -= 0.5;
        }
        else if (entry.second == 1 || entry.second == 2) {
            fitness -= 0.4;
        }
    }

    return fitness;
}

//code from ChatGPT, as I am not familiar with the softmax function.
vector<double> softmax(const vector<double>& x) {
    vector<double> y(x.size());
    double sum = 0.0;
    for (int i = 0; i < x.size(); ++i) {
        y[i] = std::exp(x[i]);
        sum += y[i];
    }
    transform(y.begin(), y.end(), y.begin(), [sum](double v) { return v / sum; });
    return y;
}

//compares 2 schedules by their scores.
bool compareByScore(const Schedule& scheduleA, const Schedule& scheduleB) {
    return scheduleA.score > scheduleB.score;
}

//take a vector full of all the schedules, sort them by their scores, and return a vector with half the size of the input of the schedules with the higher scores.
vector<Schedule> cullHalf(vector<Schedule> population) {
    int newPopSize = population.size() / 2;
    sort(population.begin(), population.end(), compareByScore);
    while (population.size() > newPopSize) {
        population.pop_back();
    }
    return population;
}


Schedule breedSchedules(const Schedule& parent1, const Schedule& parent2, double mutationRate) {
    // Create a new child schedule
    Schedule child;

    // Copy the activity names from one of the parents
    for (int i = 0; i < numActivities; i++) {
        child.activityNames[i] = parent1.activityNames[i];
    }

    // Randomly select activities from each parent
    for (int i = 0; i < numActivities; i++) {
        // Randomly choose which parent to take the activity from
        if (rand() % 2 == 0) {
            child.activities.push_back(parent1.activities[i]);
            child.activityFacilitator[i] = parent1.activityFacilitator[i];
            child.activityRoom[i] = parent1.activityRoom[i];
            child.activityTime[i] = parent1.activityTime[i];
        }
        else {
            child.activities.push_back(parent2.activities[i]);
            child.activityFacilitator[i] = parent2.activityFacilitator[i];
            child.activityRoom[i] = parent2.activityRoom[i];
            child.activityTime[i] = parent2.activityTime[i];
        }

        // Apply mutation
        if (rand() < mutationRate * RAND_MAX) {
            // Mutate the activityFacilitator
            child.activityFacilitator[i] = facilitators[rand() % numFacilitators];
            // Mutate the activityRoom
            child.activityRoom[i] = rooms[rand() % numRooms];
            // Mutate the activityTime
            child.activityTime[i] = timeSlots[rand() % numTimeSlots] ;
        }
    }

    // Set the score to zero
    child.score = 0.0;

    return child;
}

vector<Schedule> produceNewGeneration(vector<Schedule> parents, double mutationRate) {
    vector<Schedule> children;
    for (int i = 0; i < parents.size()-1; i += 2) {
        children.push_back(parents[i]);
        children.push_back(parents[i + 1]);
        children.push_back(breedSchedules(parents[i], parents[i + 1], mutationRate));
        children.push_back(breedSchedules(parents[i], parents[i + 1], mutationRate));
    }
    return children;
}

/*
Schedule createSchedule() {
    int popSize = 100;
    vector<double> scheduleScores; //initialize a vector for scores

    vector<Schedule> population = initializePopulation(popSize); //generate a random population of schedules
    for (int i = 0; i < popSize; i++) { //run the fitness function on each schedule and insert it into the scheduleScores vector
        scheduleScores.push_back(fitnessFunction(population[i]));
    }
    vector<double> x = softmax(scheduleScores); //convert the scores using softmax
    for (int i = 0; i < popSize; i++) { //set the scores of the schedule objects to the resulting softmax values
        population.at(i).score = x.at(i);
    }
    vector<Schedule> y = cullHalf(population); //remove the lower half of the population based on their scores


    vector<Schedule> z = produceNewGeneration(y); // produce a new generation z
}
*/



//============================================= main =============================================

int main()
{
    srand(time(0));
    //createSchedule();
    int popSize = 500;
    int numGenerations = 100;

    double mutationRate = 0.01;

    vector<double> scheduleScores; //initialize a vector for scores
    vector<Schedule> population = initializePopulation(popSize); //generate a random population of schedules






    for (int i = 0; i < numGenerations; i++) {
        mutationRate -= 0.0002;

        scheduleScores.clear();
        for (int j = 0; j < population.size(); j++) { //run the fitness function on each schedule and insert it into the scheduleScores vector
            scheduleScores.push_back(fitnessFunction(population[j]));
        }
        vector<double> x = softmax(scheduleScores); //convert the scores using softmax
        for (int k = 0; k < population.size(); k++) { //set the scores of the schedule objects to the resulting softmax values
            population.at(k).score = x.at(k);
        }
        vector<Schedule> y = cullHalf(population); //remove the lower half of the population based on their scores
        //vector<Schedule> y = population;

        for (int l = 0; l < population.size(); l++) { //output the schedules so i can see
            cout << "\n\nThe schedule of child " << l << "\n";
            printSchedule(population[l]);
            cout << "\nThe score for this schedule is \n" << population[l].score << "\n\n";
        }
        population.clear();
        population = produceNewGeneration(y,mutationRate); // produce a new generation z
    }

    double bestScore = 0.0;
    int bestScoreIndex = 0;
    for (int i = 0; i < population.size(); i++) {
        if (population[i].score > bestScore) {
            bestScore = population[i].score;
            bestScoreIndex = i;
        }
    }
    
    ofstream outputFile("Schedule.txt");
    outputFile << left << setw(10) << "ClassID" << " " << left << setw(12) << "Facilitator" << " " << left << setw(15) << "Classroom" << " " << left << setw(10) << "Time" << "\n-----------------------------------------------\n";
    for (int i = 0; i < numActivities; i++) {
        outputFile << left << setw(10) << population[bestScoreIndex].activityNames[i] << " " << left << setw(12) << population[bestScoreIndex].activityFacilitator[i] << " " << left << setw(15) << population[bestScoreIndex].activityRoom[i].first << " " << left << setw(10) << population[bestScoreIndex].activityTime[i];
        outputFile << "\n";
    }
    outputFile << "\nThe score for this schedule is " << population[bestScoreIndex].score;



    /*
    scheduleScores.clear();

    cout << "\n\n\n scores: \n";
    for (int p = 0; p < population.size(); p++) {
        scheduleScores.push_back(fitnessFunction(population[p]));
    }
    vector<double> x = softmax(scheduleScores); //convert the scores using softmax
    for (int k = 0; k < population.size(); k++) { //set the scores of the schedule objects to the resulting softmax values
        population.at(k).score = x.at(k);
        cout << population[k].score << "\n";
    }

    cout << "AAAAAAAAA \n";
    printSchedule(population[3]);
    cout << population[3].score;
    */


    /*
    for (int i = 0; i < popSize; i++) {
        printSchedule(population[i]);
        scheduleScores.push_back(fitnessFunction(population[i]));

        cout << "\n" << fitnessFunction(population[i]);
        cout << "\n\n";
    
    }
    */
    
    /*
    cout << "\nThe softmax values for the schedules are: \n";

    for (int i = 0; i < x.size(); i++) {
        cout << population.at(i).score << "\n";
    }
    */
    
    //cout << "\n\nThe softmax values AFTER culling are: \n";
    // 
    //for (int i = 0; i < y.size(); i++) {
    //    cout << y.at(i).score << "\n";
    //}

    //cout << "This schedule: \n\n";
    //printSchedule(y.at(0));
    //cout << "Is bred with this schedule: \n\n";
    //printSchedule(y.at(1));
    //cout << "To produce this schedule: \n\n";
    //printSchedule(breedSchedules(y.at(0), y.at(1)));
    
    //while (!scheduleScores.empty()) {
    //    scheduleScores.pop_back();
    //}

    

    //cout << "\nThe softmax values for the schedules are: \n";
    //for (int i = 0; i < z.size(); i++) {
    //    scheduleScores.push_back(fitnessFunction(z[i]));
    //}
    //
    //vector<double> d = softmax(scheduleScores);
    //
    //for (int i = 0; i < popSize; i++) {
    //    z.at(i).score = d.at(i);
  //  }
//
    //for (int i = 0; i < z.size(); i++) {
    //    cout << z.at(i).score << "\n";
    //}

}
