//#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("usage: %s <structure name> <path to input file>\n",
			argv[0]);
		goto END;
	}

	FILE* f = fopen(argv[2], "rb");
	FILE* o = fopen(argv[1], "wb");

	if ( !f )
	{
		printf("can't open '%s'\n", argv[2]);
		goto END;
	}

	if (!o)
	{
		printf("can't open '%s'\n", argv[1]);
		fclose(f);
		goto END;
	}

	fprintf(o, "/* bin2header output - automatically generated */\n");
	fprintf(o, "unsigned char %s[] = {\n", argv[1]);

	while (1)
	{
		int i = 0;
		byte buf[16];
		int nread = fread(buf, sizeof(byte), sizeof(buf), f);
		if (nread <= 0 || feof(f))
			break;

		fprintf(o, "\t");
		for (i = 0; i < nread - 1; i++)
			fprintf(o, "0x%02x, ", buf[i]);

		fprintf(o, "0x%02x", buf[nread-1]);

		if (!feof(f))
			fprintf(o, ",\n");
		else
			fprintf(o, "\n");
	}

	fprintf(o, "};\n");
	fflush(o);

	fclose(f);
	fclose(o);

END:
	return 0;
}