#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 50

typedef struct Food {
	struct Food *llink; // Leading node
	char location[SIZE];// Position of food
	char name[SIZE];    // food
	char state[SIZE];   // unit of food (L, kg, etc.)
	int amount;         // amount of food
	struct Food *rlink; // next node
}Food;

Food *head, *tail;

void Initialize(); // initialization
void Run();
void Exit(); // Release the memory allocated before exiting

int main()
{
	Initialize(); // initialization
	Run();
	Exit(); //Release the memory allocated before exiting
	return 0;
}

void Initialize()
{
	head = (Food *)malloc(sizeof(Food)); // Create Dummy Node
	tail = (Food *)malloc(sizeof(Food)); // Create Dummy Node
	head->rlink = tail; // Set the front dummy node 'next' to 'tail'
	tail->llink = head; // Set the last dummy node 'prev' to 'head'
	head->llink = tail->rlink = NULL;
}

int SelectMenu(); // Menu output and selection
void AddFood(); // Add food to refrigerator
void UseFood(); // Use of food in the refrigerator
void RemoveFood(); // Remove food from the refrigerator
void URemoveFood(Food *seek, char *nm); // Removal by use of food
void FindFood(); // Search food
void ListFood(); // Food list
void ViewFood(Food *Fd); // Print food information

void Run()
{
	int key = 0;
	while ((key = SelectMenu()) != 0) // Repeat if the selected menu is not 0
	{
		getchar();
		switch (key) // select menu
		{
		case 1:
			AddFood();
			getchar();
			break;
		case 2:
			UseFood();
			getchar();
			break;
		case 3:
			RemoveFood();
			getchar();
			getchar();
			break;
		case 4:
			FindFood();
			getchar();
			getchar();
			break;
		case 5:
			ListFood();
			getchar();
			break;
		default:
			printf("Incorrect selection.\n");
			break;
		}
		system("cls");
	}
	printf("Exit the program\n");
}

int SelectMenu()
{
	int key = 0;
	printf("==Refrigerator Food Management Program==\n");
	printf("1. Add Food\n");
	printf("2. Use Food\n");
	printf("3. Remove Food\n");
	printf("4. Search Food\n");
	printf("5. Food List\n");
	printf("0. Exit the program\n");
	printf("=============================\n");
	printf("Select menu ");
	scanf_s("%d", &key);
	return key;
}

void AddFood()
{
	Food *Fd = 0;
	int a=0;

	Fd = (Food *)malloc(sizeof(Food)); // Structure memory allocation

	printf("Position : ");
	scanf_s("%s", Fd->location, sizeof(Fd->location));
	printf("Food : ");
	scanf_s("%s", Fd->name, sizeof(Fd->name));
	printf("Amount (enter up to units) : ");
	scanf_s("%d %s", &a, Fd->state, sizeof(Fd->state));
	Fd->amount = a;

	Fd->rlink = tail;
	Fd->llink = tail->llink;
	tail->llink->rlink = Fd;
	tail->llink = Fd;
}

void UseFood()
{
	int am = 0;
	char nm[50], st[50];
	Food *seek;
	printf("Food to use : ");
	scanf_s("%s", nm, sizeof(nm));
	printf("Amount to use : ");
	scanf_s("%d %s", &am, st, sizeof(st));

	for (seek = head->rlink; seek != tail; seek = seek->rlink)
	{
		if (strcmp(seek->name, nm) == 0)
		{
			if (seek->amount < am)
			{
				printf("We are short of food.\n");
				return;
			}
			else if (seek->amount == am)
			{
				printf("All the food is used.\n");
				URemoveFood(seek, nm);
				return;
			}
			else
			{
				seek->amount = seek->amount - am;
				return;
			}
		}
	}	
}

void RemoveFood()
{
	char name[50];
	Food *seek;
	printf("Food to remove : ");
	scanf_s("%s", name, sizeof(name));

	for (seek = head->rlink; seek != tail; seek = seek->rlink)
	{
		if (strcmp(seek->name, name) == 0)
		{
			// Adjust links in the linked list
			seek->llink->rlink = seek->rlink;
			seek->rlink->llink = seek->llink;
			free(seek); // Memory release
			printf("Removed\n");
			return;
		}
	}
	printf("There is no data\n");
}

void URemoveFood(Food *seek, char *nm)
{
	for (seek = head->rlink; seek != tail; seek = seek->rlink)
	{
		if (strcmp(seek->name, nm) == 0)
		{
			// Adjust links in the linked list
			seek->llink->rlink = seek->rlink;
			seek->rlink->llink = seek->llink;
			free(seek); // Memory release
			return;
		}
	}
}

void FindFood()
{
	char name[50];
	Food *seek;
	printf("Food to find : ");
	scanf_s("%s", name, sizeof(name));

	for (seek = head->rlink; seek != tail; seek = seek->rlink)
	{
		if (strcmp(seek->name, name)==0)
		{
			ViewFood(seek);
			return;
		}
	}
	printf("There is no data\n");
}

void ViewFood(Food *Fd)
{
	printf("Position : %s, Food : %s, Amounts : %d%s", Fd->location, Fd->name, Fd->amount, Fd->state);

	printf("\n");
}

void ListFood()
{
	Food *seek = 0;
	
	for (seek = head->rlink; seek != tail; seek = seek->rlink)
	{
		ViewFood(seek);
	}
}

void Exit()
{
	Food *seek = head;
	while (seek->rlink)
	{
		seek = seek->rlink;
		free(seek->llink);
	}
	free(seek);
}
