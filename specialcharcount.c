/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */


#include <stdio.h> 
#include "count.h"



int isTextFile(char* file_name) {
  int i = 0;
  while (file_name[i] != '\0' && file_name[i] != '.') {i+=1;}
  if (file_name[i] == '.') {
    if (file_name[i+1] != 't')   {return 0;}
    if (file_name[i+2] != 'x') {return 0;}
    if (file_name[i+3] != 't') {return 0;}
    return 1;
  }
  else {
    return 0;
  }
}


void specialcharcount(char *path, char *filetowrite, long charfreq[])
{
      DIR* dir = opendir(path);
      struct dirent *dr;
      while ((dr = readdir(dir)) != NULL) {
        if (isTextFile(dr->d_name)) {
          char file_name[500];
          int i =0 ;
          while (path[i] != '\0') {
            file_name[i] = path[i];
            i += 1;
          }
          file_name[i] = '/';
          int j = i+1;
          i = 0;
          while (dr->d_name[i] != '\0') {
            file_name[j] = dr->d_name[i];
             i += 1;
             j+=1;
          }
          FILE* file = fopen(file_name,"r");
          int c;
          while ((c = getc(file)) != EOF ) {
            switch(c) {
              case ',':
                charfreq[0] += 1;
              break;
              case '.':
                charfreq[1] += 1;
              break;
              case ':':
                charfreq[2] += 1;              
              break;
              case ';':
                charfreq[3] += 1;
              break;
              case '!':
                charfreq[4] += 1;
              break;
              default:
              break;

            }


          }
        }
      }


      FILE* write_file = fopen(filetowrite, "w");
      
     fprintf(write_file, ", -> %ld\n", charfreq[0]);
     fprintf(write_file, ". -> %ld\n", charfreq[1]);
     fprintf(write_file, ": -> %ld\n", charfreq[2]);
     fprintf(write_file, "; -> %ld\n", charfreq[3]);
     fprintf(write_file, "! -> %ld\n", charfreq[4]);


		
}
/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'

  
  Output: a new file named as filetowrite with the frequency of the above special characters written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/

