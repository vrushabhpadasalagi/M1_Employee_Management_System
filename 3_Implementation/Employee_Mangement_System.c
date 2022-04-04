// C program for the Employee Management System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// structure of Employee
struct emp {
	char name[100];
	float salary;
	int age;
	int id;
};
struct emp E;

// size of the structure
long int size = sizeof(E);

// In the start coordinates, will be 0, 0

COORD cord = { 0, 0 };

// function to set the coordinates
void gotoxy(int a, int b)
{
	cord.X = a;
	cord.Y = b;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		cord);
}

FILE *fp, *ft;

// Function to add the records
void addrecord()
{
	system("cls");
	fseek(fp, 0, SEEK_END);
	char another = 'b';

	while (another == 'b') {
		printf("\nEnter Name : ");
		scanf("%s", E.name);

		printf("\nEnter Age : ");
		scanf("%d", &E.age);

		printf("\nEnter Salary : ");
		scanf("%f", &E.salary);

		printf("\nEnter EMP-ID : ");
		scanf("%d", &E.id);

		fwrite(&E, size, 1, fp);

		printf("\nWant to add another"
			" record (Yes/No) : ");
		fflush(stdin);

		scanf("%c", &another);
	}
}

// Function to delete the records
void deleterecord()
{
	system("cls");
	char empname[100];
	char another = 'b';

	while (another == 'b') {
		printf("\nEnter employee "
			"name to delete : ");
		scanf("%s", empname);

		ft = fopen("temp.txt", "wb");
		rewind(fp);

		while (fread(&E, size,
					1, fp)
			== 1) {
			if (strcmp(E.name,
					empname)
				!= 0)
				fwrite(&E, size, 1, ft);
		}

		fclose(fp);
		fclose(ft);
		remove("data.txt");
		rename("temp.txt", "data.txt");
		fp = fopen("data.txt", "rb+");

		printf("\nWant to delete another"
			" record (Yes/No) :");
		fflush(stdin);
		another = getche();
	}
}

// Function to display the record
void displayrecord()
{
	system("cls");

	// sets pointer to start of the file
	rewind(fp);

	printf("\n========================="
		"==========================="
		"======");
	printf("\nNAME\t\tAGE\t\tSALARY\t\t"
		"\tID\n",
		E.name, E.age,
		E.salary, E.id);
	printf("==========================="
		"==========================="
		"====\n");

	while (fread(&E, size, 1, fp) == 1)
		printf("\n%s\t\t%d\t\t%.2f\t%10d",
			E.name, E.age, E.salary, E.id);

	printf("\n\n\n\t");
	system("pause");
}

// Function to modify the record
void modifyrecord()
{
	system("cls");
	char empname[100];
	char another = 'b';

	while (another == 'b') {
		printf("\nEnter employee name"
			" to modify : ");
		scanf("%s", empname);

		rewind(fp);

		// While File is open
		while (fread(&E, size, 1, fp) == 1) {
			// Compare the employee name with ename
			if (strcmp(E.name, empname) == 0) {
				printf("\nEnter new name:");
				scanf("%s", E.name);
				printf("\nEnter new age :");
				scanf("%d", &E.age);
				printf("\nEnter new salary :");
				scanf("%f", &E.salary);
				printf("\nEnter new EMP-ID :");
				scanf("%d", &E.id);

				fseek(fp, -size, SEEK_CUR);
				fwrite(&E, size, 1, fp);
				break;
			}
		}

		// Ask for modifying another record
		printf("\nWant to modify another"
			" record (Yes/No) :");
		fflush(stdin);
		scanf("%c", &another);
	}
}

// Driver code
int main()
{
	int choice;

	// opening the file
	fp = fopen("data.txt", "rb+");

	// showing error if file is unable to open.
	if (fp == NULL) {
		fp = fopen("data.txt", "wb+");
		if (fp == NULL) {
			printf("\nCannot open file...");
			exit(1);
		}
	}

	system("Color 3F");
	printf("\n\n\n\n\t\t\t\t============="
		"============================="
		"===========");
	printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~");
	printf("\n\t\t\t\t==================="
		"============================="
		"=====");
	printf("\n\t\t\t\t[|:::>:::>:::>::> "
		"EMPLOYEE RECORD <::<:::<:::"
		"<:::|]\t");
	printf("\n\t\t\t\t==================="
		"============================="
		"=====");
	printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~");
	printf("\n\t\t\t\t====================="
		"==============================\n");
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t"
		"Developer : @VRUSHABH_PADASALAGI"
		"\n\n\t\t\t\t");

	system("pause");

	while (1) {
		// Clearing console and asking the user for input
		system("cls");
		gotoxy(30, 10);
		printf("\n1. ADD RECORD\n");
		gotoxy(30, 12);
		printf("\n2. DELETE RECORD\n");
		gotoxy(30, 14);
		printf("\n3. DISPLAY RECORDS\n");
		gotoxy(30, 16);
		printf("\n4. MODIFY RECORD\n");
		gotoxy(30, 18);
		printf("\n5. EXIT\n");
		gotoxy(30, 20);
		printf("\nENTER YOUR CHOICE...\n");
		fflush(stdin);
		scanf("%d", &choice);

		// Switch Case
		switch (choice) {
		case 1:

			// Add the records
			addrecord();
			break;

		case 2:

			// Delete the records
			deleterecord();
			break;

		case 3:

			// Display the records
			displayrecord();
			break;

		case 4:

			// Modify the records
			modifyrecord();
			break;

		case 5:
			fclose(fp);
			exit(0);
			break;

		default:
			printf("\nINVALID CHOICE...\n");
		}
	}

	return 0;
}
