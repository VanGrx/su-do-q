#include <stdio.h>
#include <stdlib.h>





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





int skini1(moguc *lista[9][9], int i, int j,int broj,int matrica[9][9])
{
	
	int p,q,m,n;
	for (p=0; p<9; p++) 
	{
		
		if (matrica[p][j]==0 && lista[p][j]->sledeci!=NULL) {
			brisi_iz_liste(lista,p,j,broj);
		}
		if (lista[p][j]->sledeci==NULL && lista[p][j]->vrednost==broj) {
			return 0;
		}
		
	}
	
	for (q=0; q<9; q++) {
		
		
		if (matrica[i][q]==0 && lista[i][q]->sledeci!=NULL) {
			brisi_iz_liste(lista,i,q,broj);
		}
		if (lista[i][q]->sledeci==NULL && lista[i][q]->vrednost==broj) {
			return 0;
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
			if (matrica[m][n]==0 && lista[m][n]->sledeci!=NULL) {
				brisi_iz_liste(lista,m,n,broj);
			}
			if (lista[m][n]->sledeci==NULL && lista[m][n]->vrednost==broj) {
				return 0;
			}
		}
		n=n-3;
	}
	
	return 1;
	
	
	
}







void pogodak_kocka(int matrica[9][9], int i, int j, moguc* lista[9][9])
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
	
	if(skini1(lista,i,j,matrica[i][j],matrica)==0)
	{
		matrica[i][j]=0;
		lista[i][j]=lista[i][j]->sledeci;
		goto pogpocetak;
	}
	
	
	return;

}



void pogodak_red(int matrica[9][9], int i, int j, moguc* lista[9][9])
{
	int m,n,p,q,vr,a=1;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j];
pogpocetak1:

	
	
	a=1;
	if (lista[i][j]==NULL)
	{
		lista[i][j]=pom1;
		return;
	}
	vr=lista[i][j]->vrednost;
	
	
	
	for (p=0;p<9;p++) {
			if (matrica[p][j]==0 && p!=i) {
				
				
				pom=lista[p][j];
				while (lista[p][j]!=NULL) {
					if (vr==lista[p][j]->vrednost) {
						a=0;
						break;
					}
					lista[p][j]=lista[p][j]->sledeci;
					
				}
				lista[p][j]=pom;
				if (a==0) {
					lista[i][j]=lista[i][j]->sledeci;
					goto pogpocetak1;
				}
			}
	}
	
	
	matrica[i][j]=vr;
	if(skini1(lista,i,j,matrica[i][j],matrica)==0)
	{
		matrica[i][j]=0;
		lista[i][j]=lista[i][j]->sledeci;
		goto pogpocetak1;
	}
	
	
	
	
	return;
	
}

int funkcija_koja_vraca_int(moguc* blok[9][9],int i, int j,int k)
{
	int br=0;
	moguc* pom=NULL;
	pom=blok[i][j];
	while (blok[i][j]!=NULL) {
		br++;
		blok[i][j]=blok[i][j]->sledeci;
	}
	blok[i][j]=pom;
	return br;


}










void pogodak_kolona(int matrica[9][9], int i, int j, moguc* lista[9][9])
{
	int m,n,p,q,vr,a=1;
	int wo;
	moguc* pom=NULL;
	moguc* pom1=NULL;
	pom1=lista[i][j];
pogpocetak2:
		
	
	a=1;
	if (lista[i][j]==NULL)
	{
		lista[i][j]=pom1;
		return;
	}
	vr=lista[i][j]->vrednost;
	
	
	
			for (q=0; q<9;q++) {
			
			
			
			if (matrica[i][q]==0 && q!=j) {
				
				
				pom=lista[i][q];
				while (lista[i][q]!=NULL) {
					if (vr==lista[i][q]->vrednost) {
						a=0;
						break;
					}
					lista[i][q]=lista[i][q]->sledeci;
					
				}
				lista[i][q]=pom;
				if (a==0) {
					lista[i][j]=lista[i][j]->sledeci;
					goto pogpocetak2;
				}
			}
	}
	
	
	matrica[i][j]=vr;
	
	if(skini1(lista,i,j,matrica[i][j],matrica)==0)
	{
		matrica[i][j]=0;
		lista[i][j]=lista[i][j]->sledeci;
		goto pogpocetak2;
	}
	
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
	FILE* ulaz;
	moguc *lista[9][9];
	int z;
	char s;
	int po=0;
	
	ulaz=fopen("brojevi.txt","r");
	if (ulaz==NULL) {
		fprintf(stderr,"GRESKA");
		exit(EXIT_FAILURE);
	}
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
	
	for (i=0; i<9; i++ ) 
		for (j=0; j<9; j++) {
			fscanf(ulaz, "%c", &s);
			matrica[i][j]=s-'0';
		if (matrica[i][j]!=0)
		skini(lista,i,j,matrica[i][j],matrica);
					
			
	
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
				
				skini1(lista,i,j,matrica[i][j],matrica);
			}
				if (matrica[i][j]==0) {
					pogodak_kocka(matrica,i,j,lista);
				}	
			if (matrica[i][j]==0) {
				pogodak_red(matrica,i,j,lista);
			}	
			if (matrica[i][j]==0) {
				pogodak_kolona(matrica,i,j,lista);
			}	
			
																		/* DRUGI DEO, ako u 3x3 ne moze taj broj, mora tu */
			

			
		}
	}
	
	po++;
	
	for (i=0; i<9; i++) 
		for (j=0; j<9; j++) 
			if (matrica[i][j]==0 && po<30) 
				goto rad;
			if (po<30) {
				ispisi(matrica);
				fclose(ulaz);
				return 0;
				
			}
	
	
	/*ODAVDE KRECE ZAEBAN DEO!!!*/
	
	int i1,j1;
	int kocka[9][9][81];
	moguc *pom_lista[9][9];
	int najmanje=2;
	int k=0;
	int w1,w2;
	int poso=0;
	for (i=0; i<9; i++) 
		for (j=0; j<9; j++) 
		{
			free(lista[i][j]);
			lista[i][j]=NULL;
			start(lista,i,j);
			start(pom_lista,i,j);
		}
amerikano:
	if (poso==1) {
		for (i=0; i<9; i++) 
			for (j=0; j<9; j++) 
			{
				free(pom_lista[i][j]);
				pom_lista[i][j]=NULL;
				start(pom_lista,i,j);
			}
	}
	
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			kocka[i][j][k]=matrica[i][j];
			if (kocka[i][j][k]!=0)
				skini(pom_lista,i,j,matrica[i][j],matrica);
		}
	}
rusofil:
		najmanje=2;
	while (1)
	{
		for (i=0; i<9; i++) {
			for (j=0; j<9; j++) {
	if (najmanje==funkcija_koja_vraca_int(pom_lista,i,j,k))
	{
		i1=i;
		j1=j;
		goto vajl;
	}	
		
		
		

		}
	}
			najmanje++;
}
	
vajl:
	
	
	kocka[i1][j1][k]=-1;
	
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			matrica[i][j]=kocka[i][j][k];
			if (kocka[i][j][k]!=0 && kocka[i][j][k]!=-1)
				po=skini1(lista,i,j,matrica[i][j],matrica);
			if (po==0) {
				if (pom_lista[i][j]==NULL)
				{
				k--;
					goto amerikano;
				}
				goto vajl;
			}
			if (kocka[i][j][k]==-1) {
				if (pom_lista[i][j]==NULL) {
					k--;
					goto amerikano;
				}
				matrica[i][j]=pom_lista[i][j]->vrednost;
				pom_lista[i][j]=pom_lista[i][j]->sledeci;
				po=skini1(lista,i,j,matrica[i][j],matrica);
				if (po==0) {
					if (pom_lista[i][j]==NULL)
					{
						k--;
						goto amerikano;
					}
					goto vajl;
				}
			}
		}
	}
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			if (matrica[i][j]!=0) {
				po=skini1(lista,i,j,matrica[i][j],matrica);
				if (po==0) {
					if (pom_lista[i][j]==NULL)
					{
						k--;
						goto amerikano;
					}
					goto vajl;
				}
				
			}
			
			
			
			
		}
	
	}
	ispisi(matrica);
	
rad1:
	
	for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
			
			
			
			if (lista[i][j]->sledeci==NULL) {							/* PRVI DEO, ako je moguc samo jedan broj, upisuje ga */
			
				matrica[i][j]=lista[i][j]->vrednost;
			
				
				po=skini1(lista,i,j,matrica[i][j],matrica);
				if (po==0) {
					if (pom_lista[i][j]==NULL)
					{
						k--;
						goto amerikano;
					}
					goto vajl;
				}
				
				
				
			}
			if (matrica[i][j]==0) {
				pogodak_kocka(matrica,i,j,lista);
			}	
			if (matrica[i][j]==0) {
				pogodak_red(matrica,i,j,lista);
			}	
			if (matrica[i][j]==0) {
				pogodak_kolona(matrica,i,j,lista);
			}	
			
			/* DRUGI DEO, ako u 3x3 ne moze taj broj, mora tu */
			
			
			
		}
	}
	po++;
	if (po<30) {
		goto rad1;
	}
	
	ispisi(matrica);
	k++;
	poso=1;
	goto rusofil;
	
	
	
	
	
	
	
	
	
	
	
	
	
					fclose(ulaz);
	
return 0;

}
