/*
 * CSE30 WI22 HW3
 * Username: cse30wi22mt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	/* Local Variables */
    size_t size_arg = 0; // size_t variable for getlines
    unsigned long str_len = 0; // maximum field count variable
    char  **buf, *curr_str,*readbuffer = NULL; // char pointers
    int *obuf, obuf_len, curr_idx, num_cols; // int variables
    int num_rows = 0, is_del = 0, c_exist = strcmp(argv[1], "-c"); // int variables

    // no "-c" argument
    if(c_exist != 0) {
        num_cols = atoi(argv[1]);
        obuf_len = argc - 2;
    }

    // yes "-c" argument
    else {
        num_cols = atoi(argv[2]);
        obuf_len = argc - 3;
    }

    // malloc memories
    buf = malloc(sizeof(char*) * num_cols);
    obuf = malloc(sizeof(int) * obuf_len);

    // set a temp index for obuf and put indices in
    for(int i = 0; i < obuf_len; i++) {
        // positive argument
        if((atoi(argv[argc - obuf_len + i])) >= 0)
            obuf[i] = atoi(argv[argc - obuf_len + i]);

        // negative argument to positive
        else
            obuf[i] = atoi(argv[argc - obuf_len + i]) +  num_cols;
    }

	/* process the input as described in the writeup */
    while(getline(&readbuffer, &size_arg, stdin) > 0) {
        // initialize variables
        curr_idx = 0;

        // loop through readbuffer
        for(int i = 0; readbuffer[i] != '\0'; i++) {
            // first character or first character after delimiter
            if((readbuffer[i] != ' ' && readbuffer[i] != '\t' &&
                    readbuffer[i] != '\n' && is_del == 1) || i == 0) {
                // change variables
                curr_str = &(readbuffer[i]);
                buf[curr_idx++] = &(readbuffer[i]);
                is_del = 0;
            }

            // first delimiter after character
            else if((readbuffer[i] == ' ' || readbuffer[i] == '\t' ||
                    readbuffer[i] == '\n') && is_del == 0) {
                // change variables
                readbuffer[i] = '\0';
                is_del = 1;

                // compare current with the longest string and set variables
                if(strlen(curr_str) > str_len)
                    str_len = strlen(curr_str);
            }
        }

        // print the columns for current record
        for(int i = 0; i < obuf_len-1; i++)
            printf("%s ", buf[obuf[i]]);
        printf("%s\n", buf[obuf[obuf_len-1]]);

        // variables change and free memories
        num_rows++;
        free(readbuffer);
        readbuffer = NULL;
    }

    // free memories
    if(readbuffer != NULL) {
        free(readbuffer);
        readbuffer = NULL;
    }
    free(obuf);
    free(buf);

	/* Format string for output to be printed when -c option is given */
    if(c_exist == 0)
        printf("Number of lines: %d\nLongest field: %ld characters\n", num_rows, str_len);
}
