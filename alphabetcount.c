/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
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

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:
      alphabetfreq[0]: the frequency of 'a'
      alphabetfreq[1]: the frequency of 'b'
         ... ...
      alphabetfreq[25]:the frequency of 'z'

  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     a -> 200
     b -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
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
            if (c < 97) {
              c+= 32;
            }
            if (c >= 97 && c <= 122) {
              alphabetfreq[c-'a'] += 1;
            }
          }
        }
      }

      printf("%s\n", filetowrite);


      FILE* write_file = fopen(filetowrite, "w");
      for (int k = 0; k < ALPHABETSIZE; k++) {
            fprintf(write_file, "%c -> %ld\n",'a' + k, alphabetfreq[k]);
      }		
  	
}
