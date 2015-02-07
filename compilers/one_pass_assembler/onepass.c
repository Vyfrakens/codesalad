#include<stdio.h>

typedef struct {
	char symbol[10];
	int value;
	linked_list link;
} symtab; // symtab as a binary file? using fread, fwrite?

typedef struct {
	int loc;
	linked_list *link;
} linked_list;

void one_pass() {
	FILE *f = fopen("copy.asm", "r");
	char label[10], mnemonic[10], operand[10];
	int staddr, locctr;
	while(!feof(f)) {
		fscanf(f, "%s", label);

		if(strcmp(label, ".") == 0) {
			while(fgetc(f) != '\n');
			continue;
		}

		fscanf(f, "%s%s", mnemonic, operand);
		if(feof(f)) break;
		if(strcmp(mnemonic, "START") == 0) {
			// TODO: Fishy Code Please Correct :D
			// basically perform conversion of string to hex
			//staddr = ;
			locctr = staddr;
		} else if(strcmp(label, "-") != 0) {
			// symtab lookup
				// insert fresh, or
				// insert and traverse linked list
		} else {
			// optab lookup
				// if not found in optab, run away
				// if found, move onto operand
				if(strcmp(operand, "-") != 0) {
					// check operand in symtab
						// if symtab has entry with value, substitute here
						// if entry with no value, add to end of linked list
						// if no entry, create one with null value and linked list
				}
		}
		
		
		// write object code
		// also check for size exceeding max size of T record
		
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

