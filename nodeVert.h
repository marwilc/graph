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
//#include "nodeAdy.h"
template <class T>
class NodeAdy;

template <class T>
class NodeVert
{
    private:
        
        T info;
        int tag;
        int arcsIn;
        int arcsOut;
        NodeVert *next;
        NodeVert *prev;
        NodeAdy<T> *listAdy;
        
    public:
        //constructores
        NodeVert():prev(NULL),next(NULL), listAdy(NULL), tag(0), arcsIn(0),arcsOut(0) {};
        NodeVert(const T &v):info(v),prev(NULL),next(NULL), listAdy(NULL), tag(0), arcsIn(0),arcsOut(0){};
        NodeVert(NodeVert const &n): info(n.info), next(n.next), prev(n.prev), listAdy(n.listAdy), tag(n.tag),arcsIn(n.arcsIn),arcsOut(n.arcsOut){};
        NodeVert(const T &v, const int &tags):info(v),prev(NULL),next(NULL),listAdy(NULL), tag(tags),arcsIn(0),arcsOut(0){};
        //NodeVert(const T &v, NodeVert<T> *prv,NodeVert<T> *nxt, NodeAdy<NodeVert<T>* > *list): info(v), prev(prv),next(nxt), listAdy(list){};
        //consultores
        int getTag()const{return(this->tag);};
        int getGradeIn()const {return(this->arcsIn);};
        int getGradeOut()const {return(this->arcsOut);};
        T getInfo()const{return(this->info);};
        NodeVert* getNext()const {return(this->next);};
        NodeVert* getPrev()const {return(this->prev);};
        NodeAdy<T>* getListAdy()const {return(this->listAdy);};
        //modificadores
        void setGradeIn(const int &n){this->arcsIn=n;};
        void setGradeOut(const int &n){this->arcsOut=n;};
        void setTag(const int &tags){this->tag=tags;};
        void setInfo(const T &v){this->info=v;};
        void setNext(NodeVert *ptr){this->next=ptr;};
        void setPrev(NodeVert *ptr){this->prev=ptr;};
        void setListAdy(NodeAdy<T> *ptr){this->listAdy=ptr;};
        NodeVert& operator=(const NodeVert &n);
};

template <class T>
NodeVert<T>& NodeVert<T>::operator=(const NodeVert<T> &n)
{
	if(this!= &n)
	{
		info=n.info;
		next=n.next;
		prev=n.prev;
		listAdy=n.listAdy;
		tag=n.tag;
		arcsIn=n.arcsIn;
		arcsOut=n.arcsOut;
	}
	return(*this);
}
#endif /* NODEVERT_H */

