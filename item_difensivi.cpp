#ifndef DEFENSIVE_ITEM_HPP
#define DEFENSIVE_ITEM_HPP

class Item_difensivi: public item{
    protected:
        int difesa;
        int difesa_magica;
        bool potere=false;
    public:
        Item_difensivi(int d, int d_m){
            difesa=d;
            difesa_magica=d_m;

        }

        void power_up (){
            potere=true;        //ogni item può avere al massimo un potere speciale (altrimenti troppo sgravato)
        
        }
};