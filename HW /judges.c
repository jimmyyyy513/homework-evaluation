#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define STR_SIZE 512
#define REQUIRED_FIELDS 7

char judges_array[MAX_JUDGES][STR_SIZE];

void clear_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int count_commas(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ',') count++;
        str++;
    }
    return count;
}

void parse_and_display(int count, const char *project) {
    printf("####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (int i = 0; i < count; i++) {
        printf("[Judge %d]\n", i + 1);
        char buffer[STR_SIZE];
        strcpy(buffer, judges_array[i]);

        char *token = strtok(buffer, ",");
        const char *labels[] = {
            "Name", "Gender", "Affiliation", "Title",
            "Expertise", "Email", "Phone"
        };

        int j = 0;
        while (token && j < REQUIRED_FIELDS) {
            while (*token == ' ') token++; // trim leading space
            printf("%s: %s\n", labels[j], token);
            token = strtok(NULL, ",");
            j++;
        }
        printf("-----------------------------------\n");
    }
}

int main() {
    char project[STR_SIZE];
    int total_judges = 0;
    int selected_members = 0;
    int count = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, STR_SIZE, stdin);
    clear_newline(project);

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // clear newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (count < total_judges) {
        printf("Judge %d: ", count + 1);
        char input[STR_SIZE];
        fgets(input, STR_SIZE, stdin);
        clear_newline(input);

        if (count_commas(input) != REQUIRED_FIELDS - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        strcpy(judges_array[count], input);
        count++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char confirm;
    printf("\"Should we check the judge information?\" ");
    scanf(" %c", &confirm); // include space to consume leftover newline

    if (confirm == 'Y') {
        printf("[%s] Should we check the judge information? Y\n", project);
        parse_and_display(total_judges, project);
    } else {
        printf("Program terminated without displaying data.\n");
    }

    return 0;
}
