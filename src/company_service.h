#ifndef COMPANY_SERVICE_H
#define COMPANY_SERVICE_H

#include "models.h"
#include <stddef.h>

size_t company_input_array(InternationalCompany *arr, size_t max_n);
void company_print_with_employees_gt(const InternationalCompany *arr, size_t n, int threshold,
                                    void (*printer)(const InternationalCompany*, int));

#endif
