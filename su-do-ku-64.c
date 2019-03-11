#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int indi=0;

typedef struct _moguc
{
	int vrednost;
	struct _moguc *sledeci;
	
}moguc;

moguc* kreiraj_novi(int vrednost)
{
	moguc* novi= (moguc*)malloc(sizeof(moguc));
	if (novi==NULL) {
		fprintf(stderr,"Greska");
		exit(EXIT_FAILURE);
	}
	novi->vrednost=vrednost;
	novi->sledeci=NULL;
	return novi;
}

moguc* dodaj_u_listu(moguc* koren, int vrednost)
{
	if(koren==NULL)
		return kreiraj_novi(vrednost);
	
	koren->sledeci=dodaj_u_listu(koren->sledeci, vrednost);
	
	return koren;
	
	
}

void start(moguc *lista[64][64][5], int i, int j,int k)
{
	moguc *pom;
	pom=lista[i][j][k];
	int p=1;
	while (p<65)
	{
		lista[i][j][k]=dodaj_u_listu(lista[i][j][k],p);			
		p++;
		
	}
	
	return;
}


void brisi_iz_liste(moguc *lista[64][64][5], int i, int j, int k, int broj)
{
	
	moguc *pom;
	moguc *pro;
	pro=NULL;
	pom=lista[i][j][k];
	if (lista[i][j][k]->vrednost==broj) {
		
		lista[i][j][k]=lista[i][j][k]->sledeci;
		return;
	}
	
	while (lista[i][j][k]->sledeci!=NULL) {
		if ((lista[i][j][k]->sledeci)->vrednost==broj) {
			lista[i][j][k]->sledeci=(lista[i][j][k]->sledeci)->sledeci;
			lista[i][j][k]=pom;
			return;
		}
		lista[i][j][k]=lista[i][j][k]->sledeci;
		
		
	}
	lista[i][j][k]=pom;
	return;
	
	
	
}

void skini(moguc *lista[64][64][5], int i, int j, int k,int broj,int matrica[64][64][5])
{
	
	int p,q,m,n;
	for (p=0; p<64; p++) 
	{
		
		if (matrica[p][j][k]==0 && lista[p][j][k]!=NULL) {
			brisi_iz_liste(lista,p,j,k,broj);
		}
		
	}
	
	for (q=0; q<64; q++) {
		
		
		if (matrica[i][q][k]==0 && lista[i][q][k]!=NULL) {
			brisi_iz_liste(lista,i,q,k,broj);
		}
	}
	
	if (i<=7) 
		m=0;
	else
	{
		if (i<=15) 
			m=8;
		else
			if(i<=25)
			m=16;
		else
			if(i<=51)	
			m=24;
			else
				if(i<=59)
				m=52;
			else
				if(i<=47)
				m=40;
			else
				if(i<55)
				m=48;
			else
				m=56;
			}
	
	
	if (j<=7) 
		n=0;
	else
	{
		if (j<=15) 
			n=8;
		else
			if(j<=25)
			n=16;
		else
			if(j<=51)	
			n=24;
			else
				if(j<=59)
				n=52;
			else
				if(j<=47)
				n=40;
			else
				if(j<55)
				n=48;
			else
				n=56;
			}
	for (p=0; p<8; p++,m++) {
		for (q=0; q<8;q++,n++) {
			if (matrica[m][n][k]==0 && lista[m][n][k]!=NULL) {
				brisi_iz_liste(lista,m,n,k,broj);
			}
		}
		n=n-8;
	}
	
	return;
	
	
	
}


void pogodak_kocka(int matrica[64][64][5], int i, int j, int k, moguc* lista[64][64][5])
{
	int m,n,p,q,vr,a=1;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j][k];
pogpocetak:
	if (i<=7) 
		m=0;
	else
	{
		if (i<=15) 
			m=8;
		else
			if(i<=25)
			m=16;
		else
			if(i<=51)	
			m=24;
			else
				if(i<=59)
				m=52;
			else
				if(i<=47)
				m=40;
			else
				if(i<55)
				m=48;
			else
				m=56;
			}
	
	
	if (j<=7) 
		n=0;
	else
	{
		if (j<=15) 
			n=8;
		else
			if(j<=25)
			n=16;
		else
			if(j<=51)	
			n=24;
			else
				if(j<=59)
				n=52;
			else
				if(j<=47)
				n=40;
			else
				if(j<55)
				n=48;
			else
				n=56;
			}
	
	a=1;
	if (lista[i][j][k]==NULL)
	{
		lista[i][j][k]=pom1;
		return;
	}
	vr=lista[i][j][k]->vrednost;
	
	
	
	for (p=0; p<8; p++,m++) {
		for (q=0; q<8;q++,n++) {
			
			//Trazi za uneto i i j da li se vrednost iz liste moze smestiti samo na tu poziciju i nigde drugde u 5x5 kvadratu
			
			if (matrica[m][n][k]==0 && (m!=i || n!=j)) {
				
				
				pom=lista[m][n][k];
				while (lista[m][n][k]!=NULL) {
					if (vr==lista[m][n][k]->vrednost) {
						a=0;
						break;
					}
					lista[m][n][k]=lista[m][n][k]->sledeci;
					
				}
				lista[m][n][k]=pom;
				if (a==0) {
					lista[i][j][k]=lista[i][j][k]->sledeci;
					goto pogpocetak;
				}
			}
		}
		n=n-8;
	}
	
	
	matrica[i][j][k]=vr;
		indi=1;
	skini(lista,i,j,k,matrica[i][j][k],matrica);
	
	return;
	
}


void pogodak_red(int matrica[64][64][5], int i, int j, int k, moguc* lista[64][64][5])
{
	int m,n,p,q,vr,a=1;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j][k];
pogpocetak1:
	
	
	
	a=1;
	if (lista[i][j][k]==NULL)
	{
		lista[i][j][k]=pom1;
		return;
	}
	vr=lista[i][j][k]->vrednost;
	
	
	
	for (p=0;p<64;p++) {
		if (matrica[p][j][k]==0 && p!=i) {
			
			
			pom=lista[p][j][k];
			while (lista[p][j][k]!=NULL) {
				if (vr==lista[p][j][k]->vrednost) {
					a=0;
					break;
				}
				lista[p][j][k]=lista[p][j][k]->sledeci;
				
			}
			lista[p][j][k]=pom;
			if (a==0) {
				lista[i][j][k]=lista[i][j][k]->sledeci;
				goto pogpocetak1;
			}
		}
	}
	
	
	matrica[i][j][k]=vr;
	indi=1;
	skini(lista,i,j,k,matrica[i][j][k],matrica);
	
	return;
	
}

void pogodak_kolona(int matrica[64][64][5], int i, int j,int k, moguc* lista[64][64][5])
{
	int m,n,p,q,vr,a=1;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j][k];
pogpocetak2:
	
	
	a=1;
	if (lista[i][j][k]==NULL)
	{
		lista[i][j][k]=pom1;
		return;
	}
	vr=lista[i][j][k]->vrednost;
	
	
	
	for (q=0; q<64;q++) {
		
		
		
		if (matrica[i][q][k]==0 && q!=j) {
			
			
			pom=lista[i][q][k];
			while (lista[i][q][k]!=NULL) {
				if (vr==lista[i][q][k]->vrednost) {
					a=0;
					break;
				}
				lista[i][q][k]=lista[i][q][k]->sledeci;
				
			}
			lista[i][q][k]=pom;
			if (a==0) {
				lista[i][j][k]=lista[i][j][k]->sledeci;
				goto pogpocetak2;
			}
		}
	}
	
	
	matrica[i][j][k]=vr;
	indi=1;
	skini(lista,i,j,k,matrica[i][j][k],matrica);
	
	return;
	
}

int funkcija_koja_vraca_int(moguc* lista[64][64][5],int i, int j,int k)
{
	int br=0;
	moguc* pom=NULL;
	pom=lista[i][j][k];
	while (lista[i][j][k]!=NULL) {
		br++;
		lista[i][j][k]=lista[i][j][k]->sledeci;
	}
	lista[i][j][k]=pom;
	return br;
	
	
}

int provera(int matrica[64][64][5],moguc* lista[64][64][5],int k)
{
	int i;
	int j;
	int m;
	int n;
	int p;
	int q;
	int br=1;
	int brojac=0;
	while(br<65)
	{
		for (i=0; i<64; i++) {
			brojac=0;
			for (j=0; j<64; j++) {
				if (matrica[i][j][k]==br) {
					brojac++;
				}
				if (brojac>1) {
					return 0;
				}
			}
			
		}
		br++;
	}
	br=1;
	while(br<65)
	{
		for (j=0; j<64; j++) {
			brojac=0;
			for (i=0; i<64; i++) {
				if (matrica[i][j][k]==br) {
					brojac++;
				}
				if (brojac>1) {
					return 0;
				}
			}
			
		}
		br++;
	}
	br=1;
	while(br<65)
	{
		for (i=0; i<64; i++) {
			for (j=0; j<64; j++) {
				
				
				if (i<=7) 
		m=0;
	else
	{
		if (i<=15) 
			m=8;
		else
			if(i<=25)
			m=16;
		else
			if(i<=51)	
			m=24;
			else
				if(i<=59)
				m=52;
			else
				if(i<=47)
				m=40;
			else
				if(i<55)
				m=48;
			else
				m=56;
			}
	
	
	if (j<=7) 
		n=0;
	else
	{
		if (j<=15) 
			n=8;
		else
			if(j<=25)
			n=16;
		else
			if(j<=51)	
			n=24;
			else
				if(j<=59)
				n=52;
			else
				if(j<=47)
				n=40;
			else
				if(j<55)
				n=48;
			else
				n=56;
			}
				brojac=0;	
				for (p=0; p<8; p++,m++) 
				{
					for (q=0; q<8;q++,n++) 
						if (matrica[m][n][k]==br) {
							brojac++;
							if (brojac>1) {
								return 0;
							}
						}
					n=n-8;
				}
			
			}
		}
				br++;
		}
	
	for (i=0; i<64; i++) {
		for (j=0; j<64; j++) {
			if (lista[i][j][k]==NULL && matrica[i][j][k]==-1) {
				return 0;
			}
		}
	}
	
	
	
	
	
	
	return 1;
}

void kopiranje(int matrica[64][64][5],moguc* lista[64][64][5], int k)
{
	int i,j;
	
	for (i=0; i<64; i++) 
		for (j=0; j<64; j++) 							//FIZZ ME!!! RESIO STA JE -1!!!
			{	
			lista[i][j][k+1]=NULL;		
			start(lista,i,j,k+1);
			matrica[i][j][k+1]=0;
			}
	for (i=0; i<64; i++) {
		for (j=0; j<64; j++) { 	
			matrica[i][j][k+1]=matrica[i][j][k];
			if (matrica[i][j][k]!=0 && matrica[i][j][k]!=-1) {
				skini(lista,i,j,k+1,matrica[i][j][k],matrica);
			}
			if (matrica[i][j][k]==-1) {
				matrica[i][j][k+1]=lista[i][j][k]->vrednost;
				skini(lista,i,j,k+1,matrica[i][j][k+1],matrica);
				lista[i][j][k]=lista[i][j][k]->sledeci;
			}
		}
	}
	
	return;
	
	
}

void ispisi(int matrica[64][64][5],int k)
{
	int i,j;
	FILE* izlaz=fopen("izlaz.txt","w");
		if (izlaz==NULL) {
		fprintf(stderr,"GRESKA");
		exit(EXIT_FAILURE);
	}
	for (i=0; i<64; i++) {
		if (i%8==0) {
			fprintf(izlaz," ____________________________\n");
		}
		for (j=0; j<64; j++) {
			if (j%8==0) {
				fprintf(izlaz,"|");
			}
			fprintf(izlaz,"%d  ", matrica[i][j][k]);
		}
		fprintf(izlaz,"\n");
	}
	
	return;
}



int main()
{
	int matrica[64][64][5];
	int i,j,k=0;
	int najmanje=2;
	int x,a;
	int op=0;
	int i1,j1;
	FILE* ulaz;
	moguc *lista[64][64][5];
	int z;
	int s;
	int po=0;
	int ququ=0;
	ulaz=fopen("brojevi.txt","r");
	if (ulaz==NULL) {
		fprintf(stderr,"GRESKA");
		exit(EXIT_FAILURE);
	}
	
pocetak:
	for (i=0; i<64; i++) {
		for (j=0; j<64; j++) {
			for (k=0; k<5; k++) {
				matrica[i][j][k]=0;
				lista[i][j][k]=NULL;
				start(lista,i,j,k);
			}
		}
	}
	k=0;
	a=1;
	
	
	for (i=0; i<64; i++ ) 
		for (j=0; j<64; j++) {
			fscanf(ulaz, "%d", &s);
			matrica[i][j][k]=s;
			if (matrica[i][j][k]!=0)
				skini(lista,i,j,k,matrica[i][j][k],matrica);
			
			
			
		}
	
	printf("Da li je ispsiana matrica dobro napisana?");
	scanf("%d", &a);
	if (a==0) {
		goto pocetak;
	}
	clock_t start=clock();
rad:	
		printf("%d",ququ++);
		indi=0;
	for (i=0; i<64; i++) {
		for (j=0; j<64; j++) {
			
				if(matrica[i][j][k]==0 && lista[i][j][k]==NULL)
					{
					k--;
				goto prv;					
					}
	if (matrica[i][j][k]<1 && lista[i][j][k]->sledeci==NULL) {/* PRVI DEO, ako je moguc samo jedan broj, upisuje ga */
		matrica[i][j][k]=lista[i][j][k]->vrednost;
		skini(lista,i,j,k,matrica[i][j][k],matrica);
		indi=1;
	}
	if (matrica[i][j][k]==0) {			//DRUGI DEO, proverava da li je samo na toj poziciji moguc taj broj
		pogodak_kocka(matrica,i,j,k,lista);
	}	
	if (matrica[i][j][k]==0) {
		pogodak_red(matrica,i,j,k,lista);
	}	
	if (matrica[i][j][k]==0) {
		pogodak_kolona(matrica,i,j,k,lista);
	}	
		}
	}
	prv:
	if (provera(matrica,lista,k)==0) {
	

		while (provera(matrica,lista,k)==0) {
			k--;
		}
		kopiranje(matrica,lista,k);
		k++;
		goto rad;
	}
	
	
	
	
		
	
	for (i=0; i<64; i++) 
		for (j=0; j<64; j++) 
			{
			if (matrica[i][j][k]==0 && indi==1) 
			goto rad;
			if(matrica[i][j][k]==0 && indi==0)
			goto jmp;			
			}	
		
		ispisi(matrica,k);
		printf("%d\n",k);
		fclose(ulaz);
		printf("%f", ((double)clock()-start)/CLOCKS_PER_SEC);
		return 0;

	jmp:	
	najmanje=2;
	
	while (najmanje<=64) {
	for (i=0; i<64 && najmanje<65; i++) 
		for (j=0; j<64 && najmanje<65; j++) 
	if (najmanje==funkcija_koja_vraca_int(lista,i,j,k) && matrica[i][j][k]==0) {
		matrica[i][j][k]=-1;
		kopiranje(matrica,lista,k);
		najmanje=65;
	}
		najmanje++;
	}
	k++;
	goto rad;

	
	return 0;
}


