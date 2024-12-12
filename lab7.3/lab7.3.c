#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
    char date[11]; 
    float temperature;
    float humidity;
    float pressure;
    float wind_speed;
} WeatherRecord;
void addRecord(const char* filename) 
{
    FILE* file = fopen(filename, "ab");
    if (file == NULL) 
    {
        printf("Can`t open.\n");
        return;
    }
    WeatherRecord record;
    printf("Enert date (YYYY-MM-DD): ");
    scanf("%10s", record.date);
    printf("Enert temperature: ");
    scanf("%f", &record.temperature);
    printf("Enter wet: ");
    scanf("%f", &record.humidity);
    printf("¬вед≥ть тиск: ");
    scanf("%f", &record.pressure);
    printf("Enter wind speed: ");
    scanf("%f", &record.wind_speed);
    fwrite(&record, sizeof(WeatherRecord), 1, file);
    fclose(file);
    printf("Note is added\n");
}
void searchRecords(const char* filename, const char* criteria, float max_value)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Can`t open.\n");
        return;
    }
    WeatherRecord record;
    int found = 0;
    while (fread(&record, sizeof(WeatherRecord), 1, file)) 
    {
        float value = 0;
        if (strcmp(criteria, "temperature") == 0) value = record.temperature;
        else if (strcmp(criteria, "humidity") == 0) value = record.humidity;
        else if (strcmp(criteria, "pressure") == 0) value = record.pressure;

        if (value <= max_value) {
            printf("Date: %s, Temperature: %.2f, Wet: %.2f, Preser: %.2f, Wind speed: %.2f\n",
                record.date, record.temperature, record.humidity, record.pressure, record.wind_speed);
            found = 1;
        }
    }
    if (!found) 
    {
        printf("Notes with this did not find.\n");
    }
    fclose(file);
}
void calculateProbability(const char* filename, const char* criteria, float target_value) 
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Can`t open.\n");
        return;
    }
    WeatherRecord record;
    int count = 0, match = 0;
    while (fread(&record, sizeof(WeatherRecord), 1, file)) 
    {
        float value = 0;
        if (strcmp(criteria, "temperature") == 0) value = record.temperature;
        else if (strcmp(criteria, "humidity") == 0) value = record.humidity;
        else if (strcmp(criteria, "pressure") == 0) value = record.pressure;
        count++;
        if (value == target_value) 
        {
            match++;
        }
    }
    if (count > 0)
    {
        printf("Importance of internationality has appeared: %.2f дл€ %s: %.2f%%\n",
            target_value, criteria, (match / (float)count) * 100);
    }
    else 
    {
        printf("File is empty.\n");
    }
    fclose(file);
}
void importFromText(const char* binary_filename, const char* text_filename) 
{
    FILE* text_file = fopen(text_filename, "r");
    FILE* binary_file = fopen(binary_filename, "ab");
    if (text_file == NULL || binary_file == NULL) 
    {
        printf("Can`t open.\n");
        if (text_file) fclose(text_file);
        if (binary_file) fclose(binary_file);
        return;
    }
    WeatherRecord record;
    while (fscanf(text_file, "%10s %f %f %f %f", record.date, &record.temperature,
        &record.humidity, &record.pressure, &record.wind_speed) == 5) 
    {
        fwrite(&record, sizeof(WeatherRecord), 1, binary_file);
    }
    fclose(text_file);
    fclose(binary_file);
    printf("Import sucseed.\n");
}
int main() 
{
    const char* binary_file = "weather.dat";

    int choice;
    do
    {
        printf("\nћеню:\n");
        printf("1. Add note\n");
        printf("2. Search days by criterion\n");
        printf("3. Importance of internationality has appeared\n");
        printf("4. Import data from files\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
        case 1:
            addRecord(binary_file);
            break;
        case 2: 
        {
            char criteria[20];
            float max_value;
            printf("Enter criteria: (temperature/humidity/pressure): ");
            scanf("%s", criteria);
            printf("Enter max: ");
            scanf("%f", &max_value);
            searchRecords(binary_file, criteria, max_value);
            break;
        }
        case 3:
        {
            char criteria[20];
            float target_value;
            printf("Enter criteria: (temperature/humidity/pressure): ");
            scanf("%s", criteria);
            printf("Enter the desired value: ");
            scanf("%f", &target_value);
            calculateProbability(binary_file, criteria, target_value);
            break;
        }
        case 4:
        {
            char text_file[256];
            printf("Enter the name of the text file: ");
            scanf("%s", text_file);
            importFromText(binary_file, text_file);
            break;
        }
        case 5:
            printf("Exit.\n");
            break;
        default:
            printf("Wrong choice. Try again.\n");
        }
    } while (choice != 5);
    return 0;
}