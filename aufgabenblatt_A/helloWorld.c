#include <stdio.h>

int main()
{
	/*1st Variables to save the input*/
	char* name[256];
	int age = 0;
	float height = 0;

	/*2nd Save input in the variables*/
	printf("Name: ");
	scanf("%s", &name);

	printf("Alter (in Jahre): ");
	scanf("%i", &age);

	printf("Groesse (in m): ");
	scanf("%f", &height);

	/*3rd Output of the sentence with the help of the variables*/
	printf("%s ist %i Jahr(e) alt und hat eine Groesse von %.2f Meter\n", name, age, height);
	return 0;
}
