#include "funcs.h" // підключення заголовка з прототипами функцій

int main() // головна функція програми
{
    double x1, x2, delta; // початкове та кінцеве значення аргументу, крок його зміни
    unsigned int N;
    char group[20] = ""; 
    char name[100] = ""; 

    FILE* input_data_file; // вказівник на потік читання вхідного файлу

    if((input_data_file = fopen("Texts/input_data.txt", "r")) != 0) { // відкриття вхідного файлу для читання та перевірка успішності
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

    printf("x1: %lf\n", x1); // контрольний вивід початкового значення аргументу
    printf("x2: %lf\n", x2); // контрольний вивід кінцевого значення аргументу
    printf("N: %u\n", N); // контрольний вивід кількості точок
    printf("delta: %lf\n", delta); // контрольний вивід кроку
    printf("Group: %s\n", group); // контрольний вивід шифру групи
    printf("Name: %s\n", name); // контрольний вивід прізвища та імені

    print_output_data(x1, x2, N, delta, group, name); // побудова таблиці, вивід на екран та запис у текстовий файл

    write_bin_file(x1, x2, N, delta); // запис кількості точок і пар значень у бінарний файл

    print_bin_data(x1, x2, N, delta); // читання бінарного файлу та вивід даних на екран

    return 0; 
} 