struct list {
	int value;
	struct list *next;
};
typedef struct list list;

typedef struct {
	char *label;
	char *opcode;
	char *operand;
} instruction;

typedef struct {
	char *name;
	int value;
} opcode;
typedef struct {
	char *name;
	int value;
	list *list;
} symbol;

// Data Structures
int LOCCTR;

opcode OPTAB[] = {
	{"STL", 0x14},
	{"JSUB", 0x48},
	{"LDA", 0x00},
	{"COMP", 0x28},
	{"JEQ", 0x30},
	{"J", 0x3C},
	{"STA", 0x0C},
	{"LDL", 0x08},
	{"RSUB", 0x4C},
	{"LDX", 0x04},
	{"TD", 0xE0},
	{"RD", 0xD8},
	{"STCH", 0x54},
	{"TIX", 0x2C},
	{"JLT", 0x38},
	{"STX", 0x10},
	{"LDCH", 0x50},
	{"WD", 0xDC}
};
int optab_size = sizeof(OPTAB) / sizeof(opcode);

symbol SYMTAB[100];
int symtab_size = 0;

char object_code[20][500];
int rec = 0;

int LINE = -1;

int hextoint(char *s) {
	int hex;
	sscanf(s, "%x", &hex);
	return hex;
}
int dectoint(char *s) {
	int dec;
	sscanf(s, "%d", &dec);
	return dec;
}
int gethex(FILE *f) {
	int x;
	fscanf(f, "%x", &x);
	return x;
}
char *getstring(FILE *f) {
	char *str = malloc(7);
	fscanf(f, "%s", str);
	return str;
}
int strequals(char *a, char *b) {
	return a && b && strcmp(a, b)==0;
}

symbol *search_symtab(char *label) {
	int i;
	for (i = 0; i<symtab_size; ++i) {
		if(strequals(SYMTAB[i].name, label)) {
			return &SYMTAB[i];
		}
	}
	return NULL;
}
opcode *search_optab(char *opcode) {
	int i;
	for (i = 0; i<optab_size; ++i) {
		if(strequals(OPTAB[i].name, opcode)) {
			return &OPTAB[i];
		}
	}
	return NULL;
}

list *create_node(int e, list *l) {
	list *temp = (list*) malloc(sizeof(list));
	temp->value = e;
	temp->next = l;
	return temp;
}
void print_list(list *head) {
	list *ptr;
	for(ptr = head; ptr; ptr = ptr->next) {
		printf(" %06X -> ", ptr->value);
	}
}

void insert_symtab(char *name, int value) {
	symbol *label;
	SYMTAB[symtab_size].name = name;
	SYMTAB[symtab_size].value = value;
	SYMTAB[symtab_size].list = NULL;
	symtab_size++;
}
void insert_symtab_list(char *label, int addr) {
	list *ptr;
	symbol *l = search_symtab(label);
	if(!l->list) {
		l->list = create_node(addr, NULL);
	}
	else {
		for(ptr=l->list; ptr->next; ptr = ptr->next);
		ptr->next = create_node(addr, NULL);
	}
}

instruction *getinstruction(FILE *f) {
	instruction *ins = (instruction*) malloc(sizeof(instruction));
	ins->label = getstring(f);
	if(strequals(ins->label, ".")) {
		while (getc(f)!='\n');
		LINE++;
		return ins;
	}
	if(strequals(ins->label, "-")) {
		ins->label = NULL;
	}
	ins->opcode = getstring(f);
	if (strequals(ins->opcode, "-")) {
		ins->opcode = NULL;
	}
	ins->operand = getstring(f);
	if (strequals(ins->operand, "-")) {
		ins->operand = NULL;
	}
	LINE++;
	return ins;
}
void add_text_record(int rstart, int rlen, char *text_record) {
	sprintf(object_code[rec++], "T %06X %02X %s", rstart, rlen, text_record);
}
void update_object_code_length(int length) {
	sprintf(object_code[0] + 16, "%06X", length);
}
void print_object_code() {
	int i;
	for(i=0; i<rec; ++i) {
		printf("%s\n", object_code[i]);
	}
}
char *endof(char *s) {
	return s + strlen(s);
}

int strlen_wows(char *str) { // String length without whitespaces
	int i = 0, count = 0;
	while(str[i] != '\0')
		if (str[i++] != ' ')
			count++;
	return count;
}