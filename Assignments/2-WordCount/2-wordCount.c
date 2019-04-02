/* ------------------------------------------------------------------------------ 
 *   Author         : HARISH
 *   Date           : Thu Mar 27
 *   File           : my_copy.c
 *   Title          : word count implementation using SystemCalls
 *   Description    : This program counts the characters, words, lines in a 
 *                    file and prints the output in the stdout file.
 * ---------------------------------------------------------------------------- */
#include "common.h"

int main(int argc, char **argv)
{
        /**************** Declare all the variables ****************/
        int fs;
        char ch, lastc = '\0';
        char buf[9] = {'\0'};
        
        int index = 0, times = 0;
        int lc, wc, cc, tc, tw, tl;
        lc = wc = cc = tc = tw = tl = 0;

        int i = 0, key = 0;
        while (i < argc)
        {
                if (argv[i][0] != '.' && argv[i][0] != '-')
                {
                        key = 1;
                        break;
                }
                else
                        ++i;

        }
       /***************** If no arguments are passed through command line ****************/ 
        if (key == 0) {
                printf("No file names mentioned through command line, enter something:\n");
                while ((ch = getchar()) != EOF)
                {
                        if (ch == ' ' && lastc != ' ') {
                                ++cc, ++wc;
                        } else if (ch == '\n') {
                                ++cc, ++wc, ++lc;
                        } else
                                ++cc;
                        lastc = ch;
                }
                while ((ch = getopt(argc, argv, "lwc")) != -1)
                {
                        switch (ch)
                        {
                                case 'c':
                                        printf("%5d ", cc);
                                        break;
                                case 'w':
                                        printf("%5d ", wc);
                                        break;
                                case 'l':
                                        printf("%5d ", lc);
                                        break;
                                default:
                                        printf("Undefined option -%c\n", ch);
                                        return 0;
                        }
                        ++times;
                }
                if (!times)
                        printf("%5d %5d %5d\n", lc, wc, cc);
                else
                        putchar('\n');
                return 0;
        }

        /**************** Else if arguments are present ****************/
        int argcount = argc;
        while ((ch = getopt(argc, argv, "lwc")) != -1);

        while (argv[index] != NULL && index < argcount)
        {
                 if (argv[index][0] == '-' || argv[index][0] == '.') {
                        ++index;
                        continue;
                }

        /* open the files */
                fs = open(argv[index], O_RDONLY);
        /* do error checking */
                if (fs == -1) {
                        perror(argv[index]);
                        exit(2);
                }
                else
                        ++times;

        /**************** start counting the words, lines and characters ******************/
                int count;
                lc = wc = cc = 0;
                while ((count = read(fs, buf, 8)) > 0)
                {
                        int i = 0;
                        while ((ch = buf[i]) != '\0' && ch != EOF && i < 9)
                        {
                                if (buf[i] == ' ' && lastc != ' ') {
                                        ++cc, ++wc;
                                } else if (buf[i] == '\n') {
                                        ++cc, ++wc, ++lc;
                                } else
                                        ++cc;

                                ++i;
                                lastc = ch;
                        }
                        memset(buf, 0, 8);
                }
                /* close the file once done */
                close(fs);


        /************************* print the word, line, character counts **********************/
                char ch1 = '\0';   int flag = 0;
                optind = 1;
                while ((ch1 = getopt(argc, argv, "lwc")) != -1)
                {
                        switch (ch1)
                        {
                                case 'c':
                                        printf("%5d ", cc);
                                        tc += cc;
                                        break;
                                case 'w':
                                        printf("%5d ", wc);
                                        tw += wc;
                                        break;
                                case 'l':
                                        printf("%5d ", lc);
                                        tl += lc;
                                        break;
                                default:
                                        printf("Undefined option -%c\n", ch1);
                                        return 0;
                        }
                        flag = 1;
                }
                
                /* print the file name */
                if (flag == 1)
                        printf("%10s\n", argv[index]);
                
                ++index;
                flag = 0;
        }

        /********************* print the total *******************/
        char ch1; optind = 1;
        if (times > 1) {
                while ((ch1 = getopt(argc, argv, "lwc")) != -1)
                {
                        switch (ch1)
                        {
                                case 'c':
                                        printf("%5d ", tc);
                                        break;
                                case 'w':
                                        printf("%5d ", tw);
                                        break;
                                case 'l':
                                        printf("%5d ", tl);
                                        break;
                                default:
                                        printf("Undefined option -%c\n", ch1);
                                        return 0;
                        }
                }
                printf("%10s\n", "total");
        }
        return 0;
}
