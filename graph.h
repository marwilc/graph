/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: marwilc holaaaaaaaa
 *
 * Created on 16 de junio de 2016, 01:42 PM
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <stack>
#include "nodeAdy.h"
#include "nodeVert.h"

using std::ostream;
using std::cout;
using std::endl;

using namespace std;

template <class T>
class Graph
{
    private:
        NodeVert<T> *first, *last;
        int nVert, nArc;

        static NodeVert<T> *findVert(const T&v ,NodeVert<T> *ptr);
        static NodeAdy<T> *findArc(const T&w, NodeAdy<T> *ptr);
    
    public:
        //constructores
        Graph():first(NULL),last(NULL), nVert(0), nArc(0){};
        Graph(const T &e);
        //destructores
        ~Graph();
        void clear();
        //consultores
        NodeVert<T>* getG()const {return(this->first);};
        bool isEmpty()const {return(this->first==NULL);}
        bool thereVert(const T &v)const;
        bool thereArc(const T &v, const T &w)const;
        float costArc(const T &v, const T &w)const;
        int orderGraph()const{return(this->nVert);};
        list<T> predecessors(const T &v)const;
        list<T> successors(const T &v)const;
        void print();
        //modificadores
        void setG(NodeVert<T> *ptr);
        void addVert(const T &v);
        void addArc(const T &v, const T &w, const float &c);
        void deleteVert(const T &v);
        void deleteArc(const T &v, const T &w);
        void replaceVert(const T &x, const T &y);
        void replaceArc(const T &xv, const T &xw, const T &yw, const float cost);
};
// metodos privados
template <class T>
NodeVert<T>* Graph<T>::findVert(const T &v, NodeVert<T> *ptr)
{
	NodeVert<T> *aux;
	bool encontrado=false;

	aux=ptr;
	while(aux!=NULL && !encontrado)
	{
		if(aux->getInfo()==v)
			encontrado=true;
		else
			aux=aux->getNext();
	}
	return(aux);
}
template <class T>
NodeAdy<T>* Graph<T>::findArc(const T &w, NodeAdy<T> *ptr)
{
	NodeAdy<T> *aux;
	bool encontrado=false;

	aux=ptr;
	while(aux!=NULL && !encontrado)
	{
		if(aux->getPtrVert()->getInfo()==w)
			encontrado=true;
		else
			aux=aux->getNext();
	}

	return(aux);
}
//constuctor
template <class T>
Graph<T>::Graph(const T &e)
{
	NodeVert<T>* aux;

	aux=new NodeVert<T>(e);
	this->nVert=1;
	this->nArc=0;
	this->first=aux;
	this->last=aux;
}
//destructores
template <class T>
Graph<T>::~Graph()
{
    NodeVert<T> *auxVert, *antVert;
    NodeAdy<T> *auxAdy, *antAdy;
    
    if(this->first!=NULL)
    {
        auxVert=this->first;
        while(auxVert!=NULL)
        {
            auxAdy=auxVert->getListAdy();
            while(auxAdy!=NULL)
            {
                antAdy=auxAdy;
                auxAdy=auxAdy->getNext();
                antAdy->setNext(NULL);
                antAdy->setPrev(NULL);
                antAdy->setPtrVert(NULL);
                antAdy->setCost(0.0);
                delete(antAdy);
            }
            antVert=auxVert;
            auxVert=auxVert->getNext();
            antVert->setNext(NULL);
            antVert->setPrev(NULL);
            antVert->setListAdy(NULL);
            delete(antVert);
        }
        this->first=NULL;
        this->last=NULL;
        this->nVert=0;
        this->nArc=0;
    }
}

template <class T>
void Graph<T>::clear()
{
    NodeVert<T> *auxVert, *antVert;
    NodeAdy<T> *auxAdy, *antAdy;
    
    if(this->first!=NULL)
    {
        auxVert=this->first;
        while(auxVert!=NULL)
        {
            auxAdy=auxVert->getListAdy();
            while(auxAdy!=NULL)
            {
                antAdy=auxAdy;
                auxAdy=auxAdy->getNext();
                antAdy->setNext(NULL);
                antAdy->setPrev(NULL);
                antAdy->setCost(0.0);
                antAdy->setPtrVert(NULL);
                delete(antAdy);
            }
            antVert=auxVert;
            auxVert=auxVert->getNext();
            antVert->setNext(NULL);
            antVert->setPrev(NULL);
            antVert->setListAdy(NULL);
            delete(antVert);
        }
        this->first=NULL;
        this->last=NULL;
        this->nVert=0;
        this->nArc=0;
    }
}
//consultores
template <class T>
bool Graph<T>::thereVert(const T& v) const
{
    return (findVert(v,this->first)!=NULL);
}

template <class T>
bool Graph<T>::thereArc(const T& v, const T& w) const
{
    NodeVert<T> *auxVert=NULL;
    NodeAdy<T> *auxAdy=NULL;
    
    if(this->first!=NULL)
    {
    	auxVert=findVert(v,this->first);
    	if(auxVert!=NULL)
    	    	auxAdy=findArc(w,auxVert->getListAdy());
    }
    return(auxVert!=NULL && auxAdy!=NULL);
}

template <class T>
float Graph<T>::costArc(const T& v, const T& w) const
{
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    float coste=0;
    
    if(this->first!=NULL)
    {
    	auxVert=findVert(v,this->first);
    	auxAdy=findArc(w,auxVert->getListAdy());
    	if(auxVert!=NULL && auxAdy!=NULL)
    	{
    		coste=auxAdy->getCost();
    	}

    }
    return(coste);
}

template <class T>
list<T> Graph<T>::predecessors(const T& v) const
{
    list<T> p;
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    
    if(this->first!=NULL)
    {
        auxVert=this->first;
        while(auxVert!=NULL)
        {
            	auxAdy=findArc(v,auxVert->getListAdy());
                if(auxAdy!=NULL)
                {
                    p.push_back(auxVert->getInfo());
                }
            auxVert=auxVert->getNext();
        }
    }
    return (p);
}

template <class T>
list<T> Graph<T>::successors(const T& v) const
{
    list<T> p;
    NodeVert<T> *auxVert;
    NodeAdy<T> *auxAdy;
    
    if(this->first!=NULL)
    {
        	auxVert=findVert(v,first);
            if(auxVert!=NULL)
            {
                auxAdy=auxVert->getListAdy();
                while(auxAdy!=NULL )
                {
                    p.push_back(auxAdy->getPtrVert()->getInfo());
                    auxAdy=auxAdy->getNext();
                }
            }
    }
    return (p);
}

/*template <class T>
T Graph<T>::getVert() const
{
	return(g->getInfo());
}*/
template <class T>
void Graph<T>::print()
{
	 NodeVert<T> *auxVert;
	 NodeAdy<T> *auxAdy;

	    if(this->first!=NULL)
	    {
	        auxVert=this->first;
	        while(auxVert!=NULL)
	        {
	        	cout<<"   ("<<auxVert->getInfo()<<")";
	            auxAdy=auxVert->getListAdy();
	            while(auxAdy!=NULL)
	            {
	            	cout<<setprecision(2)<<fixed;
	            	cout<<"---"<<auxAdy->getCost()<<"--->("<<auxAdy->getPtrVert()->getInfo()<<")";
	                auxAdy=auxAdy->getNext();
	            }
	            auxVert=auxVert->getNext();
	            if(auxVert!=NULL)
	            	cout<<endl<<"    |"<<endl;
	        }
	    }
}
//modificadores
template <class T>
void Graph<T>::addVert(const T& v)
{
    NodeVert<T> *newVert, *antVert, *nextVert;
    
    newVert= new NodeVert<T>(v);
    antVert=NULL;
    nextVert=this->first;
    
    while(nextVert!=NULL && nextVert->getInfo()<v)
    {
        antVert=nextVert;
        nextVert=nextVert->getNext();
    }
    if(antVert==NULL && nextVert==NULL)
    {
        first=newVert;
        last=newVert;
    }
    else if(antVert==NULL && nextVert!=NULL)
    	{
    		first=newVert;
    		nextVert->setPrev(newVert);
    		newVert->setNext(nextVert);
    	}
    	else if(antVert!=NULL && nextVert==NULL)
    		{
    			last=newVert;
    			antVert->setNext(newVert);
    			newVert->setPrev(antVert);
    		}
    		else
    		{
    			newVert->setNext(nextVert);
    			newVert->setPrev(antVert);
    			antVert->setNext(newVert);
    			nextVert->setPrev(newVert);
    		}
    nVert++;
}

template <class T>
void Graph<T>::addArc(const T& v, const T& w, const float& c)
{
    NodeVert<T> *vertA, *vertB;
    NodeAdy<T> *antAdy, *nextAdy, *newAdy;
    
    vertA=findVert(v,first);
    vertB=findVert(w,first);
    if(vertA!=NULL && vertB!=NULL)
    {

    	antAdy=NULL;
        nextAdy=vertA->getListAdy();
        while(nextAdy!=NULL && nextAdy->getPtrVert()->getInfo()<w)
        {
        	antAdy=nextAdy;
            nextAdy=nextAdy->getNext();
        }
        nArc++;
        newAdy=new NodeAdy<T>(vertB,c);
        if(antAdy==NULL && nextAdy==NULL)
        {
           vertA->setListAdy(newAdy);
        }
        else if(antAdy==NULL && nextAdy!=NULL)
        	{
        		vertA->setListAdy(newAdy);
        		nextAdy->setPrev(newAdy);
        		newAdy->setNext(nextAdy);
        	}
        	else if(antAdy!=NULL && nextAdy==NULL)
        		{
        			antAdy->setNext(newAdy);
        			newAdy->setPrev(antAdy);
        		}
        		else
        		{
        			antAdy->setNext(newAdy);
        			nextAdy->setPrev(newAdy);
        			newAdy->setNext(nextAdy);
        			newAdy->setPrev(antAdy);
        		}
      }
 }


template <class T>
void Graph<T>::deleteVert(const T& v)
{
    NodeVert<T> *actVert, *antVert,*nextVert, *vert;
    NodeAdy<T> *actAdy, *antAdy,*nextAdy;

    actVert=findVert(v,first);
    if(actVert!=NULL)
    {
    	actAdy=actVert->getListAdy();
    	while(actAdy!=NULL)
    	{
    		antAdy=actAdy;
    		actAdy=actAdy->getNext();
    		antAdy->setNext(NULL);
    		antAdy->setPrev(NULL);
    		antAdy->setPtrVert(NULL);
    		delete(antAdy);
    	}
    	actVert->setListAdy(NULL);

    	vert=first;
    	while(vert!=NULL)
    	{
    	   actAdy=findArc(v,vert->getListAdy());
    	   if(actAdy!=NULL)
    	   {
    		   antAdy=actAdy->getPrev();
    		   nextAdy=actAdy->getNext();
    		   if(antAdy==NULL && nextAdy==NULL)
    		   {
    			   vert->setListAdy(NULL);
    		   }
    		   else if(antAdy==NULL && nextAdy!=NULL)
    		   	   {
    			   	   vert->setListAdy(nextAdy);
    			   	   nextAdy->setPrev(NULL);
    			   	   actAdy->setNext(NULL);
    		   	   }
    		   	   else if(antAdy!=NULL && nextAdy==NULL)
    		   	   	   {
    		   		   	   antAdy->setNext(NULL);
    		   		   	   actAdy->setPrev(NULL);
    		   	   	   }
    		   	   	   else
    		   	   	   {
    		   	   		   antAdy->setNext(nextAdy);
    		   	   		   nextAdy->setPrev(antAdy);
    		   	   		   actAdy->setNext(NULL);
    		   	   		   actAdy->setPrev(NULL);
    		   	   	   }
    		   actAdy->setPtrVert(NULL);
    		   delete(actAdy);
    	   }
    	   vert=vert->getNext();
    	}
    	antVert=actVert->getPrev();
    	nextVert=actVert->getNext();
    	if(antVert==NULL && nextVert==NULL)
    	{
    		first=NULL;
    		last=NULL;
    	}
    	else if(antVert==NULL && nextVert!=NULL)
    		{
    			first=nextVert;
    			nextVert->setPrev(NULL);
    			actVert->setNext(NULL);
    		}
    		else if(antVert!=NULL && nextVert==NULL)
    			{
    				last=antVert;
    				antVert->setNext(NULL);
    				actVert->setPrev(NULL);
    			}
    			else
    			{
    				 antVert->setNext(nextVert);
    				 nextVert->setPrev(antVert);
    		   		 actVert->setNext(NULL);
    				 actVert->setPrev(NULL);
    			}
    	delete(actVert);
    	this->nVert--;
    }
}

template <class T>
void Graph<T>::deleteArc(const T &v, const T &w)
{
	NodeVert<T> *actVert;
	NodeAdy<T> *actAdy, *antAdy, *nextAdy;

	actVert=findVert(v,first);
	if(actVert!=NULL)
	{
		actAdy=findArc(w,actVert->getListAdy());
		if(actAdy!=NULL)
		{
			antAdy=actAdy->getPrev();
			nextAdy=actAdy->getNext();
			if(antAdy==NULL && nextAdy==NULL)
			{
				actVert->setListAdy(NULL);
			}
			else if(antAdy==NULL && nextAdy!=NULL)
				{
					actVert->setListAdy(nextAdy);
					actAdy->setNext(NULL);
					nextAdy->setPrev(NULL);
				}
				else if(antAdy!=NULL && nextAdy==NULL)
					{
						actAdy->setPrev(NULL);
						antAdy->setNext(NULL);
					}
					else
					{
						antAdy->setNext(nextAdy);
						nextAdy->setPrev(antAdy);
						actAdy->setNext(NULL);
						actAdy->setPrev(NULL);
					}

				delete(actAdy);
				nArc--;
		}
	}

}
template <class T>
void Graph<T>::replaceVert(const T &x, const T &y )
{
	NodeVert<T> *aux;

	if(first!=NULL)
	{
		aux=findVert(x,first);
		if(aux!=NULL)
		{
			aux->setInfo(y);
		}
	}
}
template <class T>
void Graph<T>::replaceArc(const T &xv, const T &xw, const T &yw, const float cost)
{
	NodeVert<T> *vertOrigen, *vertDestino;
	NodeAdy<T> *actAdy;

	if(first!=NULL)
	{
		vertOrigen=findVert(xv,first);
		vertDestino=findVert(yw,first);
		if(vertOrigen!=NULL && vertDestino!=NULL)
		{
			actAdy=findArc(xw,vertOrigen->getListAdy());
			if(actAdy!=NULL)
			{
				actAdy->setPtrVert(vertDestino);
				actAdy->setCost(cost);
			}
		}
	}
}
#endif /* GRAPH_H */

