#include<stdio.h>
#include<string.h>
#include<math.h>
struct {
	char symbol[10];
	int value;
	struct linked_list *link;
} symtab[100];
int sym_count = 0;

struct linked_list{
	int loc;
	struct linked_list *link;
};

void one_pass() {
	FILE *f = fopen("copy.asm", "r");
	char label[10], mnemonic[10], operand[10], obj[7];
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
			staddr = strtodec(mnemonic);
			locctr = staddr;
		} else if(strcmp(label, "-") != 0) {
			// symtab lookup
				// insert fresh, or
				// insert and traverse linked list
			//optab lookup
				// if not found in optab,
					//check if byte word resw resb
					//else print error and exit program
				// if found, move onto operand
		} else {
			// optab lookup
				// if not found in optab, error exit program
				if(get_opcode(mnemonic) == -1)
					return 1;
				// if found, move onto object code
				strcpy(obj, get_opcode(mnemonic));
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

int get_symtab_entry(char *ch) {
	int i;
	for(i = 0; i < sym_count; i++) {
		if(strcmp(symtab[i].symbol, ch) == 0)
			return symtab[i].value;
	}
	return -1;
}

void add_to_symtab(char *sym, int val) {
	int entry = get_symtab_entry(sym);
	if(entry == -1) {
		strcpy(symtab[sym_count].symbol, sym);
		symtab[sym_count].value = val;
		sym_count++;
	} else if(symtab[entry].value == -1) {
		symtab[entry].value = val;
		// traverse and solve ll replacing.
		symtab[entry].link = NULL;
	}
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
	
int strtodec(char* str) {
	char ch;
	int res = 0, i, x, len;
	for(len=0; str[len]!='\0'; ++len);
	for(i=0; i<len; ++i) {
		ch = str[i];
		x = (ch>='0'&&ch<='9')?(ch-'0'):((ch>='A'&&ch<='F')?(ch-'A'+10):(ch-'a'+10));
		res += x * pow(16, len-i-1);
	}
	return res;
}

main() {
	one_pass();
}

