#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "onepassasm.h"

void create_record(char *text_record, int *rstart);

int main(int argc, const char * argv[]) {
	int start, i, rstart;
	char text_record[500];
	
	FILE *f = fopen("copy.asm", "r");
	instruction *inst;
	symbol *label;
	opcode *opcode;
	
	if(!f) return -1;
	if(strequals((inst = getinstruction(f))->opcode, "START")) {
		start = hextoint(inst->operand);
		LOCCTR = start;
		sprintf(object_code[rec++], "H %-6s %06X %06X", inst->label, LOCCTR, 0);
	}
	else {
		LOCCTR = start = 0;
	}
	rstart = start;
	
	while (!strequals((inst = getinstruction(f))->opcode, "END")) {
		if (!strequals(inst->label, ".")) {	// If it is not a comment line
			printf("%3d. %06X\t%-10s\t%-10s\t%-10s\t\t", 
				LINE, LOCCTR, inst->label, inst->opcode, inst->operand);
			if(inst->label) {				// If there is a symbol in the LABEL field
				if((label = search_symtab(inst->label))) {
					// Label already there; forward referencing -> pop, add text records
					label->value = LOCCTR;
					list *ptr;
					char str[6];
					
					create_record(text_record, &rstart);
					for(ptr = label->list; ptr; ptr=ptr->next) {
						printf("%04X -> ", LOCCTR);
						sprintf(str, "%04X", LOCCTR);
						add_text_record(ptr->value, 2, str);
					}
					free(label->list);
				}
				else
					insert_symtab(inst->label, LOCCTR);
			}
			
			if ((opcode = search_optab(inst->opcode))) {
				printf("%02X", opcode->value);
				sprintf(endof(text_record), "%02X", opcode->value);
				if((label = search_symtab(inst->operand))) {	// Label in operand present in symtab
					if(!label->list) {	// If label has value
						printf("%04X", label->value);
						sprintf(endof(text_record), "%04X", label->value);
					}
					else {	// If label has list
						printf("%04X", 0);
						sprintf(endof(text_record), "%04X", 0);
						// print_list(label->list);
						insert_symtab_list(inst->operand, LOCCTR + 1);
					}
				}
				else {	// Label not in symtab
					printf("%04X", 0);
					sprintf(endof(text_record), "%04X", 0);
					if(inst->operand) {
						insert_symtab(inst->operand, 0);
						insert_symtab_list(inst->operand, LOCCTR + 1);
					}
				}
				LOCCTR += 3;
			}
			else if(strequals(inst->opcode, "WORD")) {
				printf("%06X", dectoint(inst->operand));
				sprintf(endof(text_record), "%06X", dectoint(inst->operand));
				LOCCTR += 3;
			}
			else if(strequals(inst->opcode, "RESW")) {
				LOCCTR += (3 *  dectoint(inst->operand));
			}
			else if(strequals(inst->opcode, "RESB")) {
				LOCCTR += dectoint(inst->operand);
			}
			else if(strequals(inst->opcode, "BYTE")) {
				char type = inst->operand[0];
				inst->operand += 2;
				inst->operand[strlen(inst->operand) - 1] = '\0';
				switch(type) {
					case 'C':
						for(i = 0; i < strlen(inst->operand); ++i) {
							printf("%02X", inst->operand[i]);
							sprintf(endof(text_record), "%02X", inst->operand[i]);
						}
						LOCCTR += strlen(inst->operand);
						break;
					case 'X':
						printf("%02X", hextoint(inst->operand));
						sprintf(endof(text_record), "%02X", hextoint(inst->operand));
						LOCCTR += strlen(inst->operand) / 2;
						break;
				}
			}
			sprintf(endof(text_record), " ");
			if(LOCCTR - rstart >= 0x1C) {
				create_record(text_record, &rstart);
			}
			printf("\n");
		}
	}
	create_record(text_record, &rstart);

	sprintf(object_code[rec++], "E %06X", LOCCTR);
	update_object_code_length(LOCCTR - start);
	print_object_code();
	fclose(f);
	return 0;
}

void create_record(char *text_record, int *rstart) {
	if(strlen_wows(text_record) > 0) {
		add_text_record(*rstart, (strlen_wows(text_record)) / 2, text_record);
		text_record[0] = '\0';
		*rstart = LOCCTR;
	}
}
