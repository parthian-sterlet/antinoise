#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  <time.h>
#define Min(a,b) ((a)>(b))? (b):(a);
#define Max(a,b) ((a)>(b))? (a):(b);
#define NCHR 100

#include "chromosome_name.h"

int StrNStr(char* str, char c, int n)
{
	if (n == 0)return -1;
	int i, len = strlen(str);
	int k = 1;
	for (i = 0; i < len; i++)
	{
		if (str[i] == c)
		{
			if (k == n)return i;
			k++;
		}
	}
	return -1;
}
int UnderStol(char* str, int nstol, char* ret, size_t size, char sep)
{
	memset(ret, 0, size);
	int p1, p2, len;
	if (nstol == 0)
	{
		p2 = StrNStr(str, sep, 1);
		if (p2 == -1)p2 = strlen(str);
		strncpy(ret, str, p2);
		ret[p2] = '\0';
		return 1;
	}
	else
	{
		p1 = StrNStr(str, sep, nstol);
		p2 = StrNStr(str, sep, nstol + 1);
		if (p2 == -1)
		{
			p2 = strlen(str);
		}
		if (p1 == -1 || p2 == -1) return -1;
		len = p2 - p1 - 1;
		strncpy(ret, &str[p1 + 1], len);
		ret[len] = '\0';
		return 1;
	}
}
// delete symbol 'c' from input string
void DelChar(char* str, char c)
{
	int i, lens, size;

	size = 0;
	lens = strlen(str);
	for (i = 0; i < lens; i++)
	{
		if (str[i] != c)str[size++] = str[i];
	}
	str[size] = '\0';
}

int main(int argc, char* argv[])
{
	int i, nc, n_chr;
	char filei[500], fileo_base[500], **fileochr, genome[10], d[500];
	FILE* in;
	if (argc != 4)
	{
		printf("Syntax %s: 1file_input 2file_output_base 3char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61)", argv[0]);
		exit(1);
	}
	strcpy(filei, argv[1]);
	strcpy(fileo_base, argv[2]);
	strcpy(genome, argv[3]);
	char name_chr[NCHR][10], bedext[10];
	strcpy(bedext,".bed");
	int genome_rec = 0;
	if (strcmp(genome, "at10") == 0)
	{
		genome_rec = 1;
		n_chr = n_chr_at;
		for (i = 0; i < n_chr; i++)
		{
			strcpy(name_chr[i], name_chr_at[i]);
		}
	}
	else
	{
		if (strcmp(genome, "hg38") == 0)
		{
			genome_rec = 1;
			n_chr = n_chr_hg;
			for (i = 0; i < n_chr; i++)
			{
				strcpy(name_chr[i], name_chr_hg[i]);
			}
		}
		else
		{
			if (strcmp(genome, "mm10") == 0)
			{
				genome_rec = 1;
				n_chr = n_chr_mm;
				for (i = 0; i < n_chr; i++)
				{
					strcpy(name_chr[i], name_chr_mm[i]);
				}
			}
			else
			{
				if (strcmp(genome, "rn6") == 0)
				{
					genome_rec = 1;
					n_chr = n_chr_rn;
					for (i = 0; i < n_chr; i++)
					{
						strcpy(name_chr[i], name_chr_rn[i]);
					}
				}
				else
				{
					if (strcmp(genome, "dm6") == 0)
					{
						genome_rec = 1;
						n_chr = n_chr_dm;
						for (i = 0; i < n_chr; i++)
						{
							strcpy(name_chr[i], name_chr_dm[i]);
						}
					}
					else
					{
						if (strcmp(genome, "ce235") == 0)
						{
							genome_rec = 1;
							n_chr = n_chr_ce;
							for (i = 0; i < n_chr; i++)
							{
								strcpy(name_chr[i], name_chr_ce[i]);
							}
						}
						else
						{
							if (strcmp(genome, "sc64") == 0)
							{
								genome_rec = 1;
								n_chr = n_chr_sc;
								for (i = 0; i < n_chr; i++)
								{
									strcpy(name_chr[i], name_chr_sc[i]);
								}
							}
							else
							{
								if (strcmp(genome, "sch294") == 0)
								{
									genome_rec = 1;
									n_chr = n_chr_sch;
									for (i = 0; i < n_chr; i++)
									{
										strcpy(name_chr[i], name_chr_sch[i]);
									}
								}
								else
								{
									if (strcmp(genome, "gm21") == 0)
									{
										genome_rec = 1;
										n_chr = n_chr_gm;
										for (i = 0; i < n_chr; i++)
										{
											strcpy(name_chr[i], name_chr_gm[i]);
										}
									}
									else
									{
										if (strcmp(genome, "mp61") == 0)
										{
											genome_rec = 1;
											n_chr = n_chr_mp;
											for (i = 0; i < n_chr; i++)
											{
												strcpy(name_chr[i], name_chr_mp[i]);
											}
										}
										else
										{
											if (strcmp(genome, "zm73") == 0)
											{
												genome_rec = 1;
												n_chr = n_chr_zm;
												for (i = 0; i < n_chr; i++)
												{
													strcpy(name_chr[i], name_chr_zm[i]);
												}
											}
											else
											{
												if (strcmp(genome, "zf11") == 0)
												{
													genome_rec = 1;
													n_chr = n_chr_zf;
													for (i = 0; i < n_chr; i++)
													{
														strcpy(name_chr[i], name_chr_zf[i]);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (genome_rec == 0)
	{
		printf("Genome %s is not recognized\n", genome);
		exit(1);
	}
	
	fileochr = new char* [n_chr];
	if (fileochr == NULL) { printf("Not  enough memory!"); return -1; }
	for (i = 0; i < n_chr; i++)
	{
		fileochr[i] = new char[500];
		if (fileochr[i] == NULL) { printf("Not  enough memory!"); return -1; }
	}

	for (i = 0; i < n_chr; i++)
	{
		strcpy(fileochr[i], fileo_base);
		strcat(fileochr[i], "_chr");
		strcat(fileochr[i], name_chr[i]);
		strcat(fileochr[i], bedext);
	}

	FILE** out;
	out = new FILE * [n_chr];
	if (out == NULL) { printf("Not  enough memory!"); return -1; }
	for (i = 0; i < n_chr; i++)
	{
		if ((out[i] = fopen(fileochr[i], "wt")) == NULL)
		{
			printf("Out file %s can't be opened!\n", fileochr[i]);
			exit(1);
		}		
	}
	if ((in = fopen(filei, "rt")) == NULL)
	{
		printf("Input file %s can't be opened!\n", filei);
		exit(1);
	}
	char chr0[] = "chr";
	while (fgets(d, sizeof(d), in) != NULL)
	{
		DelChar(d, '\n');
		if (strncmp(d, chr0, 3) != 0)continue;
		char chr[50], chr_here[50], tab = '\t';
		int test;
		test = UnderStol(d, 0, chr, sizeof(chr), tab);
		if (test == -1)
		{
			printf("Wrong format %s\n", d);
			exit(1);
		}		
		int nclen = strlen(chr);
		int gom = -1;
		for (nc = 0; nc < n_chr; nc++)
		{
			strcpy(chr_here, chr0);
			strcat(chr_here, name_chr[nc]);			
			int sc = strncmp(chr, chr_here, nclen);
			if (sc == 0)
			{
				gom = nc;
				break;
			}
		}
		if (gom == -1)
		{
			printf("Bed file %s line %s chromosome %s is absent in genome %s", filei, d, chr, genome);
			continue;
		}	
		fprintf(out[gom], "%s\n", d);
	}
	for (i = 0; i < n_chr; i++)fclose(out[i]);
	fclose(in);	
	delete[] out;
	for (i = 0; i < n_chr; i++) delete[] fileochr[i];
	delete[] fileochr;
	return 0;
}

