#define _CRT_SECURE_NO_WARNINGS

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
//#include  <conio.h>
#include  <math.h>
#include  <time.h>
#define SEQLEN 5000

void Mix(char *a, char *b)
{
	char buf = *a;
	*a = *b;
	*b = buf;
}
void BigMix1(char *d)
{
	int r;
	int len = strlen(d);
	static int m = 0;
	time_t t;

	t = time(NULL);
	if (m == 0){ srand((unsigned)t); m++; }
	for (r = 0; r<len - 1; r++) Mix(&d[r], &d[1 + r + (rand() % (len - 1 - r))]);
}
int IdeLet(char c)
{
	int ret;
	switch (c){
	case 'a': case 'A':ret = 0; break;
	case 't': case 'T':ret = 1; break;
	case 'g': case 'G':ret = 2; break;
	case 'c': case 'C':ret = 3; break;
	default: {ret = -1; }
	}
	return(ret);
}
void DelChar(char *str, char c)
{
	int i, lens, size;

	size = 0;
	lens = strlen(str);
	for (i = 0; i<lens; i++)
	{
		if (str[i] != c)str[size++] = str[i];
	}
	str[size] = '\0';
}
void DelHole(char *str)
{
	char *hole;

	hole = strstr(str, "\n");
	if (hole != NULL) *hole = 0;
}
char *TransStr(char *d)
{
	int i, c, lens;
	lens = strlen(d);
	for (i = 0; i<lens; i++)
	{
		c = int(d[i]);
		if (c<97) d[i] = char(c + 32);
		//	else break;
	}
	return(d);
}
int CheckStr(char* file, char* d, int n, int print)
{
	int i, len, ret;
	len = (int)strlen(d);
	ret = 1;
	for (i = 0; i < len; i++)
	{
		int di = (int)d[i];
		if (strchr("atgcATGC", di) != NULL)continue;
		if (strchr("nN", di) != NULL)
		{
			ret = 0; continue;
		}
		if (print == 1)printf("File %s; sequence %d position %d (%c) bad. Sequence deleted!\n", file, n, i + 1, d[i]);
		ret = -1;
		break;
	}
	return(ret);
}
void ReadSeq(char* filei, int len_min, int len_max, int height, char* fileo)
{
	char l[SEQLEN], d[SEQLEN], head[400];
	int fl = 0, t;
	FILE* in, *out;

	if ((in = fopen(filei, "rt")) == NULL)
	{
		printf("ReadSeq! Input file %s can't be opened!\n", filei);
		exit(1);
	}
	if ((out = fopen(fileo, "wt")) == NULL)
	{
		printf("ReadSeq! Output file %s can't be opened!\n", fileo);
		exit(1);
	}	
	char symbol = fgetc(in);
	rewind(in);
	int nn = 0, n = 0;
	while (n >= 0)
	{
		if (fgets(l, sizeof(l), in) == NULL) fl = -1;
		if (*l == '\n' && fl != -1)continue;
		if (((*l == symbol) || (fl == -1)) && (fl != 0))
		{
			int lenx = (int)strlen(d);
			int check = CheckStr(filei, d, nn, 0);
			nn++;
			if ((lenx >= len_min && lenx <= len_max) && check != -1)
			{
				TransStr(d);
				int len = strlen(d);
				d[len] = '\0';
				if (check != 0)
				{
					for (t = 0; t < height; t++)
					{
						BigMix1(d);
						fprintf(out, "%s_N%d_H%d\n%s\n", head, n, t + 1, d);
					}
				}
				else
				{
					int i;
					for (t = 0; t < height; t++)
					{
						BigMix1(d);						
						int pur = 0;
						int x = 'n';
						for (i = 0; i < len; i++)
						{
							if (d[i] != x)
							{
								pur++;
								if (pur > len_min)break;
							}
						}
						if (pur > len_min)
						{
							fprintf(out, "%s_N%d_H%d\n", head, n, t + 1);
							for (i = 0; i < len; i++)if (d[i] != x)fprintf(out, "%c", d[i]);
							fprintf(out, "\n");
						}
					}
				}
				n++;
			}
			else
			{
				if (lenx < len_min)
				{
					printf("ReadSeq! Short peak %d (Len %d) ignored\n", nn + 1, lenx);
				}
				if (lenx > len_max)
				{
					printf("ReadSeq! Long peak %d (Len %d) ignored\n", nn + 1, lenx);
				}
				if (check != 1)
				{
					printf("ReadSeq! Unusual symbol, peak %d partially ignored\n%s\n", nn + 1, d);
				}
			}
			if (fl == -1)
			{
				fclose(in);				
				break;
			}
		}
		if (*l == symbol)
		{
			memset(head, 0, sizeof(head));
			DelHole(l);
			strcpy(head, l);
			fl = 0; continue;
		}
		if (fl == 0)
		{
			memset(d, 0, sizeof(d));
			DelHole(l);
			strcpy(d, l);
			fl = 1; continue;
		}
		if (strlen(d) + strlen(l) > sizeof(d))
		{
			printf("Size is large...");
			printf("l:%s\nstrlen(l):%zu\n", l, strlen(l));
			printf("d:%s\nstrlen(d):%zu\n", d, strlen(d));
			exit(1);
		}
		DelHole(l);
		strcat(d, l);
	}
}
int main(int argc, char *argv[])
{
	char filei[500], fileo[500];
	int height;
	int len_min =6, len_max = SEQLEN;

	if (argc != 4)
	{
		puts("Syntax: 1<input_file> 2<output_file> 3<height>"); // 5<width> 6<join> 7<split>
		return 1;
	}
	strcpy(filei, argv[1]);
	strcpy(fileo, argv[2]);
	height = atoi(argv[3]);
	ReadSeq(filei, len_min,len_max,height,fileo);
	return 1;
}