#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SEQLEN 5000
//#define DELTA 5000 // perekryvanie mejdu posl-tyami

void DelHole(char *str)
{
   char *hole;

   hole=strstr(str,"\n");
   if(hole!=NULL) *hole=0;
}

int main(int argc, char *argv[])
{
int nseq=0;
FILE *in, *out;
char head[SEQLEN], basename[80], file[80], str_num[20];// , d[DELTA];
int string_len=50000;
int shift=200;
char ext[]=".fa";

if(argc!=3)
{
	printf("Command line error: %s 1 file_input_fasta 2file_out_name", argv[0]);
    exit(1);
}
if((in=fopen(argv[1],"rt"))==NULL)
{
	puts("Input file can't be opened");
	exit(1);
}
int length=0;
strcpy(basename,argv[2]);
char c, symbol, c2;
symbol=getc(in);
rewind(in);
int part;
out = NULL;
  while((c=getc(in))!=EOF)
  {
	if(c==symbol)
	{
		nseq++;
		length=0;
		part=1;
		fgets(head,sizeof(head),in);
		DelHole(head);
		if(nseq>1)fclose(out);
		memset(file,0,sizeof(file));
		strcpy(file,basename);		
		//_itoa(nseq,str_num,10);
		sprintf(str_num, "%d", nseq);
		strcat(file,str_num);		
		strcat(file,ext);
		if((out=fopen(file,"w+t"))==NULL)
		{
			puts("Output file can't be opened");
			exit(1);
		}
		//if(nseq!=1)fprintf(out,"\n");	
		fprintf(out,">%s\n",head);	
		continue;
	}
//	if(c=='\n')continue;	
	length++;	
	fprintf(out,"%c",c);
	/*if(length==string_len)
	{
		part++;
		memset(d,0,sizeof(d));
		long pp=ftell(out);
		fseek(out,pp-(long)shift,SEEK_SET);
		for(int i=0;i<shift;i++)
		{
			c2=getc(out);
			d[i]=c2;
		}		
		fseek(out,pp,SEEK_SET);
		d[shift]='\0';
		fprintf(out,"\n>%s\tpart%d\n%s",head,part,d);
		length=0;
	}*/
  }
fclose(in);
//fprintf(out,"\n");
fclose(out);
return 1;
}