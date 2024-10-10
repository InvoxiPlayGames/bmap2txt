#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bmapEntry {
	unsigned int address;
	unsigned int stringOffset;
} bmapEntry;

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;
	
	char *in_filename = argv[1];
	//char *out_filename =argv[2];
	
	FILE *in_bmap = fopen(in_filename, "rb");
	//FILE *out_txt = fopen(out_filename, "wb");
	
	fseek(in_bmap, 0, SEEK_END);
	long filesize = ftell(in_bmap);
	fseek(in_bmap, 0, SEEK_SET);
	
	void *bmapBuf = malloc(filesize);
	fread(bmapBuf, 1, filesize, in_bmap);
	
	bmapEntry *entry = (bmapEntry *)bmapBuf;
	int num_entries = entry->stringOffset / sizeof(bmapEntry);
	for (int i = 0; i < num_entries; i++) {
		char *name = (char *)(bmapBuf + entry->stringOffset);
		printf("%s 0x%08x %c\n", name, entry->address, 'l');
		entry++;
	}
	
	free(bmapBuf);
	
	fclose(in_bmap);
	//fclose(out_txt);
	
	return 0;
}