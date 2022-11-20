/*
    Author: Ahmet KARAÇALI
    Date  : 14.05.2017

*/

#include <gtk/gtk.h>
#include <stdio.h>

typedef struct
{
    GtkWidget       *main_window;
    GtkWidget       *open;
    GtkWidget       *addfull;
    GtkWidget       *addid;
    GtkWidget       *updatebyid;
    GtkWidget       *deletebyid;
    GtkWidget       *deletebyname;
    GtkWidget       *searchbyid;
    GtkWidget       *searchbyname;
} widgets_t;
widgets_t   widgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *id, *name, *middlename, *lastname, *occupation, *salary, *birthday;
} addfull_t;

addfull_t   addfull;

typedef struct {
    GtkWidget *window;
    GtkWidget *id;
} justid_t;

justid_t   justid;

typedef struct {
    GtkWidget *window;
    GtkWidget *name;
} deletebyname_t;

deletebyname_t   deletebyname;

typedef struct {
    GtkWidget *window;
    GtkWidget *name,*middlename,*lastname;
} allname_t;

allname_t   allname;

FILE *fp;

typedef struct {
    char id[80];
    char name[80];
    char middlename[80];
    char lastname[80];
    char occupation[80];
    char salary[80];
    char birthday[80];
} person_t;


void delete_button_clicked(GtkWidget *widget, gpointer data) { }
void update_button_clicked(GtkWidget *widget, gpointer data) { }
void save_button_clicked(GtkWidget *widget, gpointer data) { }
void find_button_clicked(GtkWidget *widget, gpointer data) { }
void searchbyname_button_clicked(GtkWidget *widget, gpointer data) { }

static void quit_activated(GtkWidget *widget)
{
    g_print("Quit button clicked.");
    gtk_main_quit();
}

static void closeentry_event(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(justid.window));
}

static void closefullentry_event(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(addfull.window));
    gtk_widget_destroy(GTK_WIDGET(justid.window));
    gtk_widget_destroy(GTK_WIDGET(allname.window));
    gtk_widget_destroy(GTK_WIDGET(deletebyname.window));
}

int find_record(char *id)
{
    int         found = 0;
    person_t    p;

    fp = fopen("accounts.dat","rb");

    fseek(fp, 0, SEEK_SET);

    while(!feof(fp)) {
        fread(&p, sizeof(person_t), 1, fp);
        if (!strcmp(p.id, id)) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
}

void addfull_record(char *id, char *name, char *lastname, char *middlename, char *salary, char *birthday, char *occupation)
{
    person_t p;

    fp = fopen("accounts.dat","wb");
    strcpy(p.id, id);
    strcpy(p.name, name);
    strcpy(p.middlename, middlename);
	strcpy(p.lastname, lastname);
	strcpy(p.occupation,occupation);
	strcpy(p.salary, salary);
	strcpy(p.birthday, birthday);

    fseek(fp, 0 , SEEK_END);
    fwrite(&p,sizeof(person_t), 1, fp);
    fflush(fp);
    fclose(fp);
}

void justid_record(char* id)
{
    person_t p;

    fp = fopen("accounts.dat","wb");
    strcpy(p.id, id);

    fseek(fp, 0 , SEEK_END);
    fwrite(&p,sizeof(person_t), 1, fp);
    fflush(fp);
    fclose(fp);
}

void addfull_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar id[80];
    const gchar name[80];
	const gchar middlename[80];
	const gchar lastname[80];
	const gchar salary[80];
	const gchar birthday[80];
    const gchar occupation[80];

    fp = fopen("accounts.dat","wb");

    strcpy(id,gtk_entry_get_text (GTK_ENTRY (addfull.id)));
    strcpy(name,gtk_entry_get_text (GTK_ENTRY (addfull.name)));
    strcpy(occupation,gtk_entry_get_text (GTK_ENTRY (addfull.occupation)));
	strcpy(middlename,gtk_entry_get_text (GTK_ENTRY (addfull.middlename)));
    strcpy(lastname,gtk_entry_get_text (GTK_ENTRY (addfull.lastname)));
    strcpy(salary,gtk_entry_get_text (GTK_ENTRY (addfull.salary)));
	strcpy(birthday,gtk_entry_get_text (GTK_ENTRY (addfull.birthday)));

    if (!find_record(id)) {
            addfull_record(id,name,lastname,middlename,salary,birthday,occupation);
    }
    else {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(addfull.window),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_WARNING,
                    GTK_BUTTONS_OK,
                    "Record already exists");
        gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    fclose(fp);
}

static void addid_button_clicked(GtkWidget *widget, gpointer data)
{
    const gchar id[80];

    strcpy(id,gtk_entry_get_text (GTK_ENTRY (justid.id)));

    if (!find_record(id)) {
            justid_record(id);
    }
    else {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(justid.window),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_WARNING,
                    GTK_BUTTONS_OK,
                    "Record already exists");
        gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

static void addfull_activated(GtkWidget *widget, gpointer data)
{
  //g_print("File -> Open activated.\n");

  GtkWidget *table;
  GtkWidget *id, *first, *middle, *last, *occupation, *salary,*birthday;
  GtkWidget *halign1, *halign2, *halign3;
  GtkWidget *btn1, *btn2, *btn3;

  addfull.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(addfull.window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(addfull.window), "Add By Full");
  gtk_container_set_border_width(GTK_CONTAINER(addfull.window), 10);

  table = gtk_table_new(6, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(addfull.window), table);

  id = gtk_label_new("ID");
  first = gtk_label_new("First Name");
  middle = gtk_label_new("Middle Name");
  last = gtk_label_new("Last Name");
  occupation = gtk_label_new("Occupation");
  salary = gtk_label_new("Salary");
  birthday = gtk_label_new("Birthday");

  gtk_table_attach(GTK_TABLE(table), id, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), first, 0, 1, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), middle, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), last, 0, 1, 3, 4,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), occupation, 0, 1, 4, 5,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), salary, 0, 1, 5, 6,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), birthday, 0, 1, 6, 7,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  addfull.id = gtk_entry_new();
  addfull.name = gtk_entry_new();
  addfull.middlename = gtk_entry_new();
  addfull.lastname = gtk_entry_new();
  addfull.occupation = gtk_entry_new();
  addfull.salary = gtk_entry_new();
  addfull.birthday = gtk_entry_new();


	  gtk_table_attach(GTK_TABLE(table), addfull.id, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	  gtk_table_attach(GTK_TABLE(table), addfull.name, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	  gtk_table_attach(GTK_TABLE(table), addfull.middlename, 1, 2, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), addfull.lastname, 1, 2, 3, 4,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), addfull.occupation, 1, 2, 4, 5,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), addfull.salary, 1, 2, 5, 6,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_table_attach(GTK_TABLE(table), addfull.birthday, 1, 2, 6, 7,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Save");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 7, 8,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(addfull_button_clicked), (gpointer) NULL);

  halign2 = gtk_alignment_new(0, 0, 0, 0);
  btn2 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn2, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign2), btn2);
  gtk_table_attach(GTK_TABLE(table), halign2, 1, 2, 8, 9,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  g_signal_connect(G_OBJECT(btn2), "clicked",
      G_CALLBACK(closefullentry_event), (gpointer) NULL);

  g_signal_connect(addfull.window, "destroy",
      G_CALLBACK(closefullentry_event), (gpointer) NULL);


  gtk_widget_show_all(addfull.window);

}
static void addid_activated(GtkWidget *widget, gpointer data)
{
    g_print("Add -> Add id Activated.\n");

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *id ;

  GtkWidget *halign1, *halign3;
  GtkWidget *btn1,*btn3;

  gtk_widget_set_sensitive(widgets.addid, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Add id Record");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  justid.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  id = gtk_label_new("ID");

  gtk_table_attach(GTK_TABLE(table), id, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  justid.id = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), justid.id, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Save");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(addid_button_clicked), (gpointer) NULL);

  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(justid.window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}

static void searchbyid_activated(GtkWidget *widget, gpointer data)
{
    g_print("Search -> Search by id Activated.\n");

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *id ;
  GtkWidget *entry1;

  GtkWidget *halign1, *halign3;
  GtkWidget *btn1,*btn3;

  /* Disable open */
  gtk_widget_set_sensitive(widgets.searchbyid, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Search by ID");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  justid.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  id = gtk_label_new("ID");

  gtk_table_attach(GTK_TABLE(table), id, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  justid.id = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), justid.id, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Find");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(find_button_clicked), (gpointer) NULL);


  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}

static void searchbyname_activated(GtkWidget *widget, gpointer data)
{
    g_print("Search -> Search by name Activated.\n");

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *first, *middle, *last;

  GtkWidget *halign1, *halign2, *halign3;
  GtkWidget *btn1, *btn2, *btn3;

  /* Disable open */
  gtk_widget_set_sensitive(widgets.searchbyname, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Search by Name");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  allname.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);


  first = gtk_label_new("First Name");
  middle = gtk_label_new("Middle Name");
  last = gtk_label_new("Last Name");

  gtk_table_attach(GTK_TABLE(table), first, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), middle, 0, 1, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), last, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  allname.name = gtk_entry_new();
  allname.middlename = gtk_entry_new();
  allname.lastname = gtk_entry_new();


  gtk_table_attach(GTK_TABLE(table), allname.name, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), allname.middlename, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), allname.lastname, 1, 2, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Find");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 3, 4,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 4, 5,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(searchbyname_button_clicked), (gpointer) NULL);

  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}

static void updatebyid_activated(GtkWidget *widget, gpointer data)
{
    g_print("Update -> Update by id Activated.\n");

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *id ;

  GtkWidget *halign1, *halign3;
  GtkWidget *btn1,*btn3;

  /* Disable open */
  gtk_widget_set_sensitive(widgets.updatebyid, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Update by ID");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  justid.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  id = gtk_label_new("ID");

  gtk_table_attach(GTK_TABLE(table), id, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  justid.id = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), justid.id, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Update");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(update_button_clicked), (gpointer) NULL);

  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}


static void deletebyid_button_clicked(GtkWidget *widget, gpointer data)
{
     const gchar id[80];
     strcpy(id,gtk_entry_get_text (GTK_ENTRY (justid.id)));
     person_t a;
     FILE *newfile,*deletefile;

         deletefile= fopen("accounts.dat","rb");
        if(deletefile==NULL)
        {
                                 GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(addfull.window),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_WARNING,
                    GTK_BUTTONS_OK,
                    "Record not found");
        gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
            fclose(deletefile);
        }
        else
        {
                newfile= fopen("temporary.dat","wb");

                while(!feof(deletefile))
                {
                    fread(&a,sizeof(person_t),1,deletefile);
                    if(strcmp(id,a.id)!=0)
                    {
                        fwrite(&a,sizeof(person_t),1,newfile);
                    }
                }
                fclose(newfile);
                fclose(deletefile);
                remove("accounts.dat");
               rename("temporary.dat","accounts.dat");
        }

                fclose(newfile);
                fclose(deletefile);
}

static void deletebyid_activated(GtkWidget *widget, gpointer data)
{
    g_print("Delete -> Delete by id Activated.\n");

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *id ;

  GtkWidget *halign1, *halign3;
  GtkWidget *btn1,*btn3;

  /* Disable open */
  gtk_widget_set_sensitive(widgets.deletebyid, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Delete by ID");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  justid.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  id = gtk_label_new("ID");

  gtk_table_attach(GTK_TABLE(table), id, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  justid.id = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), justid.id, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Delete");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(deletebyid_button_clicked), (gpointer) NULL);

  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}





static void deletebyname_activated(GtkWidget *widget, gpointer data)
{
    g_print("Delete -> Delete by name Activated.\n");

  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *name;

  GtkWidget *halign1, *halign3;
  GtkWidget *btn1,*btn3;

  /* Disable open */
  gtk_widget_set_sensitive(widgets.deletebyname, FALSE);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Delete by Name");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  deletebyname.window = window;

  table = gtk_table_new(8, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  name = gtk_label_new("Name");

  gtk_table_attach(GTK_TABLE(table), name, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  deletebyname.name = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), deletebyname.name, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign1 = gtk_alignment_new(0, 0, 0, 0);
  btn1 = gtk_button_new_with_label("Delete");
  gtk_widget_set_size_request(btn1, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign1), btn1);
  gtk_table_attach(GTK_TABLE(table), halign1, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  halign3 = gtk_alignment_new(0, 0, 0, 0);
  btn3 = gtk_button_new_with_label("Close");
  gtk_widget_set_size_request(btn3, 70, 30);
  gtk_container_add(GTK_CONTAINER(halign3), btn3);
  gtk_table_attach(GTK_TABLE(table), halign3, 0, 1, 2, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  g_signal_connect(G_OBJECT(btn1), "clicked",
      G_CALLBACK(delete_button_clicked), (gpointer) NULL);

  g_signal_connect(G_OBJECT(btn3), "clicked",
      G_CALLBACK(closeentry_event), (gpointer) NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(closeentry_event), (gpointer) NULL);


  gtk_widget_show_all(window);
}

int main( int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *menubar;
    GtkWidget *filemenu;
    GtkWidget *file;
    GtkWidget *open;
    GtkWidget *quit;

    GtkWidget *addmenubar;
    GtkWidget *addmenu;
    GtkWidget *addfull;
    GtkWidget *addid;

    GtkWidget *searchmenubar;
    GtkWidget *searchmenu;
    GtkWidget *searchbyid;
    GtkWidget *searchbyname;

    GtkWidget *updatemenubar;
    GtkWidget *updatemenu;
    GtkWidget *updatebyid;

    GtkWidget *deletemenubar;
    GtkWidget *deletemenu;
    GtkWidget *deletebyid;
    GtkWidget *deletebyname;

    if ((fp = fopen("accounts.dat", "wb+")) == NULL) {
      printf("File could not be opened.\n");
      return -1;
    }


    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);
    gtk_window_set_title(GTK_WINDOW(window), "Person Handling System");

    widgets.main_window = window;
    menubar = gtk_menu_bar_new();


    addmenubar = gtk_menu_item_new_with_label("Add");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), addmenubar);

    addmenu = gtk_menu_new();
    addid = gtk_menu_item_new_with_label("Add ID");
    addfull = gtk_menu_item_new_with_label("Add Full Record");
    gtk_menu_shell_append(GTK_MENU_SHELL(addmenu), addid);
    gtk_menu_shell_append(GTK_MENU_SHELL(addmenu), addfull);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(addmenubar), addmenu);
    widgets.addid = addid;
    widgets.addfull = addfull;

    searchmenubar = gtk_menu_item_new_with_label("Search");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), searchmenubar);

    searchmenu = gtk_menu_new();
    searchbyid = gtk_menu_item_new_with_label("Search by ID");
    searchbyname = gtk_menu_item_new_with_label("Search by Name");
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), searchbyid);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), searchbyname);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(searchmenubar), searchmenu);

    widgets.searchbyid = searchbyid;
    widgets.searchbyname = searchbyname;

    updatemenubar = gtk_menu_item_new_with_label("Update");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), updatemenubar);

    updatemenu = gtk_menu_new();
    updatebyid = gtk_menu_item_new_with_label("Update by ID");
    gtk_menu_shell_append(GTK_MENU_SHELL(updatemenu), updatebyid);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(updatemenubar), updatemenu);

    widgets.updatebyid = updatebyid;

    deletemenubar = gtk_menu_item_new_with_label("Delete");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), deletemenubar);
    deletemenu = gtk_menu_new();
    deletebyid = gtk_menu_item_new_with_label("Delete by ID");
    deletebyname = gtk_menu_item_new_with_label("Delete by Name");
    gtk_menu_shell_append(GTK_MENU_SHELL(deletemenu), deletebyid);
    gtk_menu_shell_append(GTK_MENU_SHELL(deletemenu), deletebyname);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(deletemenubar), deletemenu);


    widgets.deletebyid = deletebyid;
    widgets.deletebyname = deletebyname;

    file = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

    widgets.open = open;

    g_signal_connect(G_OBJECT(addfull), "activate", G_CALLBACK(addfull_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(addid), "activate", G_CALLBACK(addid_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(searchbyid), "activate", G_CALLBACK(searchbyid_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(searchbyname), "activate", G_CALLBACK(searchbyname_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(deletebyid), "activate", G_CALLBACK(deletebyid_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(deletebyname), "activate", G_CALLBACK(deletebyname_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(updatebyid), "activate", G_CALLBACK(updatebyid_activated), (gpointer) NULL);
    g_signal_connect(G_OBJECT(file), "activate", G_CALLBACK(quit_activated), NULL);


    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 3);
    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    fclose(fp);

    return 0;
}
