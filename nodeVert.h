/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nodeVert.h
 * Author: marwilc
 *
 * Created on 15 de junio de 2016, 10:36 PM
 */

#ifndef NODEVERT_H
#define NODEVERT_H
#include <iostream>
#include "nodeAdy.h"

template <class T>
class NodeVert
{
    private:
        
        T info;
        NodeVert<T> *next;
        NodeAdy<T> *listAdy;
        
    public:
        //constructores
        NodeVert<T>():next(NULL), listAdy(NULL) {};
        NodeVert<T>(const T &v):info(v),next(NULL),listAdy(NULL){};
        NodeVert<T>(const T &v, NodeVert<T> *ptr, NodeAdy<T> *list): info(v), next(ptr), listAdy(list){};
        //consultores
        T getInfo()const{return(info);};
        NodeVert<T>* getNext(){return(next);};
        NodeAdy<T>* getListAdy(){return(listAdy);};
        //modificadores
        void setInfo(const T &v){this->info=v;};
        void setNext(NodeVert<T>* ptr){next=ptr;};
        void setListAdy(NodeAdy<T>* list){listAdy=list;};
};

#endif /* NODEVERT_H */

