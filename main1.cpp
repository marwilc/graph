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
#include "graph.h"
using namespace std;

/*
 * 
 */
int main() {

	Graph<int> grafo, grafo1(1), grafo2(2), grafo3(3);
	int i, n=100, p=33;

	for(i=1;i<=10;i++)
	{
		grafo.addVert(i);

	}
	grafo.addArc(1, 2, 1/1);
	grafo.print();
	//cout<<grafo1.getVert();
	//cout<<grafo2.getVert();
	//cout<<grafo3.getVert();
	cout<<endl;

    return (0);
}

