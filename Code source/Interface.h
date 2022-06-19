#ifndef Interface_h
#define Interface_h

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Decryptage.h"
#include "Dechiffrement.h"
#include "Chiffrement.h"


void fenetre_principale(int argc, char **argv);
void OnQuitter(gpointer data, guint callback_action,GtkWidget *widget);
void OnAbout(gpointer data, guint callback_action,GtkWidget *widget);
void cb_chiffrement(GtkWidget *pwidget, gpointer data);
void cb_afficher_chif_substitution(GtkButton *button, GtkWidget **pwidget, gpointer data);
void cb_afficher_chif_vigenere(GtkButton *button, GtkWidget **pwidget, gpointer data);
char *ni_espace_ni_accent(char*);
void cb_sauvegarder(gpointer data, guint callback_action,GtkWidget *widget);
void cb_enregistrer(GtkButton *button, GtkWidget *pwidget, gpointer data, guint callback_action);
void cb_annuler_enregistrement(gpointer data, guint callback_action,GtkWidget *widget);
// fonction pour dechiffrement
void cb_dechiffrement(GtkWidget *pwidget, gpointer data);
void cb_afficher_dechif_substitution(GtkButton *button, GtkWidget **pwidget, gpointer data);
void cb_afficher_dechif_vigenere(GtkButton *button, GtkWidget **pwidget, gpointer data);
// fonction pour l'analyse des frenquences
void cb_analyse_frequence(GtkWidget *pwidget, gpointer data);
void cb_afficher_frequence(GtkButton *button, GtkWidget **pwidget, gpointer data);
// fonction pour decryptage
void cb_decryptage(GtkWidget *pwidget, gpointer data);
void cb_afficher_decrypt_substitution(GtkButton *button, GtkWidget *pwidget, gpointer data);
void cb_afficher_decrypt_vigenere(GtkButton *button, GtkWidget *pwidget, gpointer data);
void cb_changer_cle_sub(GtkButton *button, GtkWidget **pwidget, gpointer data);
void cb_changer_cle_vig(GtkButton *button, GtkWidget **pwidget, gpointer data);
// fonction pour coffre fort
char *retour_a_la_ligne(char*text);
void cb_fichier_recent();
void cb_coffre_fort();
void cb_recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
#endif /*Interface_h*/
