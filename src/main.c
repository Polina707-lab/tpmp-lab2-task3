#include <stdio.h>

#include "ui.h"
#include "models.h"
#include "date_service.h"
#include "worker_service.h"
#include "company_service.h"

static void run_date_tasks(void) {
    Date d;
    for (;;) {
        d = ui_read_date("Enter a date:");
        if (date_is_valid(d)) break;
        printf("Invalid date. Try again.\n");
    }

    int dim = date_days_in_month(d.year, d.month);
    printf("\nDays in this month: %d\n", dim);

    Date prev = date_prev_day(d);
    Date next = date_next_day(d);

    ui_print_date("Previous day:", prev);
    ui_print_date("Next day:    ", next);
}

static void run_worker_tasks(void) {
    WORKER2 workers[12];
    size_t n = worker_input_array(workers, 12);

    worker_print_all(workers, n, ui_print_worker);

    Date today;
    for (;;) {
        today = ui_read_date("\nEnter today's date (for '< 1 year ago' check):");
        if (date_is_valid(today)) break;
        printf("Invalid date. Try again.\n");
    }

    worker_print_signed_less_than_year_ago(workers, n, today, ui_print_worker);
    worker_print_double_contracts(workers, n, ui_print_worker);

    char pos[POSITION_MAX];
    ui_read_string("\nEnter position to compute average contract term: ", pos, sizeof(pos));
    double avg_months = 0.0;
    if (worker_avg_term_for_position(workers, n, pos, &avg_months)) {
        printf("Average term for position '%s' = %.2f months\n", pos, avg_months);
    } else {
        printf("No workers with position '%s'\n", pos);
    }

    int male = 0, female = 0;
    worker_count_gender(workers, n, &male, &female);
    printf("Gender count: M=%d, F=%d\n", male, female);
}

static void run_company_tasks(void) {
    InternationalCompany companies[20];
    size_t n = company_input_array(companies, 20);
    company_print_with_employees_gt(companies, n, 10000, ui_print_company);
}

int main(void) {
    for (;;) {
        ui_print_main_menu();
        int choice = ui_read_int("Select: ", 0, 3);

        if (choice == 0) {
            printf("Bye!\n");
            return 0;
        } else if (choice == 1) {
            run_date_tasks();
        } else if (choice == 2) {
            run_worker_tasks();
        } else if (choice == 3) {
            run_company_tasks();
        }
    }
}
