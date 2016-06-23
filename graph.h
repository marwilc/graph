/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: marwilc
 *
 * Created on 16 de junio de 2016, 01:42 PM
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <queue>
#include <stack>
#include "nodeAdy.h"
#include "nodeVert.h"

using namespace std;

template <class T>
class Graph
{
    private:
        NodeVert<T>* g;
        int dim;
    
    public:
        //constructores
        Graph<T>():g(NULL), dim(0){};
        //destructores
        ~Graph<T>();
        void clear();
        //consultores
        NodeVert<T>* getG(){return(g);};
        bool isEmpty()const {return(g==NULL);};
        bool thereVert(const T &v)const;
        bool thereArc(const T &v, const T &w)const;
        float costArc(const T &v, const T &w)const;
        int orderGraph()const{return(dim);};
        list<T> predecessors(const T &v);
        list<T> successors(const T &v);
        //modificadores
        void setG(NodeVert<T>* ptr);
        void addVert(const T &v);
        void addArc(const T &v, const T &w, const float &c);
        void deleteVert(const T &v);//falta
        void deleteArc(const T &v, const T &w);//falta        
};
//destructores
template <class T>
Graph<T>::~Graph()
{
    NodeVert<T> *auxVert, *antVert;
    NodeAdy<T> *auxAdy, *antAdy;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL)
        {
            auxAdy=auxVert->getListAdy();
            while(auxAdy!=NULL)
            {
                antAdy=auxAdy;
                auxAdy=auxAdy->getNext();
                antAdy->setNext(NULL);
                delete(antAdy);
            }
            antVert=auxVert;
            auxVert=auxVert->getNext();
            antVert->setNext(NULL);
            antVert->setListAdy(NULL);
            delete(antVert);
        }
        this->g=NULL;
        dim=0;
    }
}

template <class T>
void Graph<T>::clear()
{
    NodeVert<T> *auxVert, *antVert;
    NodeAdy<T> *auxAdy, *antAdy;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL)
        {
            auxAdy=auxVert->getListAdy();
            while(auxAdy!=NULL)
            {
                antAdy=auxAdy;
                auxAdy=auxAdy->getNext();
                antAdy->setNext(NULL);
                delete(antAdy);
            }
            antVert=auxVert;
            auxVert=auxVert->getNext();
            antVert->setNext(NULL);
            antVert->setListAdy(NULL);
            delete(antVert);
        }
        this->g=NULL;
        dim=0;
    }
}
//consultores
template <class T>
bool Graph<T>::thereVert(const T& v) const
{
    NodeVert<T> *aux;
    bool band=false;
    
    if(this->g!=NULL)
    {
        aux=this->g;
        while(aux!=NULL && !band)
        {
            if(aux->getInfo()==v)
                band=true;
            
            aux=aux->getNext();
        }
    }
    return band;
}

template <class T>
bool Graph::thereArc(const T& v, const T& w) const
{
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    bool band=false;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL && !band)
        {
            if(auxVert->getInfo()==v)
            {
                auxAdy=auxVert->getListAdy();
                while(auxAdy!=NULL && !band)
                {
                    if(auxAdy->getInfo()==w)
                        band=true;
                    
                    auxAdy=auxAdy->getNext();    
                }
            }
            auxVert=auxVert->getNext();            
        }
    }
    return(band);
}

template <class T>
float Graph<T>::costArc(const T& v, const T& w) const
{
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    float coste=0;
    bool band=false;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL && !band)
        {
            if(auxVert->getInfo()==v)
            {
                auxAdy=auxVert->getListAdy();
                while(auxAdy!=NULL && !band)
                {
                    if(auxAdy->getInfo()==w)
                    {    
                        band=true;
                        coste=auxAdy->getCost();
                    }
                    auxAdy=auxAdy->getNext();    
                }
            }
            auxVert=auxVert->getNext();            
        }
    }
    return(coste);
}

template <class T>
list<T> Graph<T>::predecessors(const T& v)
{
    list<T> p;
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    bool band=false;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL)
        {
            auxAdy=auxVert->getListAdy();
            while(auxAdy!=NULL && !band)
            {
                if(auxAdy->getInfo()==v)
                {
                    p.push_back(auxVert->getInfo());
                    band=true;
                }
                auxAdy=auxAdy->getNext();
            }
            band=false;
            auxVert=auxVert->getNext();
        }
    }
    return (p);
}

template <class T>
list<T> Graph<T>::successors(const T& v)
{
    list<T> p;
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    bool band=false;
    
    if(this->g!=NULL)
    {
        auxVert=this->g;
        while(auxVert!=NULL && !band)
        {
            if(auxVert->getInfo()==v)
            {
                auxAdy=auxVert->getListAdy();
                while(auxAdy!=NULL )
                {
                    p.push_back(auxAdy->getInfo());
                    auxAdy=auxAdy->getNext();
                }
                band=true;      
            }
            auxVert=auxVert->getNext();
        }
    }
    return (p);
}

//modificadores
template <class T>
void Graph<T>::addVert(const T& v)
{
    NodeVert<T> *newVert, *antVert, *nextVert;
    
    newVert= new NodeVert<T>(v);
    antVert=NULL;
    nextVert=g;
    
    while(nextVert!=NULL && nextVert->getInfo()<v)
    {
        antVert=nextVert;
        nextVert=nextVert->getNext();
    }
    if(antVert==NULL)
    {
        newVert->setNext(g);
        g=newVert;
    }
    else
    {
        antVert->setNext(newVert);
        newVert->setNext(nextVert);
    }
    dim++;
}

template <class T>
void Graph<T>::addArc(const T& v, const T& w, const float& c)
{
    NodeVert<T> *origin;
    NodeAdy<T> *antAdy, *nextAdy, *newAdy;
    bool band1=false;
    
    if(this->g!=NULL)
    {
        newAdy=new NodeAdy<T>(w,c,NULL);
        origin=g;
        while(origin!=NULL && !band1)
        {
            if(origin->getInfo()==v)
            {
                band1=true;
                antAdy=NULL;
                nextAdy=origin->getListAdy();
                while(nextAdy!=NULL && nextAdy->getInfo()<w)
                {
                    antAdy=nextAdy;
                    nextAdy=nextAdy->getNext();                   
                }
                if(antAdy==NULL)
                {
                    newAdy->setNext(nextAdy);
                    origin->setListAdy(newAdy);
                }
                else
                {
                    antAdy->setNext(newAdy);
                    newAdy->setNext(nextAdy);
                }
            }
        }
    }
}

template <class T>
void Graph::deleteVert(const T& v)
{
    
}
#endif /* GRAPH_H */

