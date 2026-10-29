#include "funcs.h"

double func(double x)
{
    return x * x * x / 30.0 - 4.0 * x * x + 50.0;
}

void print_output_data(double x1, double x2, unsigned int N, double delta, char* group, char* name)
{
    unsigned int i;
    double x;
    FILE* output_data_file;

    if((output_data_file = fopen("Texts/output_data.txt", "w")) != 0) {
        printf("+-------+------------+------------+\n");
        printf("| No    |     x      |    f(x)    |\n");
        printf("+-------+------------+------------+\n");
        fprintf(output_data_file, "+-------+------------+------------+\n");
        fprintf(output_data_file, "| No    |     x      |    f(x)    |\n");
        fprintf(output_data_file, "+-------+------------+------------+\n");

        for(i = 0; i < N; i++) {
            x = x1 + i * delta;
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x));
            fprintf(output_data_file, "| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x));
        }

        printf("+-------+------------+------------+\n");
        fprintf(output_data_file, "+-------+------------+------------+\n");
        fprintf(output_data_file, "\n%s\n", group);
        fprintf(output_data_file, "%s\n", name);

        fclose(output_data_file);
    } else {
        printf("Error! File cannot be opened 2");
    }
}

void write_bin_file(double x1, double x2, unsigned int N, double delta)
{
    unsigned int i;
    double x, y;
    FILE* bin_data_file;

    if((bin_data_file = fopen("Texts/bin_data.bin", "wb")) != 0) {
        fwrite(&N, sizeof(unsigned int), 1, bin_data_file);

        for(i = 0; i < N; i++) {
            x = x1 + i * delta;
            y = func(x);
            fwrite(&x, sizeof(double), 1, bin_data_file);
            fwrite(&y, sizeof(double), 1, bin_data_file);
        }

        fclose(bin_data_file);
    } else {
        printf("Error! File cannot be opened 3");
    }
}

void print_bin_data(double x1, double x2, unsigned int N, double delta)
{
    unsigned int i, count;
    double* data;
    FILE* bin_data_file;

    if((bin_data_file = fopen("Texts/bin_data.bin", "rb")) != 0) {
        fread(&count, sizeof(unsigned int), 1, bin_data_file);

        data = (double*)malloc(2 * count * sizeof(double));
        if(data == NULL) {
            printf("Error! Memory cannot be allocated");
            fclose(bin_data_file);
            return;
        }

        fread(data, sizeof(double), 2 * count, bin_data_file);
        fclose(bin_data_file);

        printf("+-------+------------+------------+\n");
        printf("| No    |     x      |    f(x)    |\n");
        printf("+-------+------------+------------+\n");
        for(i = 0; i < count; i++) {
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, data[2 * i], data[2 * i + 1]);
        }
        printf("+-------+------------+------------+\n");

        free(data);
    } else {
        printf("Error! File cannot be opened 4");
    }
}