#include "stdio.h"

#define Max_Chars 1024
#define Max_Lines 2048

int main(int argc , char* argv[]){
	FILE *file;
	char buffer[Max_Chars] = {};
	
	file = fopen("Names.txt" , "r");
	
	if(file == NULL){
	
		printf("File is not exist");
	}
	else{
		int LineNum = 0 , currentLine = 0;
		printf("enter the line number:\n");
		scanf("%d" , &LineNum);
		
		do{
			fgets(buffer , Max_Chars , file);
			if(currentLine == LineNum){
				printf("%s",buffer);
				break;
			}
			currentLine++;
		}while(currentLine != feof(file));
		}
}
