#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct {
    char *name;
    char *description;
    char *usage;
    char *license;
    char *author;

    int versionMajor;
    int versionMinor;
    int versionPatch;

    char *buildDate;
    char *buildTime;
    char *buildAuthor;
} wkattributes;

void wkattributes_write(wkattributes *attr) {
    FILE *fp = fopen("wkattributes", "w");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(1);
    }
    fprintf(fp, "name: %s\n", attr->name);
    fprintf(fp, "description: %s\n", attr->description);
    fprintf(fp, "usage: %s\n", attr->usage);
    fprintf(fp, "license: %s\n", attr->license);
    fprintf(fp, "author: %s\n", attr->author);
    fprintf(fp, "versionMajor: %d\n", attr->versionMajor);
    fprintf(fp, "versionMinor: %d\n", attr->versionMinor);
    fprintf(fp, "versionPatch: %d\n", attr->versionPatch);
    fprintf(fp, "buildDate: %s\n", attr->buildDate);
    fprintf(fp, "buildTime: %s\n", attr->buildTime);
    fprintf(fp, "buildAuthor: %s\n", attr->buildAuthor);
    fclose(fp);
}

wkattributes *wkattributes_read() {
    FILE *fp = fopen("wkattributes", "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(1);
    }
    wkattributes *attr = malloc(sizeof(wkattributes));
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        char *key = strtok(line, ":");
        char *value = strtok(NULL, ":");
        if (strcmp(key, "name") == 0) {
            attr->name = value;
        } else if (strcmp(key, "description") == 0) {
            attr->description = value;
        } else if (strcmp(key, "usage") == 0) {
            attr->usage = value;
        } else if (strcmp(key, "license") == 0) {
            attr->license = value;
        } else if (strcmp(key, "author") == 0) {
            attr->author = value;
        } else if (strcmp(key, "versionMajor") == 0) {
            attr->versionMajor = atoi(value);
        } else if (strcmp(key, "versionMinor") == 0) {
            attr->versionMinor = atoi(value);
        } else if (strcmp(key, "versionPatch") == 0) {
            attr->versionPatch = atoi(value);
        } else if (strcmp(key, "buildDate") == 0) {
            attr->buildDate = value;
        } else if (strcmp(key, "buildTime") == 0) {
            attr->buildTime = value;
        } else if (strcmp(key, "buildAuthor") == 0) {
            attr->buildAuthor = value;
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }
    return attr;
}

int main(int argc, char *argv[]) {
    // Check if the user inputed either read or write
    if (argc < 2) {
        printf("Usage: %s [read|write]\n", argv[0]);
        return 1;
    } 
    if (strcmp(argv[1], "read") == 0) {
        printf("Reading...\n");
        return 0;
    } else if (strcmp(argv[1], "write") == 0) {
        printf("Writing...\n");
        return 0;
    } else {
        printf("Usage: %s [read|write]\n", argv[0]);
        return 1;
    }
}