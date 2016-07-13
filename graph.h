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
#include <limits>
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
        static list< NodeVert <T>* > successorsPt(NodeVert<T> *v);
        static void taging(NodeVert<T> *ptr, const int &tag);
        static void recorridoDfs(NodeVert<T> *u, vector<char> &color, int &vf);
        static vector<int> getGradeEntry(NodeVert<T> *ptr);
        list< NodeVert <T>* > predecessorsPtr(const T &v);
        list< NodeVert <T>* > successorsPtr(const T &v);//
        void dfsVisit(NodeVert<T> *u, vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, vector<char> &color, int &tiempo, list<T> &r);
        void dfsSimpleVisit(NodeVert<T> *u, list<T> &r, vector<char> &color);


    public:
        //Constructor's
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
        bool thereCyclesGraphDirect();//solo para grafos dirigidos
        bool itIsAdjacent(const T &v, const T &w);//verifica si dos vertices son adyacentes
        bool itIsIsolated(const T &v);//verifica si un vertice es de grado cero(aislado)
        bool itIsSource(const T &v);//verifica si un vertice es fuente (sin arcos de entrada)
        bool itIsSunken(const T &v);// verifica si un vertice es sumidero (sin arcos de salida)
        float costArc(const T &v, const T &w)const;//listo
        int orderGraph()const{return(this->nVert);};//listo
        int nArcs()const {return(this->nArc);};
        int gradeIn(const T &v); // grado de entrada de un vertice(cantidad de arcos que llegan a el)
        int gradeOut(const T &v);// grado de salida de un vertice (cantidad de arcos que salen de el)
        int grade(const T &v);// grado total del vertice(cantidad de arcos de entrada mas la cantidad de arcos de salida)
        void print();//listo
        list<T> predecessors(const T &v)const;//listo
        list<T> successors(const T &v)const;//listo
        list<T> storageSuccesors();
        //modificadores
        void setG(NodeVert<T> *ptr);//innesesaria
        void addVert(const T &v);//listo
        void addArc(const T &v, const T &w, const float &c);//listo
        void deleteVert(const T &v);//listo
        void deleteArc(const T &v, const T &w);//listo
        void replaceVert(const T &x, const T &y);//listo
        void replaceArc(const T &xv, const T &xw, const T &yw, const float cost);//listo
        //recorridos
        list<T> dfsSimple();//listo
        list<T> dfsSimple(const T &v);//listo
        void dfs(vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, list<int> &r);//listoS
        void bfs(const T &s, vector<int> &dist, vector<int> &pred, list<T> &r);//listo
        //ordenamiento
        list<T> topologicalSort();
};
// Methods privates
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
list<NodeVert <T>* > Graph<T>::successorsPt(NodeVert<T> *v)
{
    list<NodeVert <T>* > p;
    NodeAdy<T> *auxAdy;

    if(v!=NULL)
    {
        auxAdy=v->getListAdy();
        while(auxAdy!=NULL )
        {
        	p.push_back(auxAdy->getPtrVert());
        	auxAdy=auxAdy->getNext();
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
			r.push_back(v->getInfo());
			pred[v->getTag()-1]=u->getTag();
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
template <class T>
void Graph<T>::recorridoDfs(NodeVert<T> *u, vector<char> &color, int &vf)// recorrido para ver si hay ciclos en un grafo dirigido
{

	list< NodeVert <T>* > l;
	NodeVert<T> *v;

	color[u->getTag()-1]='g';
	l=successorsPt(u);
	while(!l.empty())
	{
		v=l.front();
		l.pop_front();
		vf=v->getTag();
		if(color.at(v->getTag()-1)=='\0')
		{
			recorridoDfs(v, color, vf);
		}
	}
	color[u->getTag()-1]='n';
}

template <class T>
vector<int> Graph<T>::getGradeEntry(NodeVert<T> *ptr)
{
	vector<int> grades;

	while(ptr!=NULL)
	{
		grades.push_back(ptr->getGradeIn());
		ptr=ptr->getNext();
	}
	return(grades);
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
            antVert->setGradeIn(0);
            antVert->setGradeOut(0);
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
	        	cout<<auxVert->getTag()<<"  ("<<auxVert->getInfo()<<")";
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
template <class T>
bool Graph<T>:: thereCyclesGraphDirect()
{
	NodeVert<T> *vert;
	int vf;
	bool band=false;
	if(this->first!=NULL)
	{
		vert=first;
		while(vert!=NULL && !band)
		{
			vector<char> color(this->nVert);
			recorridoDfs(vert,color, vf);
			if(vert->getTag()==vf)
			{
				band=true;
			}
			vf=-1;
			vert=vert->getNext();

		}
	}
	return(band);
}

template <class T>
bool Graph<T>:: itIsAdjacent(const T &v, const T &w)
{
	return(this->thereArc(v, w));
}
template <class T>
bool Graph<T>::itIsIsolated(const T &v)
{
	NodeVert<T> *vert;
	bool band=false;

	vert=findVert(v,this->first);
	if(vert!=NULL)
	{
		if(vert->getGradeIn()+vert->getGradeOut()==0)
			band=true;
	}
	return(band);
}
template <class T>
bool Graph<T>::itIsSource(const T &v)
{
	NodeVert<T> *vert;
	bool band=false;

	vert=findVert(v,this->first);
	if(vert!=NULL)
	{
		if(vert->getGradeIn()==0)
			band=true;
	}
	return(band);
}
template <class T>
bool Graph<T>::itIsSunken(const T &v)
{
	NodeVert<T> *vert;
	bool band=false;

	vert=findVert(v,this->first);
	if(vert!=NULL)
	{
		if(vert->getGradeOut()==0)
			band=true;
	}
	return(band);
}
template <class T>
int Graph<T>:: gradeIn(const T &v)
{
		NodeVert<T> *vert;
		int entero=0;

		vert=findVert(v,this->first);
		if(vert!=NULL)
		{
			entero=vert->getGradeIn();
		}
		return(entero);
}

template <class T>
int Graph<T>:: gradeOut(const T &v)
{
		NodeVert<T> *vert;
		int entero=0;

		vert=findVert(v,this->first);
		if(vert!=NULL)
		{
			entero=vert->getGradeOut();
		}
		return(entero);
}
template<class T>
int Graph<T>:: grade(const T &v)
{
		NodeVert<T> *vert;
		int entero=0;

		vert=findVert(v,this->first);
		if(vert!=NULL)
		{
			entero=(vert->getGradeOut()+vert->getGradeIn());
		}
		return(entero);
}
template <class T>
list<T> Graph<T>:: storageSuccesors()
{
	NodeVert<T> *vert;
	NodeAdy<T> *ady;
	list<T> l;
	if(this->first!=NULL)
	{
		vert=first;
		for(int i=1;i<=this->nVert;i++)
		{
			ady=vert->getListAdy();
			while(ady!=NULL)
			{
				l.push_back(ady->getPtrVert()->getInfo());
				ady=ady->getNext();
			}
			vert=vert->getNext();
		}
	}
	return(l);
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
    	vertA->setGradeOut(vertA->getGradeOut()+1);
    	vertB->setGradeIn(vertB->getGradeIn()+1);
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
    		antAdy->getPtrVert()->setGradeIn(antAdy->getPtrVert()->getGradeIn()-1);
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
    		   actVert->setGradeOut(actVert->getGradeOut()-1);
    		   actAdy->setPtrVert(NULL);
    		   actAdy->setCost(0.0);
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
    	actVert->setGradeIn(0);
    	actVert->setGradeOut(0);
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
			actVert->setGradeOut(actVert->getGradeOut()-1);
			actAdy->getPtrVert()->setGradeIn(actAdy->getPtrVert()->getGradeIn()-1);
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
				actAdy->setPtrVert(NULL);
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
				vertDestino->setGradeIn(vertDestino->getGradeIn()+1);
				actAdy->getPtrVert()->setGradeIn(actAdy->getPtrVert()->getGradeIn()-1);
				actAdy->setPtrVert(vertDestino);
				actAdy->setCost(cost);
			}
		}
	}
}

template <class T>
list<T> Graph<T>:: topologicalSort()
{
	vector<int> gradeEntry(this->nVert);
	queue<NodeVert <T> *> c;
	list<NodeVert <T> *> l;
	list<T> ord;
	NodeVert<T> *vert, *u,*v;

	if(this->first!=NULL)
	{
		vert=this->first;
		gradeEntry=getGradeEntry(vert);
		for(int i=1;i<=this->nVert;i++)
		{
			if(gradeEntry.at(vert->getTag()-1)==0)
			{
				c.push(vert);
			}
			vert=vert->getNext();
		}
		while(!c.empty())
		{
			u=c.front();
			c.pop();
			ord.push_back(u->getInfo());
			l=successorsPt(u);
			while(!l.empty())
			{
				v=l.front();
				l.pop_front();
				gradeEntry[v->getTag()-1]=gradeEntry[v->getTag()-1]-1;
				if(gradeEntry.at(v->getTag()-1)==0)
				{
					c.push(v);
				}
			}
		}
	}
	return(ord);


}
template <class T>
void Graph<T>::dfs(vector<int> &pred, vector<int> &tdesc, vector<int> &tfinal, list<int> &r)
{
	int tiempo, i;
	vector<char> color (this->orderGraph());
	NodeVert<T> *aux;

	if(first!=NULL)
	{
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
}

template <class T>
list<T> Graph<T> ::dfsSimple()
{

	int i;
	list<T> r;
	vector<char> color (this->orderGraph());
	NodeVert<T> *aux;

	if(first!=NULL)
	{
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
	}
	return(r);
}

template <class T>
list<T> Graph<T> ::dfsSimple( const T &v)
{

	int i;
	list<T> r;
	vector<char> color (this->orderGraph());
	NodeVert<T> *aux;

	aux=findVert(v,first);
	if(aux!=NULL)
	{

		for(i=1;i<=this->orderGraph();i++)
		{
			color[i-1]='b';
		}
		r.push_back(aux->getInfo());
		this->dfsSimpleVisit(aux,r, color);
	}
	return(r);
}


template <class T>
void Graph<T>::bfs(const T &s, vector<int> &dist, vector<int> &pred, list<T> &r)
{
	//int max=numeric_limits<int>::max();
	int i;
	NodeVert<T> *aux, *v, *u;
	queue<NodeVert<T> *> c;
	list< NodeVert <T> *> l;
	vector<char> color(this->orderGraph());


	aux=findVert(s, first);
	if(aux!=NULL)
	{
		for(i=0;i<this->orderGraph();i++)
		{
			color[i]='b';
			dist[i]=-1;
		}
		color[aux->getTag()-1]='g';
		dist[aux->getTag()-1]=0;
		c.push(aux);
		r.push_back(s);
		while(!c.empty())
		{
			u=c.front();
			c.pop();
			l=this->successorsPtr(u->getInfo());
			while(!l.empty())
			{
				v=l.front();
				l.pop_front();
				if(color[v->getTag()-1]=='b')
				{

					color[v->getTag()-1]='g';
					dist[v->getTag()-1]=dist[u->getTag()-1]+1;
					pred[v->getTag()-1]=u->getTag();
					c.push(v);
				}

			}
			r.push_back(u->getInfo());
			color[u->getTag()-1]='n';
		}
	}
}
#endif /* GRAPH_H */

