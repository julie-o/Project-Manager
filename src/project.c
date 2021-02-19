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

#define DATE_FORMAT "DD-MM-YYYY"
#define BUFFER_LENGTH 6

enum project_part
{
	title,
	description,
	tags,
	status,
	deadline,
	number_of_parts
};

typedef struct
{
	char title[MAX_NAME_SIZE];
	struct tm deadline;
	char description[MAX_DESC_SIZE];
	char tags[MAX_TAGS*MAX_TAGSIZE];
	int status;
} project_details;

typedef struct
{
	project_details details;

} project;

char *request_input(char *request, char* input, int size)
{
	printf("%s\n", request);
	fgets(input, size, stdin);
	input[strlen(input) - 1] = '\0';
	return input;
}

project_details init_details()
{
	project_details new_project;

	getchar();
	request_input("Name the project:", new_project.title, MAX_NAME_SIZE);
	request_input("Write a description:", new_project.description, MAX_DESC_SIZE);
	request_input("Add tags separated by commas:", new_project.tags, MAX_TAGS * MAX_TAGSIZE);

	char dl[sizeof(char) * strlen(DATE_FORMAT)];
	request_input("Deadline, in the format DD-MM-YYYY (leave empty if none):", dl, MAX_NAME_SIZE);
	int DD = 0, MM = 0, YYYY = 0;
	sscanf(dl, "%02d-%02d-%04d", &DD, &MM, &YYYY);
	struct tm deadline = {0};
	deadline.tm_mday = DD;
	deadline.tm_mon = MM;
	deadline.tm_year = YYYY;

	new_project.deadline = deadline;
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
	project_details new_project = init_details();

	char file_path[MAX_NAME_SIZE + strlen(FILETYPE) + strlen(FILELOCATION)];
	strcpy(file_path, FILELOCATION);
	strcat(file_path, new_project.title);
	strcat(file_path, FILETYPE);

	FILE *fp;
	fp = fopen(file_path, "w");
	fprintf(fp, "Name: %s\nDescription: %s\nTags: %s\nStatus: %s\nDeadline: %02d-%02d-%04d\n",
			new_project.title, new_project.description, new_project.tags, status_tostring(new_project.status),
			new_project.deadline.tm_mday, new_project.deadline.tm_mon, new_project.deadline.tm_year);
	fclose(fp);

	fp = fopen(ALL_PROJECTS, "a");
	fprintf(fp, "{%s}{%s}{%s}{%d}{%d-%d-%d}\n", new_project.title, new_project.description, new_project.tags, new_project.status,
			new_project.deadline.tm_mday, new_project.deadline.tm_mon, new_project.deadline.tm_year);
	fclose(fp);
}

void open_project()
{
	char name[MAX_NAME_SIZE];
	getchar();
	request_input("Name of file to open:", name, MAX_NAME_SIZE);

	char file_path[MAX_NAME_SIZE + strlen(FILETYPE) + strlen(FILELOCATION)];
	strcpy(file_path, FILELOCATION);
	strcat(file_path, name);
	strcat(file_path, FILETYPE);

	FILE *fp;

	char ch;
	char *line;
	int line_length = 0;
	line = malloc(BUFFER_LENGTH);

	enum project_part part = 0;

	fp = fopen(file_path, "r");
	while (part < number_of_parts)
	{
		while ((ch = fgetc(fp)) != '\n'){
			strncat(line, &ch, 1);
			if (strlen(line)==(BUFFER_LENGTH-1)){
				printf("%s", line);
				line[0] = '\0';
			}
		}

		printf("%s\n", line);
		line[0] = '\0';
		part = part + 1;
	}

	fclose(fp);
	if (line)
		free(line);
}