#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Min(a,b) ((a)>(b))? (b):(a);
#define Max(a,b) ((a)>(b))? (a):(b);

int StrNStr(char *str,char c, int n)
{
	if(n==0)return -1;
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
	return -10;
}
void DelHole(char *str)
{
   char *hole;
   hole=strstr(str,"\n");
   if(hole!=NULL) *hole=0;
}
int NthColumn(char *din, char *dout, int nstol)
{
   	int p1=StrNStr(din,'\t',nstol);
	int p2=StrNStr(din,'\t',nstol+1);
	if(p1==-1 || p2==-1)return -1;
	int len=p2-p1-1;
	strncpy(dout,&din[p1+1],len);		
	dout[len]='\0';
	return 1;
}
// delete symbol 'c' from input string
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
void ProbelToTab(char *d)
{
	int i, len=strlen(d);
	char pro=' ';
	char tab='\t'; 
	for(i=1;i<len;i++)
	{
		if(d[i-1]!=pro && d[i]==pro)
		{
			d[i]=tab;
			i++;
		}
	}
	DelChar(d,pro);
}
int main(int argc, char *argv[])
{
	char din[30000],**dout;
	char filei[300], fileo[300], file_sta[300];
	char path_in[300], path_out[300];
	FILE *out, *in;
	if(argc!=9)
	{
		puts("Sintax: 1in_file, 2out_file 3int no. of_stolbik_nomer 4char list_nomerov_stolbikov,razdelenie-zapyataya ");//char path_in char path_out
		puts("5char list_words_in_strings 6int match type(1 exact coincidence, 0 only occurrence 7int contain_type(0 no 1 yes) 8int logic(1 AND 0 OR");
		exit(1);
	}
	memset(path_in, '\0', sizeof(path_in));
	memset(path_out, '\0', sizeof(path_out));
//	strcpy(path_in, argv[1]); //folder in		
	strcpy(filei, path_in);
	strcat(filei,argv[1]);//in_file
//	strcpy(path_out, argv[3]); //folder out
	strcpy(fileo, path_out);
	strcat(fileo,argv[2]);//out_file
	int nstol_tot=atoi(argv[3]);	
	if(nstol_tot<1 || nstol_tot> 1000)
	{
		puts("No of column wrong!");
		exit(1);
	}
	char razd=',', **dword;			
	int *nstol;
	nstol = new int[nstol_tot];
	if(nstol==NULL){puts("Out of memory...");exit(1);}		
	char strnum[30000], strword[30000], value[30000];
	memset(value,0,sizeof(value));
	strcpy(strnum,argv[4]);
	strcpy(strword,argv[5]);
	int match_type=atoi(argv[6]);
	int contain_type=atoi(argv[7]);
	if(contain_type!=0)contain_type=1;
	int logic=atoi(argv[8]);//1= each column case should contain word (AND), 0 only one case among all should be present (OR)
	int i, strnum_len=strlen(strnum), strword_len=strlen(strword),sta=0,i_num=0;
	if(nstol_tot>=2 && strchr(strnum,razd)==NULL)
	{
		puts("Razdelitel ne nayden v spiske kolonok!");
		exit(1);
	}	
	dout = new char*[nstol_tot];
	if(dout==NULL){puts("Out of memory...");exit(1);}
	for(i=0;i<nstol_tot;i++)
	{
		dout[i] = new char[1000];
		if(dout[i]==NULL){puts("Out of memory...");exit(1);}
	}
	//char word[100];
	dword = new char*[nstol_tot];
	if(dword==NULL){puts("Out of memory...");exit(1);}
	for(i=0;i<nstol_tot;i++)
	{
		dword[i] = new char[20000];
		if(dword[i]==NULL){puts("Out of memory...");exit(1);}
	}
	for(i=0;i<nstol_tot;i++)memset(dword[i],0,sizeof(dword[i]));
	for(i=0;i<=strnum_len;i++)
	{
		if(strnum[i]==razd || i==strnum_len)
		{
			value[sta]='\0';
			nstol[i_num++]=atoi(value);
			memset(value,0,sizeof(value));
			sta=0;
		}
		else value[sta++]=strnum[i];
	}
	//value[sta]='\0';
	sta=0,i_num=0;
	for(i=0;i<=strword_len;i++)
	{
		if(strword[i]==razd || i==strword_len)
		{
			value[sta]='\0';
			strcpy(dword[i_num++],value);
			memset(value,0,sizeof(value));
			sta=0;
		}
		else value[sta++]=strword[i];
	}	
	if((in=fopen(filei,"rt"))==NULL)
	{
		printf("Input file %s can't be opened!",filei);
		 exit(1);
	}
	if((out=fopen(fileo,"wt"))==NULL)
	{
		printf("Input file %s can't be opened!",fileo);
		 exit(1);
	}
	int n_str=0, n_found=0;	   
	fgets(din,sizeof(din),in);
	if(*din!='#')rewind(in);
	//fprintf(out,"> =chr%s\n",dword[0]);
	int word1len=strlen(dword[0]);
	while(fgets(din,sizeof(din),in)!=NULL)
	{
		if(*din=='#')continue;
		DelHole(din);
		char *strstr1;
		strstr1=NULL;
		int present;
		if(logic==1)
		{
			present=1;
			for(i=0;i<nstol_tot;i++)
			{
				strstr1=strstr(din,dword[i]);
				if(strstr1==NULL){present=-1;break;}
			}
		}
		else
		{
			present=-1;			
			for(i=0;i<nstol_tot;i++)
			{
				strstr1=strstr(din,dword[i]);
				if(strstr1!=NULL){present=1;break;}
			}
		}
		if(present==-1)continue;
		for(i=0;i<nstol_tot;i++)
		{
			memset(dout[i],0,sizeof(dout[i]));
			int nst=nstol[i], p1,p2;
   			if(nst==1)p1=-1;
			else p1=StrNStr(din,'\t',nst-1);
			p2=StrNStr(din,'\t',nst);
			if(p2==-10)p2=strlen(din);
			int len=p2-p1-1;
			strncpy(dout[i],&din[p1+1],len);		
			dout[i][len]='\0';
		}	
		if(contain_type==1)
		{
			if(match_type==0 && strstr1==NULL)continue;
			if(match_type==1 && strstr1==NULL)continue;				
	//		ProbelToTab(din);					
			int print_it=-1;
			if(match_type==0)
			{
				print_it=1;
   				/*for(i=0;i<nstol_tot;i++)
				{
					if(strstr(dout[i],dword[i])==NULL)
					{
						print_it=1;
						break;
					}
				}*/
			}
			else
			{				
				if(logic==1)
				{
					print_it=1;
   					for(i=0;i<nstol_tot;i++)
					{
						if(strcmp(dout[i],dword[i])!=0)
						{
							print_it=-1;
							break;
						}
					}
				}
				else
				{
					print_it=-1;
   					for(i=0;i<nstol_tot;i++)
					{
						if(strcmp(dout[i],dword[i])==0)
						{
							print_it=1;
							break;
						}
					}
				}
			}
			if(print_it==1)
			{
			//	int loc=1+StrNStr(din,'\t',1);
			//	fprintf(out,"%s\n",&din[loc]);
				fprintf(out,"%s\n",din);
				n_found++;
			//	fprintf(out,"%s\n",dout[0]);
				//printf("%s\n",din);
				/*for(i=0;i<nstol_tot;i++)
				{
					if(i!=0)fprintf(out,"\t");
					fprintf(out,"%s",dout[i]);			
				}
				fprintf(out,"\n");*/
			}
		}
		else
		{
			if(match_type==0 && strstr1!=NULL)continue;
			if(match_type==1 && strstr1!=NULL)continue;				
	//		ProbelToTab(din);					
			int print_it=-1;
			if(match_type==0)
			{
				print_it=1;
   				/*for(i=0;i<nstol_tot;i++)
				{
					if(strstr(dout[i],dword[i])==NULL)
					{
						print_it=1;
						break;
					}
				}*/
			}
			else
			{
				print_it=1;
   				for(i=0;i<nstol_tot;i++)
				{
					if(strcmp(dout[i],dword[i])==0)
					{
						print_it=-1;
						break;
					}
				}
			}
			if(print_it==1)
			{
			//	int loc=1+StrNStr(din,'\t',1);
			//	fprintf(out,"%s\n",&din[loc]);
				fprintf(out,"%s\n",din);
			//	fprintf(out,"%s\n",dout[0]);
				//printf("%s\n",din);
				/*for(i=0;i<nstol_tot;i++)
				{
					if(i!=0)fprintf(out,"\t");
					fprintf(out,"%s",dout[i]);			
				}
				fprintf(out,"\n");*/
			}
		}
		n_str++;
		if(n_str%(int)1000000==0)
		{
			printf("\b\b\b\b\b\b\b\b\b\b%10d",n_str);	
		}
	}
  	fclose(in);
  	fclose(out);
	strcpy(file_sta,"tabnslolbik_wordget.txt");
	if((out=fopen(file_sta,"at"))==NULL)
	{
		printf("Input file %s can't be opened!",file_sta);
		 exit(1);
	}
	fprintf(out,"%s\t%s\t%s\t%d\n",argv[2],argv[4],argv[7],n_found);
	fclose(out);
	return 0;
}
