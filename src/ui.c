#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void flush_stdin_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

void ui_print_main_menu(void) {
    printf("\n=== MAIN MENU ===\n");
    printf("1) Date tasks (prev/next day, days in month)\n");
    printf("2) WORKER2 tasks\n");
    printf("0) Exit\n");
}

int ui_read_int(const char *prompt, int min_value, int max_value) {
    int x;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &x) == 1) {
            flush_stdin_line();
            if (x >= min_value && x <= max_value) return x;
            printf("Error: enter a value in [%d..%d]\n", min_value, max_value);
        } else {
            printf("Error: enter an integer\n");
            flush_stdin_line();
        }
    }
}

double ui_read_double(const char *prompt, double min_value) {
    double x;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%lf", &x) == 1) {
            flush_stdin_line();
            if (x >= min_value) return x;
            printf("Error: enter a value >= %.2f\n", min_value);
        } else {
            printf("Error: enter a number\n");
            flush_stdin_line();
        }
    }
}

void ui_read_string(const char *prompt, char *buffer, size_t buffer_size) {
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, (int)buffer_size, stdin)) {
            buffer[0] = '\0';
            return;
        }
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        if (buffer[0] == '\0') {
            printf("Error: empty string, try again.\n");
            continue;
        }
        return;
    }
}

char ui_read_gender(const char *prompt) {
    char s[16];
    for (;;) {
        ui_read_string(prompt, s, sizeof(s));
        if (strlen(s) == 1) {
            char g = (char)toupper((unsigned char)s[0]);
            if (g == 'M' || g == 'F') return g;
        }
        printf("Error: enter M or F\n");
    }
}

Date ui_read_date(const char *prompt) {
    Date d;
    printf("%s\n", prompt);
    d.year  = ui_read_int("  Year (e.g. 2025): ", 1, 9999);
    d.month = ui_read_int("  Month (1-12): ", 1, 12);
    d.day   = ui_read_int("  Day (1-31): ", 1, 31);
    return d;
}

void ui_print_date(const char *label, Date d) {
    printf("%s %04d-%02d-%02d\n", label, d.year, d.month, d.day);
}

void ui_print_worker(const WORKER2 *w, int index) {
    printf("[%d] code=%d, surname=%s, position=%s, gender=%c, sign=%04d-%02d-%02d, term=%d months, salary=%.2f\n",
           index,
           w->code,
           w->surname,
           w->position,
           w->gender,
           w->sign_date.year, w->sign_date.month, w->sign_date.day,
           w->term_months,
           w->salary);
}