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
//#include "nodeVert.h"

template <class T>
class NodeVert;

template <class T>
class NodeAdy
{
    private:
        NodeVert<T> *ptrVert;
        NodeAdy *next;
        NodeAdy *prev;
        float cost;
        

    public:
        //contructores
        NodeAdy(): cost(0), next(NULL), ptrVert(NULL), prev(NULL){};
        NodeAdy(const NodeAdy &n): ptrVert(n.ptrVert), next(n.next), prev(n.prev), cost(n.cost){};
        NodeAdy(NodeVert<T> *ptr, const float &c): ptrVert(ptr),cost(c),next(NULL), prev(NULL){};
        //NodeAdy(NodeVert<T> *ptr, const float &c, NodeAdy<T> *nxt, NodeAdy<T> *prv): ptrVert(ptr), cost(c), next(nxt), prev(prv){};
        //consultores
        //T getInfo()const {return(ptrVert->getInfo());};
        float getCost() const {return(this->cost);};
        NodeAdy* getNext()const {return (this->next);};
        NodeAdy* getPrev()const {return(this->prev);};
        NodeVert<T>* getPtrVert()const {return (this->ptrVert);};
        //modificadores
        //void setInfo(const T &v){this->ptrVert->setInfo(v);};
        void setCost(const float &c){this->cost=c;};
        void setNext(NodeAdy *ptr){this->next=ptr;};
        void setPrev(NodeAdy *ptr){this->prev=ptr;};
        void setPtrVert(NodeVert<T> *ptr){this->ptrVert=ptr;};
        NodeAdy& operator=(const NodeAdy &n);
};

template <class T>
NodeAdy<T>& NodeAdy<T>::operator=(const NodeAdy<T> &n)
{
	if(this != &n)
	{
		next=n.next;
		prev=n.prev;
		cost=n.cost;
		ptrVert=n.ptrVert;
	}
	return(*this);
}

#endif /* NODEADY_H */

