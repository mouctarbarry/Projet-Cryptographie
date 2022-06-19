#include "Decryptage.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dechiffrement.h"


int chercherOccurrence(char* messageEntree, char* sequence, int tailleSeq, int debut)
{
   int iDeb;
   int tailleMessage = strlen(messageEntree);

   for(iDeb = debut; iDeb < tailleMessage - tailleSeq + 1; ++iDeb) {
      int i, iSeq;
      i = iDeb;
      iSeq = 0;
      while(i < tailleMessage && sequence[iSeq] == messageEntree[i])
      {
         ++i;
         ++iSeq;
      }

      if(iSeq == tailleSeq)
         return iDeb;
   }

   return -1;
}


int ajouterEcart(int ecart, int taillesPossibles[], int tailleProbable)
{
   int i;

   for(i = 2; i <= ecart; ++i) {
      if(ecart % i == 0) {
         ++taillesPossibles[i];
         if(taillesPossibles[i] > taillesPossibles[tailleProbable])
            tailleProbable = i;
      }
   }
   return tailleProbable;
}

int Kasiski(char* messageEntree)
{
   int tailleSeq, iDeb;
   bool find;
   int tailleMessage = strlen(messageEntree);
   int tailleProbable = 0;
   int taillesPossibles[tailleMessage];
   int i;
     for(i=0;i<tailleMessage;i++){
         taillesPossibles[i] = 0;
     }
   tailleSeq = 3;
   find = true;

   while(find) {
      find = false;
      for(iDeb = 0; iDeb < tailleMessage - tailleSeq + 1; ++iDeb) {
         char sequence[tailleSeq + 1];
         int i;
         int occ;

         for(i = 0; i < tailleSeq; ++i)
         sequence[i] = messageEntree[iDeb + i];
         sequence[i] = '\0';

         occ = chercherOccurrence(messageEntree, sequence, tailleSeq, iDeb + tailleSeq);
         if(occ != -1) {
            int ecart;

            ecart =  occ - iDeb;
            find = true;


           tailleProbable = ajouterEcart(ecart,taillesPossibles,tailleProbable);
         }
      }

      ++tailleSeq;
   }

   printf(" taille cle : %d\n",tailleProbable );
   return tailleProbable;
}

int longueurCleIC(char* messageEntree){

  int i,k,N,m,j,longueur_cle;
  float Ic, max,len,tab[7];
  char* tampon = malloc(sizeof(char)*strlen(messageEntree));

  int *a = calloc(strlen(messageEntree),sizeof(int));
  

  for(i = 1; i< 8; i++)
  {

    Ic = 0;
    k = 0;
	  
    while(k <= strlen(messageEntree))
    {
  
      tampon[k] = messageEntree[k];
      k = k+i;

    } 
  
    len = strlen(messageEntree)/(float)i;
  
    for (j = 0;j < strlen(messageEntree); j = j+i)
    {

      a[j] = (int)tampon[j]; 
    }

    for (j= 65; j <= 90; ++j)
    {
    
      N = 0;

      for (m= 0; m < strlen(messageEntree); m = m+i)
      {
        if (a[m] == j)
        {
          N = N + 1;
        }
      } 
    
      Ic += (( N * (N-1) )/ (ceil(len) * (ceil(len)-1))) ;
      tab[i] = Ic;
    }    

  } 
  
  max = 0.0;
  longueur_cle = 0;

  for (int m = 1; m < 8; ++m)
  {

    if(tab[m] > max && m > 1)
    {
      longueur_cle = m;
      max = tab[m];
    }
  }
   	
return longueur_cle;
  
}

char* rechercherCle(char* messageEntree, int tailleCle){
char morceau[tailleCleMax][tailleMax];
int iMorceau[tailleCleMax];
int freq[tailleCleMax][26];
int freqmax[tailleCleMax];
char* cle = malloc(sizeof(int)*(tailleCleMax));
int i, iL, iC;

   for(i = 0; messageEntree[i] != '\0'; ++i) {
      iL = i % tailleCle;
      morceau[iL][iMorceau[iL]] = messageEntree[i];
      ++iMorceau[iL];
   }
 
  for(iC = 0; iC < tailleCle; ++iC) {
      for(i = 0; i < iMorceau[iC]; ++i) {
         iL = morceau[iC][i] - 'A';

         ++freq[iC][iL];
         if(freq[iC][iL] > freq[iC][freqmax[iC]])
            freqmax[iC] = iL;
      }
   }

   for(iC = 0; iC < tailleCle; ++iC) {
      cle[iC] = (freqmax[iC] + 'A') - ('E' - 'A');
      if(cle[iC] < 'A')
         cle[iC] += 26;
   }


   cle[iC] = '\0';

return cle;
}



char* decryptageVigenere(char* messageEntree)
{
    int i = 0;
    int j = 0;
    int tailleCle = 0;

    j = Kasiski(messageEntree);
    i = longueurCleIC(messageEntree);
    

    if (i%j == 0)
    {
        tailleCle = i;
    }
    else
    {
        printf("Erreur dans la taille de la clé \n");
        exit(0);
    }


   char* cle = rechercherCle(messageEntree, tailleCle);
  
   char* messageSortie = DechiffrementVigenere(messageEntree, cle);

   return messageSortie; 
}



FREQLETTRE * load2gramme (){
    FILE *f = NULL;
    FREQLETTRE * f2gram = malloc(T2gram*sizeof(FREQLETTRE));
    //chargement des bigrammes 
    f = fopen ("t2grams.txt", "r");
    if (f==NULL) {
        perror("impossible douvrir le fichier !");
        exit(2);
    }
    for (int i = 0; i < T2gram; i++)   
    {
        fscanf (f, "%s", f2gram[i].gramme);
        //printf("%s\n", f2gram[i].gramme);
    }
    return f2gram;
}   

FREQLETTRE * load3gramme (){
    FILE *f = NULL;
    FREQLETTRE * f3gram = malloc(T2gram*sizeof(FREQLETTRE));
    //chargement des trigrammes 
    f = fopen ("t3grams.txt", "r");
    if (f==NULL) {
        perror("impossible douvrir le fichier !");
        exit(2);
    }
    for (int i = 0; i < T3gram; i++)   
    {
        fscanf (f, "%s", f3gram[i].gramme);
       // printf("%s\n", f3gram[i].gramme);
    }
    return f3gram;
}

int compare (const void * c1, const void * c2){
    FREQLETTRE first = * (const FREQLETTRE * ) c1;
    FREQLETTRE second = * (const FREQLETTRE * ) c2;
    return  second.freq- first.freq;
}

void trier(FREQLETTRE *freq, int taille){
    qsort (freq, taille, sizeof(FREQLETTRE), compare);
}

FREQLETTRE * freq1lettre(char *message){
    if (message==NULL)
    {
        printf("Le Message ne doit pas etre vide!!!\n");
        exit(2);
    }
    FREQLETTRE *freq = calloc (26, sizeof(FREQLETTRE));

    for (int i = 0; i < strlen(message); i++)
    {
        freq[message[i]-'A'].gramme[0] = message[i];
        freq[message[i]-'A'].gramme[1] ='\0';
        freq[message[i]-'A'].freq++;
    }
    trier(freq, 26);
    for (int i = 0; i < 26; i++)
    {
        freq[i].freq /= strlen(message);
        //printf ("%s-->%f\n", freq[i].gramme, freq[i].freq);
    }
    return freq;
}

/* int nb_elem2; //nobmre de bigrammes du texte
int nb_elem3; //nobmre de trigrammes du texte
 */
FREQLETTRE * freq2lettre(char *message){
    if (message==NULL)
    {
        printf("Le Message ne doit pas etre vide!!!\n");
        exit(2);
    }
    FREQLETTRE *freq = calloc (strlen(message)-1, sizeof(FREQLETTRE));

    for (int i = 0; i < strlen(message)-1; i++) //
    {
        for (int j =0 ; j < 2; j++)
            freq[i].gramme[j] = message[i+j];
        freq[i].gramme[2] ='\0';          //ma am ma ad do ou um mo ou uc ct ta ar ........
    }                                       //i      j 

    int k=0;
    FREQLETTRE * tabRet = NULL; 
    for (int i = 0; i < strlen(message)-1; i++)
    {
        freq[i].freq++;
        for (int j = i+1; j < strlen(message)-1; j++)
        {
            if (freq[i].gramme[0]!='\0' && freq[j].gramme[0]!='\0' && (strcmp(freq[i].gramme, freq[j].gramme)==0)  ){
                freq[i].freq++;
                freq[j].gramme[0] = '\0';
            }
        }
        if (freq[i].gramme[0]!='\0')
        {
            tabRet = realloc (tabRet, sizeof(FREQLETTRE)*(k+1));
            tabRet[k] = freq[i];
            k++;
        } 
    }
    
    trier(tabRet, k);
    for (int i = 0; i <k ; i++)
    {
       // printf ("%s-->%.1f\n", tabRet[i].gramme, tabRet[i].freq);
    }
    free (freq);
    return tabRet;
}

FREQLETTRE * freq3lettre(char *message){ 
    if (message==NULL)
    {
        printf("Le Message ne doit pas etre vide!!!\n");
        exit(2);
    }
    FREQLETTRE *freq = calloc (strlen(message)-2, sizeof(FREQLETTRE));

    for (int i = 0; i < strlen(message)-1; i++) 
    {
        for (int j =0 ; j < 3; j++)
            freq[i].gramme[j] = message[i+j];
        freq[i].gramme[3] ='\0';         
    }                                      

    int k=0;
    FREQLETTRE * tabRet = NULL; 
    for (int i = 0; i < strlen(message)-2; i++)
    {
        freq[i].freq++;
        for (int j = i+1; j < strlen(message)-2; j++)
        {
            if (freq[i].gramme[0]!='\0' && freq[j].gramme[0]!='\0' && (strcmp(freq[i].gramme, freq[j].gramme)==0)  ){
                freq[i].freq++;
                freq[j].gramme[0] = '\0';
            }
        }
        if (freq[i].gramme[0]!='\0')
        {
            tabRet = realloc (tabRet, sizeof(FREQLETTRE)*(k+1));
            tabRet[k] = freq[i];
            k++;
        }
    }
  
    trier(tabRet, k);
    for (int i = 0; i <k ; i++)
    {
        //printf ("%s-->%.1f\n", tabRet[i].gramme, tabRet[i].freq);
    }
    free (freq);
    return tabRet;
}

//cette fonction sert à permuter 2 lettres dans la clé
void permuter2lettres(char *cle, char l1, char l2){
    char tmp;
    int i1;
    for (int i = 0; i < 26; i++)
    {
        if (l1==cle[i])
        {
            tmp = cle[i];
            i1=i;
        }
    }
     for (int i = 0; i < 26; i++)
    {
        if (l2==cle[i])
        {
            cle[i1] = l2;
            cle[i] = tmp;
        }
    }
    
}

DECRYPT  DecryptageSubstitution (char * text){

    char tab_Fr1[] = "EAISTNRULODMPCVQGBFJHZXYKW";
                
    char *cle_canditate = malloc(sizeof(char)*26);
                
    FREQLETTRE * f1 = freq1lettre (text);
    printf("---------frequence des lettres du texte par ordre decroissant-------\n");
    printf("freq= ");
    for (int i = 0; i < 26; i++)
    {
        printf("%c", f1[i].gramme[0]);
    } printf("\n");

    int x = 0;
    while (isalpha(f1[x].gramme[0])) //si le nombre de lettres utilisées est < 26 on complète par des _
         x++;

    for (int i = x; i < 26; i++)
        f1[i].gramme[0] = '_';

    //générer une clé candidate, par rapport aux frequence d'apparition de chaque lettre
    for (int i = 0; i < 26; i++)
    {
        cle_canditate[tab_Fr1[i]-65] = f1[i].gramme[0];        
    }
    cle_canditate[26] = '\0';
   
  
permuter2lettres(cle_canditate, 'X', 'N'); //I<->T
permuter2lettres(cle_canditate, 'F', 'I'); //C<->M  
permuter2lettres(cle_canditate, 'J', 'Z'); //F<->H   
permuter2lettres(cle_canditate, 'U', 'R'); //W<->Z  
permuter2lettres(cle_canditate, 'H', 'B'); //B<->Q    
permuter2lettres(cle_canditate, 'T', 'H'); //J<->B   
permuter2lettres(cle_canditate, 'Z', 'H'); //F<->J   
permuter2lettres(cle_canditate, 'G', 'U'); //K<->Z    

    printf("cle = %s\n", cle_canditate);
    printf("      ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\n");

    char * dec = DechiffrementSubstitution (text, cle_canditate);
    //printf("%s\n", text); 


    //comparaison avec les bigrammes
    FREQLETTRE * f2gram = load2gramme(); //on charge les frequences des bigrammes en français
    FREQLETTRE * f2 = freq2lettre (text); //on génère les frequences des bigrammes du texte  
    for (int i = 0; i < 50; i++)
    {
      //printf("%.1f  %s <--> %s\n",f2[i].freq, f2[i].gramme, f2gram[i].gramme);
    }

    //comparaison avec les trigrammes
    FREQLETTRE * f3gram = load3gramme();  
    FREQLETTRE * f3 = freq3lettre (dec); 
    printf("\n");
    for (int i = 0; i < 50; i++)
    {
       //printf("%.1f %s <--> %s\n",f3[i].freq, f3[i].gramme, f3gram[i].gramme);
    }


   DECRYPT ret;
   
   ret.texte = dec;
   ret.cle = cle_canditate;
   ret.bigrammeRef = f2gram; 
   ret.trigrammeRef = f3gram;
   ret.bigrammeTxt = f2; 
   ret.trigrammeTxt = f3;

   printf ("%s\n cle= %s\n", ret.texte, ret.cle);
   for (int i = 0; i < 30; i++){
       printf("%s <--> %s -   ",ret.bigrammeTxt[i].gramme, ret.bigrammeRef[i].gramme);
       printf("%s <--> %s\n", ret.trigrammeTxt[i].gramme, ret.trigrammeRef[i].gramme);
   }
       
return ret;

}


