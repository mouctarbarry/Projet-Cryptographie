#include "Interface.h"

static GtkItemFactoryEntry MenuItem[] = {
	{ "/_Fichier", NULL, NULL, 0, "<Branch>" },
	{ "/Fichier/_Ouvrir", "<CTRL>O", cb_coffre_fort, 0, "<StockItem>", GTK_STOCK_OPEN },
	{ "/Fichier/_Importer", NULL, NULL, 0, "<StockItem>", GTK_STOCK_FILE },
	{ "/Fichier/_Fichier récent", NULL, cb_fichier_recent, 0, "<StockItem>", GTK_STOCK_NEW },
	{ "/Fichier/Sep1", NULL, NULL, 0, "<Separator>" },
	{ "/Fichier/_Quitter", "<CTRL>Q", OnQuitter, 1, "<StockItem>", GTK_STOCK_QUIT},
    { "/_?", NULL, NULL, 0, "<Branch>" },
    { "/?/_A propos de...", "<CTRL>A", OnAbout, 1, "<StockItem>", GTK_STOCK_HELP}
};
static gint iNbMenuItem = sizeof(MenuItem) / sizeof(MenuItem[0]);
void fenetre_principale(int argc, char **argv){
	GtkWidget *pWindow = NULL;
    GtkWidget *pVBox = NULL;
    GtkWidget *pMenuBar = NULL;
    GtkItemFactory *pItemFactory = NULL;
    GtkAccelGroup *pAccel = NULL;
	gtk_init(&argc, &argv); 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Fenêtre Principale");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 700, 700);
    gtk_window_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
    pAccel = gtk_accel_group_new();
 	pItemFactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", pAccel);
    gtk_item_factory_create_items(pItemFactory, iNbMenuItem, MenuItem, (GtkWidget*)pWindow);
    pMenuBar = gtk_item_factory_get_widget(pItemFactory, "<main>");
    gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
    gtk_window_add_accel_group(GTK_WINDOW(pWindow), pAccel);
	GtkWidget *pTable =NULL;
    pTable=gtk_table_new(3,2,TRUE);
    gtk_container_add(GTK_CONTAINER(pVBox), GTK_WIDGET(pTable));
    GtkWidget *pButton[5];
    pButton[0]= gtk_button_new_with_label("Chiffrement");
    pButton[1]= gtk_button_new_with_label("Déchiffrement");
    pButton[2]= gtk_button_new_with_label("Analyse Fréquence");
    pButton[3]= gtk_button_new_with_label("Décryptage");
    pButton[4]= gtk_button_new_with_label("Coffres-Fort");
 	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(cb_chiffrement),pVBox);
	g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(cb_dechiffrement),pVBox);
	g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(cb_analyse_frequence),pVBox);
	g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(cb_decryptage),pVBox);
	g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(cb_coffre_fort),NULL);
    gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[0],0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[1],1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[2],0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[3],1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[4],0, 2, 2, 3);
      gtk_widget_show_all(pWindow);
    gtk_main();
}
void OnQuitter(gpointer data, guint callback_action,GtkWidget *widget)
{
    GtkWidget *pQuestion;
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
        "quitter le programme?");
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
    case GTK_RESPONSE_YES:
        gtk_main_quit();
        break;
    case GTK_RESPONSE_NONE:
    case GTK_RESPONSE_NO:
        gtk_widget_destroy(pQuestion);
        break;
    }
}
void OnAbout(gpointer data, guint callback_action,GtkWidget *widget)
{
    GtkWidget *pAbout;
    pAbout = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Rendez-vous dans le manuel d'utilisation pour plus d'imformation ou sur YouToube en cliquant sur ce lien:\n...");
    gtk_dialog_run(GTK_DIALOG(pAbout));
    gtk_widget_destroy(pAbout);
}
void cb_fichier_recent(){
struct stat buffer;
	if(stat("tmp.txt",&buffer)!=-1){
		GtkWidget *pBoite = NULL;
		GtkWidget *text_view[2];
		GtkWidget *scrollbar = NULL;
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), "Fichier récent");
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);

		text_view[0] = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		gchar *texte = 0;
		g_file_get_contents("tmp.txt",&texte,NULL,NULL);
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view[0]));
		gtk_text_buffer_set_text(buffer, texte,-1); //texte doit etre remplacer par chiffre
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view[0]),buffer);
		gtk_container_add(GTK_CONTAINER(scrollbar),text_view[0]);
		text_view[1] = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),text_view[1], FALSE, FALSE, 0);
		GtkWidget *pTable =NULL;
		pTable=gtk_table_new(3,2,FALSE);
		gtk_container_add(GTK_CONTAINER(GTK_DIALOG(pBoite)->vbox), GTK_WIDGET(pTable));
	
		/* Creation des boutons */
		GtkWidget *pButton[7];
		pButton[0]= gtk_button_new_with_label("Chiffrement Sub");
		pButton[1]= gtk_button_new_with_label("Chiffrement Vig");
		pButton[2]= gtk_button_new_with_label("Déchiffrement Sub");
		pButton[3]= gtk_button_new_with_label("Déchiffrement Vig");
		pButton[6]= gtk_button_new_with_label("Analyse Fréquence");
		pButton[4]= gtk_button_new_with_label("Décryptage Sub");
		pButton[5]= gtk_button_new_with_label("Décryptage Vig");
		g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(cb_afficher_chif_substitution),text_view);
		g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(cb_afficher_chif_vigenere), text_view);
		g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(cb_afficher_dechif_substitution), text_view);
		g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(cb_afficher_dechif_vigenere), text_view);
		g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(cb_afficher_decrypt_substitution),text_view[0]);
		g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(cb_afficher_decrypt_vigenere),text_view[0]);
		g_signal_connect(G_OBJECT(pButton[6]), "clicked", G_CALLBACK(cb_afficher_frequence),text_view[0]);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[0],0, 1, 0, 1);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[1],1, 2, 0, 1);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[2],0, 1, 1, 2);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[3],1, 2, 1, 2);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[4],0, 1, 2, 3);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[5],1, 2, 2, 3);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[6],0, 3, 3, 4);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		GtkWidget *pBoite = NULL;
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y a pas de fichier récent.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}	
}
void cb_chiffrement(GtkWidget *pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkWidget *text_view[2];
	GtkWidget *scrollbar = NULL;
	pBoite = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(pBoite), "Chiffrement");
	gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
	gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
	scrollbar = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);
	text_view[0] = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrollbar),text_view[0]);
	text_view[1] = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),text_view[1], FALSE, FALSE, 0);
	GtkWidget *substitution = NULL;
	GtkWidget *vigenere = NULL;
	substitution = gtk_button_new_with_label("Substitution");
	vigenere = gtk_button_new_with_label("Vigenère");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),vigenere, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_afficher_chif_substitution),text_view);
	g_signal_connect(G_OBJECT(vigenere), "clicked", G_CALLBACK(cb_afficher_chif_vigenere),text_view);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	gtk_dialog_run(GTK_DIALOG(pBoite));
	gtk_widget_destroy(pBoite);
	
}
void cb_afficher_chif_substitution(GtkButton *button, GtkWidget **pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	const gchar *cle = 0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clair = ni_espace_ni_accent((char*)texte);
	char *clef = ni_espace_ni_accent((char*)cle);
	g_free(texte);
	if(strlen(clair)==0){
		free(clef);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à chiffré.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)!=26){
		free(clef);
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé doit être égal à 26\npour le chiffrement par substitution\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		int tab[26] = {0};
		int cmp  = 0;
		for(int i=0; i<26; i++){
			for(int j=i; j<26; j++){
				if(clef[i] == clef[j])
					tab[clef[i]%26]++;
			}
			if(tab[clef[i]%26]>1)
				cmp++;
		}
		if(cmp){
			free(clef);
			free(clair);
			pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nLa clé ne doit pas avoir de doublon\n");
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
		else{
			char *chiffre = ChiffrementSubstitution(clair,clef);
			chiffre = retour_a_la_ligne(chiffre);
			free(clef);
			free(clair);
			FILE *filename = fopen("tmp.txt","w+");
			if (filename)
			{
				fwrite(chiffre,strlen(chiffre),1,filename);
				fclose(filename);
			}
			pBoite = gtk_dialog_new();
			gtk_window_set_title(GTK_WINDOW(pBoite), "Chiffrement: Substitution");
			gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			GtkWidget *scrollbar = NULL;
			GtkWidget *ptext_view = NULL;
			scrollbar = gtk_scrolled_window_new(NULL,NULL);
			gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
			ptext_view = gtk_text_view_new();
			GtkTextBuffer *buffer = NULL;
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
			gtk_text_buffer_set_text(buffer,g_locale_to_utf8(chiffre,-1,NULL,NULL,NULL),-1); //texte doit etre remplacer par chiffre
			free(chiffre);
			gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
			gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
			gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
			GtkWidget *substitution = NULL;
			substitution = gtk_button_new_with_label("Sauvegarder");
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
			g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view);
			gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
	}
}
void cb_afficher_chif_vigenere(GtkButton *button, GtkWidget **pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	const gchar *cle = 0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clair = ni_espace_ni_accent((char*)texte);
	char *clef = ni_espace_ni_accent((char*)cle);
	g_free(texte);
	if(strlen(clair)==0){
		free(clef);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à chiffré.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)==0){
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de clé de chiffrement.\nVeillez saisir une clé pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)>strlen(clair)){
		free(clef);
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé ne doit pas dépasser celle du message.\nVeillez entrer une clé de taille inferieur.\nMerci.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		char *chiffre = ChiffrementVigenere(clair,clef);
		free(clef);
		free(clair);
		chiffre = retour_a_la_ligne(chiffre);
		FILE *filename = fopen("tmp.txt","w+");
		if (filename){
			fwrite(chiffre,strlen(chiffre),1,filename);
			fclose(filename);
		}
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), "Chiffrement: Vigenère");
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		GtkWidget *scrollbar = NULL;
		GtkWidget *ptext_view = NULL;
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		ptext_view = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
		gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
		free(chiffre);
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
		gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
		GtkWidget *substitution = NULL;
		substitution = gtk_button_new_with_label("Sauvegarder");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
}
char *ni_espace_ni_accent(char *text){
    int taille1 = (int)strlen(text);
    char tmp[taille1];
    int i=0, j=0;
    while (i<taille1) {
        if(text[i]>=65 && text[i]<=90){
            tmp[j] = text[i];
            j++; i++;
        }
        else if(text[i]>=97 && text[i]<=122){
            tmp[j] = text[i]-32;
            j++; i++;
        }
        else if(text[i]==-61 || text[i]==-59){
            if(text[i]==-61){
                i++;
                if (text[i] == -128 || text[i] == -127 || text[i] == -126 || text[i] == -125
                 || text[i] == -124 || text[i] == -123 || text[i] == -122 || text[i] == -96
                 || text[i] == -95  || text[i] == -94  || text[i] == -93  || text[i] == -92
                 || text[i] == -91  || text[i] == -90) {
                    tmp[j] = 'A';
                    j++; i++;
                }
               else if (text[i] == -121 || text[i] == -89) {
                    tmp[j] = 'C';
                    j++; i++;
                }
               else if (text[i] == -120 || text[i] == -119 || text[i] == -118 || text[i] == -117
                     || text[i] == -88  || text[i] == -87  || text[i] == -86  || text[i] == -85) {
                    tmp[j] = 'E';
                    j++; i++;
                }
               else if (text[i] == -116 || text[i] == -115 || text[i] == -114 || text[i] == -113
                     || text[i] == -84  || text[i] == -83  || text[i] == -82  || text[i] == -81) {
                    tmp[j] = 'I';
                    j++; i++;
                }
               else if (text[i] == -112 || text[i] == -80) {
                    tmp[j] = 'D';
                    j++; i++;
                }
               else if (text[i] == -111 || text[i] == -79) {
                    tmp[j] = 'N';
                    j++; i++;
                }
               else if (text[i] == -110 || text[i] == -109 || text[i] == -108 || text[i] == -107
                 || text[i] == -106 || text[i] == -104 || text[i] == -122 || text[i] == -78
                 || text[i] == -77  || text[i] == -76  || text[i] == -75  || text[i] == -74
                 || text[i] == -72) {
                    tmp[j] = 'O';
                    j++; i++;
                }
               else if (text[i] == -103 || text[i] == -102 || text[i] == -101 || text[i] == -100
                     || text[i] == -71  || text[i] == -70  || text[i] == -69  || text[i] == -68) {
                    tmp[j] = 'U';
                    j++; i++;
                }
               else if (text[i] == -99 || text[i] == -67 || text[i] == -65) {
                    tmp[j] = 'Y';
                    j++; i++;
                }
                else
                    i++;
            }
            else{
                if (text[i] == -96 || text[i] == -95) {
                    tmp[j] = 'S';
                    j++; i++;
                 }
                else if (text[i] == -110 || text[i] == -109) {
                     tmp[j] = 'O';
                     j++; i++;
                 }
                else if (text[i] == -72) {
                     tmp[j] = 'Y';
                     j++; i++;
                 }
                else
                    i++;
            }
        }
        else
            i++;
    }
    tmp[j] = '\0';
    return strdup(tmp);
}
char *retour_a_la_ligne(char*text){
	int taille = (int)strlen(text)/80;
	taille= (int)strlen(text) + (2*taille)+1;
	char tmp[taille];
	int j =0;
	for (int i = 1; i < strlen(text)+1; i++){
		if(i%80){
			tmp[j] = text[i-1];
			j++;
		}
		else{
			tmp[j] = text[i-1];
			tmp[j+1] = '\n';
			j+=2;
		}
	}
	tmp[j]='\0';
	free(text);
	return strdup(tmp);
}
void cb_sauvegarder(gpointer data, guint callback_action,GtkWidget *widget)
{
	GtkWidget *pBoite = NULL;
	GtkWidget *text_view = NULL;
	pBoite = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(pBoite), "Enregistrement");
	gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
	gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);

	//text_view[0] = gtk_text_view_new();
	//gtk_container_add(GTK_CONTAINER(scrollbar),text_view[0]);
	text_view = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),text_view, TRUE, TRUE, 0);
	
	GtkWidget *pHbox = NULL;
	pHbox = gtk_hbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(pBoite)->vbox),pHbox);
	//gtk_box_pack_start(GTK_DIALOG(pBoite)->vbox, pHbox, TRUE, TRUE, 0);
	GtkWidget *substitution = NULL;
	GtkWidget *vigenere = NULL;
	substitution = gtk_button_new_with_label("Enregister");
	vigenere = gtk_button_new_with_label("Annuler");
	gtk_box_pack_start(GTK_BOX(GTK_BOX(pHbox)),substitution, FALSE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(GTK_BOX(pHbox)),vigenere, FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_enregistrer),text_view);
	g_signal_connect(G_OBJECT(vigenere), "clicked", G_CALLBACK(cb_annuler_enregistrement),pBoite);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	gtk_dialog_run(GTK_DIALOG(pBoite));
	if (GTK_IS_WINDOW(pBoite)){
		gtk_widget_destroy(pBoite);
	}
}
void cb_enregistrer(GtkButton *button, GtkWidget *pwidget, gpointer data, guint callback_action){
	GtkWidget *pBoite = NULL;
	const gchar *cle = 0;
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget));
	if(strlen((char*)cle)==0){
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nVeillez saisir le nom du fichier pour enregister.\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		struct stat buffer;
		char*tmp = strcat((char*)cle,".txt");
		if(stat(tmp,&buffer)==-1){
			rename("tmp.txt",tmp);
			//gtk_widget_destroy(data);
			GtkWidget *toplevel = gtk_widget_get_toplevel(pwidget);
			if (GTK_IS_WINDOW(toplevel))
			{
				gtk_widget_destroy(toplevel);
			}
		}
		else{
			pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nCe fichier existe.\nVeillez entrer un autre nom.\n");
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
	}
}
void cb_annuler_enregistrement(gpointer data, guint callback_action,GtkWidget *widget){
	GtkWidget *toplevel = gtk_widget_get_toplevel(data);
	if (GTK_IS_WINDOW(toplevel))
	{
		gtk_widget_destroy(toplevel);
	}
}
// dechiffrement
void cb_dechiffrement(GtkWidget *pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkWidget *text_view[2];
	GtkWidget *scrollbar = NULL;
	pBoite = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(pBoite), "Déchiffrement");
	gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
	gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
	scrollbar = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);
	text_view[0] = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrollbar),text_view[0]);
	text_view[1] = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),text_view[1], FALSE, FALSE, 0);
	GtkWidget *substitution = NULL;
	GtkWidget *vigenere = NULL;
	substitution = gtk_button_new_with_label("Substitution");
	vigenere = gtk_button_new_with_label("Vigenère");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),vigenere, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_afficher_dechif_substitution),text_view);
	g_signal_connect(G_OBJECT(vigenere), "clicked", G_CALLBACK(cb_afficher_dechif_vigenere),text_view);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	gtk_dialog_run(GTK_DIALOG(pBoite));
	gtk_widget_destroy(pBoite);	
}
void cb_afficher_dechif_substitution(GtkButton *button, GtkWidget **pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	const gchar *cle = 0;
	
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clef = ni_espace_ni_accent((char*)cle);
	char *clair = ni_espace_ni_accent((char*)texte);
	g_free(texte);
	if(strlen(clair)==0){
		free(clef);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à déchiffré.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)!=26){
		free(clef);
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé doit être égal à 26\npour le déchiffrement par substitution\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		int tab[26] = {0};
		int cmp  = 0;
		for(int i=0; i<26; i++){
			for(int j=i; j<26; j++){
				if(clef[i] == clef[j])
					tab[clef[i]%26]++;
			}
			if(tab[clef[i]%26]>1)
				cmp++;
		}
		if(cmp){
			free(clef);
			free(clair);
			pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nLa clé ne doit pas avoir de doublon\n");
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
		else{
			char *chiffre = DechiffrementSubstitution(clair,clef);
			free(clef);
			free(clair);
			chiffre = retour_a_la_ligne(chiffre);
			FILE *filename = fopen("tmp.txt","w+");
			if (filename)
			{
				fwrite(chiffre,strlen(chiffre),1,filename);
				fclose(filename);
			}
			pBoite = gtk_dialog_new();
			gtk_window_set_title(GTK_WINDOW(pBoite), "Déchiffrement: Substitution");
			gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			GtkWidget *scrollbar = NULL;
			GtkWidget *ptext_view = NULL;
			scrollbar = gtk_scrolled_window_new(NULL,NULL);
			gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
			ptext_view = gtk_text_view_new();
			GtkTextBuffer *buffer = NULL;
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
			gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
			free(chiffre);
			gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
			gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
			gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
			GtkWidget *substitution = NULL;
			substitution = gtk_button_new_with_label("Sauvegarder");
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
			g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view);
			gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
	}
}
void cb_afficher_dechif_vigenere(GtkButton *button, GtkWidget **pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	const gchar *cle = 0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clair = ni_espace_ni_accent((char*)texte);
	char *clef = ni_espace_ni_accent((char*)cle);
	g_free(texte);
	if(strlen(clair)==0){
		free(clef);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à déchiffré.\nVeillez saisir un texte chiffré pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)==0){
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de clé de déchiffrement.\nVeillez saisir la clé pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)>strlen((char*)texte)){
		free(clef);
		free(clair);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé ne doit pas dépasser celle du message.\nVeillez entrer une clé de taille inferieur.\nMerci.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		char *chiffre = DechiffrementVigenere(clair,clef);
		free(clef);
		free(clair);
		chiffre = retour_a_la_ligne(chiffre);
		FILE *filename = fopen("tmp.txt","w+");
		if (filename)
		{
			fwrite(chiffre,strlen(chiffre),1,filename);
			fclose(filename);
		}
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), "Déchiffrement Vigenère");
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		GtkWidget *scrollbar = NULL;
		GtkWidget *ptext_view = NULL;
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		ptext_view = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
		gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
		free(chiffre);
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
		gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
		GtkWidget *substitution = NULL;
		substitution = gtk_button_new_with_label("Sauvegarder");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
}
// analyse frequence
void cb_analyse_frequence(GtkWidget *pwidget, gpointer data){
/*	GtkWidget *pBoite = NULL;
	GtkWidget *text_view;
	GtkWidget *scrollbar = NULL;
	pBoite = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(pBoite), "Analyse des fréqunces");
	gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
	gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
	scrollbar = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);

	text_view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrollbar),text_view);
	GtkWidget *substitution = NULL;
	substitution = gtk_button_new_with_label("Analyser");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_afficher_frequence),text_view);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	gtk_dialog_run(GTK_DIALOG(pBoite));
	gtk_widget_destroy(pBoite);		*/
}
void cb_afficher_frequence(GtkButton *button, GtkWidget **pwidget, gpointer data){
/*	GtkWidget *pBoite = NULL;
	GtkWidget *text_view;
	GtkWidget *scrollbar;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	char *clair = ni_espace_ni_accent((char*)texte);
	g_free(texte);
	if(strlen(clair)==0){
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à analysé.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		char *chiffre = NULL;
		FREQLETTRE *mono = freq1lettre(clair);
		//FREQLETTRE bi = freq2lettre(clair);
		for (int i = 0; i < 2; i++)
		{
			char tmp[20];
			sprintf(tmp,"%s = %d\n",mono[i].gramme,mono[i].freq);
			strcat(chiffre,tmp);
		}
		
		free(clair);
		//chiffre = retour_a_la_ligne(chiffre);
		FILE *filename = fopen("tmp.txt","w+");
		if (filename)
		{
			fwrite(chiffre,strlen(chiffre),1,filename);
			fclose(filename);
		}
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), "Analyse des fréqunces");
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		GtkWidget *ptext_view = NULL;
		ptext_view = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
		gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
		free(chiffre);
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
		gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
		GtkWidget *substitution = NULL;
		substitution = gtk_button_new_with_label("Sauvegarder");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),text_view);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}*/
}
// decryptage
void cb_decryptage(GtkWidget *pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkWidget *text_view;
	GtkWidget *scrollbar = NULL;
	pBoite = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(pBoite), "Décryptage");
	gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
	gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
	scrollbar = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);
	text_view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrollbar),text_view);
	GtkWidget *substitution = NULL;
	GtkWidget *vigenere = NULL;
	substitution = gtk_button_new_with_label("Substitution");
	vigenere = gtk_button_new_with_label("Vigenère");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),vigenere, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_afficher_decrypt_substitution),text_view);
	g_signal_connect(G_OBJECT(vigenere), "clicked", G_CALLBACK(cb_afficher_decrypt_vigenere),text_view);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	gtk_dialog_run(GTK_DIALOG(pBoite));
	gtk_widget_destroy(pBoite);	
}
void cb_afficher_decrypt_substitution(GtkButton *button, GtkWidget *pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	char *clair = ni_espace_ni_accent((char*)texte);
	g_free(texte);
	if(strlen(clair)==0){
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à décrypté.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		DECRYPT dec = DecryptageSubstitution(clair);
		free(clair);
		char *chiffre = dec.texte;
		chiffre = retour_a_la_ligne(chiffre);
		FILE *filename = fopen("tmp.txt","w+");
		if (filename)
		{
			fwrite(chiffre,strlen(chiffre),1,filename);
			fclose(filename);
		}
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), "Décryptage-Substitution");
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		GtkWidget *scrollbar = NULL;
		GtkWidget *ptext_view[2];
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		ptext_view[0] = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view[0]));
		gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
		free(chiffre);
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view[0]),buffer);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view[0]),FALSE);
		gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view[0]);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
		GtkWidget *pHbox = NULL;
		GtkWidget *changer_cle = NULL;
		pHbox = gtk_hbox_new(FALSE,0);
		ptext_view[1] = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(ptext_view[1]),dec.cle);
		changer_cle = gtk_button_new_with_label("Modifier la clé");
		gtk_container_add(GTK_CONTAINER(GTK_DIALOG(pBoite)->vbox),pHbox);
		gtk_box_pack_start(GTK_BOX(pHbox),ptext_view[1],TRUE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(pHbox),changer_cle,FALSE,FALSE,0);
		g_signal_connect(G_OBJECT(changer_cle),"clicked",G_CALLBACK(cb_changer_cle_sub),ptext_view);
		free(dec.cle);
		free(dec.bigrammeRef);
		free(dec.bigrammeTxt);
		free(dec.trigrammeRef);
		free(dec.trigrammeTxt);
		GtkWidget *substitution = NULL;
		substitution = gtk_button_new_with_label("Sauvegarder");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),substitution, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(substitution), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view[0]);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
}
void cb_changer_cle_sub(GtkButton *button, GtkWidget **pwidget, gpointer data){
	GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	const gchar *cle = 0;
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clef = ni_espace_ni_accent((char*)cle);
	if(strlen(clef)==0){
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nVeillez entrer la nouvelle clé pour cette action.\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)!=26 && strlen(clef)!=0){
		free(clef);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé doit être égal à 26 pour cette action\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
		int tab[26] = {0};
		int cmp  = 0;
		for(int i=0; i<26; i++){
			for(int j=i; j<26; j++){
				if(clef[i] == clef[j])
					tab[clef[i]%26]++;
			}
			if(tab[clef[i]%26]>1)
				cmp++;
		}
		if(cmp){
			free(clef);
			pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nLa clé ne doit pas avoir de doublon\n");
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
		}
		else{
			text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
			gtk_text_buffer_get_start_iter(text_buffer,&start);
			gtk_text_buffer_get_end_iter(text_buffer,&end);
			texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
			char * message = DechiffrementSubstitution((char*)texte,clef);
			message = retour_a_la_ligne(message);
			free(clef);
			g_free(texte);
			gtk_text_buffer_set_text(text_buffer, message,-1);
			FILE *filename = fopen("tmp.txt","w+");
			if (filename)
			{
				fwrite(message,strlen(message),1,filename);
				fclose(filename);
			}
		}
	}
}
void cb_afficher_decrypt_vigenere(GtkButton *button, GtkWidget *pwidget, gpointer data){


GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte=0;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	if(strlen((char*)texte)==0){
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nIl n'y pas de texte à chiffré.\nVeillez saisir un texte pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	
	else{
		//les deux lignes suivantes retournent un pointeur null se qui genere une erreur de segmatation
			char *clair = ni_espace_ni_accent((char*)texte);
			char *chiffre = decryptageVigenere(clair);
			chiffre = retour_a_la_ligne(chiffre);
			FILE *filename = fopen("tmp.txt","w+");
			if (filename)
			{
				fwrite(chiffre,strlen(chiffre),1,filename);
				fclose(filename);
			}
			
			pBoite = gtk_dialog_new();
			//pReturn = pBoite;
			gtk_window_set_title(GTK_WINDOW(pBoite), "Décryptage par Vigenère");
			gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
			gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
			GtkWidget *scrollbar = NULL;
			GtkWidget *ptext_view = NULL;
			scrollbar = gtk_scrolled_window_new(NULL,NULL);
			ptext_view = gtk_text_view_new();
			GtkTextBuffer *buffer = NULL;
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(ptext_view));
			gtk_text_buffer_set_text(buffer, chiffre,-1); //texte doit etre remplacer par chiffre
			free(clair);
			free(chiffre);
			gtk_text_view_set_buffer(GTK_TEXT_VIEW(ptext_view),buffer);
			gtk_text_view_set_editable(GTK_TEXT_VIEW(ptext_view),FALSE);
			gtk_container_add(GTK_CONTAINER(scrollbar),ptext_view);
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar, TRUE, TRUE, 0);
			
			GtkWidget *vigenere = NULL;
			//GtkWidget *vigenere = NULL;
			vigenere = gtk_button_new_with_label("Sauvegarder");
			//vigenere = gtk_button_new_with_label("Retour");
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),vigenere, FALSE, FALSE, 0);
			//gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),vigenere, FALSE, FALSE, 0);
			g_signal_connect(G_OBJECT(vigenere), "clicked", G_CALLBACK(cb_sauvegarder),ptext_view);
			//g_signal_connect(G_OBJECT(vigenere), "clicked",(void*)gtk_widget_destroy,pReturn);
			gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
			gtk_dialog_run(GTK_DIALOG(pBoite));
			gtk_widget_destroy(pBoite);
	}
	g_free(texte);
}
void cb_changer_cle_vig(GtkButton *button, GtkWidget **pwidget, gpointer data){
GtkWidget *pBoite = NULL;
	GtkTextBuffer *text_buffer = 0;
	GtkTextIter start;
	GtkTextIter end;
	gchar *texte =0;
	const gchar *cle = 0;
	cle = gtk_entry_get_text(GTK_ENTRY(pwidget[1]));
	char *clef = ni_espace_ni_accent((char*)cle);
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pwidget[0]));
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	gtk_text_buffer_get_end_iter(text_buffer,&end);
	texte = gtk_text_buffer_get_text(text_buffer,&start,&end,TRUE);
	if(strlen(clef)==0){
		g_free(texte);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nVeillez entrer la nouvelle clé pour cette action.\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else if(strlen(clef)>strlen(texte)){
		free(clef);
		g_free(texte);
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"La taille de la clé doit être supperieur à celle du texte pour cette action\n");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
	else{
	const char * message = DechiffrementVigenere((char*)texte,clef);
	free(clef);
	free(texte);
	gtk_text_buffer_set_text(text_buffer, message,-1);
	//gtk_entry_set_text(GTK_ENTRY(pwidget[1]),"la nouvelle clé");
	FILE *filename = fopen("tmp.txt","w+");
	if (filename)
	{
		fwrite(message,strlen(message),1,filename);
		fclose(filename);
	}
	}	
}
//fonction coffre fort
void cb_coffre_fort(){
	GtkWidget *selection = NULL;
	selection = gtk_file_selection_new(g_locale_to_utf8("Sélectionnez un fichier",-1,NULL,NULL,NULL));
	gtk_window_set_default_size(GTK_WINDOW(selection),700,700);
	//gtk_file_selection_set_filename(GTK_FILE_SELECTION(selection),"../Bureau");
	//gtk_file_selection_hide_fileop_buttons(GTK_FILE_SELECTION(selection));
	gtk_widget_show(selection);
	gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(cb_recuperer_chemin), selection );
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
	
}

void cb_recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin;
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
	struct stat buffer;
	if(stat(chemin,&buffer)!=-1){
		GtkWidget *pBoite = NULL;
		GtkWidget *text_view[2];
		GtkWidget *scrollbar = NULL;
		pBoite = gtk_dialog_new();
		gtk_window_set_title(GTK_WINDOW(pBoite), chemin);
		gtk_window_set_default_size(GTK_WINDOW(pBoite), 700, 700);
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		scrollbar = gtk_scrolled_window_new(NULL,NULL);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),scrollbar,TRUE,TRUE,0);

		text_view[0] = gtk_text_view_new();
		GtkTextBuffer *buffer = NULL;
		gchar *texte = 0;
		g_file_get_contents(chemin,&texte,NULL,NULL);
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view[0]));
		gtk_text_buffer_set_text(buffer, texte,-1); //texte doit etre remplacer par chiffre
		gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view[0]),buffer);
		gtk_container_add(GTK_CONTAINER(scrollbar),text_view[0]);
		text_view[1] = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox),text_view[1], FALSE, FALSE, 0);
		GtkWidget *pTable =NULL;
		pTable=gtk_table_new(3,2,FALSE);
		gtk_container_add(GTK_CONTAINER(GTK_DIALOG(pBoite)->vbox), GTK_WIDGET(pTable));
	
		/* Creation des boutons */
		GtkWidget *pButton[7];
		pButton[0]= gtk_button_new_with_label("Chiffrement Sub");
		pButton[1]= gtk_button_new_with_label("Chiffrement Vig");
		pButton[2]= gtk_button_new_with_label("Déchiffrement Sub");
		pButton[3]= gtk_button_new_with_label("Déchiffrement Vig");
		pButton[6]= gtk_button_new_with_label("Analyse Fréquence");
		pButton[4]= gtk_button_new_with_label("Décryptage Sub");
		pButton[5]= gtk_button_new_with_label("Décryptage Vig");
		g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(cb_afficher_chif_substitution),text_view);
		g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(cb_afficher_chif_vigenere), text_view);
		g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(cb_afficher_dechif_substitution), text_view);
		g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(cb_afficher_dechif_vigenere), text_view);
		g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(cb_afficher_decrypt_substitution),text_view[0]);
		g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(cb_afficher_decrypt_vigenere),text_view[0]);
		g_signal_connect(G_OBJECT(pButton[6]), "clicked", G_CALLBACK(cb_afficher_frequence),text_view[0]);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[0],0, 1, 0, 1);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[1],1, 2, 0, 1);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[2],0, 1, 1, 2);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[3],1, 2, 1, 2);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[4],0, 1, 2, 3);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[5],1, 2, 2, 3);
		gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[6],0, 3, 3, 4);
		gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
		gtk_widget_destroy(file_selection);
	}
	else{
		GtkWidget *pBoite = NULL;
		pBoite = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"\nCe fichier n'existe pas.\nVeillez selectionner un fichier pour cette action.");
		gtk_window_position(GTK_WINDOW(pBoite), GTK_WIN_POS_CENTER);
		gtk_dialog_run(GTK_DIALOG(pBoite));
		gtk_widget_destroy(pBoite);
	}
}