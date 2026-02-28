#ifndef MODELS_H
#define MODELS_H

#include <stddef.h>

#define SURNAME_MAX 64
#define POSITION_MAX 64

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    int code;
    char surname[SURNAME_MAX];
    char position[POSITION_MAX];
    char gender;           // 'M' or 'F'
    Date sign_date;        // date of contract signing
    int term_months;       // contract term in months
    double salary;
} WORKER2;

#endif