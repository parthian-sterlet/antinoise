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

//parse one razmetka 
//input 1st
//chrX a	b
//input 2nd
//chrX
//c d
//output
//chrX intercection (a,b) & (c,d)
struct areas {
	int lev;
	int pra;
	char cat;//popalsya
	double rat;// rate of occurence per 1bp = average no. of transcript
	char nam[50];
	char cep;
	//void areas::get_copy(areas *a);
} ;
struct regs {
	int pos;
	int cov;
//	int *lst;//pointer to the list of area2 = overlapped annotations
	char sta;//'+' = start '-' = end 
	int num;//nomer rayona area2
};
/*
void areas::get_copy(areas *a )
{
 a->lev = lev;
 a->pra = pra;
};*/
int compare_areas( const void *X1, const void *X2 )
{
	struct areas *S1 = (struct areas *)X1;
	struct areas *S2 = (struct areas *)X2; 
	if(S1->lev - S2->lev >0)return 1;
	if(S1->lev - S2->lev <0)return -1;		
	if(S1->pra - S2->pra >0)return 1;
	if(S1->pra - S2->pra <0)return -1;		
	return 0;
}
int compare_reg( const void *X1, const void *X2 )
{
	struct regs *S1 = (struct regs *)X1;
	struct regs *S2 = (struct regs *)X2; 
	if(S1->pos - S2->pos >0)return 1;
	if(S1->pos - S2->pos <0)return -1;			
	return 0;
}
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
void RazborArea(char *str, areas *a)
{
	int loc;
	char sep = '\t';
	DelChar(str,'\n');
	loc=StrNStr(str,sep,1);
	a->lev=atoi(&str[loc]);	
	loc=StrNStr(str, sep,2);
	a->pra=atoi(&str[loc]);
	a->cat='-';
	a->rat=0;
	char heads[2000];	
	if (loc != -1)
	{		
		int test = UnderStol(str, 4, heads, sizeof(heads), sep);
		if (test == -1)
		{
			strcpy(a->nam, "absent");
		}
		strcpy(a->nam, heads);
	}
	else strcpy(a->nam,"absent");
	if(strstr(str,"+")!=NULL)a->cep='+';
	else 
	{
		a->cep='-';
	}
}
void Mix(int *a, int *b)
{
  int buf=*a;
  *a=*b;
  *b=buf;
}
int main(int argc, char *argv[])
{	
	int i, j, k, nc;
	char str[200], filei[500], fileo[500], filesta[500], genome[10], filei_base[500], fileo_base[500], bedext[10], chrext[10];
	if(argc!=5)
	{
		printf ("%s 1file_profile_area1_base 2file_profile_area_self_overlapped_base 3char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61) 4file_statistics",argv[0]);
        exit (1);
	}	
	FILE *in, *out;	
	strcpy(filei_base,argv[1]);	
	strcpy(fileo_base,argv[2]);
	strcpy(genome, argv[3]);
	strcpy(filesta, argv[4]);

	char name_chr[NCHR][10];
	int n_chr, genome_rec = 0;
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
	strcpy(bedext, ".bed");
	strcpy(chrext, "_chr");
	char chr[10];
	strcpy(chr, "chr");
	//char filesta[] = "area_self_overlap.txt";

	int string_area_tot = 0, length_tot = 0, overlap_tot = 0;
	for (nc = 0; nc < n_chr; nc++)
	{
		strcpy(fileo, fileo_base);
		strcat(fileo, chrext);
		strcat(fileo, name_chr[nc]);
		strcat(fileo, bedext);
		strcpy(filei, filei_base);
		strcat(filei, chrext);
		strcat(filei, name_chr[nc]);
		strcat(filei, bedext);
		if ((out = fopen(fileo, "wt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", fileo);
			exit(1);
		}
		if ((in = fopen(filei, "rt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filei);
			exit(1);
		}
		int string_area = 0;
		while (fgets(str, sizeof(str), in) != NULL)
		{
			if (*str != '\n')string_area++;
		}
		rewind(in);
		string_area_tot += string_area;
		areas* area;
		area = new areas[string_area];
		if (area == NULL) { printf("Not  enough memory!"); exit(1); }
		j = 0;
		int length = 0;
		while (fgets(str, sizeof(str), in) != NULL)
		{
			if (strncmp(str, chr, 3) != 0)continue;
			RazborArea(str, &area[j]);
			length += area[j].pra - area[j].lev + 1;
			j++;
		}
		length_tot += length;
		fclose(in);
		int string_reg = 2 * string_area + 2;
		regs* reg;
		reg = new regs[string_reg];
		if (reg == NULL) { printf("Not  enough memory!"); exit(1); }
		reg[0].pos = 0;	reg[0].sta = '\0';	reg[0].cov = 0; reg[0].num = -1;
		i = 1;
		for (j = 0; j < string_area; j++)
		{
			reg[i].pos = area[j].lev;
			reg[i].sta = '+';
			reg[i].num = j;
			reg[i].cov = 0;
			i++;
			reg[i].pos = area[j].pra + 1;
			reg[i].sta = '-';
			reg[i].num = j;
			reg[i].cov = 0;
			i++;
		}
		int string_reg1 = string_reg - 1;
		reg[string_reg1].pos = area[string_area - 1].pra + 1;
		reg[string_reg1].sta = '\0';
		reg[string_reg1].cov = 0;
		reg[string_reg1].num = -1;
		int last = reg[string_reg1].pos;
		qsort(reg, string_reg, sizeof(reg[0]), compare_reg);
		int cover = 0, cover_max = 0;
		for (j = 1; j < string_reg1; j++)
		{
			char ch = reg[j].sta;
			if (ch == '+')cover++;
			else
			{
				if (ch == '-')cover--;
			}
			reg[j].cov = cover;
			if (cover > cover_max)cover_max = cover;
		}
		int string_reg11 = string_reg1 - 1;
		char filelog[500];
		strcpy(filelog, fileo);
		strcat(filelog, "_log");
		FILE* outlog;
		if ((outlog = fopen(filelog, "wt")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filelog);
			exit(1);
		}
		for (j = 0; j < string_reg1; j++)
		{
			//if (j != string_reg11 && reg[j].pos == reg[j + 1].pos)continue;
			fprintf(outlog, "%s%s\t%d\t%d\t%d\t\t", chr, name_chr[nc], reg[j].pos, reg[j + 1].pos - 1, reg[j].cov);
			//if(reg[j].cov>0)for(i=0;i<reg[j].cov;i++)fprintf(outlog,"\t%d",reg[j].lst[i]);
			fprintf(outlog, "\n");
		}
		fclose(outlog);
	/*	for (j = 0; j < string_reg; j++)
		{
			reg[j].lst = new int[reg[j].cov];
			//	printf("%d\t%d\n", reg[j].cov);
			if (reg[j].lst == NULL)
			{
				puts("Out of memory...");
				exit(1);
			}
		}
		int* height;
		height = new int[cover_max];
		if (height == NULL)
		{
			puts("Out of memory...");
			exit(1);
		}
		for (j = 0; j < cover_max; j++)height[j] = -1;
		int qu_size = 0;//dlina o4eredi
		for (j = 1; j < string_reg1; j++)
		{
			if (reg[j].sta == '+')
			{
				height[qu_size] = reg[j].num;
				qu_size++;
				for (i = 0; i < qu_size; i++)reg[j].lst[i] = height[i];
			}
			if (reg[j].sta == '-')
			{
				for (i = 0; i < qu_size; i++)
				{
					if (height[i] == reg[j].num)
					{
						height[i] = -1;
						Mix(&height[i], &height[qu_size - 1]);
						qu_size--;
						for (k = 0; k < qu_size; k++)reg[j].lst[k] = height[k];
						break;
					}
				}
			}
		}*/
		int overlap = 0;
		for (j = 1; j < string_reg11; j++)
		{
			int nextp = reg[j + 1].pos - 1;
			if (reg[j].pos >= nextp)continue;
			if (reg[j].cov > 0)
			{
				fprintf(out, "%s%s\t%d\t%d\t%d\t", chr, name_chr[nc], reg[j].pos, nextp, reg[j].cov);
				overlap += reg[j + 1].pos - reg[j].pos;
				//	for(i=0;i<reg[j].cov;i++)fprintf(out,"\t%d",reg[j].lst[i]);
				fprintf(out, "\n");
			}
		}
		fclose(out);
		overlap_tot += overlap;
		/*for (j = 1; j < string_reg11; j++)
		{
			if (reg[j].pos == last)continue;
			int cov = reg[j].cov;
			int reg_len = reg[j + 1].pos - reg[j].pos;
			if (cov > 0 && reg_len > 1)
			{
				//		printf("%d\t%d..%d\t\t",j+1,reg[j+1].pos-1,reg[j].pos);
					//	for(i=0;i<cov;i++)printf("%d ",reg[j].lst[i]);
					//	printf("\n");
				for (i = 0; i < cov; i++)
				{
					area[reg[j].lst[i]].rat += reg_len * cov;
				}
			}
		}
		for (j = 0; j < string_area; j++)
		{
			int area_len = area[j].pra - area[j].lev + 1;
			area[j].rat /= area_len;
		}
		char filerate[] = "area_self_overlap.rate";
		if ((out = fopen(filerate, "at")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filerate);
			exit(1);
		}
		for (j = 0; j < string_area; j++)fprintf(out, "%s%s\t%d\t%d\t%s_%f\n", chr, name_chr[nc],area[j].lev, area[j].pra, area[j].nam, area[j].rat);
		fclose(out);*/
		delete[] area;
	//	for (j = 0; j < string_reg; j++)delete[] reg[j].lst;
		delete[] reg;
		//delete[] height;
		if ((out = fopen(filesta, "at")) == NULL)
		{
			printf("Input file %s can't be opened!\n", filesta);
			exit(1);
		}
		fprintf(out, "%s_%s%s\tArea\t%d\t\tLen\t%d\tOverlap\t%d\n", argv[1], chr,name_chr[nc], string_area, length, overlap);
		fclose(out);
	}	
	if ((out = fopen(filesta, "at")) == NULL)
	{
		printf("Input file %s can't be opened!\n", filesta);
		exit(1);
	}
	fprintf(out, "%s\tArea\t%d\t\tLen\t%d\tOverlap\t%d\n", argv[1], string_area_tot, length_tot, overlap_tot);
	fclose(out);
	return 0;
}
