#include<stdio.h>

main() {
	
}

int get_opcode(char *ch) {
	FILE *f = fopen("optab", "r");
	char mnemonic[10];
	int opcode;
	
	while(!feof(f)) {
		fscanf(f, "%s%x", mnemonic, &opcode);
		if(feof(f)) break;
		if(strcmp(mnemonic, ch) == 0) {
			fclose(f);
			return opcode;
		}
	}
	
	fclose(f);
	return -1;
}
