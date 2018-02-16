/*
 * centrality.cpp
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
void printList(list<string> l)
{
	list<string>:: iterator it = l.begin();
	while( it != l.end())
	{
		cout <<" "<<*it++;
	}
}

void printVector(vector<float> vect)
{
	for (unsigned i=0; i<vect.size(); i++)
	{
		cout<<setprecision(3)<<fixed;
		cout<<vect.at(i)<<" ";
	}

}

void print(vector<float> vect, list<string> l, int n)
{
	int i=0;
	list<string>:: iterator it = l.begin();
	cout<<"****************"<<endl;
	cout<<"*    Caso #"<<n<<" *"<<endl;
	cout<<"****************"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"     Nombre              EC"<<endl;
	cout<<"-----------------------------"<<endl;
	while( it != l.end())
	{
		cout<<setprecision(3)<<fixed;
		cout<<setw(20)<<*it++;
		cout<<setw(10)<<vect.at(i);
		cout<<endl;
		
		i++;
	}
	cout<<"----------------------"<<endl;

}
int main() {

	Graph<string> grafo;
	//list<char> lSucces, lPre, r;
	string cad1,cad2;
	char cadena1[80], cadena2[80],x;
	int k,i,n,cases, m;
	float c=0.0;

	cin>>cases;
	for(i=1;i<=cases;i++)
	{
		cin>>m;
		x=cin.get();
		for(k=1;k<=m;k++)
		{
			cin.getline(cadena1,sizeof(cadena2),',');
			x=cin.get();
			cin.getline(cadena2,sizeof(cadena2));
			cad1=cadena1;
			cad2=cadena2;
			if(!grafo.thereVert(cad1))
			{
				grafo.addVert(cad1);
			}
			if(!grafo.thereVert(cad2))
			{
				grafo.addVert(cad2);
			}
			grafo.addArc(cad1,cad2, c);
			grafo.addArc(cad2,cad1,c);			
			
			//cout<<cad1<<" "<<cad2<<endl;
			
		}
		vector<float> result(grafo.orderGraph());
		list<string> vertices;
		
		cout<<endl;
		//grafo.print();
		grafo.centrality(result, vertices);
		print(result,vertices, i);
		//pintList
		grafo.clear();
		cout<<endl;
	}
	return(0);
}
