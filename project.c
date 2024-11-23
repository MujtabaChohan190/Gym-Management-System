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
    } //fscanf reads data from file in a loop until it reaches EOF
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

// Writing function to Add a new member
void addMember() {
    if (memberCount >= 100) {
        printf("Member limit reached. Cannot add more members.\n");
        return;
    }

    Member m; // I created m variable as temporary variable to store user input
    printf("Enter Member ID: ");
    scanf("%d", &m.id);
    getchar(); // Consume the newline left by scanf so that fgets read the name string

    printf("Enter Name: ");
    fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = '\0'; // Remove newline

    printf("Enter Membership Type (Monthly/Yearly): ");
    fgets(m.membershipType, sizeof(m.membershipType), stdin);
    m.membershipType[strcspn(m.membershipType, "\n")] = '\0';

    m.feesPaid = 0;
    m.attendance = 0;
    m.paymentStatus = false;
    strcpy(m.feedback, "");

    members[memberCount++] = m;
    saveMembersToFile();
    printf("Member added successfully!\n");
    pressAnyKey(); //This function waits for the user to press any key to continue.
}
