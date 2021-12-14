#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "utilisateur.h"



void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *pInfo;
utilisateur u;
int c;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
u.id=atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
u.role = gtk_combo_box_get_active(GTK_COMBO_BOX(mod2))+1;
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(mod3)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(mod4)));
strcpy(u.password,gtk_entry_get_text(GTK_ENTRY(mod5)));
u.nv = gtk_combo_box_get_active(GTK_COMBO_BOX(mod6))+1;
modifier_utilisateur(u,"utilisateur.txt");
}


void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *pInfo;
utilisateur u;
int a=0;
char ch[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
int id = atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
f = fopen("utilisateur.txt","r");
if(f!=NULL){
while(fscanf(f,"%d %d %s %s %s %d %d %d %d %d\n",&(u.id),&(u.role),u.prenom,u.nom,u.password,&(u.sexe),&(u.d.j),&(u.d.m),&(u.d.a),&(u.nv))!=EOF)
	{
		if(u.id==id){
			a=1;
			break;
                 }
	}
fclose(f);
}
if(a==1){
gtk_combo_box_set_active(GTK_COMBO_BOX(mod2),u.role-1);
gtk_entry_set_text(GTK_ENTRY(mod3),u.prenom);
gtk_entry_set_text(GTK_ENTRY(mod4),u.nom);
gtk_entry_set_text(GTK_ENTRY(mod5),u.password);
gtk_combo_box_set_active(GTK_COMBO_BOX(mod6),u.nv-1);
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Utilisateur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_treeview_utilisateur_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gint id;
	utilisateur u;
	GtkWidget *pInfo;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path))
{
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	u.id=id;
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer cet utilisateur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer_utilisateur(u,"utilisateur.txt");
	afficher_utilisateur(treeview,"utilisateur.txt");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}


void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af_utilisateur;


af_utilisateur=lookup_widget(objet,"af_utilisateur");

gtk_widget_destroy(af_utilisateur);
af_utilisateur=lookup_widget(objet,"af_utilisateur");
af_utilisateur=create_af_utilisateur();

gtk_widget_show(af_utilisateur);

treeview=lookup_widget(af_utilisateur,"treeview_utilisateur");

afficher_utilisateur(treeview,"utilisateur.txt");
}


void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *aj5, *aj6, *h, *f;
GtkCalendar *ajc;
utilisateur u;
guint day, month, year;
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
ajc=lookup_widget(objet,"ajc");
h=lookup_widget(objet,"h");
f=lookup_widget(objet,"f");
aj4=lookup_widget(objet,"aj4");
aj5=lookup_widget(objet,"aj5");
aj6=lookup_widget(objet,"aj6");
u.id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aj1));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(aj3)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(aj4)));
strcpy(u.password,gtk_entry_get_text(GTK_ENTRY(aj5)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(h))?0:1;
gtk_calendar_get_date(GTK_CALENDAR(ajc), &day, &month, &year);
u.d.j=year;
u.d.m=month+1;
u.d.a=day;
u.role = gtk_combo_box_get_active(GTK_COMBO_BOX(aj2))+1;
u.nv = u.role==6?gtk_combo_box_get_active(GTK_COMBO_BOX(aj6))+1:0;
ajouter_utilisateur(u,"utilisateur.txt");
}


void
on_chercher_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *r1, *r2, *r3, *r4, *r5, *r6, *r7, *r8, *pInfo;
char date_inscription[20], sexe[20], role[30], niveau[20];
r1=lookup_widget(objet,"r1");
r2=lookup_widget(objet,"r2");
r3=lookup_widget(objet,"r3");
r4=lookup_widget(objet,"r4");
r5=lookup_widget(objet,"r5");
r6=lookup_widget(objet,"r6");
r7=lookup_widget(objet,"r7");
r8=lookup_widget(objet,"r8");
int id = atoi(gtk_entry_get_text(GTK_ENTRY(r1)));
utilisateur u = chercher_utilisateur(id,"utilisateur.txt");
if (u.id==-1){
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"ID introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
else{
sprintf(role,u.role==1?"Admin":u.role==2?"Technicien":u.role==3?"Responsable réclamations":u.role==4?"Agent de foyer":u.role==5?"Agent de restaurant":"Etudiant");
gtk_label_set_text(GTK_LABEL(r2),role);
gtk_label_set_text(GTK_LABEL(r3),u.prenom);
gtk_label_set_text(GTK_LABEL(r4),u.nom);
gtk_label_set_text(GTK_LABEL(r5),u.password);
sprintf(sexe,u.sexe==0?"Homme":"Femme");
gtk_label_set_text(GTK_LABEL(r6),sexe);
sprintf(date_inscription,"%d/%d/%d",u.d.j,u.d.m,u.d.a);
gtk_label_set_text(GTK_LABEL(r7),date_inscription);
sprintf(niveau,u.role==6?(u.nv==1?"1ère année":"%déme année"):"Employé",u.nv);
gtk_label_set_text(GTK_LABEL(r8),niveau);
}
}




void
on_ajouter_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj_utilisateur, *af_utilisateur;
af_utilisateur=lookup_widget(objet,"af_utilisateur");
aj_utilisateur=lookup_widget(objet,"aj_utilisateur");
aj_utilisateur=create_aj_utilisateur();
gtk_widget_show(aj_utilisateur);
}


void
on_modifier_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod_utilisateur, *af_utilisateur;
af_utilisateur=lookup_widget(objet,"af_utilisateur");
mod_utilisateur=lookup_widget(objet,"mod_utilisateur");
mod_utilisateur=create_mod_utilisateur();
gtk_widget_show(mod_utilisateur);
}


void
on_rechercher_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *recherche, *af_utilisateur;
af_utilisateur=lookup_widget(objet,"af_utilisateur");
recherche=lookup_widget(objet,"recherche");
recherche=create_recherche();
gtk_widget_show(recherche);
}


void
on_nb_etudiant_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *pInfo, *n;
n=lookup_widget(objet,"nb_etudiant");
char str[1000], ch[1000]="";
strcpy(ch,nombre_etudiant("utilisateur.txt"));
sprintf(str,"%s",ch);
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,str);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_button2_ree_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *mod_utilisateur ;
GtkWidget *af_utilisateur;
af_utilisateur=create_af_utilisateur();
gtk_widget_show (af_utilisateur);
mod_utilisateur=lookup_widget(button,"mod_utilisateur");
gtk_widget_hide(mod_utilisateur);
}


void
on_button_re_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login ;
GtkWidget *af_utilisateur;
Login=create_Login();
gtk_widget_show (Login);
af_utilisateur=lookup_widget(button,"af_utilisateur");
gtk_widget_hide(af_utilisateur);
}


void
on_button4_re_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *aj_utilisateur ;
GtkWidget *af_utilisateur;
af_utilisateur=create_af_utilisateur();
gtk_widget_show (af_utilisateur);
aj_utilisateur=lookup_widget(button,"aj_utilisateur");
gtk_widget_hide(aj_utilisateur);
}


void
on_button3_re_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *recherche ;
GtkWidget *af_utilisateur;
af_utilisateur=create_af_utilisateur();
gtk_widget_show (af_utilisateur);
recherche=lookup_widget(button,"recherche");
gtk_widget_hide(recherche);
}


void
on_cnx_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *inputid;
GtkWidget *inputpasswd;

GtkWidget *welcome;
GtkWidget *output;
GtkWidget *af_utilisateur;
GtkWidget *Login;
utilisateur u;
char ID[50];
char PWD[50];
char id[50];
char pwd[50];
char x[50];
char role[50];
date d;
Login=lookup_widget(button,"Login");
inputid=lookup_widget(button,"entryident");
inputpasswd=lookup_widget(button,"entrymotp");
strcpy(ID,gtk_entry_get_text(GTK_ENTRY(inputid)));
strcpy(PWD,gtk_entry_get_text(GTK_ENTRY(inputpasswd)));

FILE *f;
f=fopen("utilisateur.txt","r");
if(f !=NULL){
while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s\n",id,role,x,x,pwd,x,x,x,x,x)!=EOF)
{
	if(strcmp(ID,id)==0)
		if (strcmp(pwd,PWD)==0)
			if (strcmp(role,"1")==0)
			{
			gtk_widget_hide(Login);
			af_utilisateur=create_af_utilisateur();
			gtk_widget_show(af_utilisateur);			
			}	
			else 	
			{
			gtk_widget_hide(Login);
			welcome=create_welcome();
			gtk_widget_show(welcome);

			}	
}fclose(f);
}

/*if (x == 0)
{output=lookup_widget(button,"label5");
gtk_label_set_text(GTK_LABEL(output),"error");
}*/

}

