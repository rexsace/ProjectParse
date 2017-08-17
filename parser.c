
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TH - TravelHawk	W - Wireshark
int main(void){
	char *filen = "parsed_training.txt";
	char *fn_TH = "training.rec";
	
	FILE *parsedfile = fopen(filen, "wb");
	FILE *TH = fopen(fn_TH, "rb");
	int i;
	
	if (parsedfile == NULL){
    	printf("Error opening file: %s\n", parsedfile);
    	exit(1);
	}
	
	if (TH == NULL){
    	printf("Error opening file: %s\n", fn_TH);
    	exit(1);
	}
	
	// GLOBAL PCAP HEADER
	i=0;
	unsigned char x;
	while(i<271){
		x = fgetc(TH);
		fprintf(parsedfile, "%c", x);
		i++;
	}
	char temp[] = "***GLOBAL HEADER***";
	fprintf(parsedfile, "%s", temp);
	// ****************************
	int psize = 480;
	int count = 0;
	int zero = 0;
	int upp_psize, low_psize;
	for(count=0; count <100; count++){
		strcpy(temp,"HEADER NO. ");
		fprintf(parsedfile, "**%s%d:**", temp, count+1);
		i=0;
		while(i<47){
			x = fgetc(TH);
			fprintf(parsedfile, "%c", x);
			i++;
		}
		i=0;
		while(i<4){
			x = fgetc(TH);
			fprintf(parsedfile, "%c", x);
			if(i==0)
				psize = x;
			else
				psize = psize | x<<8;
			i++;
		}
		psize = psize/8;
		
		strcpy(temp,"PACKET NO. ");
		fprintf(parsedfile, "**%s%d:**", temp, count+1);
		i=0;
		while(i<psize){
			x = fgetc(TH);
			fprintf(parsedfile, "%c", x);
			i++;
			if(i==100)
				break;
		}
	}
	
	fclose(parsedfile);
	
	return 0;
}
