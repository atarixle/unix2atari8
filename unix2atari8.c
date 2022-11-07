#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"str_replace.c"

int main(int argc, char* argv[]) {
	// printf("argc = %d\n", argc);
	unsigned char replace[]={155, 0};
	
	// replace[0]=(unsigned char)155; replace[1]=(unsigned char)0;
	
	if (argc<2) {
		printf("usage: %s unix_text_files\n", argv[0]);
		return 0;
	}
	
	if ((strcmp(argv[1], "--help") && strcmp(argv[1], "-h"))==0) {
		printf("\nreplaces UNIX linebreaks with Atari's CHR$(155)\n");
		printf("Outputs are named CONV0001.TXT, CONV0002.TXT and so on\n");
		printf("which works well with most Atari-DOSses and Emulators\n");
		printf("Files will be overwritten WITHOUT ANY WARNING!\n\n");
		return 0;
	}
	
	if ((strcmp(argv[1], "--version") && strcmp(argv[1], "-v"))==0) {
		printf("\n2021.04.04\n\n");
		return 0;
	}
	
	for(int i=1; i<argc; i++) {
		// printf("arg[%d]=\"%s\"\n", i, argv[i]);
		FILE *fp;
		
		fp=fopen(argv[i], "r");
		
		if (fp==NULL) {
			printf("File \"%s\" not found\n", argv[i]);
		} else {
			char *unix_text, *atari8_text;
			size_t size;
			char filename[20];
			fseek(fp, 0, SEEK_END); // seek to end of file
			size = ftell(fp); // get current file pointer
			fseek(fp, 0, SEEK_SET); // seek back to beginning of file
			// proceed with allocating memory and reading the file
			unix_text=(char*)malloc(size+1);
			fread(unix_text, 1, size, fp);
			fclose(fp);
			sprintf(filename, "CONV%04d.TXT", i);
			atari8_text=str_replace(unix_text, "\n", replace);
			if (atari8_text==NULL) {
				printf("Nothing to convert in file \"%s\"\n", argv[i]);
			} else {
				printf("Writing converted file \"%s\" to \"%s\"\n", argv[i], filename);
				fp=fopen(filename, "wb");
				fwrite(atari8_text, 1, size, fp);
				fclose(fp);
				free(atari8_text);
			}
			free(unix_text);
		}
	}
	
	return 0;
}
