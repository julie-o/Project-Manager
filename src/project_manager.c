/***
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include "project.c"

#define EXIT 0
#define ADD_PROJECT 1

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
	case 1:
		add_project();
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