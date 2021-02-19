/***
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include "project.c"

#define EXIT 0
#define ADD_PROJECT 1
#define OPEN_PROJECT 2

int current_action;
int exit_prompt = 0;

void prompt_action()
{
	printf("Choose action:\n");
	scanf("%d", &current_action);
}

void action()
{
	switch (current_action)
	{
	case ADD_PROJECT:
		add_project();
		break;
	case OPEN_PROJECT:
		open_project();
		break;
	default:
		printf("No such action found\n");
		break;
	}
}

void start_manager()
{
	printf("Project Manager starting\n");
}

int main()
{

	start_manager();

	while (true)
	{

		prompt_action();

		if (current_action == EXIT)
		{
			break;
		}

		action();
	}
}