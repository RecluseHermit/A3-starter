/*
 * CSE30 WI22 HW3
 * Username: cse30wi22mt
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	/* Local Variables */
    char c_arg[] = "-c";
    int c_exist = strcmp(argv[1], c_arg);
    int num_cols, obuf_len, curr_idx, num_rows = 0;
    char *curr_str, *long_str = "";
    char **buf, **readbuffer = NULL;
    size_t read_line, *temp_n;
    // 0  means the last character is NOT a delimiter, 1 means it IS a delimiter
    int is_del = 0;

	/* save the other cli args */
    // no "-c" argument
    if(c_exist != 0) {
        num_cols = atoi(argv[1]);
        obuf_len = argc - 1;
    }

    // have "-c" argument
    else {
        num_cols = atoi(argv[2]);
        obuf_len = argc - 2;
    }

    // initialize the buf
    buf = malloc(sizeof(char*) * num_cols);

    // indices array and the size_t variable
    int obuf[obuf_len];

    // put indices in
    for(int i = argc - obuf_len + 1; i <= argc; i++) {
        if(atoi(argv[i]) >= 0) {
            obuf[i] = atoi(argv[i]);
        }

        // change negative values to positive values
        else {
            obuf[i] = atoi(argv[i]) +  num_cols;
        }
    }

	/* process the input as described in the writeup */
    while((read_line = getline(readbuffer, temp_n, stdin)) >= 0) {
        // set the curren index to 0
        curr_idx = 0;

        // set the longest to the first field
        if(num_rows == 0) {
            long_str = readbuffer[0];
        }

        // loop through readbuffer
        for(int i = 0; i < (int)read_line; i++) {
            // first index situation
            if(i == 0) {
                // change variables
                curr_str = readbuffer[i];
                buf[curr_idx] = curr_str;
                is_del = 0;
                curr_idx++;
            }

            // not first index situation
            else if(*readbuffer[i] != ' ' && *readbuffer[i] != '\t' &&
                    *readbuffer[i] != '\n' && is_del == 1) {
                // change variables
                curr_str = readbuffer[i];
                buf[curr_idx] = curr_str;
                is_del = 0;
                curr_idx++;
            }

            // delimiter situation
            else if((*readbuffer[i] == ' ' || *readbuffer[i] == '\t' ||
                    *readbuffer[i] == '\n') && is_del == 0) {
                // change variables
                *readbuffer[i] = '\0';
                is_del = 1;

                // compare current string with the longest string, then set value
                if(strcmp(long_str, curr_str) < 0) {
                    long_str = curr_str;
                }
            }
        }

        // print the first n-1 columns current record
        for(int i = 0; i < num_cols - 1; i++){
            printf("%s ", buf[i]);
        }

        // print the last column
        printf("%s\n", buf[num_cols-1]);

        // end variable changes
        num_rows++;
        readbuffer = NULL;
    }

	/* Format string for output to be printed when -c option is given */

    printf("Number of lines: %d\n "
           "Longest field: %d characters\n",
           num_rows, (int)strlen(long_str));
}
