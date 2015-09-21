/*
Autor: Raquel Romero Silva.

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stddef.h>


using namespace std;

FILE *fp;
char Entrada;
const char *Reservada[]={"DO","BEGIN","ELSE","END","IF","THEN","VAR","WHILE","REAL"};
const char *Delimitador[]={",",";",":=",".","(",")"};
const char *Matematica[]={"+","-","*","/"};
const char *Asignacion[]={"<","<=","=",">",">=","<>","!"};
int contaRese=0;
int contaDeli=0;
int contaMat=0;
int contaAsig=0;
int contaVari=0;
int contacost=0;
int Lexico(char Analizar[],int Decision);
char Principal(char Limite);
char Digito(char Limite);
char Otro(char Limite);

int main()
{
	if ((fp=fopen("fuente.txt","r"))==NULL)
		cout  << "nCrear el Archivo *.pasn";
	else
	{
		cout  << "Analizando";
		//Entrada = fgetc(fp);
	/*while (Entrada!=EOF)
	{
		printf("%c",Entrada);
		/*if (isalpha(Entrada))
		Entrada=Principal(Entrada);
		else if (isdigit(Entrada))
		Entrada=Digito(Entrada);
		else Entrada=Otro(Entrada);
		
		
	}
	*/
	char caracter;
	if (fp == NULL){

		printf("\nError de apertura del archivo. \n\n");
        }else{
        
	
	    printf("\nEl contenido del archivo de prueba es \n\n");
	
	    while (feof(fp) == 0)
	    {
			caracter = fgetc(fp);
			if (isalpha(caracter)){
				caracter=Principal(caracter);
			}
			else{
				if (isdigit(caracter)){
					caracter=Digito(caracter);
				}else{
					caracter=Otro(caracter);
				}
			}
			
		
				
		
	    }
        }
        fclose(fp);
	
	
	
	
		cout << "nSe llego en fin del archivo";
	}
		system("PAUSE");
	return 0;
}

int Lexico(char Analizar[],int Decision)
{
	int i=0;

	switch (Decision)
	{
	case 1:
	for (i=0;i<=9;i++)
	{
	if (strcmp(Reservada[i],Analizar)==0)
	return(i+1);
	}
	case 2:
	{
	for (i=0;i<=5;i++)
	{
	if (strcmp(Delimitador[i],Analizar)==0)
	return(i+1);
	}
	return(0);
	}
	case 3:
	{
	for (i=0;i<=3;i++)
	{
	if (strcmp(Matematica[i],Analizar)==0)
	{
	return(i+1);
	}
	}
	return(0);
	}
	case 4:
	{
	for (i=0;i<=6;i++)
	{
	if (strcmp(Asignacion[i],Analizar)==0)
	{
	return(i+1);
	}
	}
	return(0);
	}
	}
}

char Principal(char Limite)
{
	
	int Proto;
	int i=-1;
	char IniComp[20];

	while((isalpha(Limite))||(isdigit(Limite)))
	{
		IniComp[++i]=Limite;
		Limite=fgetc(fp);
	}

	IniComp[i+1]='\0';
	

	
	if (Proto=Lexico(IniComp,1))
	{
		cout << IniComp << " (1," << (Proto-1) << ")";
		contaRese++;
		cout << "Palabras Reservadas: " << contaRese << "\n";
	} else
	{
		Proto=Lexico(IniComp,6);
		cout << IniComp << " (6," << (Proto-1) << ")n";
		contaVari++;
		cout << "ttVariables: " << contaVari << "nn";
	}
	
	return(Limite);
}

char Digito(char Limite)
{
int i=-1;
char DigiTipo[20];
int TipDat;

while((isdigit(Limite)))
{
DigiTipo[++i]=Limite;
Limite=fgetc(fp);
}

DigiTipo[i+1]='\0';
TipDat=Lexico(DigiTipo,5);
cout << DigiTipo << " (5," << (TipDat-1) << ")";
contacost++;
cout << "Constantes numericos: " << contacost << "\n";
return(Limite);
}

char Otro(char Limite)
{
	char OtrTipo[20];
	int AsigYN,AsigXN;
	OtrTipo[0]=Limite;
	OtrTipo[1]='\0';

	if (AsigYN=Lexico(OtrTipo,3))
	{
		cout << OtrTipo << " (3," << (AsigYN-1) << ")n";
		Limite=fgetc(fp);
		contaMat++;
		cout << "ttOperador Matematico: " << contaMat << "nn";
		goto Brincar;
	}

	if (AsigYN=Lexico(OtrTipo,4))
	{
		Limite=fgetc(fp);
		OtrTipo[1]=Limite;
		OtrTipo[2]='\0';

		if (AsigXN=Lexico(OtrTipo,4))
		{
			cout << OtrTipo << " (4," << (AsigXN-1) << ")n";
			contaAsig++;
			cout << "ttAsignacion: " << contaAsig << "nn";
			goto Brincar;
		}   else
			OtrTipo[1]='\0';
			cout << OtrTipo << " (4," << (AsigYN-1) << ")n";
			contaAsig++;
			cout << "ttAsignacion: " << contaAsig << "nn";
			goto Brincar;
	}

	if (Limite==':')
	{
		Limite=fgetc(fp);
	if (Limite=='=')
	{
		cout << ":= (2,2)n";
		contaAsig++;
		cout << "ttAsignacion: " << contaAsig << "n";
	}
		Limite=fgetc(fp);
		goto Brincar;
	} 
	else
	{
	if (AsigYN=Lexico(OtrTipo,2))
	{
	cout << OtrTipo << " (2," << (AsigYN-1) << ")n";
	contaDeli++;
	cout << "ttDelimitador: " << contaDeli << "nn";
	Limite=fgetc(fp);
	goto Brincar;
	}
	}

	if ((Limite!='n')&&(Limite!=' '))
	cout << "nVerificar sintaxis……n"<< Limite;
	Limite=fgetc(fp);
	Brincar: return(Limite);
	}

