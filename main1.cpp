/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marwilc
 *
 * Created on 15 de junio de 2016, 09:54 PM
 */

#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graph.h"
using namespace std;

/*
 * 
 */
void printList(list<int> l)
{
	list<int>:: iterator it = l.begin();
	while( it != l.end())
	{
		cout <<" "<<*it++;
	}
}
int main() {

	Graph<int> grafo, grafo1(1), grafo2(2), grafo3(3);
	int i,num;
	list<int> lSucces, lPre;
	float n=100, p=5.2, c;
	srand(time(NULL));
	for(i=1;i<=10;i++)
	{
		grafo.addVert(i);

	}
	for(i=1;i<=10;i++)
	{
		num = 1 + rand() % (11 - 1);
		c=(float)pow(num,2)+p;
		grafo.addArc(i, num, c);
		p=+cos(p);
	}

	for(i=1;i<=10;i++)
	{
		cout<<setprecision(2)<<fixed;
		cout<<grafo.costArc(1,i)<<endl;
	}
	grafo.print();
	lSucces=grafo.successors(1);
	lPre=grafo.predecessors(10);
	//imprimir lista sucesores====================
	cout << endl<< "sucesores" << endl;
	printList(lSucces);
	cout << endl<< "predecesores" << endl;
	printList(lPre);

	cout<<endl;
	//============================================
	grafo.deleteVert(1);
	grafo.print();
	cout<<endl;
    return (0);
}

