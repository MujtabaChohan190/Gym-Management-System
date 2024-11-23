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

//Writing function to load members from file to process things
void loadMembersFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        file = fopen(FILE_NAME, "w");
        if (file == NULL) {
            printf("Error: Unable to create members file.\n");
            exit(1);
        }
        fclose(file);
        return;
    }

    memberCount = 0;
    Member member;
    while (fscanf(file, "%d,%49[^,],%19[^,],%d,%d,%d,%199[^\n]\n",
                  &member.id, member.name, member.membershipType,
                  &member.feesPaid, &member.attendance,
                  &member.paymentStatus, member.feedback) != EOF) {
        members[memberCount++] = member;
    }
    fclose(file);
}

//Writing function to save members to file
void saveMembersToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Unable to save members to file.\n");
        return;
    }

    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n", members[i].id, members[i].name, members[i].membershipType, members[i].feesPaid, members[i].attendance, members[i].paymentStatus, members[i].feedback);
    }   //fprintf used to write formatted output to the file 
    fclose(file);
}
