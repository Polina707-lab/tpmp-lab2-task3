#include "worker_service.h"
#include "ui.h"
#include "date_service.h"
#include <string.h>
#include <stdio.h>

size_t worker_input_array(WORKER2 *arr, size_t max_n) {
    int n = ui_read_int("Enter number of workers (1..12): ", 1, 12);
    if ((size_t)n > max_n) n = (int)max_n;

    for (int i = 0; i < n; i++) {
        printf("\n--- Worker #%d ---\n", i + 1);
        arr[i].code = ui_read_int("Code: ", 1, 1000000000);
        ui_read_string("Surname: ", arr[i].surname, sizeof(arr[i].surname));
        ui_read_string("Position: ", arr[i].position, sizeof(arr[i].position));
        arr[i].gender = ui_read_gender("Gender (M/F): ");

        for (;;) {
            arr[i].sign_date = ui_read_date("Contract signing date:");
            if (date_is_valid(arr[i].sign_date)) break;
            printf("Invalid date, try again.\n");
        }

        arr[i].term_months = ui_read_int("Contract term (months, 1..600): ", 1, 600);
        arr[i].salary = ui_read_double("Salary (>= 0): ", 0.0);
    }
    return (size_t)n;
}

void worker_print_all(const WORKER2 *arr, size_t n, void (*printer)(const WORKER2*, int)) {
    printf("\n=== ALL WORKERS ===\n");
    for (size_t i = 0; i < n; i++) {
        printer(&arr[i], (int)i);
    }
}

void worker_print_signed_less_than_year_ago(const WORKER2 *arr, size_t n, Date today,
                                            void (*printer)(const WORKER2*, int)) {
    printf("\n=== WORKERS WHO SIGNED CONTRACT < 1 YEAR AGO ===\n");
    for (size_t i = 0; i < n; i++) {
        int diff = date_days_between(arr[i].sign_date, today); // today - sign_date
        if (diff >= 0 && diff < 365) {
            printer(&arr[i], (int)i);
        }
    }
}

void worker_print_double_contracts(const WORKER2 *arr, size_t n,
                                  void (*printer)(const WORKER2*, int)) {
    printf("\n=== WORKERS WITH DOUBLE CONTRACTS (same code appears >= 2) ===\n");
    int printed_any = 0;

    for (size_t i = 0; i < n; i++) {
        int count = 0;
        for (size_t j = 0; j < n; j++) {
            if (arr[j].code == arr[i].code) {
                count++;
            }
        }

        if (count >= 2) {
            /* print only first occurrence of this code */
            int first = 1;
            for (size_t k = 0; k < i; k++) {
                if (arr[k].code == arr[i].code) {
                    first = 0;
                    break;
                }
            }

            if (first) {
                printer(&arr[i], (int)i);
                printed_any = 1;
            }
        }
    }
}

int worker_avg_term_for_position(const WORKER2 *arr, size_t n, const char *position, double *out_avg_months) {
    long sum = 0;
    long cnt = 0;
    for (size_t i = 0; i < n; i++) {
        if (strcmp(arr[i].position, position) == 0) {
            sum += arr[i].term_months;
            cnt++;
        }
    }
    if (cnt == 0) return 0;
    *out_avg_months = (double)sum / (double)cnt;
    return 1;
}

void worker_count_gender(const WORKER2 *arr, size_t n, int *out_male, int *out_female) {
    int m = 0, f = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i].gender == 'M') m++;
        else if (arr[i].gender == 'F') f++;
    }
    *out_male = m;
    *out_female = f;
}
