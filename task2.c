#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task2.h"

#define ONE_LINE_CHR 100
#define STUD_FIELDS 5
#define MAT_FIELDS 3
#define INR_FIELDS 3
#define NR_OF_NOTES 3
#define ZECIMALS 100
#define ID_CODE 1
#define NAME_CODE 2
#define YEAR_CODE 3
#define STATUS_CODE 4
#define AVG_CODE 5
#define TITULAR_CODE 3
#define STUD_ID_CODE 1
#define MAT_ID_CODE 2
#define NOTES_CODE 3


int verifyCondition(secretariat s, char *condition, int category, int index) {
    if (condition == NULL) return 1;

    char* copy = strdup(condition);

    // Keep for free
    char *original_copy = copy;

    // Find field
    char *space_pos = strchr(copy, ' ');
    size_t length = space_pos - copy;
    char *field = malloc((length + 1) * sizeof(*field));
    field[length] = '\0';
    strncpy(field, copy, length);

    // Eliminate field from condition
    copy = space_pos + 1;

    // Find operator
    space_pos = strchr(copy, ' ');
    length = space_pos - copy;
    char *operator = malloc((length + 1) * sizeof(*operator));
    operator[length] = '\0';
    strncpy(operator, copy, length);

    // Eliminate operator from condition
    copy = space_pos + 1;

    // Find value
    char *value = strdup(copy);

    int extractedValue = 0;
    char *extractedString = NULL;
    int valueType = 0, result = 0, strIsAllocated = 0;

    // Extract exact value
    switch (category) {
        case 1:
            if (!strcmp(field, "id")) {
                extractedValue = s.studenti[index].id;
                valueType = 0;
            }
            if (!strcmp(field, "nume")) {
                extractedString = s.studenti[index].nume;
                valueType = 1;
            }
            if (!strcmp(field, "an_studiu")) {
                extractedValue = s.studenti[index].an_studiu;
                valueType = 0;
            }
            if (!strcmp(field, "statut")) {
                extractedString = malloc(2 * sizeof(*extractedString));
                extractedString[0] = s.studenti[index].statut;
                extractedString[1] = '\0';
                valueType = 1;
                strIsAllocated = 1;
            }
            if (!strcmp(field, "medie_generala")) {
                extractedValue = (int)(s.studenti[index].medie_generala * ZECIMALS);
                valueType = 0;
            }
            break;
        case 2:
            if (!strcmp(field, "id")) {
                extractedValue = s.materii[index].id;
                valueType = 0;
            }
            if (!strcmp(field, "nume")) {
                extractedString = s.materii[index].nume;
                valueType = 1;
            }
            if (!strcmp(field, "nume_titular")) {
                extractedString = s.materii[index].nume_titular;
                valueType = 1;
            }
            break;
        case 3:
            if (!strcmp(field, "id_student")) {
                extractedValue = s.inrolari[index].id_student;
                valueType = 0;
            }
            if (!strcmp(field, "id_materie")) {
                extractedValue = s.inrolari[index].id_materie;
                valueType = 0;
            }
            break;
    }

    // Compare values
    if (valueType == 0) {
        int condValue = atoi(value);
        if (strchr(value, '.')) condValue *= ZECIMALS;

        if (!strcmp(operator, "<")) {
            if (extractedValue < condValue) result = 1;
        }
        if (!strcmp(operator, "<=")) {
            if (extractedValue <= condValue) result = 1;
        }
        if (!strcmp(operator, ">")) {
            if (extractedValue > condValue) result = 1;
        }
        if (!strcmp(operator, ">=")) {
            if (extractedValue >= condValue) result = 1;
        }
        if (!strcmp(operator, "=")) {
            if (extractedValue == condValue) result = 1;
        }
        if (!strcmp(operator, "!=")) {
            if (extractedValue != condValue) result = 1;
        }
    } else {
        if (!strcmp(operator, "=")) {
            if (strstr(extractedString, value)) result = 1;
        }
        if (!strcmp(operator, "!=")) {
            if (!strstr(extractedString, value)) result = 1;
        }
    }

    // Free memory
    free(field);
    free(operator);
    free(value);
    free(original_copy);
    if (strIsAllocated) {
        free(extractedString);
    }

    return result;
}

int FieldToNumber(char* field) {
    if (!strcmp(field, "id")) return ID_CODE;
    else if (!strcmp(field, "nume")) return NAME_CODE;
    else if (!strcmp(field, "an_studiu")) return YEAR_CODE;
    else if (!strcmp(field, "statut")) return STATUS_CODE;
    else if (!strcmp(field, "medie_generala")) return AVG_CODE;
    else if (!strcmp(field, "nume_titular")) return TITULAR_CODE;
    else if (!strcmp(field, "id_student")) return STUD_ID_CODE;
    else if (!strcmp(field, "id_materie")) return MAT_ID_CODE;
    else if (!strcmp(field, "note")) return NOTES_CODE;
    else
        return 0;
}

void printFields(secretariat s, int *fieldsArray, int arrayLen, int category, int index) {
    student *studTable = s.studenti;
    materie *matTable = s.materii;
    inrolare *inrTable = s.inrolari;

    switch (category) {
        case 1:
            for (int i = 0; i < arrayLen; i++) {
                switch (fieldsArray[i]) {
                    case ID_CODE:
                        printf("%d", studTable[index].id);
                        break;
                    case NAME_CODE:
                        printf("%s", studTable[index].nume);
                        break;
                    case YEAR_CODE:
                        printf("%d", studTable[index].an_studiu);
                        break;
                    case STATUS_CODE:
                        printf("%c", studTable[index].statut);
                        break;
                    case AVG_CODE:
                        printf("%.2f", studTable[index].medie_generala);
                        break;
                    default:
                        break;
                }
                if (i < arrayLen - 1) printf(" ");
            }
            break;
        case 2:
            for (int i = 0; i < arrayLen; i++) {
                switch (fieldsArray[i]) {
                    case ID_CODE:
                        printf("%d", matTable[index].id);
                        break;
                    case NAME_CODE:
                        printf("%s", matTable[index].nume);
                        break;
                    case TITULAR_CODE:
                        printf("%s", matTable[index].nume_titular);
                        break;
                    default:
                        break;
                }
                if (i < arrayLen - 1) printf(" ");
            }
            break;
        case 3:
            for (int i = 0; i < arrayLen; i++) {
                switch (fieldsArray[i]) {
                    case ID_CODE:
                        printf("%d", inrTable[index].id_student);
                        break;
                    case MAT_ID_CODE:
                        printf("%d", inrTable[index].id_materie);
                        break;
                    case NOTES_CODE:
                        printf("%.2f %.2f %.2f",
                        inrTable[index].note[0], inrTable[index].note[1], inrTable[index].note[2]);
                        break;
                    default:
                        break;
                }
                if (i < arrayLen - 1) printf(" ");
            }
            break;
    }
    printf("\n");
}

int* memorise_fields_in_numbers(char* queryFields, int *arrayLen, int category) {
    char *copy = queryFields;

    size_t length = 0;
    char* field = NULL;
    char* pos = NULL;
    int *copyArr = NULL, *fieldsArray = NULL;

    // Check if fields are all
    if (strstr(copy, "*")) {
        if (category == 1) *arrayLen = STUD_FIELDS;
        else if (category == 2) *arrayLen = MAT_FIELDS;
        else
        *arrayLen = INR_FIELDS;

        fieldsArray = malloc(*(arrayLen) * sizeof(*fieldsArray));
        for (int i = 0; i < *arrayLen; i++) {
            fieldsArray[i] = i + 1;
        }
        return fieldsArray;
    }

    // Fields are not all
    char *current = copy;
    while (*current != '\0') {
        pos = strchr(current, ',');

        if (pos != NULL) {
            length = pos - current;
            field = strndup(current, length);
            current = pos + 2;
        } else {
            field = strdup(current);

            // Eliminate field from command
            current += strlen(current);
        }

        // Add field number in array
        copyArr = realloc(fieldsArray, (*arrayLen + 1) * sizeof(int));
        if (copyArr != NULL) {
            fieldsArray = copyArr;
            (*arrayLen)++;
        } else {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        fieldsArray[(*arrayLen) - 1] = FieldToNumber(field);

        // Eliminate field from command
        free(field);
        field = NULL;
    }

    return fieldsArray;
}

char* extractBetweenDelims(char* str, char* start, char* end) {
    char *pos1 = strstr(str, start) + strlen(start);
    char *pos2 = strstr(str, end);

    size_t length = pos2 - pos1;
    char *extracted = malloc((length + 1) * sizeof(*extracted));
    extracted[length] = '\0';
    strncpy(extracted, pos1, length);

    return extracted;
}

void select_fun(secretariat s, char* command) {
    // Find category
    int category = 0;
    if (strstr(command, "studenti")) category = 1;
    if (strstr(command, "materii")) category = 2;
    if (strstr(command, "inrolari")) category = 3;

    // Extract fields name
    char *queryFields = extractBetweenDelims(command, "SELECT ", " FROM");

    // Memorise fields order
    int arrLength = 0;
    int *fieldsArr = memorise_fields_in_numbers(queryFields, &arrLength, category);

    // Free memory
    free(queryFields);
    queryFields = NULL;

    // Select table length
    int tableLen = 0;
    if (category == 1) tableLen = s.nr_studenti;
    else if (category == 2) tableLen = s.nr_materii;
    else
    tableLen = s.nr_inrolari;

    // Check if there is a condition
    char *condition1 = NULL, *condition2 = NULL;
    if (strstr(command, "AND")) {;
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", " AND");

        // Extract condition 2
        condition2 = extractBetweenDelims(command, "AND ", ";");
    } else if (strstr(command, "WHERE")) {
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", ";");
    }

    // Print fields
    for (int i = 0; i < tableLen; i++) {
        if (verifyCondition(s, condition1, category, i) &&
            verifyCondition(s, condition2, category, i)) {
            printFields(s, fieldsArr, arrLength, category, i);
        }
    }

    // Free memory
    free(fieldsArr);
    fieldsArr = NULL;
    if (condition1 != NULL) {
        free(condition1);
        condition1 = NULL;
    }
    if (condition2 != NULL) {
        free(condition2);
        condition2 = NULL;
    }
}

float get_avg(secretariat s, int studId) {
    float avg = 0;
    float nr_notes = 0;

    for (int i = 0; i < s.nr_inrolari; i++) {
        if (s.inrolari[i].id_student == studId) {
            for (int k = 0; k < NR_OF_NOTES; k++) {
                avg += s.inrolari[i].note[k];
            }
            nr_notes++;
        }
    }

    if (avg == 0) return 0;

    avg = avg / nr_notes;
    avg = (float)(round(avg * ZECIMALS) / ZECIMALS);


    return avg;
}

void modifyField(secretariat s, char *setting, int category, int index) {
    char *copy = strdup(setting);

    // Keeping for freeing memory
    char *original_copy = copy;

    // Find field
    char *space_pos = strchr(copy, ' ');
    size_t length = space_pos - copy;
    char *field = malloc((length + 1) * sizeof(*field));
    field[length] = '\0';
    strncpy(field, copy, length);

    // Eliminate field and operator from condition
    copy = space_pos + 3;

    // Verify if value is between quotes
    if (copy[0] == '"') {
        copy++;
        copy[strlen(copy) - 1] = '\0';
    }

    // Find value
    char *value = strdup(copy);

    // Set value
    switch (category) {
        case 1:
            if (!strcmp(field, "id")) {
                s.studenti[index].id = atoi(value);
            }
            if (!strcmp(field, "nume")) {
                strncpy(s.studenti[index].nume, value, strlen(value) + 1);
            }
            if (!strcmp(field, "an_studiu")) {
                s.studenti[index].an_studiu = atoi(value);
            }
            if (!strcmp(field, "statut")) {
                s.studenti[index].statut = value[0];
            }
            if (!strcmp(field, "medie_generala")) {
                s.studenti[index].medie_generala = (float)atof(value);
            }
            break;
        case 2:
            if (!strcmp(field, "id")) {
                s.materii[index].id = atoi(value);
            }
            if (!strcmp(field, "nume")) {
                char *helperPtr = realloc(s.materii[index].nume, (strlen(value) + 1) * sizeof(*helperPtr));
                if (helperPtr != NULL) {
                    s.materii[index].nume = helperPtr;
                    strncpy(s.materii[index].nume, value, strlen(value) + 1);
                } else {
                    printf("Memory allocation failed!\n");
                }
                helperPtr = NULL;
            }
            if (!strcmp(field, "nume_titular")) {
                char *helperPtr = realloc(s.materii[index].nume_titular, (strlen(value) + 1) * sizeof(*helperPtr));
                if (helperPtr != NULL) {
                    s.materii[index].nume_titular = helperPtr;
                    strncpy(s.materii[index].nume_titular, value, strlen(value) + 1);
                } else {
                    printf("Memory allocation failed!\n");
                }
                helperPtr = NULL;
            }
            break;
        case 3:
            if (!strcmp(field, "id_student")) {
                s.inrolari[index].id_student = atoi(value);
            }
            if (!strcmp(field, "id_materie")) {
                s.inrolari[index].id_materie = atoi(value);
            }
            if (!strcmp(field, "note")) {
                sscanf(value, "%f %f %f",
                &s.inrolari[index].note[0], &s.inrolari[index].note[1], &s.inrolari[index].note[2]);
                int studIndex = s.inrolari[index].id_student;
                // Update general average
                for (int i = 0; i < s.nr_studenti; i++) {
                    if (s.studenti[i].id == studIndex) {
                        s.studenti[i].medie_generala = get_avg(s, studIndex);
                    }
                }
            }
            break;
    }

    // Free memory
    free(field);
    free(value);
    free(original_copy);

    field = NULL;
    value = NULL;
}

void update_fun(secretariat s, char* command) {
    // Find category
    int category = 0, tableLength = 0;
    if (strstr(command, "studenti")) {
        category = 1;
        tableLength = s.nr_studenti;
    } else if (strstr(command, "materii")) {
        category = 2;
        tableLength = s.nr_materii;
    } else {
        category = 3;
        tableLength = s.nr_inrolari;
    }

    // Extract setting command
    char *setting = extractBetweenDelims(command, "SET ", " WHERE");

    // Extract conditions
    char *condition1 = NULL, *condition2 = NULL;
    if (strstr(command, "AND")) {
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", " AND");

        // Extract condition 2
        condition2 = extractBetweenDelims(command, "AND ", ";");
    } else if (strstr(command, "WHERE")) {
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", ";");
    }

    for (int i = 0; i < tableLength; i++) {
        if (verifyCondition(s, condition1, category, i) &&
            verifyCondition(s, condition2, category, i)) {
            modifyField(s, setting, category, i);
        }
    }

    // Free memory
    free(setting);
    if (condition1 != NULL) {
        free(condition1);
        condition1 = NULL;
    }
    if (condition2 != NULL) {
        free(condition2);
        condition2 = NULL;
    }
}

void delete_fun(secretariat *s, char* command) {
    // Find category
    int category = 0, tableLength = 0;
    if (strstr(command, "studenti")) {
        category = 1;
        tableLength = s->nr_studenti;
    } else if (strstr(command, "materii")) {
        category = 2;
        tableLength = s->nr_materii;
    } else {
        category = 3;
        tableLength = s->nr_inrolari;
    }

    // Extract conditions
    char *condition1 = NULL, *condition2 = NULL;
    if (strstr(command, "AND")) {
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", " AND");

        // Extract condition 2
        condition2 = extractBetweenDelims(command, "AND ", ";");
    } else if (strstr(command, "WHERE")) {
        // Extract condition 1
        condition1 = extractBetweenDelims(command, "WHERE ", ";");
    }

    // Find elements to delete
    int count = 0;
    int *deleteIndexes = NULL;
    for (int i = 0; i < tableLength; i++) {
        if (verifyCondition(*s, condition1, category, i) &&
            verifyCondition(*s, condition2, category, i)) {
            if (category == 1) {
                count++;
                deleteIndexes = realloc(deleteIndexes, count * sizeof(*deleteIndexes));
                deleteIndexes[count - 1] = i;

                s->nr_studenti--;
            } else if (category == 2) {
                count++;
                deleteIndexes = realloc(deleteIndexes, count * sizeof(*deleteIndexes));
                deleteIndexes[count - 1] = i;

                s->nr_materii--;
            } else {
                count++;
                deleteIndexes = realloc(deleteIndexes, count * sizeof(*deleteIndexes));
                deleteIndexes[count - 1] = i;

                s->nr_inrolari--;
            }
        }
    }

    // Delete elements
    int newTableIndex = 0, delIndex = 0;
    switch (category) {
        case 1:
        {
            student *newStudTable = malloc(s->nr_studenti * sizeof(*newStudTable));
            if (newStudTable == NULL) {
                printf("Memory allocation failed!\n");
                free(deleteIndexes);
                return;
            }
            for (int i = 0; i < tableLength; i++) {
                if (delIndex < count && deleteIndexes[delIndex] == i) {
                    delIndex++;
                } else {
                    newStudTable[newTableIndex] = s->studenti[i];
                    newTableIndex++;
                }
            }

            // Free memory
            free(s->studenti);

            // Update table
            s->studenti = newStudTable;
            newStudTable = NULL;
            break;
        }
        case 2:
        {
            materie *newMatTable = malloc(s->nr_materii * sizeof(*newMatTable));
            if (newMatTable == NULL) {
                printf("Memory allocation failed!\n");
                free(deleteIndexes);
                return;
            }
            for (int i = 0; i < tableLength; i++) {
                if (delIndex < count && deleteIndexes[delIndex] == i) {
                    delIndex++;
                } else {
                    newMatTable[newTableIndex] = s->materii[i];
                    newTableIndex++;
                }
            }

            // Free memory
            for (int i = 0; i < tableLength; i++) {
                free(s->materii[i].nume);
                free(s->materii[i].nume_titular);
            }
            free(s->materii);

            // Update table
            s->materii = newMatTable;
            newMatTable = NULL;
            break;
        }
        case 3:
        {
            inrolare *newInrTable = malloc(s->nr_inrolari * sizeof(*newInrTable));
            if (newInrTable == NULL) {
                printf("Memory allocation failed!\n");
                free(deleteIndexes);
                return;
            }

            for (int i = 0; i < tableLength; i++) {
                if (delIndex < count && deleteIndexes[delIndex] == i) {
                    delIndex++;
                } else {
                    newInrTable[newTableIndex] = s->inrolari[i];
                    newTableIndex++;
                }
            }

            // Free memory
            free(s->inrolari);

            // Update table
            s->inrolari = newInrTable;
            s->nr_inrolari = newTableIndex;
            newInrTable = NULL;

            //  Update general average
            for (int i = 0; i < s->nr_studenti; i++) {
                s->studenti[i].medie_generala = get_avg(*s, s->studenti[i].id);
            }

            break;
        }
        default:
            break;
    }

    // Free memory
    free(deleteIndexes);
    if (condition1 != NULL) {
        free(condition1);
        condition1 = NULL;
    }
    if (condition2 != NULL) {
        free(condition2);
        condition2 = NULL;
    }
}

int main(int argc, char *argv[]) {
    // Read secretariat
    secretariat *s = citeste_secretariat(argv[1]);

    int nr_com = 0;
    char *command = malloc(ONE_LINE_CHR);

    // Read number of commands
    scanf("%d", &nr_com);

    // Eliminate last \n
    getchar();

    // Read and execute commands
    for (int i = 0; i < nr_com; i++) {
        fgets(command, ONE_LINE_CHR, stdin);

        if (strstr(command, "SELECT") != NULL) {
            select_fun(*s, command);
        } else if (strstr(command, "UPDATE") != NULL) {
            update_fun(*s, command);
        } else if (strstr(command, "DELETE") != NULL) {
            delete_fun(s, command);
        }
    }

    // Free memory
    elibereaza_secretariat(&s);
    free(command);
    s = NULL;
    command = NULL;

    return 0;
}
