#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  <time.h>
#include "chromosome_name.h"
#define Min(a,b) ((a)>(b))? (b):(a);
#define Max(a,b) ((a)>(b))? (a):(b);
#define NCHR 100

//#define COLUMN 1000
//razbor i sortirovja annotaciy po 1mu i 2mu stolbikam
struct areas {
	char chr[10];
	int sta;
	int end;
};

int compare_areas_pos(const void* X1, const void* X2)
{
	struct areas* S1 = (struct areas*)X1;
	struct areas* S2 = (struct areas*)X2;
	int gom = strcmp(S1->chr, S2->chr);
	if (gom == 0)
	{
		if (S1->sta - S2->sta > 0)return 1;
		if (S1->sta - S2->sta < 0)return -1;
	}
	if (gom < 0)return -1;
	if (gom > 0)return 1;
	return 0;
}
int StrNStr(char* str, char c, int n)
{
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
void Mix(int* a, int* b)
{
	int buf = *a;
	*a = *b;
	*b = buf;
}
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
void RazborArea(char* str, areas* a)
{
	int i, j;
	DelChar(str, '\n');	
	j = 0;
	for (i = 3; str[i] != '\t'; i++)
	{
		a->chr[j++] = str[i];
	}
	a->chr[j] = '\0';	
	int loc = StrNStr(str, '\t', 1);
	a->sta = atoi(&str[loc]);
	loc = StrNStr(str, '\t', 2);
	a->end = atoi(&str[loc]);
}

int main(int argc, char* argv[])
{
	int size, i, nc, n_chr;
	char filei[500], fileo[500], genome[10], d[500];
	FILE* in, * out;
	if (argc != 4)
	{
		printf("Syntax %s: 1file_input_not_sort 2file_output_sort 3char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61)", argv[0]);
		exit(1);
	}
	strcpy(filei, argv[1]);
	strcpy(fileo, argv[2]);
	strcpy(genome, argv[3]);	
	char name_chr[NCHR][10];
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

	if ((in = fopen(filei, "rt")) == NULL)
	{
		printf("Input file %s can't be opened!\n", filei);
		exit(1);
	}
	if ((out = fopen(fileo, "wt")) == NULL)
	{
		printf("Input file %s can't be opened!\n", fileo);
		exit(1);
	}	
	char chr[5];	
	strcpy(chr, "chr");	
	size = 0;	
	while (fgets(d, sizeof(d), in) != NULL)
	{
		if (strncmp(d, chr, 3) == 0)size++;
	}
	rewind(in);
	areas* area;
	area = new areas[size];
	if (area == NULL) { puts("Out of memory..."); exit(1); }
	i = 0;
	while (fgets(d, sizeof(d), in) != NULL)
	{
		if (strncmp(d, chr, 3) == 0)
		{
			RazborArea(d, &area[i]);
			int gom = 0;
			for (nc = 0; nc < n_chr; nc++)
			{
				if (strcmp(area[i].chr, name_chr[nc]) == 0)
				{
					gom = 1;
					i++;
					break;
				}
			}			
			if (gom == 0)
			{
				printf("Bed file %s line %s chromosome %s is absent in genome %s", filei, d, area[i].chr, genome);
				exit(1);				
			}
		}

	}
	size = i;
	qsort(area, size, sizeof(area[0]), compare_areas_pos);
	for (i = 0; i < size; i++)
	{
		fprintf(out, "%s%s\t%d\t%d\t\n", chr, area[i].chr, area[i].sta, area[i].end);
	}
	fclose(out);
	fclose(in);
	delete[] area;
	return 0;
}

