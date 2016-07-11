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
#include <vector>
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
        list< NodeVert <T>* > predecessorsPtr(const T &v);
        list< NodeVert <T>* > successorsPtr(const T &v);//
        void dfsVisit(NodeVert<T> *u, vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, vector<char> &color, int &tiempo, list<T> &r);
        void dfsSimpleVisit(NodeVert<T> *u, list<T> &r, vector<char> &color);
        static void taging(NodeVert<T> *ptr, const int &tag);

    public:
        //constructores
        Graph():first(NULL),last(NULL), nVert(0), nArc(0){};
        Graph(const T &e);
        //Graph(list<T> &listVert, list<T> &listArc);
        //destructores
        ~Graph();
        void clear();//listo
        //consultores
        NodeVert<T>* getG()const {return(this->first);};//listo
        bool isEmpty()const {return(this->first==NULL);}//listo
        bool thereVert(const T &v)const;//listo
        bool thereArc(const T &v, const T &w)const;//listo
        float costArc(const T &v, const T &w)const;//listo
        int orderGraph()const{return(this->nVert);};//listo
        list<T> predecessors(const T &v)const;//listo
        list<T> successors(const T &v)const;//listo
        //list< NodeVert <T>* > succesors(const T&v)const;//
        //list< NodeVert <T>* > predecessors(const T&v)const;
        void print();//listo
        //modificadores
        void setG(NodeVert<T> *ptr);//innesesaria
        void addVert(const T &v);//listo
        void addArc(const T &v, const T &w, const float &c);//listo
        void deleteVert(const T &v);//listo
        void deleteArc(const T &v, const T &w);//listo
        void replaceVert(const T &x, const T &y);//listo
        void replaceArc(const T &xv, const T &xw, const T &yw, const float cost);//listo
        //recorridos
        list<T> dfsSimple();
        void dfs(vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, list<int> &r);//listoS
       //void dfsVisit(NodeVert<T> *u, vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, vector<char> &color, int &tiempo, list<T> &r);
        void bfs();
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

template <class T>
list< NodeVert <T>* > Graph<T>::predecessorsPtr(const T& v)
{
    list<NodeVert <T>* > p;
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
                    p.push_back(auxVert);
                }
            auxVert=auxVert->getNext();
        }
    }
    return (p);
}

template <class T>
list<NodeVert <T>* > Graph<T>::successorsPtr(const T& v)
{
    list<NodeVert <T>* > p;
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
                    p.push_back(auxAdy->getPtrVert());
                    auxAdy=auxAdy->getNext();
                }
            }
    }
    return (p);
}

template <class T>
void Graph<T>::dfsVisit(NodeVert<T> *u, vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, vector<char> &color, int &tiempo, list<T> &r)
{
	list< NodeVert <T>* > l;
	NodeVert<T> *v;

	color[u->getTag()-1]='g';
	tiempo++;
	tdesc[u->getTag()-1]=tiempo;
	l=this->successorsPtr(u->getInfo());
	while(!l.empty())
	{
		v=l.front();
		l.pop_front();
		if(color.at(v->getTag()-1)=='b')
		{
			pred[v->getTag()-1]=u->getTag();
			r.push_back(v->getInfo());
			this->dfsVisit(v, pred, tdesc, tfinal, color, tiempo, r);

		}
	}
	color[u->getTag()-1]='n';
	tiempo++;
	tfinal[u->getTag()-1]=tiempo;
}
template <class T>
void Graph<T>::dfsSimpleVisit(NodeVert<T> *u, list<T> &r, vector<char> &color)
{

	list< NodeVert <T>* > l;
	NodeVert<T> *v;

	color[u->getTag()-1]='g';
	l=this->successorsPtr(u->getInfo());
	while(!l.empty())
	{
		v=l.front();
		l.pop_front();
		if(color.at(v->getTag()-1)=='b')
		{
			r.push_back(v->getInfo());
			this->dfsSimpleVisit(v, r, color);
		}
	}
	color[u->getTag()-1]='n';
}
template <class T>
void Graph<T>::taging(NodeVert<T> *ptr, const int &tag)
{
	int i=tag;

	while(ptr!=NULL)
	{
		ptr->setTag(i);
		ptr=ptr->getNext();
		i++;

	}

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
    //NodeVert<T> *auxVert, *antVert;
    //NodeAdy<T> *auxAdy, *antAdy;
    
    this->clear();
   /* if(this->first!=NULL)
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
    }*/
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
            antVert->setTag(0);
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
        newVert->setTag(1);
    }
    else if(antVert==NULL && nextVert!=NULL)
    	{
    		first=newVert;
    		nextVert->setPrev(newVert);
    		newVert->setNext(nextVert);
    		taging(first,nextVert->getTag());
    	}
    	else if(antVert!=NULL && nextVert==NULL)
    		{
    			last=newVert;
    			antVert->setNext(newVert);
    			newVert->setPrev(antVert);
    			newVert->setTag(antVert->getTag()+1);
    		}
    		else
    		{
    			newVert->setNext(nextVert);
    			newVert->setPrev(antVert);
    			antVert->setNext(newVert);
    			nextVert->setPrev(newVert);
    			taging(newVert,antVert->getTag()+1);
    		}
    //newVert->setTag(nVert+1);
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
    int tag;

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
    	tag=actVert->getTag();
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
    			taging(first,tag);
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
    				 taging(nextVert,tag);
    			}
    	actVert->setTag(0);
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

template <class T>
void Graph<T>::dfs(vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, list<int> &r)
{
	int tiempo, i;
	vector<char> color (this->orderGraph());
	NodeVert<T> *aux;

	for(i=1;i<=this->orderGraph();i++)
	{
		color[i-1]='b';
		//pred[i-1]=0;
	}

	tiempo=0;
	aux=this->first;
	r.push_back(aux->getInfo());
	for(i=1;i<=this->orderGraph();i++)
	{
		if(color.at(aux->getTag()-1)=='b')
		{
			this->dfsVisit(aux, pred, tdesc, tfinal, color, tiempo, r);
		}
		aux=aux->getNext();
	}
}

template <class T>
list<T> Graph<T> ::dfsSimple()
{

	int i;
	list<T> r;
	vector<char> color (this->orderGraph());
	NodeVert<T> *aux;

	for(i=1;i<=this->orderGraph();i++)
	{
			color[i-1]='b';
	}

	aux=this->first;
	r.push_back(aux->getInfo());
	for(i=1;i<=this->orderGraph();i++)
	{
		if(color.at(aux->getTag()-1)=='b')
		{
			this->dfsSimpleVisit(aux,r, color);
		}
		aux=aux->getNext();
	}
	return(r);
}
#endif /* GRAPH_H */

