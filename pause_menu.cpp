#include "pause_menu.hpp"


Pause_menu::Pause_menu(Player * p, int stdscr_x, int stdscr_y):Pixel_art(){

zaino_x_pos = (stdscr_x - ZAINO_WIDTH) / (3.5), zaino_y_pos = (stdscr_y - ZAINO_HEIGHT) / 2.1;
inventory_x_pos = (stdscr_x - PAUSE_MENU_WIDTH) / (2.2), inventory_y_pos = 3;
item_menu_x_pos = zaino_x_pos + ZAINO_WIDTH + 3, item_menu_y_pos = (stdscr_y - ZAINO_HEIGHT) / (2.2);
status_x_pos = (stdscr_x - STATUS_MENU_WIDTH) / (2.2), status_y_pos = (stdscr_y - STATUS_MENU_HEIGHT) / (2.3);
options_x_pos = (stdscr_x - MENU_OPTIONS_WIDTH) / (2.3), options_y_pos = (stdscr_y - MENU_OPTIONS_HEIGHT) / (2.1);

this->p = p;
is_open=false;
options_is_active=false;
zaino_is_active=false;
w_use_is_active=false;
w_equip_is_active=false;

this->w_inventory = newwin(PAUSE_MENU_HEIGHT, PAUSE_MENU_WIDTH, inventory_y_pos,inventory_x_pos);
this->w_zaino = newwin(ZAINO_HEIGHT, ZAINO_WIDTH, zaino_y_pos, zaino_x_pos);
this->w_item = newwin(ITEM_MENU_HEIGHT, ITEM_MENU_WIDTH, item_menu_y_pos, item_menu_x_pos);
this->w_weapon = newwin(w_graphic_high + 1, w_graphic_lenght + 1, item_menu_y_pos + 2, item_menu_x_pos + 1);
this->w_equip = newwin(STATUS_MENU_HEIGHT, STATUS_MENU_WIDTH, status_y_pos, status_x_pos);
this->w_options = newwin(MENU_OPTIONS_HEIGHT, MENU_OPTIONS_WIDTH, options_y_pos, options_x_pos);

curr_inventory_space = 0;
}

void Pause_menu::destroy(){
    delwin(w_inventory);
    delwin(w_zaino);
    delwin(w_item);
    delwin(w_weapon);
    delwin(w_equip);
    delwin(w_options);
}

bool Pause_menu::is_active(){
    return(is_open);
}

int Pause_menu::random_item(){
int r;
bool all_artifact=true;
for(int i=0; i<curr_inventory_space;i++){
    if((check_class_name(i)==11) || (check_class_name(i)==12))
        all_artifact=false;
}
if(all_artifact)
    return (-1);
 while(true){
  r = (rand() % curr_inventory_space) + 1;
  if((check_class_name(r)==11) || (check_class_name(r)==12)){
    return r;
   }
 }
return (-1);
}

void Pause_menu::open_options(){
    options_is_active=true;
    keypad(w_inventory,false);
    box(w_options, 0, 0);
    mvwaddch(w_options, 2, 2, KEY_PAUSE);
    wprintw(w_options, " = apri e chiudi menu di pausa");
    mvwaddch(w_options, 4, 2, KEY_ESC);
    wprintw(w_options, " = torni indietro nei menu");
    mvwprintw(w_options, 6, 2, "barra spaziatrice = tasto per interagire");
    mvwaddch(w_options, 8, 2, KEY_MAP);
    wprintw(w_options, " = apri la minimappa");
    mvwprintw(w_options, 10, 2, "invio = tasto di selezione nei menu");
    mvwprintw(w_options, 12, 2, "i tasti freccia servono a muoversi nelle 4 direzioni");
    mvwprintw(w_options, 14, 2, "i tasti w a s d servono ad attaccare nelle 4 direzioni");
    mvwprintw(w_options, 16, 2, "si può attaccare pure con ctrl + frecce direzionali");
    wrefresh(w_options);
}

void Pause_menu::update_options(){

        if(input==KEY_ESC){
            options_is_active = false;
            keypad(w_inventory,true);
            werase(w_options);         
            wrefresh(w_options);
        }
}

int Pause_menu::check_class_name(int array_index){
    if(objects[array_index]->isWeapon())
        return 11;
    else if(objects[array_index]->isItemDifensivo())
        return 12;
    else if(objects[array_index]->isArtifact())
        return 13;
    return -1;
}

int Pause_menu::check_subclass_name(int array_index){
    
    if(objects[array_index]->getId()==ID_SWORD)
        return 0;
    else if(objects[array_index]->getId()==ID_WEAPON_BOW)
        return 1;
    else if(objects[array_index]->getId()==ID_ITEM_DIFENSIVO_ARMOR)
        return 2;
    else if(objects[array_index]->getId()==ID_ITEM_DIFENSIVO_SHIELD)
        return 3;
    else if(objects[array_index]->getId()==ID_ITEM_DIFENSIVO_HELM)
        return 4;
    else if(objects[array_index]->getId()==ID_WEAPON_AXE)
        return 5;
    else if((objects[array_index]->getId()==ID_HEALTH_POTION) || (objects[array_index]->getId()==ID_LIFE_ELIXIR))
        return 6;
    else if(objects[array_index]->getId()==ID_ITEM_DIFENSIVO_BOOTS)
        return 7;
    else if(objects[array_index]->getId()==ID_ITEM_DIFENSIVO_NECKLACE)
        return 8;
    else if(objects[array_index]->getId()==ID_WEAPON_ROD)
        return 9;
    else if(objects[array_index]->getId()==ID_RUNE)
        return 10;
    return -1;
}

void Pause_menu::wattroff_inventory(WINDOW * win){
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLUE)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_MAGENTA)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_CYAN)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLUE)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_MAGENTA)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_CYAN)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_BLUE, COLOR_BLACK)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_MAGENTA, COLOR_BLACK)));
    wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_CYAN, COLOR_BLACK)));
}




void Pause_menu::fix_array(int array_index){
    p->removeItem(objects[array_index]);
    objects[array_index]=NULL;
    if(array_index==curr_inventory_space){
         curr_inventory_space--;}
    else{
        curr_inventory_space--;
        objects[array_index]=objects[curr_inventory_space];
        objects[curr_inventory_space] = NULL;
        
    }
    }

  

void Pause_menu::int_to_string(int number, char string[]){
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

void Pause_menu::reverse_string(char string[]){
int lenght = strlen(string);
for (int i = 0; i < lenght / 2; i++){
	char tmp=string[i];
	string[i] = string[lenght -1 -i];
	string[lenght -1 -i]= tmp; 
}}

int Pause_menu::count_char(int start_char,char string[]){//data una stringa conta le lettere della parola seguente al punto di inizio, l'ho usata in w_item 
int count = 0;
while((string[start_char]!=' ')){
if((string[start_char]=='\0'))
    return count;
count++;
start_char++;
}
return count;
}

int Pause_menu::count_char_with_space(int start_char,char string[]){//data una stringa conta le lettere della parola seguente al punto di inizio contando gli spazi, l'ho usata in print_nome
int count = 0;
    while((string[start_char + count]!='\0')){
        count++;
    }
return count;
}

void Pause_menu::print_weapon(int high, int lenght, const char graphic_weapon[][w_graphic_lenght]){
for(int i=0; i<high; i++){
    for(int k=0; k<lenght; k++){
        mvwaddch(w_weapon, i + 2, k + 2, graphic_weapon[i][k]);
    }
}
wrefresh(w_weapon);
}

void Pause_menu::item_menu(int array_index){
box(w_item, 0, 0);
int yMax, xMax;
getmaxyx(w_item, yMax, xMax);

if(strcmp(objects[array_index]->rarity, rarity[0]) == 0)
        wattron(w_item, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
    else if(strcmp(objects[array_index]->rarity, rarity[1]) == 0)
            wattron(w_item, COLOR_PAIR(Cell::pairNumber(COLOR_BLUE, COLOR_BLACK)));
    else if(strcmp(objects[array_index]->rarity, rarity[2]) == 0)
            wattron(w_item, COLOR_PAIR(Cell::pairNumber(COLOR_MAGENTA, COLOR_BLACK)));
    else if(strcmp(objects[array_index]->rarity, rarity[3]) == 0)
            wattron(w_item, COLOR_PAIR(Cell::pairNumber(COLOR_CYAN, COLOR_BLACK)));

mvwprintw(w_item, 2, xMax/2 -3,objects[array_index]->name);

wattroff_inventory(w_item);

int high=yMax - 10;

if(curr_inventory_space>0){

aux_equip_item_menu(w_item, 6, start_written, array_index, 1, false);

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

print_weapon(w_graphic_high, w_graphic_lenght, graphic_items[check_subclass_name(array_index)]);
wrefresh(w_weapon);
}

void Pause_menu::useOrdiscardItem(int y_position, int x_position, int array_index){
u_highlight=1;
w_use_is_active=true;
    w_use_high = y_position;
    w_use_width = x_position;
this->w_use=newwin(4, 13, w_use_high, w_use_width);
box(w_use, 0, 0);
keypad(w_zaino, false);
wattron(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));

if(((check_class_name(array_index))==13)){
    mvwprintw(w_use, 1, 4, "usa");
    
}
else
    mvwprintw(w_use, 1, 2, "equipaggia");
wattroff(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
if((check_class_name(array_index))==13 || (((check_class_name(array_index))==12)&&(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped))) || (((check_class_name(array_index))==11)&&(!(static_cast<Weapon *>(objects[array_index])->is_equipped))))
   mvwprintw(w_use, 2, 3, "scarta");

keypad(w_use, true);
wrefresh(w_use); 
}

void Pause_menu::update_w_use(int array_index){
if(input==KEY_ESC){
    w_use_is_active=false;
    keypad(w_use, false); 
    keypad(w_zaino, true); 
    werase(w_use);
    wrefresh(w_zaino);
    wrefresh(w_use);
    return;
    }
if(input==scroll_up){
        u_highlight--;
        if(u_highlight<=0){
              u_highlight=1;
        }
}
if(input==scroll_down){
        if(check_class_name(array_index)==13){
            u_highlight++;
            if(u_highlight>=3){
            u_highlight=2;
            }
        }
        else if(check_class_name(array_index)==12){
            if(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped)){
                u_highlight++;
               if(u_highlight>=3){
                    u_highlight=2;
                }} 
        }
        else if(check_class_name(array_index)==11){
            if(!(static_cast<Weapon *>(objects[array_index])->is_equipped)){
                u_highlight++;
               if(u_highlight>=3){
                    u_highlight=2;
                }} 
        }
}
if(u_highlight==1){
    wattron(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK))); 
    if(((check_class_name(array_index))==13))
        mvwprintw(w_use, 1, 4, "usa");
    else
        mvwprintw(w_use, 1, 2, "equipaggia");   
    wattroff(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
    wattron(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK))); 

    if(check_class_name(array_index)==13){
            mvwprintw(w_use, 2, 3, "scarta");
        }
        else if(check_class_name(array_index)==12){
            if(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped))
               mvwprintw(w_use, 2, 3, "scarta"); 
        }
        else if(check_class_name(array_index)==11){
            if(!(static_cast<Weapon *>(objects[array_index])->is_equipped))
               mvwprintw(w_use, 2, 3, "scarta"); 
        }
    
    wattroff(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
    wrefresh(w_use);
}
else if(u_highlight==2){
    wattron(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
    if(check_class_name(array_index)==13){
            mvwprintw(w_use, 2, 3, "scarta");
        }
        else if(check_class_name(array_index)==12){
            if(!(static_cast< item_difensivo *>(objects[array_index])->is_equipped)){
               mvwprintw(w_use, 2, 3, "scarta");
            }
        }
        else if(check_class_name(array_index)==11){
            if(!(static_cast<Weapon *>(objects[array_index])->is_equipped))
               mvwprintw(w_use, 2, 3, "scarta"); 
        }
    wattroff(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
    wattron(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK))); 
    if(((check_class_name(array_index))==13))
        mvwprintw(w_use, 1, 4, "usa");
    else
        mvwprintw(w_use, 1, 2, "equipaggia");
    wattroff(w_use, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));

wrefresh(w_use);
}

if(input==invio){
 if(u_highlight==1){
    if(check_class_name(array_index)==13){
        pArtifact tmp =  static_cast< Artifact *>(objects[array_index]);
        if(tmp->getId() == ID_HEALTH_POTION) tmp->use_item(objects[array_index], p->curHealth);
        else if(tmp->getId() == ID_KEY) tmp->use_item(objects[array_index], p->n_keys);
        else if(tmp->getId() == ID_LIFE_ELIXIR) tmp->use_item(objects[array_index], p->n_hearts);
        else if(tmp->getId() == ID_RUNE) {
          int item_index=random_item();
          if(item_index!=(-1)){
            tmp->use_item(objects[item_index], p->n_hearts);
            }
        }
        fix_array(array_index);
        clean_window(w_zaino, ZAINO_HEIGHT - 1, ZAINO_WIDTH -1);
        clean_window(w_item, ITEM_MENU_HEIGHT -1, ITEM_MENU_WIDTH - 1); 
        wrefresh(w_item);
        keypad(w_use, false); 
        keypad(w_zaino, true);
        w_use_is_active=false; 
        werase(w_use);
        wrefresh(w_zaino);
        wrefresh(w_use);
        input=scroll_up;
        open_zaino();
        zaino_menu(array_index);
        return;  
    }
            if(check_class_name(array_index)==11){
                        p->change_weapon(static_cast< pWeapon> (objects[array_index]));
            }
            if(check_class_name(array_index)==12){
                        if(check_subclass_name(array_index)==2){
                            p->change_armor (static_cast< pArmor>(objects[array_index]));
                        }
                        if(check_subclass_name(array_index)==3){
                            p->change_shield (static_cast< pShield>(objects[array_index])); 
                        }
                        if(check_subclass_name(array_index)==4){
                            p->change_helm (static_cast< pHelm>(objects[array_index])); 
                        }
                        if(check_subclass_name(array_index)==8){
                            p->change_necklace (static_cast< pNecklace>(objects[array_index]));
                        }
                        if(check_subclass_name(array_index)==7){
                            p->change_boots (static_cast< pBoots>(objects[array_index]));
                        }
            }
        keypad(w_use, false); 
        keypad(w_zaino, true); 
        w_use_is_active=false;
        werase(w_use);
        wrefresh(w_zaino);
        wrefresh(w_use);
        input=scroll_up;
        open_zaino();   
        zaino_menu(array_index + 1);
        return;  
        }
        else if(u_highlight==2){
            fix_array(array_index);
            clean_window(w_zaino, ZAINO_HEIGHT - 1, ZAINO_WIDTH -1);
            clean_window(w_item, ITEM_MENU_HEIGHT -1, ITEM_MENU_WIDTH - 1);  
            wrefresh(w_item);
            keypad(w_use, false); 
            keypad(w_zaino, true); 
            w_use_is_active=false;
            werase(w_use);
            wrefresh(w_zaino);
            wrefresh(w_use);
            input=scroll_up;
            open_zaino();
            zaino_menu(array_index);
            return;  
        }
    }
}

void Pause_menu::strcmp_rarity(WINDOW * win, int array_index, bool highlight){
if(highlight){
    if(strcmp(objects[array_index]->rarity, rarity[0]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLACK)));
    else if(strcmp(objects[array_index]->rarity, rarity[1]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_BLUE)));
    else if(strcmp(objects[array_index]->rarity, rarity[2]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_MAGENTA)));
    else if(strcmp(objects[array_index]->rarity, rarity[3]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_YELLOW, COLOR_CYAN)));   
}
else{
    
    if(strcmp(objects[array_index]->rarity, rarity[0]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
    else if(strcmp(objects[array_index]->rarity, rarity[1]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLUE)));
    else if(strcmp(objects[array_index]->rarity, rarity[2]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_MAGENTA)));
    else if(strcmp(objects[array_index]->rarity, rarity[3]) == 0)
        wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_CYAN)));
}   
}

void Pause_menu::print_item_name(WINDOW * win, int y, int x, int array_index){
int n;
    mvwprintw(win, y, x, objects[array_index]->name);
    wattron(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
int high = 2;
for(int i=0; i<curr_inventory_space; i++){
    n = count_char_with_space(0, objects[i]->name) + 1;
    if((check_class_name(i))==11){
    if(static_cast< Weapon *>(objects[i])->is_equipped)
        mvwaddch(win, high, x + n, 'E');
    else
        mvwaddch(win, high, x + n, ' ');
    high = high + 2;}
 else if((check_class_name(i))==12){
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
wattroff(win, COLOR_PAIR(Cell::pairNumber(COLOR_WHITE, COLOR_BLACK)));
wrefresh(win);
}

void Pause_menu::open_zaino(){
  int xMax = getmaxx(w_zaino);      
  z_highlight=0;
  zaino_is_active=true;
  box(w_zaino, 0, 0);  
  init_color(COLOR_CYAN, 532, 250, 82);// colore arancione
  keypad(w_inventory, false);    
  keypad(w_zaino, true);
     high = 0;  //serve per implementare che le scritte dei nomi non sono tutte attaccate una sotto l'altra ma c'è una casella di spazio in altezza
        for(int i=0; i<curr_inventory_space; i++){
            strcmp_rarity(w_zaino, i, false);
            high = high + 2;
            print_item_name(w_zaino, high, xMax/2 -15, i);
            wattroff_inventory(w_zaino);
        }
        high = 2;
}

void Pause_menu::zaino_menu(int array_index){
if(w_use_is_active==true){
  update_w_use(z_highlight);
  return;
}
    int xMax = getmaxx(w_zaino);

if(curr_inventory_space<=0){
    box(w_zaino, 0,0);
    box(w_item, 0, 0);
    wrefresh(w_zaino);
    wrefresh(w_item);
    if(input==KEY_ESC){
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
    else 
        return;
} 

strcmp_rarity(w_zaino, z_highlight, true);
print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
wattroff_inventory(w_zaino);

item_menu(z_highlight);

    if(input==KEY_ESC){
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
    if(input==KEY_SELECT_MENU){
        int n = count_char_with_space(0, objects[z_highlight]->name) + 3;
        useOrdiscardItem(zaino_y_pos + high-1, zaino_x_pos + n + 17, z_highlight);
    }
    if(input==scroll_up){
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
        strcmp_rarity(w_zaino, z_highlight, true);
    print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
    wattroff_inventory(w_zaino);

    if(z_highlight + 1 < curr_inventory_space){
        strcmp_rarity(w_zaino, z_highlight + 1, false);
            print_item_name(w_zaino, high + 2, xMax/2 -15, z_highlight + 1);
            wattroff_inventory(w_zaino);
        }}
    if(input==scroll_down){
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
            zaino_menu(1);
        }
        item_menu(z_highlight);
 
        strcmp_rarity(w_zaino, z_highlight, true);
    
        print_item_name(w_zaino, high, xMax/2 -15, z_highlight);
    wattroff_inventory(w_zaino);

    if(z_highlight - 1 >= 0){
        strcmp_rarity(w_zaino, z_highlight - 1, false);

        print_item_name(w_zaino, high - 2, xMax/2 -15, z_highlight - 1);
        wattroff_inventory(w_zaino);
        }
 
}
}

void Pause_menu::aux_equip_item_menu(WINDOW * win, int y, int x, int array_index, int high, bool wrtite_name){
    int counter = 0;
     counter = counter + 3 * high;
    if(wrtite_name)
        mvwprintw(win, y, x, objects[array_index]->name);
    mvwprintw(win, y + 1 + counter, x, "rarita'");
    mvwprintw(win, y + 1 + counter, x + 10, objects[array_index]->rarity);
    counter = counter + 3 * high;
    int i = 2;
    if((check_class_name(array_index))==11){
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
    if((check_class_name(array_index))==12){
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

void Pause_menu::equip_menu(){
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

wrefresh(w_equip);


for(int i=0; i<curr_inventory_space; i++){
if(check_class_name(i)==12){
    
if((check_subclass_name(i)==2) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
    aux_equip_item_menu(w_equip, 12, 2, i, 0, true);
    }
if((check_subclass_name(i)==3) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
    aux_equip_item_menu(w_equip, 12, 2, i, 0, true);
    }

if((check_subclass_name(i)==4) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
    aux_equip_item_menu(w_equip, 7, 2, i, 0, true);
    }
if((check_subclass_name(i)==8) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
    aux_equip_item_menu(w_equip, 22, 2, i, 0, true);
    }
if((check_subclass_name(i)==7) && (static_cast< item_difensivo *>(objects[i])->is_equipped)){
    aux_equip_item_menu(w_equip, 27, 2, i, 0, true);
    }}
if(check_class_name(i)==11){
if(static_cast< Weapon *>(objects[i])->is_equipped){
    aux_equip_item_menu(w_equip, 2, 2, i, 0, true);
    }}
}        
}

void Pause_menu:: update_equip_menu(){
        if(input==KEY_ESC){
            w_equip_is_active = false;
            keypad(w_inventory, true);
            werase(w_equip);
            wrefresh(w_equip);
            return;
        }
}

void Pause_menu::open(){
    curr_inventory_space = p->getInventory(objects);
    highlight=0;
    is_open=true;
    box(w_inventory, 0, 0);
    pixel_phrase(w_inventory, 2, 2, "zaino", false);
    pixel_phrase(w_inventory, 36, 2, "equip", false);
    pixel_phrase(w_inventory, 70, 2, "opzioni", false);
    keypad(w_inventory, true);   
}


void Pause_menu::update(int input){

this->input = input;

if(options_is_active==true){
  update_options();
  return;
       }  
if(zaino_is_active==true){
    zaino_menu(1);
  return;
       }  
if(w_equip_is_active==true){
  update_equip_menu();
  return;
       }

    
    if(input==scroll_right){
        highlight++;
        if(highlight>3)
            highlight=1;
    }
    if(input==scroll_left){
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
    if(input==KEY_PAUSE){
        close();

    }
    if(input==KEY_SELECT_MENU){
        if(highlight==1){
            open_zaino();
            wrefresh(w_inventory);
        }
        if(highlight==2){
            equip_menu();
        }
        if(highlight==3){
            open_options();
            
        }
    }
}

void Pause_menu::close(){
if(zaino_is_active){
    werase(w_zaino);
    wrefresh(w_zaino);
    werase(w_item);
    wrefresh(w_item);
    werase(w_weapon);
    wrefresh(w_weapon);
    zaino_is_active=false;
    if(w_use_is_active){
        w_use_is_active=false;
        werase(w_use);
        wrefresh(w_use);
    }
}
if(w_equip_is_active){
    w_equip_is_active=false;
    werase(w_equip);
    wrefresh(w_equip);
}
if(options_is_active){
    options_is_active=false;
    werase(w_options);
    wrefresh(w_options);
}
default_color();
is_open=false;
werase(w_inventory);
wrefresh(w_inventory);
}


