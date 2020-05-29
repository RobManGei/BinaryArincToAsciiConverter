// BinaryArincToAscii.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

// returns number of TCHARs in string
int wstrlen(_TCHAR * wstr)
{
    int l_idx = 0;
    while (((char*)wstr)[l_idx]!=0) l_idx+=2;
    return l_idx;
}
 
  
// Allocate char string and copy TCHAR->char->string
char * wstrdup(_TCHAR * wSrc)
{
    int l_idx=0;
    int l_len = wstrlen(wSrc);
    char * l_nstr = (char*)malloc(l_len);
    if (l_nstr) {
        do {
           l_nstr[l_idx] = (char)wSrc[l_idx];
           l_idx++;
        } while ((char)wSrc[l_idx]!=0);
    }
    l_nstr[l_idx] = 0;
    return l_nstr;
}
 
  
 
// allocate argn structure parallel to argv
// argn must be released
char ** allocate_argn (int argc, _TCHAR* argv[])
{
    char ** l_argn = (char **)malloc(argc * sizeof(char*));
    for (int idx=0; idx<argc; idx++) {
        l_argn[idx] = wstrdup(argv[idx]);
    }
    return l_argn;
}
 
// release argn and its content
void release_argn(int argc, char ** nargv)
{
    for (int idx=0; idx<argc; idx++) {
        free(nargv[idx]);
    }
    free(nargv);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//Call must be with inputfile and outputfile
	if(argc != 3){
		std::cout << "Keine Parameter! Aufruf: binaryArincToAscii <infile> <outfile>" << std::endl;
		return 0;
	}

	char ** argn = allocate_argn(argc, argv);
    // Optionally #define argv argn
    
	FILE *f;
	FILE *g;
	long word = 0;
	long numArincWords = 0;
	char timestamp[13];


	fopen_s(&f, argn[1], "rb");
   	fopen_s(&g, argn[2], "a");

   //parse the inputfile
   while(!feof(f)){
	   
	   if(fread(&timestamp, sizeof(char) * 13, 1, f) > 0){
		   fread(&word, sizeof(long), 1, f);
		   numArincWords = word;
		   //write to outputfile
		   fprintf(g, "%s", timestamp);
		   fprintf(g, "\t");
		   fprintf(g, "%i", word);	
		   fprintf(g, "\t");
		   
		   for(int i = 0; i < numArincWords+2; i++){
			   fread(&word, sizeof(long), 1, f);
			   fprintf(g, "%i", word);	
			   fprintf(g, "\t");
		   }
		   
		   for(int i = 0; i < numArincWords+3; i++){
			   fread(&word, sizeof(long), 1, f);
			   fprintf(g, "%i", word);	
			   fprintf(g, "\t");
		   }

		//   fprintf(g, "\n");
	   }
	   
	   
   }
   fprintf(g, "\n");
   fclose(f);
   fclose(g);
   release_argn(argc, argn);

   return(0);
}

