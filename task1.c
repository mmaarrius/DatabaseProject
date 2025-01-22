#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "task1.h"
#define ENTIRE_LINE 50
#define ZECIMALS 100

secretariat *citeste_secretariat(const char *nume_fisier) {
    // Open file
    FILE *f = fopen(nume_fisier, "r");

    // Reads and processes lines
    int option = 0;
    int nr_studenti = -1, nr_materii = -1, nr_inrolari = -1;
    char *line = (char *)malloc(ENTIRE_LINE * sizeof(*line));

    // Find number of each category
    while (fgets(line, ENTIRE_LINE, f)) {
        // Select category
        if (strstr(line, "STUDENTI")) option = 1;
        else if (strstr(line, "MATERII")) option = 2;
        else if (strstr(line, "INROLARI")) option = 3;

        switch (option) {
        case 1:
            nr_studenti++;
            break;
        case 2:
            nr_materii++;
            break;
        case 3:
            nr_inrolari++;
            break;
        default:
            break;
        }
    }

    rewind(f);

    student *stud = (student *)malloc(nr_studenti * sizeof(*stud));
    materie *mat = (materie *)malloc(nr_materii * sizeof(*mat));
    inrolare *inr = (inrolare *)malloc(nr_inrolari * sizeof(*inr));

    int nr = 0;
    while (fgets(line, ENTIRE_LINE, f)) {
        // Select category
        if (strstr(line, "STUDENTI")) {
            option = 1;
            nr = 0;
        } else if (strstr(line, "MATERII")) {
            option = 2;
            nr = 0;
        } else if (strstr(line, "INROLARI")) {
            option = 3;
            nr = 0;
        } else {
            // Process line
            switch (option) {
                case 1:
                    sscanf(line, "%d, %[^,], %d, %c",
                    &stud[nr].id, stud[nr].nume, &stud[nr].an_studiu, &stud[nr].statut);
                    nr++;
                    break;
                case 2: {
                    char *ptr1 = strstr(line, ",");
                    char *ptr2 = strstr(ptr1 + 1, ",");
                    int name_len = (int)(ptr2 - ptr1);
                    mat[nr].nume = (char *)malloc(name_len * sizeof(char));
                    mat[nr].nume[name_len - 1] = '\0';

                    int tutor_len = (int)strlen(ptr2 + 1);
                    mat[nr].nume_titular = (char *)malloc(tutor_len * sizeof(char));
                    mat[nr].nume_titular[tutor_len - 1] = '\0';
                    sscanf(line, "%d, %[^,], %[^\n]", &mat[nr].id, mat[nr].nume, mat[nr].nume_titular);
                    nr++;
                    break;
                }
                case 3:
                    sscanf(line, "%d, %d, %f %f %f",
                    &inr[nr].id_student, &inr[nr].id_materie, &inr[nr].note[0], &inr[nr].note[1], &inr[nr].note[2]);
                    nr++;
                    break;
                default:
                    break;
            }
        }
    }

    // Create secretariat
    secretariat *s = malloc(sizeof(*s));

    // Calculate final note
    float sum = 0;
    float nr_of_notes = 0;
    float avg = 0;
    for (int i = 0; i < nr_studenti; i++) {
        for (int j = 0; j < nr_inrolari; j++) {
            if (inr[j].id_student == stud[i].id) {
                for (int k = 0; k < 3; k++) {
                    sum += inr[j].note[k];
                }
                nr_of_notes++;
            }
        }
        avg = sum / nr_of_notes;
        stud[i].medie_generala = (float)(round((avg * ZECIMALS))) / ZECIMALS;
        sum = 0;
        nr_of_notes = 0;
        avg = 0;
    }

    s->studenti = stud;
    s->nr_studenti = nr_studenti;

    s->materii = mat;
    s->nr_materii = nr_materii;

    s->inrolari = inr;
    s->nr_inrolari = nr_inrolari;

    free(line);
    fclose(f);

    return s;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    // Increase nr of students and realloc
    s->nr_studenti++;
    int nr = s->nr_studenti;
    student *stud = realloc(s->studenti, nr * sizeof(*stud));

    // Copy values
    stud[nr - 1].id = id;
    strncpy(stud[nr - 1].nume, nume, strlen(nume) + 1);
    stud[nr - 1].an_studiu = an_studiu;
    stud[nr - 1].statut = statut;
    stud[nr - 1].medie_generala = medie_generala;

    s->studenti = stud;
    stud = NULL;
}

void elibereaza_secretariat(secretariat **s) {
    // Free memory
    free((*s)->studenti);

    for (int i = 0; i < (*s)->nr_materii; i++) {
        free((*s)->materii[i].nume);
        free((*s)->materii[i].nume_titular);
    }
    free((*s)->materii);

    free((*s)->inrolari);

    free(*s);
    *s = NULL;
}
