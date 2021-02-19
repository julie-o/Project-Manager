#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants for project status
#define IN_PROGRESS 0
#define PAUSED 1
#define FINISHED 2
#define ALL_PROJECTS "data/all_projects.txt"

#define MAX_NAME_SIZE 30
#define MAX_DESC_SIZE 500
#define MAX_TAGS 10
#define MAX_TAGSIZE 16
#define FILETYPE ".txt"
#define FILELOCATION "data/projects/"

typedef struct
{
	char title[MAX_NAME_SIZE];
	char description[MAX_DESC_SIZE];
	char tags[MAX_TAGS*MAX_TAGSIZE];
	int status;
} project;

char *request_input(char *request, char* input, int size)
{
	printf("%s\n", request);
	fgets(input, size, stdin);
	input[strlen(input) - 1] = '\0';
	return input;
}

project init_details(){
	project new_project;
	
	getchar();
	request_input("Name the project:", new_project.title, MAX_NAME_SIZE);
	request_input("Write a description:", new_project.description, MAX_DESC_SIZE);
	request_input("Add tags separated by commas:", new_project.tags, MAX_TAGS * MAX_TAGSIZE);
	new_project.status = IN_PROGRESS;

	return new_project;
}

char* status_tostring(int status){
	switch (status){
		case IN_PROGRESS:
			return "In progress";
		case PAUSED:
			return "Paused";
		case FINISHED:
			return "Finished";
		default:
			return "Status unknown";
	}
}

void add_project()
{
	project new_project = init_details();

	char file_path[MAX_NAME_SIZE + strlen(FILETYPE) + strlen(FILELOCATION)];
	strcpy(file_path, FILELOCATION);
	strcat(file_path, new_project.title);
	strcat(file_path, FILETYPE);

	FILE *fp;
	fp = fopen(file_path, "w");
	fprintf(fp, "Name: %s\nDescription: %s\nTags: %s\nStatus: %s\n", new_project.title, new_project.description, new_project.tags, status_tostring(new_project.status));
	fclose(fp);

	fp = fopen(ALL_PROJECTS, "a");
	fprintf(fp, "{%s}{%s}{%s}{%d}\n", new_project.title, new_project.description, new_project.tags,new_project.status);
	fclose(fp);
}