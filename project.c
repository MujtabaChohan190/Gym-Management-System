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
//Writing function to view members
void viewMembers() {
    printf("\n========== MEMBERS LIST ==========\n");
    for (int i = 0; i < memberCount; i++) {
        printf("ID: %d, Name: %s, Membership Type: %s, Fees Paid: %d, Attendance: %d\n", members[i].id, members[i].name, members[i].membershipType, members[i].feesPaid, members[i].attendance);
    }
    pressAnyKey(); //This function is added to pause the program execution and wait for the user to press any key.
}
//Writing function to update members detail
void updateMember() {
    int id, found = 0;
    printf("Enter Member ID to update: ");
    scanf("%d", &id);
    getchar();  

    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id) {
            found = 1;
            printf("Enter new Name: ");
            fgets(members[i].name, 50, stdin);
            members[i].name[strcspn(members[i].name, "\n")] = 0;

            printf("Enter new Membership Type: ");
            fgets(members[i].membershipType, 20, stdin);
            members[i].membershipType[strcspn(members[i].membershipType, "\n")] = 0;

            printf("Enter new Fees Paid: ");
            scanf("%d", &members[i].feesPaid);
            members[i].paymentStatus = true;

            printf("Member updated successfully!\n");
            saveMembersToFile(); 
            break;
        }
    }

    if (!found) {
        printf("Member not found.\n");
    }
    pressAnyKey();
}
void deleteMember() {
    int id, found = 0;
    printf("Enter Member ID to delete: ");
    scanf("%d", &id);
    getchar();  

    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id) {
            found = 1;
            for (int j = i; j < memberCount - 1; j++) {
                members[j] = members[j + 1]; // Update the members index when a member is deleted
            }
            memberCount--; //reduces a member since a member is deleted
            saveMembersToFile(); //save the updated list of members to the file
            printf("Member deleted successfully!\n");
            break; //Exit the loop
        }
    }

    if (!found) {
        printf("Member not found.\n");
    }
    pressAnyKey(); //pause the program and wait for user to press any key to continue
}
void searchMember(){
    int id, found = 0;
    printf("Enter Member ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id) {
            found = 1;
            printf("ID: %d,name: %s,Membership type: %s, Fees Paid: %d, Attendance: %d\n",members[i].id,members[i].name,
            members[i].membershipType,members[i].feesPaid,members[i].attendance); //display searched member information
            break;
        } 
    }
    if (!found){
        printf("Member Not Found\n");
    }
    pressAnyKey();
}
void assignMembersToTrainers(){
    if(trainerCount==0){
        printf("No trainers available- Add trainer first");
        return;
    }

    int memberId, trainerId, Memberfound = 0, Trainerfound = 0;

    printf("Enter Member ID: ");
    scanf("%d", &memberId);

    printf("Enter Trainer ID: ");
    scanf("%d", &trainerId);

    for (int i = 0; i < memberCount; i++) { //checks and found the desired member id
        if (members[i].id == memberId) {
            Memberfound = 1;
            break;
        }
    }

    for (int i = 0; i < trainerCount; i++) {
        if (trainers[i].id == trainerId) {
            Trainerfound = 1;
            break;
        }
    }

        if (Memberfound && Trainerfound) {
        trainers[trainerId - 1].assignedMembers[trainers[trainerId - 1].assignedCount++] = memberId; //The member's id is added to the trainer's assignedMembers array
        printf("Member %d assigned to Trainer %d.\n", memberId, trainerId);
    } else {
        printf("Invalid Member ID or Trainer ID.\n");
    }
    pressAnyKey();
}
void attendanceTracking(){
    int id,found=0;
    printf("Enter ID for attendance to be marked");
    scanf("%d",&id);
    for(int i =0;i<memberCount;i++){
        if(members[i].id == id){
            found = 1;
            members[i].attendance++; //increment the attendance in members structure if id is found
            printf("Attendance marked for member %d.\n", id);
            saveMembersToFile(); //save the updated changes to the file
            break;
        }
    }

    if (!found) {
        printf("Member not found\n");
    }
    pressAnyKey();
}
void upgradeDowngradeMembership(){
    int id, found = 0;
    char NewMembType[20];

    printf("Enter Member ID to upgrade/downgrade membership: ");
    scanf("%d", &id);
    getchar(); //for newline character

    for (int i = 0; i < memberCount; i++) {
        if (members[i].id == id) {
            found = 1;
            printf("Enter new Membership Type (Monthly/Yearly): ");
            fgets(NewMembType, sizeof(NewMembType), stdin); //Inputs the New Membership Type into the variable NewMembType
            NewMembType[strcspn(NewMembType, "\n")] = '\0'; // Remove newline
            strcpy(members[i].membershipType, NewMembType); //copies the the newmembership type into the founded member's membershipType in members structure
            printf("Membership updated for member with ID: %d\n", id);
            saveMembersToFile();
            break;
        }
    }

    if (!found) {
        printf("Member not found.\n");
    }
    pressAnyKey();
}
