#include "funcs.h"

int main()
{
    double x1, x2, delta;
    unsigned int N;
    char group[20] = "";
    char name[100] = "";

    FILE* input_data_file;

    if((input_data_file = fopen("Texts/input_data.txt", "r")) != 0) {
        fscanf(input_data_file, "%lf", &x1);
        fscanf(input_data_file, "%lf", &x2);
        fscanf(input_data_file, "%u", &N);
        fscanf(input_data_file, "%lf", &delta);

        fscanf(input_data_file, "%s", group);
        fscanf(input_data_file, " %[^\r\n]", name);

        fclose(input_data_file);
    } else {
        printf("Error! File cannot be opened 1");
        return 0;
    }

    printf("x1: %lf\n", x1);
    printf("x2: %lf\n", x2);
    printf("N: %u\n", N);
    printf("delta: %lf\n", delta);
    printf("Group: %s\n", group);
    printf("Name: %s\n", name);

    print_output_data(x1, x2, N, delta, group, name);

    write_bin_file(x1, x2, N, delta);

    print_bin_data(x1, x2, N, delta);

    return 0;
}