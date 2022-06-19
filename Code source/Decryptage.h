#ifndef Decryptage_h
#define Decryptage_h

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>  
#include <errno.h>
#include <stdbool.h>
#include <ctype.h> 

#include "Dechiffrement.h"


#define T1gram 26
#define T2gram 676
#define T3gram 500    
#define T4gram 500
#define tailleMax 200000
#define tailleCleMax 8

typedef struct frequence
{
    char gramme[5];
    float freq;
}FREQLETTRE;

typedef struct  decrypt
{
    char * texte;
    char * cle;
    FREQLETTRE * bigrammeRef;
    FREQLETTRE * trigrammeRef;
    FREQLETTRE * bigrammeTxt;
    FREQLETTRE * trigrammeTxt;
}DECRYPT;


FREQLETTRE *  freq1lettre(char *message);
FREQLETTRE *  freq2lettre(char *message); 
FREQLETTRE *  freq3lettre(char *message); 

DECRYPT  DecryptageSubstitution (char * text);

int chercherOccurrence(char* messageEntree, char* sequence, int tailleSeq, int debut);
        
int ajouterEcart(int ecart, int* taillesPossibles, int tailleProbable);
        
int Kasiski(char* messageEntree);
        
int longueurCleIC(char* messageEntree);
        
char* rechercherCle(char* messageEntree, int tailleCle);
        
char* decryptageVigenere(char* messageEntree);
#endif /*Decryptage_h*/
