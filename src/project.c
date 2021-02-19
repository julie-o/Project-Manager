#include <stdio.h>
#include <time.h>

//constants for project status
#define IN_PPROGRESS 0
#define PAUSED 1
#define FINISHED 2
#define ALL_PROJECTS "../data/all_projects.txt"

#define MAX_NAME_SIZE 50

struct project_details
{
	char *title;
	char *description;
	int status;
};

void add_project(char* name)
{
	FILE *fp = fopen(ALL_PROJECTS, "a");
	fprintf(fp, "%s\n", name);
	fclose(fp);
}