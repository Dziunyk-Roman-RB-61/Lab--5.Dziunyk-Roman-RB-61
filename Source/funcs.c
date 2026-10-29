#include "funcs.h" // підключення власного заголовка з прототипами та бібліотеками

double func(double x) // функція обчислення значення f(x) для заданого аргументу
{
    return x * x * x / 30.0 - 4.0 * x * x + 50.0; 
}

void print_output_data(double x1, double x2, unsigned int N, double delta, char* group, char* name) // функція виведення таблиці на екран та запису в текстовий файл
{
    unsigned int i; // лічильник циклу та номер точки
    double x; // поточне значення аргументу (тип double, з плаваючою комою подвійної точності)
    FILE* output_data_file; // вказівник на потік виведення в текстовий файл

    if((output_data_file = fopen("Texts/output_data.txt", "w")) != 0) { // створення текстового файлу для запису та перевірка успішності відкриття
        printf("+-------+------------+------------+\n"); // верхня межа таблиці на екрані
        printf("| No    |     x      |    f(x)    |\n"); // заголовок таблиці на екрані
        printf("+-------+------------+------------+\n"); // лінія під заголовком на екрані
        fprintf(output_data_file, "+-------+------------+------------+\n"); // верхня межа таблиці у файлі
        fprintf(output_data_file, "| No    |     x      |    f(x)    |\n"); // заголовок таблиці у файлі
        fprintf(output_data_file, "+-------+------------+------------+\n"); // лінія під заголовком у файлі

        for(i = 0; i < N; i++) { // цикл по всіх точках від 0 до N - 1
            x = x1 + i * delta; // обчислення аргументу від початкового значення без накопичення похибки
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x)); // рядок таблиці на екрані: номер, x, f(x)
            fprintf(output_data_file, "| %5u | %10.4lf | %10.4lf |\n", i + 1, x, func(x)); // той самий рядок у файлі
        } 

        printf("+-------+------------+------------+\n"); // нижня межа таблиці на екрані
        fprintf(output_data_file, "+-------+------------+------------+\n"); // нижня межа таблиці у файлі
        fprintf(output_data_file, "\n%s\n", group); 
        fprintf(output_data_file, "%s\n", name); 
        fclose(output_data_file); // закриття файлу зі скиданням буфера на диск
    } else { // файл не вдалося відкрити
        printf("Error! File cannot be opened 2"); // повідомлення про помилку
    }
} 

void write_bin_file(double x1, double x2, unsigned int N, double delta) // функція запису даних у бінарний файл
{
    unsigned int i; // лічильник циклу
    double x, y; // аргумент та значення функції
    FILE* bin_data_file; // вказівник на потік запису в бінарний файл

    if((bin_data_file = fopen("Texts/bin_data.bin", "wb")) != 0) { // створення бінарного файлу для запису (режим "wb") та перевірка відкриття
        fwrite(&N, sizeof(unsigned int), 1, bin_data_file); // запис кількості точок N у файл

        for(i = 0; i < N; i++) { // цикл по всіх точках
            x = x1 + i * delta; // обчислення аргументу
            y = func(x); // обчислення значення функції
            fwrite(&x, sizeof(double), 1, bin_data_file); // запис аргументу у файл
            fwrite(&y, sizeof(double), 1, bin_data_file); // запис значення функції одразу після аргументу
        } 

        fclose(bin_data_file); // закриття бінарного файлу
    } else { // файл не вдалося створити
        printf("Error! File cannot be opened 3"); // повідомлення про помилку
    }
} 

void print_bin_data(double x1, double x2, unsigned int N, double delta) // функція читання бінарного файлу та виведення даних на екран
{
    unsigned int i, count; // лічильник циклу та кількість точок, зчитана з файлу
    double* data; // вказівник на динамічний масив пар аргумент-значення
    FILE* bin_data_file; // вказівник на потік читання з бінарного файлу

    if((bin_data_file = fopen("Texts/bin_data.bin", "rb")) != 0) { // відкриття бінарного файлу для читання (режим "rb") та перевірка успішності
        fread(&count, sizeof(unsigned int), 1, bin_data_file); // зчитування кількості точок з файлу

        data = (double*)malloc(2 * count * sizeof(double)); 
        if(data == NULL) { // перевірка успішності виділення пам'яті
            printf("Error! Memory cannot be allocated"); 
            fclose(bin_data_file); 
            return; 
        }

        fread(data, sizeof(double), 2 * count, bin_data_file); // зчитування всіх пар значень у масив одним викликом
        fclose(bin_data_file); // закриття файлу, оскільки дані вже в пам'яті

        printf("+-------+------------+------------+\n"); 
        printf("| No    |     x      |    f(x)    |\n"); 
        printf("+-------+------------+------------+\n"); 
        for(i = 0; i < count; i++) { // цикл по всіх зчитаних точках
            printf("| %5u | %10.4lf | %10.4lf |\n", i + 1, data[2 * i], data[2 * i + 1]); // номер точки, аргумент (індекс 2i) та значення функції (індекс 2i + 1)
        } 
        printf("+-------+------------+------------+\n"); // нижня межа таблиці

        free(data); 
    } else { 
        printf("Error! File cannot be opened 4"); 
    }
} 