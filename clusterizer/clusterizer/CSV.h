#pragma once
#include "FileIO 2.1 (24.06).h"

class CSV
    {
    private:
        char* buf = nullptr;
        long bufSize = 0;
        FileIO file;


        long n_rows = 0;
        long n_col = 0;

        char** strings = nullptr;

    public:
        CSV (char filename [])
            { 
            file.fastLoad (filename, buf, bufSize);

            long n_strings = 0;
            for (long i = 0; i < bufSize; i++)
                {
                if (buf [i] == '\n')
                    {
                    if (n_rows == 0)
                        n_col++;

                    n_rows++;
                    n_strings++;
                    buf [i] = '\0';
                    }

                else if (buf [i] == ';')
                    {
                    n_strings++;
                    buf [i] = '\0';

                    if (n_rows == 0)
                        n_col++;
                    }
                }

            // strings array allocation
            strings = (char**) calloc (n_strings, sizeof (char*));
            strings [0] = buf;
            
            // fills atrings array
            long strings_counter = 1;
            for (long i = 0; i < bufSize-1 && strings_counter < n_strings; i++)
                {
                if (buf [i] == '\0')
                    {
                    strings [strings_counter] = buf+(i+1);
                    strings_counter++;
                    }
                }
            }
        ~CSV ()
            {
            free (strings);
            free (buf);
            }


    public:
        char* get (unsigned long x, unsigned long y)
            { 
            if (x < n_col && y < n_rows)
                return strings [x+n_col*y];
            else
                return nullptr;
            }

        long width ()
            { 
            return n_col;
            }

        long height ()
            {
            return n_rows;
            }

        long size ()
            {
            return bufSize;
            }

        std::string getFullLine (unsigned long int row)
            { 
            std::string result;
            for (unsigned long int i = 0; i < n_col; i++)
                {
                result += get (i, row);
                
                if (i != n_col-1)
                    result += ';';
                }

            result += '\n';

            return result;
            }

    };
