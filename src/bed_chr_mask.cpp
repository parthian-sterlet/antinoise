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

//masking razmetka 
//input area
//chrX a	b
//input seq plain (chrX.plain)
//output
//fasta masked
struct areas {
	int lev;
	int pra;
} ;
int StrNStr(char *str,char c, int n)
{
	int i, len=strlen(str);
	int k=1;
	for(i=0;i<len;i++)
	{
		if(str[i]==c)
		{
			if(k==n)return i;
			k++;
		}
	}
	return -1;
}
void DelChar(char *str,char c)
{
	int i, lens, size;

	size=0;
	lens=strlen(str);
	for(i=0;i<lens;i++)
	{
		if(str[i]!=c)str[size++]=str[i];
	}
	str[size]='\0';
}
void RazborArea(char *str, areas *a)
{
	int loc;
	DelChar(str,'\n');
	loc=StrNStr(str,'\t',1);
	a->lev=atoi(&str[loc]);	
	loc=StrNStr(str,'\t',2);
	a->pra=atoi(&str[loc]);
}

int main(int argc, char *argv[])
{	
	int i, j;
	char str[200], fileareai[500], filefastai[500], filefastao[500];
	char fileaend[10], fileoend[10], fileiend[10], filei[500], fileo[500], filea[500];
	char path_in[500], path_out[500], genome[10], chrbed[10];
	FILE* ina, * inf, * out;

	if(argc!=8)
	{
		printf ("%s 1path_genome_in 2path_genome_out 3file_profile_area_base 4file_in_seq_plain_base 5file_out_seq_plain_base 6int 1alive_bed__-1alive_no_bed 7char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61)",argv[0]);
        exit (1);
	}	
	strcpy(path_in, argv[1]);
	strcpy(path_out, argv[2]);
	strcpy(fileareai, path_out);
	strcat(fileareai,argv[3]);	
	strcpy(filefastai, path_in);
	strcat(filefastai,argv[4]);	
	strcpy(filefastao, path_out);
	strcat(filefastao,argv[5]);	
	int alive=atoi(argv[6]);
	strcpy(genome, argv[7]);

	if(alive!=-1)alive=1;
	// alive = 1 pe4ataem atgc tol'ko tam gde est' bed (area)
	// alive = -1 pe4ataem atgc tol'ko tam gde net bed (area)


	int nc, n_chr;
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
	
	strcpy(fileaend, ".bed"); 
	strcpy(chrbed, "chr");
	strcpy(fileiend, ".plain");
	strcpy(fileoend, ".plain");

	for (nc = 0; nc < n_chr; nc++)
	{
		strcpy(filea, fileareai);
		strcat(filea, chrbed);
		strcpy(filei, filefastai);
		strcpy(fileo, filefastao);
		strcat(filei, name_chr[nc]);
		strcat(fileo, name_chr[nc]);
		strcat(filea, name_chr[nc]); 
		strcat(filea, fileaend);
		strcat(filei, fileiend);
		strcat(fileo, fileoend);
		if ((ina = fopen(filea, "rt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filea);
			exit(1);
		}
		if ((inf = fopen(filei, "rt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filei);
			exit(1);
		}
		if ((out = fopen(fileo, "wt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", fileo);
			exit(1);
		}
		//	fprintf(out,">%s\t%s\n",argv[1],argv[2]);
		int string_area = 0;
		while (fgets(str, sizeof(str), ina) != NULL)
		{
			if (*str != '\n')string_area++;
		}
		rewind(ina);
		areas* area;
		area = new areas[string_area];
		if (area == NULL) { printf("Not  enough memory!"); exit(1); }
		j = 0;
		while (fgets(str, sizeof(str), ina) != NULL)
		{
			RazborArea(str, &area[j]);
			j++;
		}
		fclose(ina);
		int n = (int)'n';
		int sta = 1;
		int c;
		for (j = 0; j < string_area; j++)
		{
			for (i = sta; i < area[j].lev; i++)
			{
				c = fgetc(inf);
				if (c == EOF)
				{
					printf("Unexpected end of file!!\n");
					exit(1);
				}
				if (alive == 1)fputc(n, out);
				else fputc(c, out);
			}
			for (i = area[j].lev; i <= area[j].pra; i++)
			{
				c = fgetc(inf);
				if (c == EOF)
				{
					printf("Unexpected end of file!!\n");
					exit(1);
				}
				if (alive == 1)fputc(c, out);
				else fputc(n, out);
			}
			sta = area[j].pra + 1;
		}
		do
		{
			c = fgetc(inf);
			if (c == EOF)break;
			if (alive == 1)fputc(n, out);
			else fputc(c, out);
		} 
		while (c != EOF);
		fclose(inf);
		fclose(out);
	}
	return 0;
}
