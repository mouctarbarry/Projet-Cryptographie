#ifndef Chiffrement_h
#define Chiffrement_h

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>  

char* ChiffrementSubstitution(char* messageEntree, char* cle);

char* ChiffrementVigenere(char* messageEntree, char* cle);

#endif /*Chiffrement_h*/
