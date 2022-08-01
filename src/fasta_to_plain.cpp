#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include  <conio.h>

#define SEQLEN 20000

void DelHole(char *str)
{
	char *hole;

	hole = strstr(str, "\n");
	if (hole != NULL) *hole = 0;
}

int main(int argc, char *argv[])
{
	FILE *in, *out;
	char d[SEQLEN];
	int i;

	if (argc != 4)
	{
		printf("Command line error: %s 1 file_input_fasta 2file_out_plain 3(seq,head,len,content-atgcwrmkysbvhdnx)", argv[0]);
		exit(1);
	}
	if ((in = fopen(argv[1], "rt")) == NULL)
	{
		puts("Input file can't be opened");
		exit(1);
	}
	if ((out = fopen(argv[2], "wt")) == NULL)
	{
		puts("Output file can't be opened");
		exit(1);
	}
	int mode1;
	char mode[10];
	strcpy(mode, argv[3]);
	char mod = mode[0];
	switch (mod)
	{
	case 's':case 'S': {mode1 = 0; break; }// sequences only
	case 'h':case 'H': {mode1 = 1; break; }// headers only
	case 'l':case 'L': {mode1 = 2; break; }// lengths only
	case 'c':case 'C': {mode1 = 3; break; }// content only
	default: {printf("Wrong mode %s parameter, 1st letters SHLCshlc allowed\n", mode); exit(1); }
	}
	char c, symbol = '>';
	int sostav[16];
	for (i = 0; i < 16; i++)sostav[i] = 0;
	char alfavit4[] = "atgcATGC";
	//char alfavit[]="atgcwrmkysbvhdnATGCWRMKYSBVHDN",nka='n';	
	char alfavit11[] = "wrmkysbvhdnWRMKYSBVHDN";
	char alfavit15maska[] = "atgcwrmkysbvhdnxATGCWRMKYSBVHDNX";
	char alfavit15maska_low[] = "atgcwrmkysbvhdnx";
	char maska[] = "Xx";
	if (mode1 == 3)fprintf(out, "%s\n", alfavit15maska_low);
	int n = 0;
	int len = 0;
	int mono[SEQLEN];
	for (i = 0; i < SEQLEN; i++)
	{
		mono[i] = 0;
	}
	long double sum_len = 0;
	int fl = 1;
	do
	{
		c = getc(in);
		if (c == EOF)fl = -1;
		if (c == symbol || fl == -1)
		{
			if (n > 0)
			{
				if (n % 5000 == 0)printf("\b\b\b\b\b%d", n);
				if (mode1 == 2)
				{
					fprintf(out, "%d\n", len);
					sum_len += (long double)len;
					if (n % 100000 == 0)
					{
						printf("N = %d\tCommon Lenght =  %.lf\n", n, sum_len);
					}
				}
				if (mode1 == 0)fprintf(out, "\n");
				if (mode1 == 3)
				{
					fprintf(out, "%d", n);
					for (i = 0; i < 16; i++)fprintf(out, "\t%d", sostav[i]);
					for (i = 0; i < 16; i++)sostav[i] = 0;
					fprintf(out, "\n");
				}
			}
			if (c == symbol)n++;
			if (fl != -1)if (mode1 == 2 || mode1 == 3)len = 0;
			if (fl == 1)
			{
				fgets(d, sizeof(d), in);
				if (mode1 == 1)fprintf(out, "%s", d);
				continue;
			}
		}
		if (c == '\n')continue;
		if (c == '\t')continue;
		if (c == ' ')continue;
		if (c == '\r')continue;
		if (fl == 1)
		{
			if (mode1 == 0)
			{
				if (strchr(alfavit4, c) != NULL)
				{
					fprintf(out, "%c", c);
				}
				else
				{
					if (strchr(alfavit11, c) != NULL)
					{
						fprintf(out, "%c", c);
					}
					else
					{
						if (c == maska[0] || c == maska[1])
						{
							fprintf(out, "%c", c);
						}
						else
						{
							printf("Wrong %c symbol found!", c);
							exit(1);
						}
					}
				}
			}
			if (mode1 == 2)
			{
				int cint = (int)c;
				if (strchr(alfavit15maska, cint) != NULL)len++;
			}
			if (mode1 == 3)
			{
				int bit;
				int cint = (int)c;
				if (strchr(alfavit4, cint) != NULL)mono[len]++;
				if (strchr(alfavit15maska, cint) != NULL)len++;
				if (cint < 97) cint += 32;//A->a
				char *loc;
				loc = strchr(alfavit15maska_low, cint);
				if (loc != NULL)
				{
					bit = loc - alfavit15maska_low;
					sostav[bit]++;
				}
			}
		}
	} while (fl == 1);
	//  if(mode1==2)fprintf(out,"%d\n",len);
	  //printf("%d",n);
	fclose(in);
	//if(mode1==2)fprintf(out,"\n");
	fclose(out);/*
	if(mode1==2)
	{
		printf("Nseq = %d\tCommon length = %.lf\tAverage length %.f",n,sum_len,sum_len/n);
	} */
	if ((out = fopen("fasta_to_plain.length", "at")) == NULL)
	{
		puts("Output file can't be opened");
		exit(1);
	}
	fprintf(out, "Nseq\t%d\tCommon length\t%.lf\tAverage length\t%.f\n", n, sum_len, (double)sum_len / n);
	fclose(out);
	/*
	if ((out = fopen("throw_real", "wt")) == NULL)
	{
		puts("Output file can't be opened");
		exit(1);
	}
	for (i = 0; i < n; i++)fprintf(out, "0\n");
	fclose(out);
	*/
	if (mode1 == 3)
		if ((out = fopen("fasta_to_plain.mono", "at")) == NULL)
		{
			puts("Output file can't be opened");
			exit(1);
		}
	fprintf(out, "%s", argv[1]);
	for (i = 0; i < len; i++)fprintf(out, "\t%d", mono[i]);
	fprintf(out, "\n");
	fclose(out);
	return 1;
}