#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_TRAINING 8

// Main menu and training menu (1D arrays)
const char *mainMenu[] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut"
};

const char *trainingMenu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Training status array ('N' = Not done, 'P' = Passed, 'F' = Failed)
char trainingStatus[NUM_TRAINING] = { 'N','N','N','N','N','N','N','N' };

void showMainMenu() {
    printf("\n--- Main Menu ---\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", mainMenu[i]);
    }
    printf("Enter choice (1-3) or '0', 'q', 'Q', [Enter] to quit: ");
}

void showTrainingMenu() {
    printf("\n--- Training Menu ---\n");
    for (int i = 0; i < NUM_TRAINING; i++) {
        printf("%s [%c]\n", trainingMenu[i], trainingStatus[i]);
    }
    printf("Select stage (1-8) or 0 to go back: ");
}

void handleTraining() {
    char input[10];

    while (1) {
        showTrainingMenu();
        fgets(input, sizeof(input), stdin);
        if (input[0] == '0' || input[0] == '\n') return;

        int choice = atoi(input);
        if (choice < 1 || choice > 8) {
            printf("Invalid stage. Choose between 1–8.\n");
            continue;
        }

        int index = choice - 1;

        // Restrict access by rules
        if (index == 1 && trainingStatus[0] != 'P') {
            printf("You must pass Stage 1 before accessing Stage 2.\n");
            continue;
        } else if (index >= 2 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P')) {
            printf("You must pass both Stage 1 and 2 before accessing Stage %d.\n", choice);
            continue;
        }

        if (trainingStatus[index] == 'P') {
            printf("This stage has already been passed. You cannot retake it.\n");
            continue;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (toupper(input[0]) == 'N') continue;

        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(input, sizeof(input), stdin);
        char result = toupper(input[0]);

        if (result == 'P' || result == 'F') {
            trainingStatus[index] = result;
            printf("Result recorded: %c for Stage %d\n", result, choice);
        } else {
            printf("Invalid input. Please enter 'P' or 'F'.\n");
        }
    }
}

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == '0' || tolower(input[0]) == 'q') {
            printf("Exiting program.\n");
            break;
        }

        int choice = atoi(input);
        switch (choice) {
            case 1:
                printf("Audition Management selected. (Not implemented)\n");
                break;
            case 2:
                handleTraining();
                break;
            case 3:
                printf("Debut selected. (Not implemented)\n");
                break;
            default:
                printf("Invalid selection. Choose 1, 2, or 3.\n");
        }
    }

    return 0;
}
