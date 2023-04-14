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


//generate a schedule with completely random values
Schedule generateSchedule() {
    Schedule generatedSchedule;
    vector<Activity> activityList = getActivities();

    //randomize the activities
    for (int i = 0; i < numActivities; i++) {
        generatedSchedule.activities.push_back(activityList[i]);
        generatedSchedule.activityNames[i] = activityList[i].getName();
        generatedSchedule.activityFacilitator[i] = facilitators[rand() % numFacilitators];
        generatedSchedule.activityRoom[i] = rooms[rand() % numRooms];
        generatedSchedule.activityTime[i] = timeSlots[rand() % numTimeSlots];
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
    TODO    + If any facilitator scheduled for consecutive time slots: Same rules as for SLA 191 and SLA
    TODO      101 in consecutive time slots—see below

    TODO    -In this case only (consecutive time slots), one of the activities is in Roman or Beach,
        and the other isn’t: -0.4
    TODO        -It’s fine if neither is in one of those buildings, of activity; we just want to avoid having
            consecutive activities being widely separated.
    */
    double fitness = 0.0;

    set<pair<string, string>> seenFacilitators;
    map<string, int> frequencyMap;
    for (int i = 0; i < numActivities; i++) {
        //-------------------Overlapping Room time------------------------
        for (int j = 0; j < i; j++) {
            if ((schedule.activityRoom[i] == schedule.activityRoom[j]) && schedule.activityTime[i] == schedule.activityTime[j]) {
                fitness -= 0.5;
            }
        }
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
        else {                 
            fitness += 0.2;    
        }                      
        seenFacilitators.insert({ schedule.activityFacilitator[i], schedule.activityTime[i] });



    }
    //============ACTIVITY SPECIFIC ADJUSTMENTS========
    //the 2 sections of SLA101 are more than 4 hours apart +0.5
    if ((schedule.activityTime[0] == "10 AM" && schedule.activityTime[1] == "3 PM") || (schedule.activityTime[1] == "10 AM" && schedule.activityTime[0] == "3 PM")) {
        fitness += 0.5;
    }
    //both sections of SLA101 are in the same time slot -0.5
    if (schedule.activityTime[0] == schedule.activityTime[1]) {
        fitness -= 0.5;
    }
    //the 2 sections of SLA191 are more than 4 hours apart +0.5
    if ((schedule.activityTime[2] == "10 AM" && schedule.activityTime[3] == "3 PM") || (schedule.activityTime[3] == "10 AM" && schedule.activityTime[2] == "3 PM")) {
        fitness += 0.5;
    }
    //both sections of SLA191 are in the same time slot -0.5
    if (schedule.activityTime[2] == schedule.activityTime[3]) {
        fitness -= 0.5;
    }
    //a section of SLA191 and a section of SLA101 are overseen in consecutive time slots +0.5
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[0])-timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[2]) - timeSlots.begin()))==1) {
        fitness += 0.5;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[0]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[3]) - timeSlots.begin())) == 1) {
        fitness += 0.5;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[1]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[2]) - timeSlots.begin())) == 1) {
        fitness += 0.5;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[1]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[3]) - timeSlots.begin())) == 1) {
        fitness += 0.5;
    }

    //a section of SLA191 and a section of SLA101 are taught separated by 1 hour +0.25
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[0]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[2]) - timeSlots.begin())) == 2) {
        fitness += 0.25;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[0]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[3]) - timeSlots.begin())) == 2) {
        fitness += 0.25;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[1]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[2]) - timeSlots.begin())) == 2) {
        fitness += 0.25;
    }
    if (abs((find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[1]) - timeSlots.begin()) - (find(timeSlots.begin(), timeSlots.end(), schedule.activityTime[3]) - timeSlots.begin())) == 2) {
        fitness += 0.25;
    }

    //a section of SLA191 and a section of SLA101 are taught in the same time slot -0.25
    if (schedule.activityTime[0] == schedule.activityTime[2]) {
        fitness -= 0.25;
    }
    if (schedule.activityTime[0] == schedule.activityTime[3]) {
        fitness -= 0.25;
    }
    if (schedule.activityTime[1] == schedule.activityTime[2]) {
        fitness -= 0.25;
    }
    if (schedule.activityTime[1] == schedule.activityTime[3]) {
        fitness -= 0.25;
    }

    // activity facilitator is scheduled to oversee more than 4, or 1 or 2
    for (auto const& pair : seenFacilitators) {
        frequencyMap[pair.first]++;
    }

    for (auto const& entry : frequencyMap) {
        if (entry.second > 4) {
            fitness -= 0.5;
        }
        else if ((entry.second == 1 || entry.second == 2) && entry.first!="Tyler") {
            fitness -= 0.4;
        }
    }

    return fitness;
}

//this function was written with help from ChatGPT, as I could not find a built-in softmax
//takes a vector of scores and performs softmax functionality
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

//creates a new schedule by combining random elements from the two schedules
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
        child.activities.push_back(parent1.activities[i]); //take activities from parent 1, as they will always be the same
        
        if (rand() % 2 == 0) {
            child.activityFacilitator[i] = parent1.activityFacilitator[i];
        }
        else {
            child.activityFacilitator[i] = parent2.activityFacilitator[i];
        }
        if (rand() % 2 == 0) {
            child.activityRoom[i] = parent1.activityRoom[i];
        }
        else {
            child.activityRoom[i] = parent2.activityRoom[i];
        }
        if (rand() % 2 == 0) {
            child.activityTime[i] = parent1.activityTime[i];
        }
        else {
            child.activityTime[i] = parent2.activityTime[i];
        }

        // Apply mutation
        if (rand() < mutationRate * RAND_MAX) {
            // Mutate the activityFacilitator
            child.activityFacilitator[i] = facilitators[rand() % numFacilitators];
            // Mutate the activityRoom
            child.activityRoom[i] = rooms[rand() % numRooms];
            // Mutate the activityTime
            child.activityTime[i] = timeSlots[rand() % numTimeSlots];
        }
    }

    // Set the score to zero
    child.score = 0.0;

    return child;
}
//takes the vector of already culled parents, breeds them together, and outputs a new generation that includes the parents
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


//============================================= main =============================================

int main()
{
    srand(time(0));
    int popSize = 600;
    int numGenerations = 150;

    double mutationRate = 0.01;

    vector<double> scheduleScores; //initialize a vector for scores
    vector<Schedule> population = initializePopulation(popSize); //generate a random population of schedules

    for (int i = 0; i < numGenerations; i++) {
        cout << "Creating new generation: " << i + 1 << "\n";
        mutationRate -= 0.0001;

        scheduleScores.clear();
        for (int j = 0; j < population.size(); j++) { //run the fitness function on each schedule and insert it into the scheduleScores vector
            scheduleScores.push_back(fitnessFunction(population[j]));
        }
        vector<double> x = softmax(scheduleScores); //convert the scores using softmax
        for (int k = 0; k < population.size(); k++) { //set the scores of the schedule objects to the resulting softmax values
            population.at(k).score = x.at(k);
        }
        vector<Schedule> y = cullHalf(population); //remove the lower half of the population based on their scores
        population.clear();
        population = produceNewGeneration(y,mutationRate); // produce a new generation z
    }

    //find the highest scoring schedule from the last generation
    double bestScore = 0.0;
    int bestScoreIndex = 0;
    for (int i = 0; i < population.size(); i++) {
        double tempScore= fitnessFunction(population[bestScoreIndex]);
        if (tempScore > bestScore) {
            bestScore = tempScore;
            bestScoreIndex = i;
        }
    }
    double endScore = 0.0f;
    endScore = fitnessFunction(population[bestScoreIndex]);
    
    //output the schedule to a file with formatting
    ofstream outputFile("Schedule.txt");
    outputFile << left << setw(10) << "ClassID" << " " << left << setw(12) << "Facilitator" << " " << left << setw(15) << "Classroom" << " " << left << setw(10) << "Time" << "\n-----------------------------------------------\n";
    for (int i = 0; i < numActivities; i++) {
        outputFile << left << setw(10) << population[bestScoreIndex].activityNames[i] << " " << left << setw(12) << population[bestScoreIndex].activityFacilitator[i] << " " << left << setw(15) << population[bestScoreIndex].activityRoom[i].first << " " << left << setw(10) << population[bestScoreIndex].activityTime[i];
        outputFile << "\n";
    }
    //outputFile << "\nThe score for this schedule is " << endScore;
    outputFile << "\nThe score for this schedule is " << endScore;
    cout << "\n=========================================================\n                    Schedule comeplete! \n  Check for file Schedule.txt for the complete schedule\n=========================================================\n";
}
