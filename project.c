#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct record {
 char time[6];
 char name[30];
 char place[25];
 char duration[10];
 char note[500];
};
void password();
void addRecord();
void viewRecord();
void editRecord();
void deleteRecord();
void mainMenu();
int main() {
 password();
 return 0;
}
void password() {
 char pass[15], correct_pass[15] = "pass";
 printf("\nEnter password: ");
 scanf("%s", pass);
 if (strcmp(pass, correct_pass) == 0) {
 mainMenu();
 } else {
 printf("Incorrect password! Try again.\n");
 password();
 }
}
void mainMenu() {
 int choice;
 while (1) {
 printf("\n--- Personal Diary ---\n");
 printf("1. Add Record\n");
 printf("2. View Record\n");
 printf("3. Edit Record\n");
 printf("4. Delete Record\n");
 printf("5. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar(); // to consume newline
 switch (choice) {
 case 1: addRecord(); break;
 case 2: viewRecord(); break;
 case 3: editRecord(); break;
 case 4: deleteRecord(); break;
 case 5: exit(0);
 default: printf("Invalid choice. Try again.\n");
 }
 }
}
void addRecord() {
 FILE *fp;
 struct record rec;
 char filename[15];
 printf("Enter date (DD-MM-YYYY): ");
 scanf("%s", filename);
 fp = fopen(filename, "ab+");
 if (fp == NULL) {
 printf("Error opening file!\n");
 return;
 }
 printf("Enter time (HH:MM): ");
 scanf("%s", rec.time);
 getchar();
 printf("Enter name: ");
 fgets(rec.name, sizeof(rec.name), stdin);
 printf("Enter place: ");
 fgets(rec.place, sizeof(rec.place), stdin);
 printf("Enter duration: ");
 fgets(rec.duration, sizeof(rec.duration), stdin);
 printf("Enter note: ");
 fgets(rec.note, sizeof(rec.note), stdin);
 fwrite(&rec, sizeof(rec), 1, fp);
 fclose(fp);
 printf("Record added successfully.\n");
}
void viewRecord() {
 FILE *fp;
 struct record rec;
 char filename[15], time[6];
 int found = 0;
 printf("Enter date (DD-MM-YYYY): ");
 scanf("%s", filename);
 printf("Enter time (HH:MM): ");
 scanf("%s", time);
 fp = fopen(filename, "rb");
 if (fp == NULL) {
 printf("No records found for this date.\n");
 return;
 }
 while (fread(&rec, sizeof(rec), 1, fp)) {
 if (strcmp(rec.time, time) == 0) {
 printf("\nRecord Found:\n");
 printf("Time: %s\nName: %sPlace: %sDuration: %sNote:%s\n",rec.time, rec.name, rec.place, rec.duration, rec.note);
 found = 1;
 break;
 }
 }
 fclose(fp);
 if (!found) {
 printf("No record found at that time.\n");
 }
}
void editRecord() {
 FILE *fp;
 struct record rec;
 char filename[15], time[6];
 int found = 0;
 printf("Enter date (DD-MM-YYYY): ");
 scanf("%s", filename);
 printf("Enter time of record to edit (HH:MM): ");
 scanf("%s", time);
 fp = fopen(filename, "rb+");
 if (fp == NULL) {
 printf("No records found for this date.\n");
 return;
 }
 while (fread(&rec, sizeof(rec), 1, fp)) {
 if (strcmp(rec.time, time) == 0) {
 fseek(fp, -sizeof(rec), SEEK_CUR);
 printf("Enter new details:\n");
 printf("Enter time (HH:MM): ");
 scanf("%s", rec.time);
 getchar();
 printf("Enter name: ");
 fgets(rec.name, sizeof(rec.name), stdin);
 printf("Enter place: ");
 fgets(rec.place, sizeof(rec.place), stdin);
 printf("Enter duration: ");
 fgets(rec.duration, sizeof(rec.duration), stdin);
 printf("Enter note: ");
 fgets(rec.note, sizeof(rec.note), stdin);
 fwrite(&rec, sizeof(rec), 1, fp);
 found = 1;
 break;
 }
 }
 fclose(fp);
 if (found)
 printf("Record updated successfully.\n");
 else
 printf("Record not found.\n");
}
void deleteRecord() {
 FILE *fp, *temp;
 struct record rec;
 char filename[15], time[6];
 int found = 0;
 printf("Enter date (DD-MM-YYYY): ");
 scanf("%s", filename);
 printf("Enter time of record to delete (HH:MM): ");
 scanf("%s", time);
 fp = fopen(filename, "rb");
 if (fp == NULL) {
 printf("No records found for this date.\n");
 return;
 }
 temp = fopen("temp", "wb");
 while (fread(&rec, sizeof(rec), 1, fp)) {
 if (strcmp(rec.time, time) != 0) {
 fwrite(&rec, sizeof(rec), 1, temp);
 } else {
 found = 1;
 }
 }
 fclose(fp);
 fclose(temp);
 remove(filename);
 rename("temp", filename);
 if (found)
 printf("Record deleted successfully.\n");
 else
 printf("Record not found.\n");
}