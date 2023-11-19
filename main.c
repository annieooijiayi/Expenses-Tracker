#include <stdio.h>
#include <stdlib.h>
#include <time.h>>
void getTransactionDate(char date[]){
    int validDate = 0;
    while (!validDate){
        printf("Date (YYYY-MM-DD): ");
        if (scanf("%10s", date) != 1){
            while (getchar() != '\n');
        }else{
            int year,month,day;
            if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) == 3){
                if(year >= 1900 && month >= 1 && month <= 12 && day >=1 && day <= 31){
                    validDate = 1;
                }
            }
        }
        if (!validDate){
            printf(" Invalid date format. Please try again. \n");
        }
    }
}

void addTransaction(FILE *file, int option, char *date, float amount, char *category){
    if (option == 2){
        amount = -amount;
    }
    fprintf(file, "%s \t %s \t %.2f \n", date, category, amount);
}


void printTotal(FILE *file){
    rewind(file);

    float income = 0.0, expenses = 0.0;
    float amount;
    char category[30];
    char date[10];

    printf("\n ----- Monthly Expenses ----- \n");
    printf("%-20s%-20s%-20s\n", "Date", "Category", "Amount");

    while (fscanf(file, "%[^\t] \t %[^\t] \t %f", date, category, &amount)== 3){
        if (amount > 0){
            income += amount;
        }else{
            expenses += amount;
        }

        printf("%-20s%-20s%-20.2f\n", date, category, amount);

    }

    printf("\nTotal Income: %.2f\n", income);
    printf("Total Expenses: %.2f\n", expenses);
    printf("Net Income: %.2f\n", income+expenses);


}

int main()
{
    char date[10];
    float amount;
    char category[30];
    int option;
    FILE *file;

    time_t dt = time(NULL); //current time in seconds since epoch
    struct tm *month_year = localtime(&dt); // convert the time to 'struct my' containing the individual components of the time (year, month, day, etc.).
    char filename[50];

    strftime(filename, sizeof(filename), "Expenses_%b_%Y.txt", month_year);

    file = fopen(filename, "a+");

    if (file == NULL){
        file = fopen(filename, "w+");
        if (file == NULL){
            printf("Error opening the file.\n");
            return 1;
        }
    }

    printf("[1] Income\n");
    printf("[2] Expense\n");
    printf("Please choose an option below: ");
    scanf("%d", &option);
    while (option != 1 && option != 2){
        printf("Invalid input. Please select 1 or 2.\n");
        printf("[1] Income\n");
        printf("[2] Expense\n");
        printf("Please choose an option above: ");

        scanf("%d", &option);
    }

    printf("Please enter transaction details below: \n");

    getTransactionDate(date);

    printf("Amount: ");
    scanf("%f", &amount);

    printf("Category: ");
    scanf("%s", &category);

    addTransaction(file, option, date, amount, category);
    printTotal(file);

    fclose(file);

    return 0;

}
