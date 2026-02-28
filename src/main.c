#include <stdio.h>

#include "ui.h"
#include "models.h"
#include "date_service.h"
#include "worker_service.h"

int main(void) {
    /* Demonstrate worker functions according to variant */

    WORKER2 workers[12];
    size_t n = worker_input_array(workers, 12);

    printf("\nAll workers:\n");
    worker_print_all(workers, n, ui_print_worker);

    Date today;
    for (;;) {
        today = ui_read_date("\nEnter today's date (for '< 1 year ago' check):");
        if (date_is_valid(today)) break;
        printf("Invalid date. Try again.\n");
    }

    /* workers who signed contract less than 1 year ago */
    worker_print_signed_less_than_year_ago(workers, n, today, ui_print_worker);

    /* workers with double contracts (same code appears >= 2 times) */
    worker_print_double_contracts(workers, n, ui_print_worker);

    /* average term for requested position */
    char pos[POSITION_MAX];
    ui_read_string("\nEnter position to compute average contract term: ", pos, sizeof(pos));
    double avg_months = 0.0;
    if (worker_avg_term_for_position(workers, n, pos, &avg_months)) {
        printf("Average term for position '%s' = %.2f months\n", pos, avg_months);
    } else {
        printf("No workers with position '%s'\n", pos);
    }

    /* count male/female */
    int male = 0, female = 0;
    worker_count_gender(workers, n, &male, &female);
    printf("Gender count: M=%d, F=%d\n", male, female);

    return 0;
}