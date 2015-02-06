#include<stdio.h>

void one_pass() {
	FILE *f = fopen("copy.asm", "r");
	char label[10], mnemonic[10], operand[10];
	while(!feof(f)) {
		fscanf(f, "%s", label);
		
		if(strcmp(label, ".") == 0) {
			while(fgetc(f) != '\n');
			continue;
		}
		
		fscanf(f, "%s%s", mnemonic, operand);
		if(feof(f)) break;
		printf("lab:%s mnem:%s op:%s\n", label, mnemonic, operand);
	}
	
	fclose(f);
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

main() {
	one_pass();	
}

