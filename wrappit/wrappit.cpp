// wrappit.cpp : Defines the entry point for the console application.
// 1.1

#include "stdafx.h"
// wrappit v 2.0


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
using namespace std;
//#include "z.h"

#pragma warning(disable:4996)

struct EXPORT_ITEM
{
	bool IsOnlyOrdinal;
	char in[300];
	char en[300];
	int o;
	int h;
	bool NoFrw;
};

vector<EXPORT_ITEM> v;

int main(int argc, char* argv[])
{
	printf("Wrappit v.2.1 . Copyright (C) Chourdakis Michael\r\n");
	printf("Usage: WRAPPIT <dll> <export path>\r\n");
	printf("==================================================================\r\n");

	if (argc < 3)
		return 0;
	char t1[1000] = { 0 };
	char t2[1000] = { 0 };
	char* at2;

	// 0. Copy Files
	sprintf(t2, "%s\\%s", argv[2], argv[1]);
	CopyFile(argv[1], t2, TRUE);
	strcpy(t1, argv[1]);
	at2 = strrchr(t1, '.');
	if (at2)
		*at2 = 0;
	sprintf(t2, "%s\\%sold.dll", argv[2], t1);
	CopyFile(argv[1], t2, TRUE);

	// 1. Parse Export tble
	sprintf(t1, "%s\\%s.EXPORTS", argv[2], argv[1]);
	_tprintf(_T("Step 1: Parsing %s...\r\n"), t1);
	FILE* fp = _tfopen(t1, _T("rb"));
	if (!fp)
	{
		sprintf(t1, "DUMPBIN.EXE /EXPORTS %s > %s\\%s.exports", argv[1], argv[2], argv[1]);
		system(t1);
		sprintf(t1, "%s\\%s.EXPORTS", argv[2], argv[1]);
		fp = _tfopen(t1, _T("rb"));
		if (!fp)
		{
			printf("Error 1: %s.exports file not found. \r\n", argv[1]);
			return 0;
		}
		printf("New EXPORTS file created; remember to edit it to specify exports\r\n");
	}
	int MSStart = 0;
	for (int i = 0;;)
	{
		char x[1000] = { 0 };
		EXPORT_ITEM e = { 0 };
		if (!fgets(x, 1000, fp))
			break;

		if (strnicmp(x, "EXPORT ord", 10) == 0) // tdump
		{
			//EXPORT ord:1141='AcceptEx' => 'MSWSOCK.AcceptEx'
			e.o = atoi(x + 11);
			sprintf(e.in, "__E__%u__", i);
			char* y = strchr(x, '\'');
			if (y)
			{
				y++;
				char* y2 = strchr(y, '\'');
				if (y2)
					*y2 = 0;
				strcpy(e.en, y);
				e.IsOnlyOrdinal = false;
			}
			else
			{
				e.IsOnlyOrdinal = true;
				sprintf(e.en, "___XXX___%u", i);
			}
			v.insert(v.end(), e);
		}
		else
		{
			if (strstr(x, "ordinal") != 0 && strstr(x, "hint") != 0 && strstr(x, "RVA") != 0)
			{
				MSStart = 1;
				continue;
			}
			if (!MSStart)
				continue;
			char* a1 = x;
			while (*a1 == ' ')
				a1++;
			if (*a1 == '\r' || *a1 == '\n')
			{
				if (MSStart == 1)
				{
					MSStart = 2;
					continue;
				}
				break;
			}
			e.o = atoi(a1);
			while (*a1 != ' ')
				a1++;
			while (*a1 == ' ')
				a1++;
			if (*a1 == '\r' || *a1 == '\n')
			{
				if (MSStart == 1)
				{
					MSStart = 2;
					continue;
				}
				break;
			}
			e.h = atoi(a1);
			while (*a1 != ' ')
				a1++;
			while (*a1 == ' ')
				a1++;
			if (*a1 == '\r' || *a1 == '\n')
			{
				if (MSStart == 1)
				{
					MSStart = 2;
					continue;
				}
				break;
			}
			if (*a1 >= 0x30 && *a1 <= 0x39) // RVA exists
			{
				while (*a1 != ' ')
					a1++;
				while (*a1 == ' ')
					a1++;
				if (*a1 == '\r' || *a1 == '\n')
					break;
			}

			sprintf(e.in, "__E__%u__", i++);
			e.IsOnlyOrdinal = false;
			if (strnicmp(a1, "[NONAME]", 8) == 0)
			{
				e.IsOnlyOrdinal = true;
				sprintf(e.en, "___XXX___%u", i);
			}
			else
			{
				for (int y = 0;; y++)
				{
					if (*a1 == ' ' || *a1 == '\r' || *a1 == '\n' || *a1 == '\t')
						break;
					e.en[y] = *a1++;
				}
			}
			e.NoFrw = false;
			if (e.en[0] == '*')
			{
				char aen[300] = { 0 };
				strcpy(aen, e.en + 1);
				strcpy(e.en, aen);
				e.NoFrw = true;
			}
			v.insert(v.end(), e);
		}
	}
	fclose(fp);
	_tprintf(_T("Step 1: %u exported functions parsed.\r\n"), v.size());
	printf("------------------------------------------\r\n");


	_tprintf(_T("Step 2: Generating First .DEF file %s.1.DEF ...\r\n"), argv[1]);
	sprintf(t1, "%s\\%s.1.def", argv[2], argv[1]);
	FILE* fdef = _tfopen(t1, _T("wb"));
	if (!fdef)
	{
		printf("Error 2: DEF file cannot be created.\r\n");
		return 0;
	}
	fprintf(fdef, "EXPORTS\r\n");
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].NoFrw)
			continue;

		if (v[i].IsOnlyOrdinal == false)
			fprintf(fdef, "%s @%u\r\n", v[i].en, v[i].o);
		else
			fprintf(fdef, "%s @%u NONAME\r\n", v[i].en, v[i].o);
		v[i].NoFrw = false;
	}
	fclose(fdef);
	_tprintf(_T("Step 2: %u exported functions written to DEF.\r\n"), v.size());
	printf("------------------------------------------\r\n");

	_tprintf(_T("Step 3: Generating Second .DEF file %s.2.DEF ...\r\n"), argv[1]);
	sprintf(t1, "%s\\%s.2.def", argv[2], argv[1]);

	fdef = _tfopen(t1, _T("wb"));
	if (!fdef)
	{
		printf("Error 2: DEF file cannot be created.\r\n");
		return 0;
	}
	fprintf(fdef, "EXPORTS\r\n");
	// Old name
	strcpy(t2, argv[1]);
	at2 = strrchr(t2, '.');
	if (at2)
		*at2 = 0;
	strcat(t2, "OLD");
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].NoFrw)
		{
			if (v[i].IsOnlyOrdinal == false)
				fprintf(fdef, "%s=%s @%u\r\n", v[i].en, v[i].in, v[i].o);
			else
				fprintf(fdef, "%s=%s @%u NONAME\r\n", v[i].en, v[i].in, v[i].o);
		}
		else
		{
			if (v[i].IsOnlyOrdinal == false)
				fprintf(fdef, "%s=%s.%s @%u\r\n", v[i].en, t2, v[i].en, v[i].o);
			else
				fprintf(fdef, "%s=%s.%s @%u NONAME\r\n", v[i].en, t2, v[i].en, v[i].o);
			v[i].NoFrw = false;
		}
	}
	fclose(fdef);
	_tprintf(_T("Step 3: %u exported functions written to DEF.\r\n"), v.size());
	printf("------------------------------------------\r\n");

	// Run LIB
	// LIB.EXE /DEF:
	sprintf(t1, "LIB.EXE /MACHINE:X86 /DEF:%s\\%s.1.def /OUT:%s\\%s.lib", argv[2], argv[1], argv[2], argv[1]);
	system(t1);


	// 
	_tprintf(_T("Step 4: Generating .CPP file %s.CPP...\r\n"), argv[1]);
	sprintf(t1, "%s\\%s.cpp", argv[2], argv[1]);

	strcpy(t2, argv[1]);
	at2 = strrchr(t2, '.');
	if (at2)
		*at2 = 0;
	strcat(t2, "OLD.DLL");

	FILE* fcpp = _tfopen(t1, _T("wb"));
	if (!fcpp)
	{
		printf("Error 3: CPP file cannot be created.\r\n");
		return 0;
	}

	// Write headers
	fprintf(fcpp, "#include <windows.h>\r\n");
	fprintf(fcpp, "#include <tchar.h>\r\n");
	//	fprintf(fcpp,"#pragma pack(1)\r\n\r\n\r\n");

	// Write variables
	fprintf(fcpp, "HINSTANCE hLThis = 0;\r\n");
	fprintf(fcpp, "HINSTANCE hL = 0;\r\n");
	fprintf(fcpp, "FARPROC p[%u] = {0};\r\n\r\n", v.size());

	// Write DllMain
	fprintf(fcpp, "BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)\r\n");
	fprintf(fcpp, "\t{\r\n");
	fprintf(fcpp, "\tif (reason == DLL_PROCESS_ATTACH)\r\n");
	fprintf(fcpp, "\t\t{\r\n");

	fprintf(fcpp, _T("\t\thLThis = hInst;\r\n"));
	fprintf(fcpp, _T("\t\thL = LoadLibrary(_T(\"%s\"));\r\n"), t2);
	fprintf(fcpp, "\t\tif (!hL) return false;\r\n");

	fprintf(fcpp, "\r\n\r\n");
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].NoFrw == false)
			continue;

		if (v[i].IsOnlyOrdinal == true)
			fprintf(fcpp, "\t\tp[%u] = GetProcAddress(hL,(LPCSTR)\"%u\");\r\n", i, v[i].o);
		else
			fprintf(fcpp, "\t\tp[%u] = GetProcAddress(hL,\"%s\");\r\n", i, v[i].en);
	}

	fprintf(fcpp, "\r\n\r\n");
	fprintf(fcpp, "\t\t}\r\n");

	fprintf(fcpp, "\tif (reason == DLL_PROCESS_DETACH)\r\n");
	fprintf(fcpp, "\t\t{\r\n");
	fprintf(fcpp, _T("\t\tFreeLibrary(hL);\r\n"));
	fprintf(fcpp, "\t\t}\r\n\r\n");


	fprintf(fcpp, "\treturn 1;\r\n");
	fprintf(fcpp, "\t}\r\n\r\n");


	// Write function to be exported
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].NoFrw == false)
		{
		}
		else
		{
			fprintf(fcpp, "// %s\r\nextern \"C\" __declspec(naked) void %s()\r\n", v[i].en, v[i].in);
			fprintf(fcpp, "\t{\r\n");
			fprintf(fcpp, "\t__asm\r\n");
			fprintf(fcpp, "\t\t{\r\n");

			fprintf(fcpp, "\t\tjmp p[%u*%u];\r\n", i, sizeof(void*));

			fprintf(fcpp, "\t\t}\r\n");
			fprintf(fcpp, "\t}\r\n\r\n");
		}
	}




	fclose(fcpp);
	return 0;
}