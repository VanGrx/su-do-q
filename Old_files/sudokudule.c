#include <stdio.h>
#include<stdlib.h>





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


void start(moguc *lista[9][9], int i, int j)
{
	moguc *pom;
	pom=lista[i][j];
	int p=1;
	while (p<10)
		   {
			   lista[i][j]=dodaj_u_listu(lista[i][j],p);			
			   p++;
		   
		   }
	
	return;
}


void brisi_iz_liste(moguc *lista[9][9], int i, int j, int broj)
{

	moguc *pom;
	moguc *pro;
	pro=NULL;
	pom=lista[i][j];
	if (lista[i][j]->vrednost==broj) {
		pro=(lista[i][j]->sledeci)->sledeci;
		lista[i][j]=lista[i][j]->sledeci;
		lista[i][j]->sledeci=pro;
		return;
	}
	
		while (lista[i][j]->sledeci!=NULL) {
				if ((lista[i][j]->sledeci)->vrednost==broj) {
					lista[i][j]->sledeci=(lista[i][j]->sledeci)->sledeci;
					lista[i][j]=pom;
					return;
				}
			lista[i][j]=lista[i][j]->sledeci;
			
			
		}
	lista[i][j]=pom;
	return;



}


void skini(moguc *lista[9][9], int i, int j,int broj,int matrica[9][9])
{
	
	int p,q,m,n;
	for (p=0; p<9; p++) 
	{
				
		if (matrica[p][j]==0) {
			brisi_iz_liste(lista,p,j,broj);
		}
					
	}

	for (q=0; q<9; q++) {
		
		
		if (matrica[i][q]==0) {
			brisi_iz_liste(lista,i,q,broj);
		}
	}
	
	if (i<=2) 
		m=0;
			else
			{
				if (i<=5) 
					m=3;
				else
					m=6;
			}
	
	
	if (j<=2) 
		n=0;
	else
	{
		if (j<=5) 
			n=3;
		else
			n=6;
	}
			for (p=0; p<3; p++,m++) {
				for (q=0; q<3;q++,n++) {
					if (matrica[m][n]==0) {
						brisi_iz_liste(lista,m,n,broj);
					}
				}
				n=n-3;
			}
	
	return;

	
	
}

void pogodak(int matrica[9][9], int i, int j, moguc* lista[9][9])
{
	int m,n,p,q,vr,a=1;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j];
	pogpocetak:
	if (i<=2) 
		m=0;
	else
	{
		if (i<=5) 
			m=3;
		else
			m=6;
	}
	
	
	if (j<=2) 
		n=0;
	else
	{
		if (j<=5) 
			n=3;
		else
			n=6;
	}
	

	a=1;
		if (lista[i][j]==NULL)
		{
			lista[i][j]=pom1;
			return;
		}
	vr=lista[i][j]->vrednost;


		
	for (p=0; p<3; p++,m++) {
		for (q=0; q<3;q++,n++) {
			
			
			
			if (matrica[m][n]==0 && (m!=i || n!=j)) {
				
				
				pom=lista[m][n];
				while (lista[m][n]!=NULL) {
					if (vr==lista[m][n]->vrednost) {
						a=0;
						break;
					}
					lista[m][n]=lista[m][n]->sledeci;
					
				}
				lista[m][n]=pom;
				if (a==0) {
					lista[i][j]=lista[i][j]->sledeci;
					goto pogpocetak;
				}
			}
		}
		n=n-3;
	}
	
	
	matrica[i][j]=vr;
	
skini(lista,i,j,matrica[i][j],matrica);
	
	
	return;











}
void ispisi(int matrica[9][9])
{
	int i,j;
	for (i=0; i<9; i++) {
		if (i%3==0) {
			printf(" ____________________________\n");
		}
		for (j=0; j<9; j++) {
			if (j%3==0) {
				printf("|");
			}
			printf("%d  ", matrica[i][j]);
		}
		printf("\n");
	}

	return;
}

int main()
{
	int matrica[9][9];
	int i,j;
	int x,a;
	moguc *lista[9][9];
	int z;
	char s[82];
	int po=0;
pocetak:
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			matrica[i][j]=0;
			lista[i][j]=NULL;
			start(lista,i,j);
		}
	}
	a=1;
	printf("Unesite matricu\n");
	scanf("%s", s);
	for (i=0; i<9; i++ ) 
		for (j=0; j<9; j++) {
	
			matrica[i][j]=s[po]-'0';
		if (matrica[i][j]!=0)
		skini(lista,i,j,matrica[i][j],matrica);
					
			po++;
	
	}
	
	ispisi(matrica);
	printf("Da li je ispsiana matrica dobro napisana?");
	scanf("%d", &a);
	if (a==0) {
		goto pocetak;
	}
	
	
rad:
	
	
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			
			
			
			if (lista[i][j]->sledeci==NULL) {							/* PRVI DEO, ako je moguc samo jedan broj, upisuje ga */
				matrica[i][j]=lista[i][j]->vrednost;
				
				skini(lista,i,j,matrica[i][j],matrica);
			}
				if (matrica[i][j]==0) {
					pogodak(matrica,i,j,lista);
				}	
			
																		/* DRUGI DEO, ako u 3x3 ne moze taj broj, mora tu */
			

			
		}
	}
	
			
	
	for (i=0; i<9; i++) 
		for (j=0; j<9; j++) 
			if (matrica[i][j]==0) 
				goto rad;
	
	
	
				ispisi(matrica);

	
	
return 0;

}
