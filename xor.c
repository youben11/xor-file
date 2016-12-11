#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc,char* argv[]){
	if(argc<3){
		printf("Usage: %s <inputFile> <outputFile>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *input,*output;
	
	if((input=fopen(argv[1],"r"))==NULL){
		printf("[-]Can't open \"%s\"\n",argv[1]);
		exit(EXIT_FAILURE);
	}

	if((output=fopen(argv[2],"w"))==NULL){
		printf("[-]Can't open \"%s\"\n",argv[2]);
		exit(EXIT_FAILURE);
	}

	struct stat st;
	char *key=malloc(0),c;
	int i=0,keysize=0;
	
	printf("[*]Enter the key:");

	while((c=getchar())!='\n'){
		key=realloc(key,keysize+1);
		key[keysize]=c;
		keysize++;
	}
	
	stat(argv[1],&st);
	
	for(int j=1;j<=st.st_size;j++){
		
		c=fgetc(input);
		fputc((int)(c)^(int)(key[i]),output);
		i=(i+1)%keysize;
	}
	
	fclose(input);
	fclose(output);
	puts("[+]DONE");

	return 0;
}