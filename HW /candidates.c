#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 6
#define STR_SIZE 256  // Increased to handle long emails or introductions

// Arrays for six candidates, each with 11 fields
char candidate01[11][STR_SIZE], candidate02[11][STR_SIZE], candidate03[11][STR_SIZE];
char candidate04[11][STR_SIZE], candidate05[11][STR_SIZE], candidate06[11][STR_SIZE];

// Array of pointers to candidate arrays
char* member_info[MAX] = {
    (char*)candidate01, (char*)candidate02, (char*)candidate03,
    (char*)candidate04, (char*)candidate05, (char*)candidate06
};

// Function to calculate age
int calculate_age(const char *dob) {
    int year, month, day;
    sscanf(dob, "%d/%d/%d", &year, &month, &day);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int age = tm.tm_year + 1900 - year;
    if (tm.tm_mon + 1 < month || (tm.tm_mon + 1 == month && tm.tm_mday < day)) {
        age--;
    }
    return age;
}

int main() {
    char groupName[STR_SIZE];
    char ch;
    int i = 0;
    char temp[STR_SIZE];

    printf("Enter the audition group name: ");
    fgets(groupName, STR_SIZE, stdin);
    groupName[strcspn(groupName, "\n")] = '\0';  // Remove newline

    // Flush input buffer
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", groupName);
    printf("####################################\n");

    while (i < MAX) {
        printf("Entering information for candidate %d.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. Name: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 0 * STR_SIZE), temp);

        printf("2. Date of Birth (YYYY/MM/DD format): ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 1 * STR_SIZE), temp);

        printf("3. Gender (F for Female, M for Male): ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 2 * STR_SIZE), temp);

        printf("4. Email: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 3 * STR_SIZE), temp);

        printf("5. Nationality: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 4 * STR_SIZE), temp);

        printf("6. BMI: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 5 * STR_SIZE), temp);

        printf("7. Primary Skill: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 6 * STR_SIZE), temp);

        printf("8. Secondary Skill: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 7 * STR_SIZE), temp);

        printf("9. Korean Proficiency Level (TOPIK): ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 8 * STR_SIZE), temp);

        printf("10. MBTI: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 9 * STR_SIZE), temp);

        printf("11. Introduction: ");
        fgets(temp, STR_SIZE, stdin); strcpy((member_info[i] + 10 * STR_SIZE), temp);

        i++;
        printf("=================================\n");
    }

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", groupName);
    printf("####################################\n");

    printf("=============================================================================================================\n");
    printf("Name                | Age | DOB       | Gender | Email                  | Nationality | BMI  | Primary | Secondary | TOPIK | MBTI |\n");
    printf("=============================================================================================================\n");

    for (i = 0; i < MAX; i++) {
        char* name = (member_info[i] + 0 * STR_SIZE);
        char* dob = (member_info[i] + 1 * STR_SIZE);
        char dob_clean[STR_SIZE]; strcpy(dob_clean, dob);
        dob_clean[strcspn(dob_clean, "\n")] = '\0';

        int age = calculate_age(dob_clean);

        char* gender = (member_info[i] + 2 * STR_SIZE);
        char* email = (member_info[i] + 3 * STR_SIZE);
        char* nation = (member_info[i] + 4 * STR_SIZE);
        char* bmi = (member_info[i] + 5 * STR_SIZE);
        char* pskill = (member_info[i] + 6 * STR_SIZE);
        char* sskill = (member_info[i] + 7 * STR_SIZE);
        char* topik = (member_info[i] + 8 * STR_SIZE);
        char* mbti = (member_info[i] + 9 * STR_SIZE);
        char* intro = (member_info[i] + 10 * STR_SIZE);

        // Clean newline characters
        name[strcspn(name, "\n")] = 0;
        gender[strcspn(gender, "\n")] = 0;
        email[strcspn(email, "\n")] = 0;
        nation[strcspn(nation, "\n")] = 0;
        bmi[strcspn(bmi, "\n")] = 0;
        pskill[strcspn(pskill, "\n")] = 0;
        sskill[strcspn(sskill, "\n")] = 0;
        topik[strcspn(topik, "\n")] = 0;
        mbti[strcspn(mbti, "\n")] = 0;
        intro[strcspn(intro, "\n")] = 0;

        // Convert TOPIK 0 to "Native"
        char topik_display[10];
        if (strcmp(topik, "0") == 0) {
            strcpy(topik_display, "Native");
        } else {
            strcpy(topik_display, topik);
        }

        printf("%-18s (%2d) | %-8s | %-6s | %-22s | %-11s | %-4s | %-8s | %-9s | %-5s | %-4s |\n",
               name, age, dob_clean, gender, email, nation, bmi, pskill, sskill, topik_display, mbti);

        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
