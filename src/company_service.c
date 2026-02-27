#include "company_service.h"
#include "ui.h"
#include <stdio.h>

size_t company_input_array(InternationalCompany *arr, size_t max_n) {
    int n = ui_read_int("Enter number of companies (1..20): ", 1, 20);
    if ((size_t)n > max_n) n = (int)max_n;

    for (int i = 0; i < n; i++) {
        printf("\n--- Company #%d ---\n", i + 1);
        ui_read_string("Name: ", arr[i].name, sizeof(arr[i].name));
        ui_read_string("Website: ", arr[i].website, sizeof(arr[i].website));

        ui_read_string("HQ postal index: ", arr[i].hq_address.postal_index, sizeof(arr[i].hq_address.postal_index));
        ui_read_string("HQ country: ", arr[i].hq_address.country, sizeof(arr[i].hq_address.country));
        ui_read_string("HQ region/oblast: ", arr[i].hq_address.region, sizeof(arr[i].hq_address.region));
        ui_read_string("HQ district: ", arr[i].hq_address.district, sizeof(arr[i].hq_address.district));
        ui_read_string("HQ city: ", arr[i].hq_address.city, sizeof(arr[i].hq_address.city));
        ui_read_string("HQ street: ", arr[i].hq_address.street, sizeof(arr[i].hq_address.street));
        ui_read_string("HQ house: ", arr[i].hq_address.house, sizeof(arr[i].hq_address.house));
        ui_read_string("HQ apartment: ", arr[i].hq_address.apartment, sizeof(arr[i].hq_address.apartment));

        arr[i].market_years = ui_read_int("Market years (0..300): ", 0, 300);
        arr[i].employees = ui_read_int("Employees (0..2000000): ", 0, 2000000);
        arr[i].branches_europe = ui_read_int("Branches in Europe (0..5000): ", 0, 5000);
    }

    return (size_t)n;
}

void company_print_with_employees_gt(const InternationalCompany *arr, size_t n, int threshold,
                                    void (*printer)(const InternationalCompany*, int)) {
    printf("\n=== INTERNATIONAL COMPANIES WITH EMPLOYEES > %d ===\n", threshold);
    int any = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i].employees > threshold) {
            printer(&arr[i], (int)i);
            any = 1;
        }
    }
    if (!any) {
        printf("No companies match the condition.\n");
    }
}
