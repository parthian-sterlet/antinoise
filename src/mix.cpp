#define _CRT_SECURE_NO_WARNINGS

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
//#include  <conio.h>
#include  <math.h>
#include  <time.h>

#define MIX 10
//#define SEQLEN 1000000
#define OLIGNUM 1024
void GetSost(char *d, int word, int *sost)
{
	int i, j, k, i_sost, let;
	char letter[5] = "atgc";
	int ten[6] = { 1, 4, 16, 64, 256, 1024 };
	int lens = strlen(d);
	int size = 1;
	for (k = 0; k<word; k++)size *= 4;
	for (i = 0; i<size; i++)sost[i] = 0;
	for (i = 0; i<lens - word + 1; i++)
	{
		i_sost = 0;
		for (j = word - 1; j >= 0; j--)
		{
			for (k = 0; k<4; k++)
			{
				if (d[i + j] == letter[k]){ let = k; break; }
			}
			i_sost += ten[word - 1 - j] * let;
		}
		if (i_sost<0 || i_sost>size)
		{
			printf("Error i_sost=%d i=%d\n%s\n", i_sost, i, &d[i]);
		}
		sost[i_sost]++;
	}
}
void BigMix0(char *d, int *comp1)
{
	int i, j, lens;
	int r, f;
	char mono[] = { 'a', 't', 'g', 'c' };
	static int m = 0;

	if (m == 0){ srand((unsigned)time(NULL)); m++; }
	lens = strlen(d);
	for (i = 0; i<lens; i++)
	{
		do
		{
			r = (int)((lens - i)*rand() / RAND_MAX);
			if ((r >= 0) && (r<lens - i))break;
		} while (0<1);
		f = 0;
		for (j = 0; j<4; j++)
		{
			f += comp1[j];
			if (f == 0)continue;
			if (r <= f){ d[i] = mono[j]; comp1[j]--; break; }
		}
	}
	d[lens] = '\0';
}
void GetComp(int len, int *comp1)
{
	int i, r;
	int rest;
	static int m = 0;

	if (m == 0){ srand((unsigned)time(NULL)); m++; }
	for (i = 0; i<4; i++)comp1[i] = len / 4;
	rest = len - 4 * comp1[0];
	if (rest == 0) return;
	for (i = 0; i<rest; i++)
	{
		do
		{
			r = (int)((4)*rand() / RAND_MAX);
			if ((r >= 0) && (r<4))break;
		} while (0<1);
		comp1[r]++;
	}
} /*
  char Choose(int *p1, int *p2, int *p3, int *p4)
  {
  int r;
  double val;
  static int m=0;
  int rmax;
  //   time_t t;
  //     r=random((*p1+*p2+*p3+*p4));

  rmax=*p1+*p2+*p3+*p4;
  if(m==0) {srand( (unsigned)time(NULL) );m++;}
  val=rand();
  r=int((rmax+1)*val/RAND_MAX);
  if(r<(*p1+*p2))
  {
  if(r<*p1) {*p1-=1; return 'a';}
  else     {*p2-=1; return 't';}
  }
  else
  {
  if(r<(*p1+*p2+*p3)) {*p3-=1; return 'g';}
  else 		 {*p4-=1; return 'c';}
  }
  }   */
int Choose(int *p, int **n, int j)
{
	int i;
	double r;
	int sum = 0;
	//  for(j=0;j<4;j++)for(int i=0;i<4;i++)printf("%d ",p[n[j][i]]);printf("\n");
	//printf("CompDo ");for(i=0;i<4;i++)printf("%d ",p[n[j][i]]);printf("\t");
	//printf("IndxDo ");for(i=0;i<4;i++)printf("%d ",n[j][i]);printf("\n");
	for (i = 0; i<4; i++)sum += p[n[j][i]];
	if (sum == 0)return(-1);
	r = rand()*(double)sum / RAND_MAX;
	sum = 0;
	for (i = 0; i<4; i++)
	{
		sum += p[n[j][i]];
		if (r<sum)
		{
			p[n[j][i]]--;
			return(i);
		}
	}
	//printf("CompPo ");for(i=0;i<4;i++)printf("%d ",p[n[j][i]]);printf("\t");
	//printf("IndxPo ");for(i=0;i<4;i++)printf("%d ",n[j][i]);printf("\n");
	//   getch();
	return(-1);
}
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
/*
void BigMix2(char *d, int *comp, int word, int lend)
{
char *s,letter[5]="atgc";
int i0, i1,i,j, k, ten[8]={1,4,16,64,256,1024,4096,16384};
int lens, c, sum, fl[2]={1,1}, size=1, *comp0;
for(j=0;j<word;j++)size*=4;
int size0=size/4;
int (*forw)[4], (*back)[4];    //next symbol forward next symbol backward
back = new int[size0][4];if(back==NULL) {puts("Out of memory...");exit(1);}
forw = new int[size0][4];if(forw==NULL) {puts("Out of memory...");exit(1);}
comp0 = new int[size];if(comp0==NULL) {puts("Out of memory...");exit(1);}
for(j=0;j<size0;j++)for(i=0;i<4;i++){forw[j][i]=4*j+i;back[j][i]=size0*i+j;}
//  for(j=0;j<size0;j++)for(int i=0;i<4;i++)printf("%d %d\n",forw[j][i],back[j][i]);
//0AA  1AT   2AG 3AC 4TA 5TT 6TG 7TC 8GA 9GT 10GG 11GC 12CA  13CT 14CG 15CC

s = new char[2*lend+2];if(s==NULL) {puts("Out of memory...");exit(1);}
lens=strlen(d);
i0=i1=-1;
//for(i=0;i<2*lend;i++)s[i]=' ';
memset(s,' ',2*lend+2);
for(i=0;i<size;i++)comp0[i]=comp[i];
//printf("%s\n ",d);
//for(j=0;j<size;j++)printf("%d ",comp[j]);printf("\n");
int r=rand()%(lens-word+1);
for(j=0;j<word-1;j++)s[lend+j]=d[r+j];
int lenss=word-1;
for(i=0;;i++)
{
if(fl[0]==1)
{
j=0;
for(k=0;k<word-1;k++)
{
//            printf("%c",s[lend+i+word-2-k]);
int let=IdeLet(s[lend+i+word-2-k]);
if(let!=-1)j+=ten[k]*let;
else {fl[0]=0;break;}
}
//      printf("\t");
//       printf("Comp+1  ");for(int k=0;k<4;k++)printf("%d ",comp[forw[j][k]]);printf(" ");
//         printf("Indx+1  ");for(int k=0;k<4;k++)printf("%d ",forw[j][k]);printf("\n");
c=Choose(comp,forw,j);
//           printf("Comp+2  ");for(int k=0;k<4;k++)printf("%d ",comp[forw[j][k]]);printf("\t");
//              printf("Indx+2  ");for(int k=0;k<4;k++)printf("%d ",forw[j][k]);printf("\n");
// getch();
if(c==-1)
{
fl[0]=-1;
i1=lend+i;
break;
}
else {s[lend+i+word-1]=letter[c];lenss++;}

for(int k=0;k<2*lend;k++)
{
if(s[k]==' ')continue;
printf("%c",s[k]);
}
printf("\n");
}
//      for(j=0;j<16;j++)printf("%d ",comp[j]);printf("\n");
if(fl[1]==1)
{
j=0;
for( k=0;k<word-1;k++)
{
//                        printf("%c",s[lend-i+word-2-k]);
int let=IdeLet(s[lend-i+word-2-k]);
if(let!=-1)j+=ten[k]*let;
else {fl[0]=0;break;}
}
//    printf("\t");
//      printf("Comp-1  ");for(int k=0;k<4;k++)printf("%d ",comp[back[j][k]]);printf(" ");
//       printf("Indx-1  ");for(int k=0;k<4;k++)printf("%d ",back[j][k]);printf("\n");
c=Choose(comp,back,j);
//            printf("Comp-2  ");for(int k=0;k<4;k++)printf("%d ",comp[back[j][k]]);printf("\t");
//          printf("Indx-2  ");for(int k=0;k<4;k++)printf("%d ",back[j][k]);printf("\n");
if(c==-1)
{
fl[1]=-1;i0=lend-i;
break;
}
else {s[lend-i-1]=letter[c];lenss++;}
}
for(int k=0;k<2*lend;k++)
{
if(s[k]==' ')continue;
printf("%c",s[k]);
}
//        printf(" %d %d\n",fl[0],fl[1]);
//        for(j=0;j<16;j++)printf("%d ",comp[j]);printf("\n");
if(fl[0]!=1 && fl[1]!=1)
{
for(i=0;i<size;i++)comp[i]=comp0[i];fl[0]=-fl[0];fl[1]=-fl[1];
}
//        if(fl[0]==0 || fl[1]==0){printf("UNBASE ");getch();exit(1);}
if(lenss>=lens)
{
break;
}
}
j=0;
if(i0==-1)i0=i1-lend;
if(i1==-1)i1=i0+lend;
for(i=i0;i<i1;i++)
{
//   if(s[i]==' ')continue;
// else d[j++]=s[i];
d[j++]=s[i];
//if(j==lens){d[j]='\0';break;}
}
d[j]='\0';
//  printf("D:%s\n ",d);
//printf("S:%s\n ",s);
delete(forw);
delete(back);
delete(comp0);
delete(s);
}
*/
int BigMix2(char *d, int *comp, int word, int lend)
{
	char *s, letter[5] = "atgc";
	int i, j, k, ten[8] = { 1, 4, 16, 64, 256, 1024, 4096, 16384 };
	int lens, c, fl[2] = { 1, 1 }, size = 1, *comp0;
	for (j = 0; j<word; j++)size *= 4;
	int size0 = size / 4;
	//  int forw[OLIGNUM/4][4], back[OLIGNUM/4][4];
	int **forw, **back;    //next symbol forward next symbol backward
	forw = new int*[size0];
	if (forw == NULL) { puts("Out of memory..."); return -1; }
	for (i = 0; i<size0; i++)
	{
		forw[i] = new int[4];
		if (forw[i] == NULL) { puts("Out of memory..."); return -1; }
	}
	back = new int*[size0];
	if (back == NULL) { puts("Out of memory..."); return -1; }
	for (i = 0; i<size0; i++)
	{
		back[i] = new int[4];
		if (back[i] == NULL) { puts("Out of memory..."); return -1; }
	}
	//back = new int[size0][4];if(back==NULL) {puts("Out of memory...");exit(1);}
	//forw = new int[size0][4];if(forw==NULL) {puts("Out of memory...");exit(1);}
	comp0 = new int[size]; if (comp0 == NULL) { puts("Out of memory..."); return -1; }
	for (j = 0; j<size0; j++)for (i = 0; i<4; i++){ forw[j][i] = 4 * j + i; back[j][i] = size0*i + j; }
	//  for(j=0;j<size0;j++)for(int i=0;i<4;i++)printf("%d %d\n",forw[j][i],back[j][i]);
	//0AA  1AT   2AG 3AC 4TA 5TT 6TG 7TC 8GA 9GT 10GG 11GC 12CA  13CT 14CG 15CC

	s = new char[2 * lend + 2]; if (s == NULL) { puts("Out of memory..."); return -1; }
	int i0, i1;
	lens = strlen(d);
	memset(s, ' ', 2 * lend + 1);
	//for(i=0;i<2*lend+2;i++)s[i]=' ';
	for (i = 0; i<size; i++)comp0[i] = comp[i];
	//printf("%s\n ",d);
	//for(j=0;j<size;j++)printf("%d ",comp[j]);printf("\n");
	int r = rand() % (lens - word + 1);
	i0 = i1 = lend;
	i1 += word - 1;
	for (j = 0; j<word - 1; j++)s[lend + j] = d[r + j];
	int lenss = word - 1;
	for (i = 0;; i++)
	{
		if (fl[0] == 1)
		{
			j = 0;
			for (k = 0; k<word - 1; k++)
			{
				//            printf("%c",s[lend+i+word-2-k]);
				int let = IdeLet(s[lend + i + word - 2 - k]);
				if (let != -1)j += ten[k] * let;
				else { fl[0] = 0; break; }
			}
			//      printf("\t");
			//       printf("Comp+1  ");for(int k=0;k<4;k++)printf("%d ",comp[forw[j][k]]);printf(" ");
			//         printf("Indx+1  ");for(int k=0;k<4;k++)printf("%d ",forw[j][k]);printf("\n");
			c = Choose(comp, forw, j);
			//           printf("Comp+2  ");for(int k=0;k<4;k++)printf("%d ",comp[forw[j][k]]);printf("\t");
			//              printf("Indx+2  ");for(int k=0;k<4;k++)printf("%d ",forw[j][k]);printf("\n");
			// getch();
			if (c == -1){ fl[0] = -1; if (fl[1] == -1)break; }
			else { s[lend + i + word - 1] = letter[c]; i1++; lenss++; }
		}
		//      for(j=0;j<16;j++)printf("%d ",comp[j]);printf("\n");
		if (fl[1] == 1)
		{
			j = 0;
			for (k = 0; k<word - 1; k++)
			{
				//                        printf("%c",s[lend-i+word-2-k]);
				int let = IdeLet(s[lend - i + word - 2 - k]);
				if (let != -1)j += ten[k] * let;
				else { fl[0] = 0; break; }
			}
			//    printf("\t");
			//      printf("Comp-1  ");for(int k=0;k<4;k++)printf("%d ",comp[back[j][k]]);printf(" ");
			//       printf("Indx-1  ");for(int k=0;k<4;k++)printf("%d ",back[j][k]);printf("\n");
			c = Choose(comp, back, j);
			//            printf("Comp-2  ");for(int k=0;k<4;k++)printf("%d ",comp[back[j][k]]);printf("\t");
			//          printf("Indx-2  ");for(int k=0;k<4;k++)printf("%d ",back[j][k]);printf("\n");
			if (c == -1){ fl[1] = -1; if (fl[0] == -1)break; }
			else { s[lend - i - 1] = letter[c]; i0--; lenss++; }
		}
		//        printf(" %d %d\n",fl[0],fl[1]);
		//        for(j=0;j<16;j++)printf("%d ",comp[j]);printf("\n");
		if (fl[0] != 1 && fl[1] != 1)
		{
			for (i = 0; i<size; i++)comp[i] = comp0[i]; fl[0] = -fl[0]; fl[1] = -fl[1];
		}
		//        if(fl[0]==0 || fl[1]==0){printf("UNBASE ");getch();exit(1);}
		if (lenss >= lens)break;
	}
	j = 0;
	//printf("%d..%d\n ",i0,i1);
	//printf("Ddo:%s\n ",d);
	//printf("S:");
	//for(i=i0;i<i1;i++)printf("%c",s[i]);
	//printf("\n ");
	for (i = i0; i<i1; i++)
	{
		//       if(s[i]==' ')continue;
		//else 
		d[j++] = s[i];
		if (j == lens){ d[j] = '\0'; break; }
	}
	//  printf("Dpo:%s\n ",d);
	delete(s);
	for (i = 0; i<size0; i++)delete[] forw[i]; delete forw;
	for (i = 0; i<size0; i++)delete[] back[i]; delete back;
	//  delete(forw);
	//delete(back);
	delete(comp0);
	return 1;
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
void ConvertStr(char *d)
{
	int i, c, len = strlen(d);
	char four[] = "atgc";
	char di[6][3] = { "ag", "tc", "at", "ac", "gt", "gc" };
	char tri[4][4]= { "agt", "agc", "gtc", "tca" };

	for (i = 0; i<len; i++)
	{
		c = (int)d[i];
		if ((c>64) && (c<91)) d[i] = char(c + 32);
		if (strchr("atgc\t\n ", d[i]) != NULL) continue;
		switch (d[i])
		{
		case 'r':{
			d[i] = di[1][rand() % 2];
			break; }
		case 'y':{
			d[i] = di[1][rand() % 2];
			break; }
		case 'w':{
			d[i] = di[2][rand() % 2];
			break; }
		case 'm':{
			d[i] = di[3][rand() % 2];
			break; }
		case 'k':{
			d[i] = di[4][rand() % 2];
			break; }
		case 's':{
			d[i] = di[5][rand() % 2];
			break; }
		case 'd':{
			d[i] = tri[0][rand() % 3];
			break; }
		case 'v':{
			d[i] = tri[1][rand() % 3];
			break; }
		case 'b':{
			d[i] = tri[2][rand() % 3];
			break; }
		case 'h':{
			d[i] = tri[3][rand() % 3];
			break; }
		case 'n':{
			d[i] = four[rand() % 4];
			break; }
		}
	}
}
int CheckStr(char *d)
{
	int i, len, ret, size;
	ret = size = 0;
	len = strlen(d);
	for (i = 0; i<len; i++)
	{
		if (strchr("ATGCatgc\n\t ", (int)d[i]) != NULL)
		{
			//	d[size++]=d[i];
			continue;
		}
		else {
			ret++;
			ret = (int)d[i];
		}
	}
	return(ret);
}
//void main(void)
int main(int argc, char *argv[])
{
	char cyfr[11] = "0123456789";
	char *d, *d1, s[20000], sample[500], head[1000], s1[1000];
	char file[2][500], mfile[MIX][5] = { "~-1", "~0", "~1", "~2", "~3", "~4", "~5" };
	//0 - 0hmm 0.25
	//1 - 0hmm eq f
	//2 - 1hmm eq f
	//3 - 2hmm eq f
	/*        int comp5[1024];
	int comp4[256];
	int comp3[64];
	int comp2[16]; */
	int comp10[4];
	int comp20[OLIGNUM];
	int comp1[4];
	int comp2[OLIGNUM];

	int  n, fl, mix, len, lend, lend_cur, i, j, t, w;
	int height, width, size;
	//eight=2;
	//	width=2;
	//	mix=2;
	FILE  *input, *out;
	if (argc != 5)
	{
		puts("Syntax: 1<input_file> 2<output_file> 3<mix> 4<height>"); // 5<width> 6<join> 7<split>
		return 1;
	}
	strcpy(sample, argv[1]);
	strcpy(file[1], argv[2]);
	mix = atoi(argv[3]); mix++;
	height = atoi(argv[4]);
//	width = atoi(argv[5]);
    width =1;
	//int join = atoi(argv[6]);
	int join =0;
	int split = 0;
	//int split = atoi(argv[7]);
	strcpy(file[0], sample);
	//strcat(file[0],".fas");
	if ((input = fopen(file[0], "rt")) == NULL)
	{
		puts("Input file can't be opened!");
		return -1;
	}
	char symbol, file_tmp[20];
	strcpy(file_tmp, "mix.tmp");
	if ((out = fopen(file_tmp, "wt")) == NULL)
	{
		puts("Output file can't be opened!");
		return -1;
	}
	srand((unsigned)time(NULL));
	symbol = fgetc(input);
	rewind(input);
	fgets(s, sizeof(s), input);
	fprintf(out, "%s", s);
	lend = lend_cur = 0;
	n = 0;
	int n_str = 0;
	while (fgets(s, sizeof(s), input) != NULL)
	{
		if (*s == '\n')continue;
		if (*s == symbol)
		{
			if (lend_cur>lend)
			{
				lend = lend_cur + 1;
			}
			lend_cur = 0;
			n++;
			n_str = 0;
			fprintf(out, "%s", s);
			continue;
		}
		DelChar(s, '\n');
		int c;
		c = CheckStr(s);
		if (c != 0)
		{
			//	printf("Bad symbol %c in \n%s\n %d string of %d sequence\n",(char)c, s,n_str,n+1);
			//	ConvertStr(s);
			fprintf(out, "%s\n", s);
			len = strlen(s);
			n_str++;
		}
		else
		{
			fprintf(out, "%s\n", s);
			len = strlen(s);
			n_str++;
			//	if(n_str%100==0)fprintf(out,"\n>\n");						
		}
		lend_cur += len;
	}
	if (lend_cur>lend)lend = lend_cur + 1;
	//	long x=sizeof(d);
	fclose(input);
	fclose(out);
	//	exit(1);
	if ((input = fopen(file_tmp, "rt")) == NULL)
	{
		puts("Input file can't be opened!");
		return -1;
	}

	d = new char[lend + 1]; if (d == NULL) { puts("Out of memory..."); return -1; }
	d1 = new char[lend + 1]; if (d1 == NULL) { puts("Out of memory..."); return -1; }
	//strcpy(file[1], sample);
	//strcat(file[1], mfile[mix + 1]);
	//strcat(file[1], ".txt");
	if ((out = fopen(file[1], "wt")) == NULL)
	{
		puts("Output file can't be opened!");
		return -1;
	}
	double n_str1 = n_str;
	n = n_str = fl = 0;
	while (n >= 0)
	{
		if (fgets(s, sizeof(s), input) == NULL)
		{
			fl = -1;
		}
		n_str++;
		//	if(n_str%100==0)
		if (n == 7122)
		{
			//printf("\b\b\b\b\b\b\b\b\b\b%.7f",n_str/n_str1);
			printf("%d ", n_str);
		}
		if (((*s == symbol) || (fl == -1)) && (fl != 0))
		{
			/*	if(strstr(d,"@")!=NULL || fl==-1)
			{
			int pos=(int)(strstr(d,"@")-d);
			getch();
			}*/
			//if(CheckStr(d)==0)
			{
				//memset(head,0,sizeof(head));
				TransStr(d);
				len = strlen(d);
				if (join == 1 && n == 1)fprintf(out, "%c%s_joined_H%d_W%d\n", symbol, argv[1], height, width);
				strcpy(d1, d);
				if (mix == 0)
				{
					if (len % 4 != 0)GetComp(len, comp1);
					else for (i = 0; i<4; i++)comp1[i] = len / 4;
				}
				if (mix>1)
				{
					size = 16;
					for (j = 2; j<mix; j++)size *= 4;
					GetSost(d, mix, comp2);
				}
				long len_prin = 0;
				int len_form = 60;
				for (t = 0; t<height; t++)
				{
					if (join == 0)len_prin = 0;
					if (join == 0)fprintf(out, "%s_N%d_H%d_W%d\n", head, n, t + 1, width);
					for (w = 0; w<width; w++)
					{
						strcpy(d, d1);
						if (mix == 0)
						{
							for (j = 0; j<4; j++)comp10[j] = comp1[j];
							BigMix0(d, comp10);
						}
						if (mix == 1)BigMix1(d);
						if (mix>1)
						{
							for (j = 0; j<size; j++)comp20[j] = comp2[j];
							//							for(j=0;j<size;j++)printf("%d ",comp2[j]);printf("\n");
							BigMix2(d, comp20, mix, lend);
							//printf("PO \t");
							//							GetSost(d,mix,comp20);
							//							for(j=0;j<size;j++)printf("%d ",comp20[j]);printf("\n");
							// printf("  %s\n",d);					
							//   getch();
						}
						fprintf(out, "%s", d);
						/*	for(j=0;j<len;j++)
						{
						len_prin++;
						fprintf(out,"%c",d[j]);
						if(split!=0 && len_prin%split==0) fprintf(out,"\n%c\n",head[0]);
						if(len_prin%len_form==0)
						{
						fprintf(out,"\n");
						}
						}	*/
					}
					//if(join==0 && len_prin%(len_form*width)!=0) fprintf(out,"\n");					
					fprintf(out, "\n");
				}
			}
			if (fl == -1)
			{
				rewind(input);
				break;
			}
		}
		if (*s == symbol)
		{
			memset(head, 0, sizeof(head));
			DelHole(s);
			strcpy(head, s);
			n++;
			long p;
			p = ftell(input);
			while (fgets(s1, sizeof(s1), input) != NULL)
			{
				if (*s1 != symbol)
				{
					break;
				}
				p = ftell(input);
				strcpy(head, s1);
			}
			fseek(input, p, SEEK_SET);
			fl = 0;
			continue;
		}
		else
		{
			for (i = 0; i<10; i++)
			{
				DelChar(s, cyfr[i]);
			}
			DelChar(s, ' ');
			DelChar(s, '\t');
		}
		if (fl == 0)
		{
			memset(d, '\0', lend + 1);
			DelHole(s);
			strcpy(d, s);
			fl = 1; continue;
		}
		//		printf("d:%s\nstrlen(d):%d\n",d,strlen(d));
		int sumlen = strlen(d) + strlen(s);
		if (sumlen>lend)
		{
			puts("Size is large....");
			printf("s:%s\nstrlen(s):%zu\n", s, strlen(s));
			printf("d:%s\nstrlen(d):%zu\n%d\n", d, strlen(d), lend);
			printf("head:%s\n", head);
			return -1;
		}
		DelHole(s);
		strcat(d, s);
	}
	fclose(input);
	fclose(out);
	return 1;
}