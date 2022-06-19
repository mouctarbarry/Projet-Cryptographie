#include "Dechiffrement.h"
char* DechiffrementVigenere(char* messageEntree, char* cle){

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

		if(code_lettre - decalage >= 0)
		{
			lettre = (65 + (code_lettre - decalage)%26);
			messageSortie[i-1] = lettre;
			
		}

		else
			{
				lettre = (65 + (code_lettre - decalage)%26+26);
				messageSortie[i-1] = lettre;
			}
		
	}
	
	return messageSortie;

}



char * DechiffrementSubstitution(char* messageChiffre, char* cle){
    char *messageClaire = malloc (sizeof(char)*strlen(messageChiffre));
    char * tabA_Z = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
               
    for (size_t i = 0; i < strlen(messageChiffre); i++){
        for (int j = 0; j < 26; j++){
            if (messageChiffre[i] == cle[j]){
                messageClaire[i] = tabA_Z[j];
                break;
            }     
        }
        
    }
    return messageClaire;
}
