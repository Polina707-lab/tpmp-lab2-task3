#ifndef UI_H
#define UI_H

#include "models.h"
#include <stddef.h>

void ui_print_main_menu(void);
int  ui_read_int(const char *prompt, int min_value, int max_value);
double ui_read_double(const char *prompt, double min_value);
void ui_read_string(const char *prompt, char *buffer, size_t buffer_size);
char ui_read_gender(const char *prompt);

Date ui_read_date(const char *prompt);
void ui_print_date(const char *label, Date d);

void ui_print_worker(const WORKER2 *w, int index);

#endif