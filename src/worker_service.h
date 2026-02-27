#ifndef WORKER_SERVICE_H
#define WORKER_SERVICE_H

#include "models.h"
#include <stddef.h>

size_t worker_input_array(WORKER2 *arr, size_t max_n);
void worker_print_all(const WORKER2 *arr, size_t n, void (*printer)(const WORKER2*, int));

void worker_print_signed_less_than_year_ago(const WORKER2 *arr, size_t n, Date today,
                                            void (*printer)(const WORKER2*, int));

void worker_print_double_contracts(const WORKER2 *arr, size_t n,
                                  void (*printer)(const WORKER2*, int));

int worker_avg_term_for_position(const WORKER2 *arr, size_t n, const char *position, double *out_avg_months);

void worker_count_gender(const WORKER2 *arr, size_t n, int *out_male, int *out_female);

#endif
