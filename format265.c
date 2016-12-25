#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MaxLines 500
#define MaxChar 132

char output[MaxLines * MaxChar];
char fstring[MaxChar];
int FT = 0;
int LW = 0;
int linesize = 0;
int LM = 0;
int LS = 0;


int check(char* line){
	char second[MaxChar];
	strncpy(second, line, MaxChar);
	strtok(second, " \n");
	
	
	if(!strncmp(second, ".FT", MaxChar)){	
		char* A = strtok(NULL, " \n"); 
		if(!strncmp(A, "on", 3)){  
			FT = 1;
		}
		else{
			FT = 0;
		}
	}
		
		if(!strncmp(second, ".LS", MaxChar)){
			char* B = strtok(NULL, " \n");
			if(strncmp(B, "0", 3) == 0){
				LS = 0;
			}
			else{
				LS = 1;
			}
		} 
		
		if(!strncmp(second, ".LM", MaxChar)){  
			LM = atoi(strtok(NULL, " \n"));
			return 1;
		}
	
		if(!strncmp(second, ".LW", MaxChar)){  
			LW = atoi(strtok(NULL, " \n"));
			FT = 1;
			return 1;
		}	
	return 0;
}


 void format(char* line){
 	char* word = strtok(line," \n");
 	
 	while(word){
 	
 		if(LS == 1){
 			strncat(fstring, " \n", MaxChar);
 		}
 	
 		if(linesize + strlen(word) >= LW){
 			strncat(fstring, "\n", 1);
 			linesize = 0;
 			if(LS == 1 && linesize == LW){
 				strncat(fstring, " \n\n", 1);
 			}
 			
 			if(LM){
 				while(linesize < LM){
 					strncat(fstring, " ", 1);
 					linesize++;
 					}
 					if(LS == 1 && linesize == LM - 1){
 						strncat(fstring, "\n\n", 1);     
 					}
 				}
 			}
 			
 			else if(linesize >= LM + 1){
 				linesize++;
 				strncat(fstring, " ", 1);
 			}
 			linesize = linesize + strlen(word);
 			strncat(fstring, word, MaxChar);
 			word = strtok(NULL, " \n");
 		}
 	}

int main(int argc, char **argv){
	FILE *infile;
	char line[MaxChar]; 
  
	infile = fopen (argv[1], "r");
	if (infile == NULL) {
    fprintf(stderr, "%s: cannot open %s", argv[0], argv[1]);
	exit(1);
	}
	
	while (fgets(line, MaxChar, infile)){
		if(check(line) == 1){ 
			continue;
		}      
		
		
		if(LM){
		while(linesize < LM){
			strncat(fstring, " ", 1);
			linesize++;
			}
		}
		
		if(FT == 1 && !strncmp(line, "\n", 1)){
			strncat(output, "\n\n", MaxChar);
			linesize = 0;
		}
		
		if(FT == 1){
			format(line); 
			strncat(output, fstring, MaxChar);
			strncpy(fstring, "", MaxChar);
		}
		else{
			strncat(output, line, MaxChar);
		}
	}
	
	if(FT == 1){
		strncat(output, "\n", MaxChar);
	}
	printf("%s", output);	
}

		
	
	

