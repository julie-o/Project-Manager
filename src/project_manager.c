/***
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include "project.c"

#define EXIT 0


int current_action;

void prompt_action(){
	printf("Choose action:\n");
	scanf("%d", &current_action);
}

void action(int current_action)
{
	switch (current_action) {
		case 0:
			break;
		default:
			// "No such action found"
			break;
	}
}

void start_manager(){
	printf("Project Manager starting\n");
}

int main()
{

	start_manager();

	while (true) {

		prompt_action();
		
		action(current_action);

		if (current_action==EXIT)
		{
			break;
		}
	}
}