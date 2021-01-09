#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void installPackage(char* package) {

    // set command params
    char command[] = "apt-get install ";

    // create complete command
    int total_length = strlen(command) + strlen(package) + 1;
    char* complete_command = (char*)calloc(total_length, sizeof(char));
    strcat(complete_command, command);
    strcat(complete_command, package);

    // install package
    system(complete_command);
    system("clear");
    
    // free heap storage to prevent memory leak
    free(complete_command);
}

int isValidUrl(char* url) {

    // set command params
    char command[] = "wget ";
    char options[] = "--spider ";

    // find total length of complete command
    int total_length = strlen(command) + strlen(options) + strlen(url) + 1;
    
    // create full command
    char* complete_command = (char*) calloc(total_length, sizeof(char));
    strcat(complete_command, command);
    strcat(complete_command, options);
    strcat(complete_command, url);

    int result = -1;
    // if false is returned then the url is not wrong
    if(system(complete_command)) result = 0;
    else result = 1;

    // free heap storage to prevent memory leak
    free(complete_command);

    return result;
}

char* generateFilename(int* file_no) {

    // File name prefix and extension
    char prefix[] = "./temp";
    char extension[] = ".txt";

    // Convert file number to string
    char string_file_no[10];
    sprintf(string_file_no, "%d", *file_no);

    // Create file name
    int filename_len = strlen(prefix) + strlen(string_file_no) + strlen(extension) + 1;
    char* filename = (char*)calloc(filename_len, sizeof(char));
    strcat(filename, prefix);
    strcat(filename, string_file_no);
    strcat(filename, extension);

    // uncomment for big project
    // (*file_no)++;
    return filename;

}

void getPage(char *url, char* filename) {
    // set command params
    char command[] = "wget ";
    char options[] = "-O ";

    // find total length of command
    int total_length = strlen(command) + strlen(options) + strlen(filename) + strlen(url) + 1;

    // create complete command
    char* complete_command = (char*) calloc(total_length, sizeof(char));
    strcat(complete_command, command);
    strcat(complete_command, url);
    strcat(complete_command, " ");
    strcat(complete_command, options);
    strcat(complete_command, filename);
    
    // execute complete command
    system(complete_command);
    system("clear");
    
    // free heap storage to prevent memory leak
    free(complete_command);
}

int getFileSize(char* file) {
    struct stat st;
    stat(file, &st);

    return st.st_size;
}

char* readFile(char* file) {

    // get heap storage to store file contents
    char* webpage = (char*) calloc(getFileSize(file), sizeof(char));

    FILE *fp = fopen(file, "r");

    // Read the file till EOF hasn't been reached.
    while(!feof(fp)) {

        char* buff = (char*)calloc(100, sizeof(char));

        fread(buff, sizeof(char), 100, fp);
        strcat(webpage, buff);

        free(buff);

    }

    fclose(fp);

    return webpage;
}
/* Include other headers as needed */
int main()
{
    // install wget
    installPackage("wget");
    
    // set seed url
    char seed_url[] = "https://www.google.com/";
    int* file_no = (int*) calloc(1, sizeof(int));
    
    // check if the url is valid or not
    if(!isValidUrl(seed_url)) {
        printf("Not a valid url\n");
        return 0;
    }

    char* filename = generateFilename(file_no);

    // fetch the page
    getPage(seed_url, filename);

    // Display the downloaded page on terminal
    char* webpage = readFile(filename);

    printf("%s", webpage);

    return 0;
}
