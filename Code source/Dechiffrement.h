#ifndef Dechiffrement_h
#define Dechiffrement_h


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
// pour la manipulation des fichiers qui contiendront les textes en clair et chiffrés
#include <string.h>  
// gerer la clef de chiffrement qui sera un attribut de type string

char* DechiffrementSubstitution(char* messageEntree, char* cle);

char* DechiffrementVigenere(char* messageEntree, char* cle);
#endif /*Dechiffrement_h*/
