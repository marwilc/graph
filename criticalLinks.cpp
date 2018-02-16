/*
 * criticalLinks.cpp
 *
 *  Created on: Jul 13, 2016 12:20:02 AM
 *      Author: marwilc
 *		
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

void printVector(vector<int> vect)
{
	for (unsigned i=0; i<vect.size(); i++)
		cout<<vect.at(i)<<" ";

}
int main() {

	Graph<int> grafo;
	//list<char> lSucces, lPre, r;
	int k,i,n,cases, nVertices;
	int vert, vertF;
	char p;
	float c=0.0;

	while(cin>>nVertices!=0)
	{
		for(k=1;k<=nVertices;k++)
		{
			cin>>vert;
			cin>>p;
			cin>>n;
			cin>>p;
			if(!grafo.thereVert(vert))
			{
				grafo.addVert(vert);
			}
			for(i=1;i<=n;i++)
			{
				cin>>vertF;
				if(!grafo.thereVert(vertF))
				{
					grafo.addVert(vertF);
				}
				grafo.addArc(vert, vertF, c);
			}
		}

		grafo.print();
		grafo.clear();
		cout<<endl;
	}
	return(0);
}
