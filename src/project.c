#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constants for project status
#define IN_PPROGRESS 0
#define PAUSED 1
#define FINISHED 2
#define ALL_PROJECTS "data/all_projects.txt"

#define MAX_NAME_SIZE 30
#define FILETYPE ".txt"
#define FILELOCATION "data/projects/"


struct project_details
{
	char *title;
	char *description;
	int status;
};

void add_project()
{
	printf("Name the project:\n");
	
	char name[MAX_NAME_SIZE];
	scanf("%s", name);

	char file_path[MAX_NAME_SIZE + strlen(FILETYPE) + strlen(FILELOCATION)];
	strcpy(file_path, FILELOCATION);
	strcat(file_path, name);
	strcat(file_path, FILETYPE);

	printf("Project saved in: %s\n", file_path);

	FILE *fp;
	fp = fopen(file_path, "w");

	fprintf(fp, "Project name: %s\n", name);
	fclose(fp);

	fp = fopen(ALL_PROJECTS, "a");
	fprintf(fp, "%s\n", name);
	fclose(fp);
}