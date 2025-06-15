#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_SCORES 7  // 1 for ID, 5 categories, 1 for total
#define NAME_LEN 50
#define ID_LEN 7

// Candidate structure
char candidate_names[NUM_CANDIDATES][NAME_LEN] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Aria Lee",
    "Noah Davis"
};

int candidate_ids[NUM_CANDIDATES] = {123456, 234567, 345678, 456789, 567890, 678901};

// Scoring sheet: [ID, Music, Dance, Vocal, Visual, Expression, Total]
int scoring_sheet[NUM_CANDIDATES][NUM_SCORES] = {0};

// Input and validation helper
int input_score(const char *category) {
    int score;
    while (1) {
        printf("%s (10~100): ", category);
        if (scanf("%d", &score) != 1 || score < 10 || score > 100) {
            printf("Invalid input. Please enter a score between 10 and 100.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return score;
}

// Calculate total score
void calculate_totals() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int total = 0;
        for (int j = 1; j <= 5; j++) {
            total += scoring_sheet[i][j];
        }
        scoring_sheet[i][6] = total;
    }
}

// Display scores for review
void display_scores() {
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\nPlease review your input!\n");
    printf("------------------------------------\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scoring_sheet[i][1]); // Show Music score
    }
}

// Modify scores
void modify_scores() {
    char name[NAME_LEN];
    int id;
    int found;

    while (1) {
        printf("Enter candidate name to modify (or 'done' to finish): ");
        scanf(" %[^\n]", name);
        if (strcmp(name, "done") == 0) break;

        printf("Enter 6-digit candidate ID: ");
        scanf("%d", &id);
        found = 0;

        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(name, candidate_names[i]) == 0 && id == candidate_ids[i]) {
                printf("Re-enter scores for %s:\n", name);
                scoring_sheet[i][1] = input_score("Music Proficiency");
                scoring_sheet[i][2] = input_score("Dance");
                scoring_sheet[i][3] = input_score("Vocal");
                scoring_sheet[i][4] = input_score("Visual");
                scoring_sheet[i][5] = input_score("Expression");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Candidate not found. Please try again.\n");
        }

        calculate_totals();
    }
}

// Sort and select top 4
void select_top_candidates() {
    int indices[NUM_CANDIDATES];
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        indices[i] = i;
    }

    // Simple selection sort based on total score
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[indices[j]][6] > scoring_sheet[indices[i]][6]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[indices[i]]);
    }
}

int main() {
    char judge_name[NAME_LEN];
    char expertise[NAME_LEN];
    char choice;

    while (1) {
        printf("####################################\n");
        printf("#     Audition Evaluation Entry    #\n");
        printf("####################################\n");
        printf("> Judge Name: ");
        scanf(" %[^\n]", judge_name);
        printf("> Expertise: ");
        scanf(" %[^\n]", expertise);
        printf("++++++++++++++++++++++++++++++++++++\n");

        for (int i = 0; i < NUM_CANDIDATES; i++) {
            printf("Candidate: %s\n", candidate_names[i]);
            scoring_sheet[i][0] = candidate_ids[i];
            scoring_sheet[i][1] = input_score("Music Proficiency");
            scoring_sheet[i][2] = input_score("Dance");
            scoring_sheet[i][3] = input_score("Vocal");
            scoring_sheet[i][4] = input_score("Visual");
            scoring_sheet[i][5] = input_score("Expression");
            printf("------------------------------------\n");
        }

        calculate_totals();
        display_scores();

        printf("Would you like to submit? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            printf("***Final submission completed.***\n");
            break;
        } else {
            modify_scores();
            printf("***Final submission completed.***\n");
            break;
        }
    }

    select_top_candidates();
    return 0;
}
