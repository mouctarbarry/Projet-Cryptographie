#include "Chiffrement.h"
char* ChiffrementSubstitution(char* messageEntree,  char* cle)
{
	char TAB[26];
	char messageSortie[strlen(messageEntree)+1];
	
	for(int i = 0; i < 26; i++)
	{
		TAB[i] = 'A' + i;		
	}
	for(int i = 0; i <strlen(messageEntree);i++)
	{
		messageSortie[i] = *messageEntree;
		for(int j = 0; j < 26; j++)
		{
			if(TAB[j] == messageEntree[i])
				messageSortie[i] = cle[j];
		}
	}
	messageSortie[strlen(messageEntree)]='\0';
	return strdup(messageSortie);
}

char* ChiffrementVigenere(char* messageEntree, char* cle)
{
    int i;
	int code_lettre;
	int longueur_message;
	int longueur_cle;
	int decalage;
	char lettre;
	char* messageSortie = malloc(sizeof(char)*strlen(messageEntree));
	longueur_message = strlen(messageEntree);
	longueur_cle = strlen(cle);

	for (i = 1; i<= longueur_message; i++)
	{
		code_lettre = messageEntree[i-1] - 65;
		decalage = cle[(i-1)%longueur_cle] - 65 ;
		lettre = (65 + (code_lettre + decalage)%26);
		messageSortie[i-1] = lettre;
	}
	return messageSortie;
}