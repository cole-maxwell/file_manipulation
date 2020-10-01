/* 
* Author : 
* Description:
*	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char ** fgetLines(FILE* f, int *nl)
{
	

	int cl = 2, i=0, c;
	char ** lines = malloc(cl*sizeof(char*));

	while ((c=fgetc(f))!=EOF)
	{			
		if (*nl>=cl){
			cl *= 2;
			lines = realloc(lines,cl*sizeof(char *));
		}

		int nc = 2;
		lines[*nl] = malloc(nc*sizeof(char));

		int j=0;
		while(c!='\n' && c!=EOF)
		{
			if (j>=nc)
			{
				nc*=2;
				lines[*nl] = realloc(lines[*nl],nc);
			} 

			lines[*nl][j++] = c;
			c=fgetc(f);
		}

		lines[*nl][j++] = '\n';
		lines[*nl][j++] = '\0';	
		lines[*nl] = realloc(lines[*nl],j);

		(*nl)++;
		if (c=='\0') break;
		
	}
	lines = realloc(lines,*nl*sizeof(char *));

	return lines;
}




char ** sgetWords(char *line, int *nw)
{
	int i=0,wl=0;

	char **	words = malloc((*nw+1)*sizeof(char*));
	words[*nw] = malloc(wl+1);

	for (;line[i]!=0;i++)
	{
		if (line[i] ==',' && wl!=0 )
		{			
			words[*nw][wl] = '\0';
			words = realloc(words, (++(*nw)+1)*sizeof(char *));
			wl = 0;
			words[*nw] =  malloc(wl+1);
		}else if (isalnum(line[i]))
		{
			words[*nw] = realloc(words[*nw], ++wl+1);
			words[*nw][wl-1] = line[i]; 
		}
	}

	if (wl!=0 )
	{			
		words[(*nw)++][wl] = '\0';
		return	words;		
	}

	words = realloc(words, (*nw) * sizeof(char *));
	if (*nw==0) free(words);
	return words;
	

}

char* cPrefix(char **words, int nw)
{
	int nc = 0, flag=1; 	

	while (words[0][nc]!='\0' && flag)
	{
		for (int j=1; j< nw;j++)
			if (words[j][nc] != words[0][nc])
			{ 
				flag=0;
				break;
			}
		nc++;
	}


	char *s = malloc(nc);
	memcpy(s,words[0],nc-1);
	s[nc] = 0;
	
	return s;

}





/*
	Do not modify the main function when submit.
	You can modify it when doing your homework.
*/

int main(int argc, char *argv[])
{

// Get test file name from commandline or default to test.txt
	char *fs = argc>2 ? argv[1] : "test.txt";
	FILE *f = fopen(fs,"r");

	
/*
	Read each line into lines, nl is the number of lines
*/
	int nl=0, nw=0;
	char **lines = fgetLines(f, &nl);

	for (int i = 0; i < nl; ++i)
	{	
/*
	Read each word into words, nw is the number of words for each line
	words should have separate memory than lines[i]
*/		
		nw=0;
		char **words= sgetWords(lines[i], &nw);
// Print out the common prefix of the words for each line
		if (nw==0) continue;
		
		printf("\nTotal: %d\n", nw);
		for (int i = 0; i < nw; ++i)
			printf("%s, ", words[i]);	

		printf("\nThe common prefix is: %s\n", cPrefix(words,nw));
		
		for (int i = 0; i < nw; ++i) free(words[i]);		
		free(words);

	}

	for (int i = 0; i < nl; ++i) free(lines[i]);		
	free(lines);


	fclose(f);



	return 0;
}