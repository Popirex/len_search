#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

void scanFolder(const char *path, int *fileCount, int *lineCount, int *charCount){

    DIR *dir = opendir(path);

    if(dir == NULL){
        perror("Unable to open the directory\n");
        return;
    }

    struct dirent *entry;
    char fullPath[1024];

    // while there are elements in the directory
    while((entry = readdir(dir)) != NULL){

        //ignore special files or folders
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        //ignore hidden files or folders
        if(entry->d_name[0] == '.'){
            continue;
        }

            snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

            if(entry->d_type == DT_REG) {
                printf("Opening file: %s\n", entry->d_name);
                (*fileCount)++;

                FILE *file = fopen(fullPath, "r");

                if(file) {
                    int c;
                    int lines = 0;
                    int chars = 0;

                    //iterate file characters until end of file
                    while((c = fgetc(file)) != EOF) {

                        if(c != ' ' && c != '\t' && c != '\n' && c != '\r'){
                            //if it's a real character increase the character counter
                            chars++;
                        }

                        if(c == '\n'){
                            //if it's a new line, increase the lines count
                            lines++;
                        }
                    }


                    // when done, close the file and update the counters

                    fclose(file);

                    *lineCount += lines;
                    *charCount += chars;
                }

            }

            else if(entry->d_type == DT_DIR){

                printf("Opening folder: %s\n", entry->d_name);
                //if it's a folder, recursively search inside of it
                scanFolder(fullPath, fileCount, lineCount, charCount);
            }
    
        }

    closedir(dir);
    

}


int main(int argc, char* argv[]) {


    if(argc < 2) {
        printf("Usage: %s path/to/check\n", argv[0]);
        exit(0);
    }

    int totalFiles = 0;
    int totalLines = 0;
    int totalChars = 0;

    scanFolder(argv[1], &totalFiles, &totalLines, &totalChars);


    printf("\n");
    printf("Folder: %s\n", argv[1]);
    printf("Total files: %d\n", totalFiles);
    printf("Total Lines: %d\n", totalLines);
    printf("Total characters: %d\n", totalChars);
    printf("\n");
    

    return 0;
}