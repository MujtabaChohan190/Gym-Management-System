#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Structure for members
typedef struct {
    int id;
    char name[50];
    char membershipType[20]; 
    int feesPaid;           
    int attendance;          
    char feedback[200];      
    bool paymentStatus;      
} Member;

// Structure for trainers
typedef struct {
    int id;
    char name[50];
    int assignedMembers[10]; // Max of 10 members per trainer
    int assignedCount;
} Trainer;

// Global variables
Member members[100];
Trainer trainers[10];
int memberCount = 0;
int trainerCount = 0;
const char *FILE_NAME = "members.txt";

// Function prototypes
void loadMembersFromFile();
void saveMembersToFile();
void loginSystem();
void mainMenu();
void addMember();
void viewMembers();
void updateMember();
void deleteMember();
void searchMember();
void assignMembersToTrainers();
void attendanceTracking();
void upgradeDowngradeMembership();
void automaticFeeCalculation();
void memberFeedback();
void generateReports();
void pressAnyKey();
int findMemberIndex(int id);

int main() {
    loadMembersFromFile();
    loginSystem();
    mainMenu();
    return 0;
}
