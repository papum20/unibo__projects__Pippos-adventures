#include "inventory.hpp"


Inventory::Inventory(Player * p, int * input):Pixel_art(){
p_input=input;
is_open=false;
options_is_active=false;
zaino_is_active=false;
w_use_is_active=false;
w_equip_is_active=false;
int yMax, xMax;
getmaxyx(stdscr, yMax, xMax);
this->w_inventory = newwin(8, 113, 1, 45);
this->w_zaino = newwin(38, 45, 11, 40);
this->w_item = newwin(39, 70, 12, 95);
this->w_weapon = newwin(32, 31, 14, 96);
this->w_equip = newwin(35, 100, 12, 50);
this->w_options = newwin(30, 75, yMax/2 - 12, xMax/2-35);
this->w_use=newwin(4, 13, w_use_high, w_use_width);

highlight=0;
u_highlight=1;
int Artifact_array_index=0;
int I_D_array_index=0;
int Weapons_array_index=0;
curr_inventory_space = 0;
}

void Inventory::insert(pItem item){
    if(curr_inventory_space<= n_max_inventory_objects){
        objects[curr_inventory_space]=item;
        curr_inventory_space++;
    }
}


bool Inventory::is_active(){
    return(is_open);
}

int Inventory::random_item(){
int r;
 for(int i=0;i<100;i++){
  r = (rand() % curr_inventory_space) + 1;
  if((check_class_name(r)==1) || (check_class_name(r)==2)){
    return r;
   }
 }
return (-1);
}

void Inventory::open_options(){
    options_is_active=true;
    keypad(w_inventory,false);
    box(w_options, 0, 0);
    mvwprintw(w_options, 2, 2, "m = apri menu");
    mvwprintw(w_options, 4, 2, "n = apri inventario");
    mvwprintw(w_options, 6, 2, "i tasti w a s d servono a muoversi nelle 4 direzioni");   
}

void Inventory::update_options(){
int choice;
        choice=(*p_input);
        if(choice==esc){
            keypad(w_inventory,true);
            werase(w_options);         
        }
}

int Inventory::check_class_name(int array_index){
    if(objects[array_index]->isWeapon())
        return 1;
    else if(objects[array_index]->isItemDifensivo())
        return 2;
    else if(objects[array_index]->isArtifact())
        return 3;
    else return 0;
}

void Inventory::wattroff_inventory(WINDOW * win){
    wattroff(win, COLOR_PAIR(3));
    wattroff(win, COLOR_PAIR(4));
    wattroff(win, COLOR_PAIR(5));
    wattroff(win, COLOR_PAIR(6));
    wattroff(win, COLOR_PAIR(7));
    wattroff(win, COLOR_PAIR(8));
    wattroff(win, COLOR_PAIR(9));
    wattroff(win, COLOR_PAIR(10));
    wattroff(win, COLOR_PAIR(11));
    wattroff(win, COLOR_PAIR(12));
    wattroff(win, COLOR_PAIR(13));
    wattroff(win, COLOR_PAIR(14));
}

void Inventory::init_inventory_color(){
        init_color(COLOR_CYAN, 532, 250, 82);//colore arancione
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);//comune
        init_pair(4, COLOR_YELLOW, COLOR_BLUE); //rarità raro
        init_pair(5, COLOR_YELLOW, COLOR_MAGENTA);//rarità epico
        init_pair(6, COLOR_YELLOW, COLOR_CYAN);//rarità leggendario

        init_pair(7, COLOR_WHITE, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLUE); //rarità raro
        init_pair(9, COLOR_WHITE, COLOR_MAGENTA);//rarità epico
        init_pair(10, COLOR_WHITE, COLOR_CYAN);//rarità leggendario

        init_pair(11, COLOR_WHITE, COLOR_BLACK);
        init_pair(12, COLOR_BLUE, COLOR_BLACK); //rarità raro
        init_pair(13, COLOR_MAGENTA, COLOR_BLACK);//rarità epico
        init_pair(14, COLOR_CYAN, COLOR_BLACK);//rarità leggendario

}




void Inventory::fix_array(int array_index, Player * p){
    /*
    if(array_index==curr_inventory_space){
         curr_inventory_space--;}
    else{
        curr_inventory_space--;
         strcpy(objects[array_index]->name, " ");
        strcpy(objects[array_index]->rarity, " ");
            strcpy(objects[array_index]->description, " ");
            strcpy(objects[array_index]->type, " ");
        if((check_class_name(array_index)==1))
        {
           static_cast< Weapon *>(objects[array_index])->danno_fisico=0;
           static_cast< Weapon *>(objects[array_index])->danno_magico=0;
           static_cast< Weapon *>(objects[array_index])->is_equipped=false;

           
        }
         if((check_class_name(array_index)==2))
        {
           static_cast< item_difensivo *>(objects[array_index])->difesa_fisica=0;
           static_cast< item_difensivo *>(objects[array_index])->difesa_magica=0;
           static_cast< item_difensivo *>(objects[array_index])->is_equipped=false;
           
        }
    }  */
    }

  

void Inventory::int_to_string(int number, char string[]){
	if(number==0){
		string[0]=(char)48;
		string[1]='\0';
		return;
	}
	int i = 0;
	int current = number;
	int q;
	while(current > 0){
		q = current%10;
		current = current/10;
		string[i]=(char)(q + 48);
		i++;
	}
	string[i]='\0';
	reverse_string(string);
}

void Inventory::reverse_string(char string[]){
int lenght = strlen(string);
for (int i = 0; i < lenght / 2; i++){
	char tmp=string[i];
	string[i] = string[lenght -1 -i];
	string[lenght -1 -i]= tmp; 
}}

int Inventory::count_char(int start_char,char string[]){//data una stringa conta le lettere della parola seguente al punto di inizio, l'ho usata in w_item e print_nome
int count = 0;
while((string[start_char]!=' ')){
if((string[start_char]=='\0'))
    return count;
count++;
start_char++;
}
return count;
}

void Inventory::print_weapon(int high, int lenght, const char graphic_weapon[][w_graphic_lenght]){
for(int i=0; i<high; i++){
    for(int k=0; k<lenght; k++){
        mvwaddch(w_weapon, i + 2, k + 2, graphic_weapon[i][k]);
    }
}
wrefresh(w_weapon);
}

void Inventory::item_menu(int array_index){/*
box(w_item, 0, 0);
int yMax, xMax;
getmaxyx(w_item, yMax, xMax);

if(strcmp(objects[array_index]->rarity, rarity[0]) == 0)
        wattron(w_item, COLOR_PAIR(11));
    else if(strcmp(objects[array_index]->rarity, rarity[1]) == 0)
            wattron(w_item, COLOR_PAIR(12));
    else if(strcmp(objects[array_index]->rarity, rarity[2]) == 0)
            wattron(w_item, COLOR_PAIR(13));
    else if(strcmp(objects[array_index]->rarity, rarity[3]) == 0)
            wattron(w_item, COLOR_PAIR(14));

mvwprintw(w_item, 2, xMax/2 -3,objects[array_index]->name);

wattroff_inventory(w_item);

int high=yMax - 10;//

if(curr_inventory_space>0){

aux_equip_item_menu(w_item, 6, start_written, array_index, 1);

mvwprintw(w_item, high, start_written,"descrizione:");

int start_description = start_written + 13;
int finish_description = start_written + 12 + 23;

int k=0;
int i=0;

while(objects[array_index]->description[i]!='\0'){
    if(start_description + k + count_char(i, objects[array_index]->description) > finish_description){
        k=0;
        high = high + 1;
    }
mvwaddch(w_item, high, start_description+k, objects[array_index]->description[i]);
i++;
k++;
}}
wrefresh(w_item);

for(int i = 0; i<n_graphic_types_items; i++){
    if(strcmp(objects[array_index]->type, type[i]) == 0)
        print_weapon(w_graphic_high, w_graphic_lenght, graphic_items[i]);
}
wrefresh(w_weapon);*/
}

void Inventory::useOrdiscardItem(int y_position, int x_position, int array_index){//c'è il menu solo se premi invio
w_use_is_active=true;

    w_use_high = y_position + 15;
    w_use_width = x_position + 20;

box(w_use, 0, 0);
keypad(w_zaino, false);
wattron(w_use, COLOR_PAIR(3));

if(((check_class_name(array_index))==3)){
    mvwprintw(w_use, 1, 4, "usa");
    
}
else
    mvwprintw(w_use, 1, 2, "equipaggia");
wattroff(w_use, COLOR_PAIR(3));
if((check_class_name(array_index))==3 || (((check_class_name(array_index))==2)&&(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped))) || (((check_class_name(array_index))==1)&&(!(static_cast<Weapon *>(objects[array_index])->is_equipped))))
   mvwprintw(w_use, 2, 3, "scarta");

keypad(w_use, true);
wrefresh(w_use); 


        
    

}

void Inventory::update_w_use(int array_index, Player * p){/*
bool is_item = false;
if((check_class_name(array_index))==3)
 is_item=true;

int choice;
choice = (*p_input);
if(choice==esc){
    w_use_is_active=false;
    keypad(w_use, false); 
    keypad(w_zaino, true); 
    werase(w_use);
    wrefresh(w_zaino);
    wrefresh(w_use);
    return;
    }
if(choice==scroll_up){
        u_highlight--;
        if(u_highlight<=0){
           if((check_class_name(array_index))==3 || (((check_class_name(array_index))==2)&&(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped))) || (((check_class_name(array_index))==1)&&(!(static_cast<Weapon *>(objects[array_index])->is_equipped))))
              u_highlight=2;
            else
               u_highlight=1;
        }
}
if(choice==scroll_down){
        u_highlight++;
     if((check_class_name(array_index))==3 || (((check_class_name(array_index))==2)&&(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped))) || (((check_class_name(array_index))==1)&&(!(static_cast<Weapon *>(objects[array_index])->is_equipped)))){
        if(u_highlight>=3){
            u_highlight=1;
        }
     } 
     else{
      
      if(u_highlight>=2){
            u_highlight=1;
        }
    }   
}
if(u_highlight==1){
    wattron(w_use, COLOR_PAIR(3)); 
    if(((check_class_name(array_index))==3))
        mvwprintw(w_use, 1, 4, "usa");
    else
        mvwprintw(w_use, 1, 2, "equipaggia");   
    wattroff(w_use, COLOR_PAIR(3));
    wattron(w_use, COLOR_PAIR(7)); 
    mvwprintw(w_use, 2, 3, "scarta");
    wattroff(w_use, COLOR_PAIR(7));

}
if(u_highlight==2){
    wattron(w_use, COLOR_PAIR(3)); 
    mvwprintw(w_use, 2, 3, "scarta");
    wattroff(w_use, COLOR_PAIR(3));
    wattron(w_use, COLOR_PAIR(7)); 
    if(((check_class_name(array_index))==3))
        mvwprintw(w_use, 1, 4, "usa");
    else
        mvwprintw(w_use, 1, 2, "equipaggia");
    wattroff(w_use, COLOR_PAIR(7));
}
if(choice==invio){
    if(is_item){
        pArtifact tmp =  static_cast< Artifact *>(objects[array_index]);
        if(tmp->getId() == ID_HEALTH_POTION) tmp->use_item(objects[array_index], p->curHealth);
        else if(tmp->getId() == ID_KEY) tmp->use_item(objects[array_index], p->n_keys);
        else if(tmp->getId() == ID_LIFE_ELIXIR) tmp->use_item(objects[array_index], p->n_hearts);
        else if(tmp->getId() == ID_RUNE) {
          int item_index=random_item();
          if(item_index!=(-1))
            tmp->use_item(objects[item_index], p->n_hearts);}
        fix_array(array_index, p);
        clean_window(w_zaino, 24, 44);
        keypad(w_use, false); 
        keypad(w_zaino, true);
        w_use_is_active=false; 
        werase(w_use);
        wrefresh(w_zaino);
        wrefresh(w_use);
        if(array_index<=0)
            array_index = 1;
        z_highlight=array_index-1;
        zaino_menu(array_index, p);
        return;  
    }
    else if(u_highlight==1){
        for(int i = 0; i<curr_inventory_space; i++){
            
            if(check_class_name(array_index)==1){
                if(((array_index!=i) && (static_cast< Weapon *>(objects[i])->is_equipped)) || ((strcmp(objects[array_index]->type, objects[i]->type) == 0) && (array_index!=i) && (static_cast< Weapon *>(objects[i])->is_equipped))){
                    p->change_weapon(static_cast< pWeapon> (objects[array_index]));
            }
            }
            if(check_class_name(array_index)==2){
                 if(((array_index!=i) && (static_cast< item_difensivo *>(objects[i])->is_equipped)) && (strcmp(objects[array_index]->type, objects[i]->type) == 0) /*&& (array_index!=i) && (static_cast< item_difensivo *>(objects[i])->is_equipped)*///){
  /*              if(strcmp(objects[i]->type, type[2]) == 0){
                    p->change_armor (static_cast< pArmor>(objects[array_index]));
                }
                if(strcmp(objects[i]->type, type[3]) == 0){
                   p->change_shield (static_cast< pShield>(objects[array_index])); 
                }
                if(strcmp(objects[i]->type, type[4]) == 0){
                    p->change_helm (static_cast< pHelm>(objects[array_index])); 
                }
                if(strcmp(objects[i]->type, type[8]) == 0){
                    p->change_necklace (static_cast< pNecklace>(objects[array_index]));
                }
                if(strcmp(objects[i]->type, type[7]) == 0){
                    p->change_boots (static_cast< pBoots>(objects[array_index]));
                }}
            }
                  
        }
        }
        keypad(w_use, false); 
        keypad(w_zaino, true); 
        w_use_is_active=false;
        werase(w_use);
        wrefresh(w_zaino);
        wrefresh(w_use);
        if(array_index<=0)
            array_index = 1; 
        z_highlight=array_index-1;   
        zaino_menu(array_index + 1, p);
        return;  
    }
    else if(u_highlight ==2){
        
        fix_array(array_index, p);
        clean_window(w_zaino, 24, 44);
        keypad(w_use, false); 
        keypad(w_zaino, true); 
        w_use_is_active=false;
        werase(w_use);
        wrefresh(w_zaino);
        wrefresh(w_use);
        if(array_index<=0)
            array_index = 1;
        z_highlight=0;
        zaino_menu(array_index, p);
        return;  
    }*/
}

void Inventory::strcmp_rarity(WINDOW * win, int array_index, int number){
    if(strcmp(objects[array_index]->rarity, rarity[0]) == 0)
        wattron(win, COLOR_PAIR(number));
    else if(strcmp(objects[array_index]->rarity, rarity[1]) == 0)
        wattron(win, COLOR_PAIR(number + 1));
    else if(strcmp(objects[array_index]->rarity, rarity[2]) == 0)
        wattron(win, COLOR_PAIR(number + 2));
    else if(strcmp(objects[array_index]->rarity, rarity[3]) == 0)
        wattron(win, COLOR_PAIR(number + 3));
}

void Inventory::print_item_name(WINDOW * win, int y, int x, int array_index){
int n;
/*    mvwprintw(win, y, x, objects[array_index]->name);
    wattron(win, COLOR_PAIR(7));
int high = 2;
for(int i=0; i<curr_inventory_space; i++){
    n = count_char(0, objects[i]->name) + 1;
    if((check_class_name(i))==1){
    if(static_cast< Weapon *>(objects[i])->is_equipped)
        mvwaddch(win, high, x + n, 'E');
    else
        mvwaddch(win, high, x + n, ' ');
    high = high + 2;}
 else if((check_class_name(i))==2){
    if(static_cast< item_difensivo *>(objects[i])->is_equipped)
        mvwaddch(win, high, x + n, 'E');
    else
        mvwaddch(win, high, x + n, ' ');
    high = high + 2;}

    
    else{
        mvwaddch(win, high, x + n, ' ');
        high = high + 2;
    }
}
    


wattroff(win, COLOR_PAIR(7));
wrefresh(win);*/
}
void Inventory::zaino_menu(int array_index, Player * p){
zaino_is_active=true;
if(w_use_is_active==true){
  update_w_use(array_index, p);
  return;
}
    box(w_zaino, 0, 0);
    keypad(w_inventory, true);
    clean_window(w_item, 34, 69); //queste due righe servono per quando si richiama zaino_menu dopo aver eliminato un oggetto dall'inventario
    wrefresh(w_item);

    init_inventory_color();

    int yMax, xMax;
    getmaxyx(w_zaino, yMax, xMax);
    
    keypad(w_inventory, false);   
    keypad(w_zaino, true);

    int high = 0;  //serve per implementare che le scritte dei nomi non sono tutte attaccate una sotto l'altra ma c'è una casella di spazio in altezza
        for(int i=0; i<curr_inventory_space; i++){
            strcmp_rarity(w_zaino, i, 7);
            high = high + 2;
            print_item_name(w_zaino, high, xMax/2 -15, i);
            wattroff_inventory(w_zaino);
        }
        high = array_index * 2;
int choice;


strcmp_rarity(w_zaino, z_highlight, 3);
print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
wattroff_inventory(w_zaino);

item_menu(z_highlight);


choice=(*p_input);
    if(choice==esc){
    zaino_is_active=false;
    keypad(w_zaino, false); 
    keypad(w_inventory, true); 
    werase(w_zaino);
    werase(w_item);
    wrefresh(w_zaino);
    wrefresh(w_item);
    wrefresh(w_weapon);
    return;
    }
    if(choice==invio){
        useOrdiscardItem(high-1, xMax - 8, z_highlight);
    }
    if(choice==scroll_up){
        werase(w_item);
        wrefresh(w_item);
        wrefresh(w_weapon);
        
        int tmp = high;
        z_highlight--;
        high = high - 2;
        if(z_highlight<0){
            z_highlight=0;
            high=tmp;
        }
        item_menu(z_highlight);
        strcmp_rarity(w_zaino, z_highlight, 3);
    print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
    wattroff_inventory(w_zaino);

    if(z_highlight + 1 < curr_inventory_space){
        strcmp_rarity(w_zaino, z_highlight + 1, 7);
            print_item_name(w_zaino, high + 2, xMax/2 -15, z_highlight + 1);
            wattroff_inventory(w_zaino);
        }}
    if(choice==scroll_down){
        werase(w_item);
        wrefresh(w_item);
        wrefresh(w_weapon);
        int tmp = high;
        z_highlight++;
        high = high + 2;
         
        if(z_highlight>=curr_inventory_space){
            z_highlight=curr_inventory_space-1;
            high = tmp;
        }
        if(curr_inventory_space==0){
            z_highlight=0;
            zaino_menu(1, p);
        }
        item_menu(z_highlight);
 
        strcmp_rarity(w_zaino, z_highlight, 3);
    
        print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
    wattroff_inventory(w_zaino);

    if(z_highlight - 1 >= 0){
        strcmp_rarity(w_zaino, z_highlight - 1, 7);

        print_item_name(w_zaino, high - 2, xMax/2 -15, z_highlight - 1);
        wattroff_inventory(w_zaino);
        }} 
   
}

void Inventory::aux_equip_item_menu(WINDOW * win, int y, int x, int array_index, int high){
    int counter = 0;
     counter = counter + 3 * high;
        
  //      mvwprintw(win, y, x, objects[array_index]->type);
        mvwprintw(win, y, x + 10, objects[array_index]->name);
        mvwprintw(win, y + 1 + counter, x, "rarita'");
        mvwprintw(win, y + 1 + counter, x + 10, objects[array_index]->rarity);
        counter = counter + 3 * high;
    int i = 2;
    if((check_class_name(array_index))==1){
       char s_attack[max_n_digit_stats];
       int_to_string(static_cast< Weapon *>(objects[array_index])->danno_fisico, s_attack);
            mvwprintw(win, y + i + counter, x, "attacco fisico");
            mvwprintw(win, y + i + counter, x + 15, s_attack);
            i++;
            counter = counter + 3 * high;

            char s_attack_magic[max_n_digit_stats];
       int_to_string(static_cast< Weapon *>(objects[array_index])->danno_fisico, s_attack_magic);
            mvwprintw(win, y + i + counter, x, "attacco magico");
            mvwprintw(win, y + i + counter, x + 15, s_attack_magic);
            i++;
            counter = counter + 3 * high;
    }
    if((check_class_name(array_index))==2){
         char defense[max_n_digit_stats];
       int_to_string(static_cast< item_difensivo *>(objects[array_index])->difesa_fisica, defense);
            mvwprintw(win, y + i + counter, x, "difesa fisica");
            mvwprintw(win, y + i + counter, x + 15, defense);
            i++;
            counter = counter + 3 * high;

            char defense_magic[max_n_digit_stats];
       int_to_string(static_cast< item_difensivo *>(objects[array_index])->difesa_magica, defense_magic);
            mvwprintw(win, y + i + counter, x, "difesa magica");
            mvwprintw(win, y + i + counter, x + 15, defense_magic);
            i++;
            counter = counter + 3 * high;
    }
    wrefresh(win);
}

void Inventory::equip_menu(Player * p){
w_equip_is_active=true;
int yMax, xMax;
getmaxyx(w_equip, yMax, xMax);
box(w_equip, 0, 0);
keypad(w_inventory, false);


char curr_life[max_n_digit_stats];
char attack[max_n_digit_stats];
char attack_magic[max_n_digit_stats];
char defense[max_n_digit_stats];
char defense_magic[max_n_digit_stats];
int_to_string(p->curHealth, curr_life);
int_to_string(p->danno_fisico, attack);
int_to_string(p->danno_magico, attack_magic);
int_to_string(p->difesa_fisica, defense);
int_to_string(p->difesa_magica, defense_magic);
mvwprintw(w_equip, 2, 60, "PERSONAGGIO");
mvwprintw(w_equip, 5, 55, "vita:");
mvwprintw(w_equip, 5, 72, curr_life);

mvwprintw(w_equip, 7, 55, "attacco fisico:");
mvwprintw(w_equip, 7, 72, attack);

mvwprintw(w_equip, 9, 55, "attacco magico:");
mvwprintw(w_equip, 9, 72, attack_magic);

mvwprintw(w_equip, 11, 55, "difesa fisica:");
mvwprintw(w_equip, 11, 72, defense);

mvwprintw(w_equip, 13, 55, "difesa magica:");
mvwprintw(w_equip, 13, 72, defense_magic);




//for(int i=0; i<curr_inventory_space; i++){
//if(check_class_name(i)==2){
//if((strcmp(objects[i]->type, type[2]) == 0) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
//    aux_equip_item_menu(w_equip, 12, 2, i, 0);
//    }
//
//if((strcmp(objects[i]->type, type[4]) == 0) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
//    aux_equip_item_menu(w_equip, 7, 2, i, 0);
//    }
//if((strcmp(objects[i]->type, type[8]) == 0) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
//    aux_equip_item_menu(w_equip, 22, 2, i, 0);
//    }
//if((strcmp(objects[i]->type, type[7]) == 0) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
//    aux_equip_item_menu(w_equip, 27, 2, i, 0);
//    }}
//if(check_class_name(i)==1){
//if(static_cast< Weapon *>(objects[i])->is_equipped){
//    aux_equip_item_menu(w_equip, 2, 2, i, 0);
//    }}
//}        
}

void Inventory:: update_equip_menu(){
int choice;    
        choice=(*p_input);
        if(choice==esc){
            keypad(w_inventory, true);
            werase(w_equip);
            wrefresh(w_equip);
            return;
        }
}

void Inventory::open(){
    is_open=true;
    box(w_inventory, 0, 0);
    pixel_phrase(w_inventory, 2, 2, "zaino", false);
    pixel_phrase(w_inventory, 36, 2, "equip", false);
    pixel_phrase(w_inventory, 70, 2, "opzioni", false);
    keypad(w_inventory, true);   
       
}


void Inventory::update(Player * p){

if(options_is_active==true){
  update_options();
  return;
       }  
if(zaino_is_active==true){
  z_highlight=0;
  zaino_menu(1, p);
  return;
       }  
if(w_equip_is_active==true){
  update_equip_menu();
  return;
       }

    int choice;
    choice=(*p_input);
    if(choice==scroll_right){
        highlight++;
        if(highlight>3)
            highlight=1;
    }
    if(choice==scroll_left){
        highlight--;
        if(highlight<1)
            highlight=3;
    }
    if(highlight==1){
    
     pixel_phrase(w_inventory, 2, 2, "zaino", true);   
     pixel_phrase(w_inventory, 36, 2, "equip", false);
     pixel_phrase(w_inventory, 70, 2, "opzioni", false); 
     wrefresh(w_inventory); 
    }
    if(highlight==2){
     pixel_phrase(w_inventory, 2, 2, "zaino", false);   
     pixel_phrase(w_inventory, 36, 2, "equip", true);
     pixel_phrase(w_inventory, 70, 2, "opzioni", false); 
     wrefresh(w_inventory);
    }
    if(highlight==3){
     pixel_phrase(w_inventory, 2, 2, "zaino", false);   
     pixel_phrase(w_inventory, 36, 2, "equip", false);
     pixel_phrase(w_inventory, 70, 2, "opzioni", true);
     wrefresh(w_inventory);
    }
    if(choice==esc){
        close();

    }
    if(choice==10){
        if(highlight==1){
            z_highlight=0;
            zaino_menu(1, p);
            wrefresh(w_inventory);
        }
        if(highlight==2){
            equip_menu(p);
        }
        if(highlight==3){
            open_options();
            
        }
    }
}

void Inventory::close(){
highlight=0;
u_highlight = 1;
is_open=false;
werase(w_inventory);
}
