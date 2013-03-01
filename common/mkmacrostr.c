/*
	Convert macro values to strings - compiler
	AUP2, Sec. 5.08 (not in book)

	7-May-2005: Change to initialize macrostr_db with assignments (in
	function macrostr_init) because macros don't necessarily expand
	to constants. (See also macrostr.c.)

	-----------------------------------------------------------------

	Copyright 2003 by Marc J. Rochkind. All rights reserved.
	May be copied only for purposes and under conditions described
	on the Web page www.basepath.com/aup/copyright.htm.

	The Example Files are provided "as is," without any warranty;
	without even the implied warranty of merchantability or fitness
	for a particular purpose. The author and his publisher are not
	responsible for any damages, direct or incidental, resulting
	from the use or non-use of these Example Files.

	The Example Files may contain defects, and some contain deliberate
	coding mistakes that were included for educational reasons.
	You are responsible for determining if and how the Example Files
	are to be used.

*/
#include "defs.h"

int main(int argc, char *argv[])
{
	FILE *in, *out1, *out2;
	char *file, *dir, s[100], cat[100], *macro, *desc, buf[200];
	int len, n = 0;

	if (argc < 2)
		file = "/aup/common/macrostr.txt";
	else {
		file = argv[1];
		if (argc < 3)
			dir = "/aup/common";
		else
			dir = argv[2];
	}
	(void)sprintf(buf, "%s/macrostr1.incl", dir);
	ec_null( out1 = fopen(buf, "w") )
	(void)sprintf(buf, "%s/macrostr2.incl", dir);
	ec_null( out2 = fopen(buf, "w") )
	ec_null( in = fopen(file, "r") )
	while (fgets(s, sizeof(s), in) != NULL) {
		for (len = strlen(s); len > 0 && isspace((int)s[len - 1]); len--)
			;
		s[len] = '\0';
		if (s[0] == '#') {
			fprintf(out1, "%s\n", s);
			fprintf(out2, "%s\n", s);
			continue;
		}
		if (s[len - 1] == ':') {
			strcpy(cat, s);
			cat[len - 1] = '\0';
		}
		else {
			macro = strtok(s, " \t");
			if (macro == NULL)
				continue;
			desc = strtok(NULL, "\t");
			if (desc == NULL)
				desc = "";
			else
				while (isspace((int)*desc))
					desc++;
			fprintf(out1, "{\"%s\", 0, \"%s\", \"%s\"},\n",
			  cat, macro, desc);
			fprintf(out2, "macrostr_db[%d].ms_code = (intptr_t)%s;\n", n++, macro);
		}
	}
	(void)fclose(in);
	(void)fclose(out1);
	(void)fclose(out2);
	exit(EXIT_SUCCESS);

EC_CLEANUP_BGN
	exit(EXIT_FAILURE);
EC_CLEANUP_END
}
