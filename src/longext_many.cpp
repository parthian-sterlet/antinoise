#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chromosome_name.h"
#include "chromosome_len.h"
#define Min(a,b) ((a)>(b))? (b):(a);
#define Max(a,b) ((a)>(b))? (a):(b);
#define NCHR 100

void ComplSym(char c, char &cc)
{	
	switch(c)
	{
		case 'a':{cc='t';break;}
		case 't':{cc='a';break;}
		case 'c':{cc='g';break;}
		case 'g':{cc='c';break;}
		case 'A':{cc='T';break;}
		case 'T':{cc='A';break;}
		case 'C':{cc='G';break;}
		case 'G':{cc='C';break;}
		default: cc='n';
	}		
}
void ReplaceChar(char *str,char c1, char c2)
{
	int i, len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]==c1) str[i]=c2;
	}
}
char *TransStr(char *d)
{
   int i, c, lens;
   lens=strlen(d);
   for(i=0;i<lens;i++)
   {
	c=int(d[i]);
	if(c<97) d[i]=char(c+32);
	//else break;
   }
   return(d);
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
int UnderStol(char *str, int nstol, char *ret, size_t size, char sep)
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
void Mix(int *a, int *b)// bez commentov
{
  int buf=*a;
  *a=*b;
  *b=buf;
}
int Razbor(char *str, char *chr, int &b1, int &b2, char &cep, char *head)
//1	5043771	5043781	+
//example format: chr_num, e.g.[1-22.X,Y] pos1 pos2 strand[+ -] description
{
	int i,i0;
	char heads[2000];
	if(strncmp(str,"chr",3)==0)i0=3;
	else i0=0;
	for(i=0;;i++)
	{		
		char strc=str[i+i0];
		if(strc=='\t')
		{
			chr[i]='\0';
			break;
		}
		chr[i]=strc;
		if(i>=10)return -1;
	}
	if(chr[0]!='1')
	{
		int yy=1;
	}
	int loc;	
	loc=StrNStr(str,'\t',1);
	b1=atoi(&str[loc]);
	loc=StrNStr(str,'\t',2);
	b2=atoi(&str[loc]);
	if(b1<=0 || b1>=9E8) return -1;
	if(b2<=0 || b2>=9E8) return -1;
	if(b1>b2)Mix(&b1,&b2);
	if(strstr(str,"+")!=NULL)cep='+';
	else if(strstr(str,"-")!=NULL)cep='-';
		else cep = '\0';
	//DelChar(str,'\n');
	char sep = '\t';
//	memset(head,0,sizeof(head));	
	loc=StrNStr(str,'\t',4);
	if(loc!=-1)	
	{
		int test = UnderStol(str,4,heads, sizeof(heads), sep);
		if (test == -1) { printf("Wrong format %s\n", str); return(-1); }
		int lenh=strlen(heads);
		if(lenh>50)strncpy(head,heads,50);
		else strcpy(head,heads);
	}
	return 1;
}

int main(int argc, char *argv[])
{
	int i, edge[2];
	char d[20001], cep, head[2000], genome[10], path_fasta[500];
	char fileip[80], fileissta[80], fileis[80], fileo[80], bufext[80];
	FILE *out, *inp, *ins;
	if(argc!=8)
	{
		puts("Sintax: 1path_genome 2char input_pos_file, 3char output_seq_file 4,5 int left,right 6int len_max 7char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61)");   
		exit(1);
	}
	strcpy(path_fasta, argv[1]);
	strcpy(fileissta, path_fasta);
	strcat(fileissta,"chr");
	strcpy(fileip, argv[2]);//in_pos_file
	strcpy(bufext,".plain");
	strcpy(fileo,argv[3]);//out seq_file
	int left=atoi(argv[4]);
	int right=atoi(argv[5]);   
	int maxlen=atoi(argv[6]);  
	strcpy(genome, argv[7]);

	int n_chr;
	char name_chr[NCHR][10];
	int sizelo1[NCHR];
	int genome_rec = 0;
	if (strcmp(genome, "at10") == 0)
	{
		genome_rec = 1;
		n_chr = n_chr_at;
		for (i = 0; i < n_chr; i++)
		{
			sizelo1[i] = sizelo_at10[i];
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
				sizelo1[i] = sizelo_hg38[i];
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
					sizelo1[i] = sizelo_mm10[i];
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
						sizelo1[i] = sizelo_rn6[i];
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
							sizelo1[i] = sizelo_dm6[i];
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
								sizelo1[i] = sizelo_ce235[i];
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
									sizelo1[i] = sizelo_sc64[i];
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
										sizelo1[i] = sizelo_sch294[i];
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
											sizelo1[i] = sizelo_gm21[i];
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
												sizelo1[i] = sizelo_mp61[i];
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
													sizelo1[i] = sizelo_zm73[i];
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
														sizelo1[i] = sizelo_zf11[i];
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

	if((inp=fopen(fileip,"rt"))==NULL)
	{
		printf("Input file %s can't be opened!",fileip);
		 exit(1);
	}	
	if((out=fopen(fileo,"wt"))==NULL)
	{
		printf("Input file %s can't be opened!",fileo);
		 exit(1);
	}
	char file_err[80];
	strcpy(file_err,"longext_many_err.txt");
	FILE *outerr;
	if((outerr=fopen(file_err,"wt"))==NULL)
	{
		printf("Input file %s can't be opened!",file_err);
			exit(1);
	}
	/*
	char fileisext[80];
	strcpy(fileisext,".fa");
	FILE *buf;
	char filebuf[80];
	int *sizelo1;
	sizelo1=new int[n_chr];
	if(sizelo1==NULL) {puts("Out of memory...");exit(1);}			
	for(i=0;i<n_chr;i++)
	{
		strcpy(fileis,fileissta);
		strcat(fileis,name_chr[i]);
		strcpy(filebuf,fileis);
		strcat(fileis,fileisext);
		strcat(filebuf,bufext);
		if((ins=fopen(fileis,"rt"))==NULL)
		{
			printf("Input file %s can't be opened!",fileis);
			 exit(1);
		}
		if((buf=fopen(filebuf,"wt"))==NULL)
		{
			printf("Input file %s can't be opened!",filebuf);
			 exit(1);
		}
		fgets(d,sizeof(d),ins);
		sizelo1[i]=0;
		while(fgets(d,sizeof(d),ins)!=NULL)
		{
   			DelChar(d,'\n');
     		DelChar(d,'\t');
   			DelChar(d,' ');
			TransStr(d);
		//	ReplaceChar(d,'A','N');
		//	ReplaceChar(d,'T','N');
		//	ReplaceChar(d,'G','N');
		//	ReplaceChar(d,'C','N');
			fprintf(buf,"%s",d);
			int len=strlen(d);
			sizelo1[i]+=len;
		}
  		fclose(ins);
  		fclose(buf);
	}*/
	int n_str=0, was_open=0;
	char fileis_prev[80];
	memset(fileis_prev,'\0',sizeof(fileis_prev));
	//zadanie cepi 4erez imya argv[1]
	char cep0;
	if(strstr(argv[1],"plus")!=NULL)cep0='+';
	else if(strstr(argv[1],"minus")!=NULL)cep0='-';
	else cep0='+';
	ins=NULL;
	char op='-';
	while(fgets(d,sizeof(d),inp)!=NULL)
	{
		DelChar(d,'\n');
		char chr_here[3];
		memset(chr_here,0,sizeof(chr_here));
		memset(head, 0, sizeof(head));
		if(Razbor(d,chr_here,edge[0],edge[1],cep,head)==-1)
		{
       		printf("String recognition error! %s\n",d);
			exit(1);
		}				
		//printf("%s",d);
		int diflen=edge[1]-edge[0];
		if(diflen<maxlen)
		{
			if(cep=='\0')cep=cep0;
			strcpy(fileis,fileissta);
			strcat(fileis,chr_here);		
			strcat(fileis,bufext);
			if(strcmp(fileis,fileis_prev)!=0)
			{
				if(op=='+' && n_str!=0)fclose(ins);
				if((ins=fopen(fileis,"rt"))==NULL)
				{
					printf("Input file %s can't be opened!",fileis);
					 exit(1);
				}
				strcpy(fileis_prev,fileis);
				op='+';
			}
			int nchr_here=0;
			for(i=0;i<n_chr;i++)
			{
				if(strcmp(chr_here,name_chr[i])==0)
				{
					nchr_here=i;
					break;
				}
			}
			edge[0]-=left;
			//if(edge[0]<0)edge[0]=1;
			edge[1]+=right;
			//if(edge[1]>sizelo[nchr_here])edge[1]=sizelo[nchr_here];
			if(edge[0]<0 || edge[1]>sizelo1[nchr_here])
			{
				fprintf(outerr,"Edges on chromosome %s\t0\t%d\t\tEdge query\t%d\t%d\n",chr_here,sizelo1[nchr_here],edge[0],edge[1]);
				continue;
			}
			int len1=edge[1]-edge[0];				
			fprintf(out,">chr%s %d %d %c %s\n",chr_here,edge[0]+1,edge[1],cep,head);
			i=0;
			if(cep=='+')
			{
				int pos1=edge[0];
				fseek(ins,(long)(pos1),SEEK_SET);
				while(i<len1)
				{
					int c=fgetc(ins);
					if(c==EOF)break;
					if(strchr("\n\r\t ",c)!=NULL)continue;
					if(strchr("atgcwrmkysbvhdnATGCWRMKYSBVHDN\n\r ",c)==NULL)
					{
						printf("Sequence %s Position %d (%c) bad\n",d,edge[0]+i+1,c);
						exit(1);
					}
					i++;
					fputc(c,out);
				}
			}
			else
			{
				char cc;
				int pos1=edge[1]-2;			
				while(i<len1)
				{
					fseek(ins,(long)(pos1),SEEK_SET);
					int c=fgetc(ins);
					if(c==EOF)break;
					if(strchr("\n\r\t ",c)!=NULL)continue;
					if(strchr("atgcwrmkysbvhdnATGCWRMKYSBVHDN\n\r ",c)==NULL)
					{
						printf("Sequence %s Position %d (%c) bad\n",d,edge[0]+i+1,c);
						exit(1);
					}
					i++;
					ComplSym(c,cc);
					fputc(cc,out);				
					pos1--;				
				}
			}
			fprintf(out,"\n");		
		}
		else 
		{
			printf("Sequence too long %d bp >= %d\n",diflen,maxlen);
		}
		n_str++;
		if(n_str%500==0)printf("\b\b\b\b\b\b\b%7d",n_str);
	}
	fclose(ins);
	fclose(inp);
	fclose(out);
	fclose(outerr);
	return 1;
}