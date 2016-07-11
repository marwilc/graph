/*
 * main2.cpp
 *
 *  Created on: Jul 10, 2016 10:48:09 PM
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
void printList(list<char> l)
{
	list<char>:: iterator it = l.begin();
	while( it != l.end())
	{
		cout <<" "<<*it++;
	}
}

void printVector(vector<char> vect)
{
	for (unsigned i=0; i<vect.size(); i++)
		cout<<vect.at(i)<<" ";

}
int main() {

	Graph<char> grafo;
	list<char> lSucces, lPre, r;
	int k,i,n,cases;
	char vert, vertF;
	float c=0.0;

	//srand(time(NULL));
	//num = 1 + rand() % (11 - 1);

	cin>>cases;
	for(k=1;k<=cases;k++)
	{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>vert;
		grafo.addVert(vert);
	}
	for(i=1;i<=n;i++)
	{
		cin>>vert;
		while(cin.get()!='\n')
		{
			cin>>vertF;
			grafo.addArc(vert, vertF, c);
		}
	}

	/*for(i=1;i<=10;i++)
	{
		cout<<setprecision(2)<<fixed;
		cout<<grafo.costArc(1,i)<<endl;
	}
	*/
	vector<int> pred (n), tdesc(n), tfinal(n);
	grafo.print();
	cout<<endl<<endl;
	//grafo.dfs(pred, tdesc, tfinal, r);
	r=grafo.dfsSimple();
	printList(r);
	cout<<endl;
	//grafo.deleteVert('E');
	//r=grafo.dfsSimple();
	//printList(r);
	//cout<<endl;
	//printVector(pred);
	//cout<<endl;
	//printVector(tdesc);
	//cout<<endl;
	//printVector(tfinal);

	//printList(r);

	//grafo.replaceVert(1, 21);
	//grafo.replaceArc(5, 7, 12, 1.33);
	//grafo.deleteArc(5, 20);
	//grafo.replaceArc(5, 12, 20, 2.55);
	//lSucces=grafo.successors(21);
	//printList(lSucces);
	//grafo.print();

	//lPre=grafo.predecessors(10);
	//imprimir lista sucesores====================
	//cout << endl<< "sucesores" << endl;
	//printList(lSucces);
	//cout << endl<< "predecesores" << endl;
	//printList(lPre);

	cout<<endl;
	//============================================
	//grafo.deleteVert(1);
	//grafo.print();
	//cout<<endl;
	grafo.clear();
	}
    return (0);
}
