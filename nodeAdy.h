/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nodeAdy.h
 * Author: marwilc
 *
 * Created on 15 de junio de 2016, 10:02 PM
 */

#ifndef NODEADY_H
#define NODEADY_H
#include <iostream>

template <class T>
class NodeAdy
{
    private:
        T info;
        float cost;
        NodeAdy<T> *next;
        
    public:
        //contructores
        NodeAdy<T>(): cost(0), next(NULL){};
        NodeAdy<T>(const T &v): info(v),cost(0),next(NULL){};
        NodeAdy<T>(const T &v, const float &c, NodeAdy<T> *ptr): info(v), cost(c), next(ptr){};
        //consultores
        T getInfo()const {return(info);};
        float getCost() const {return(cost);};
        NodeAdy<T>* getNext(){return (next);};
        //modificadores
        void setInfo(const T &v){this->info=v;};
        void setCost(const float &c){cost=c;};
        void setNext(NodeAdy<T> *ptr){next=ptr;};
        
};


#endif /* NODEADY_H */

