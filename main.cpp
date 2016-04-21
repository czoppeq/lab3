// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	vectorOfSlavs.push_back(&slavs[0]);
	
	srand(time(NULL));
	for (int i=1;i<n;i++)
	{
		int x=rand()%(vectorOfSlavs.size()+1);
		vectorOfSlavs.insert(vectorOfSlavs.begin()+x,&slavs[i]);}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector <Slav *>:: iterator it=vectorOfSlavs.begin();
	for (it;it!=vectorOfSlavs.end();it++)
		cout<<(**it).description()<<endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for (int i=0;i<n;i++)
	setOfSlavs.insert(vectorOfSlavs[i]);
	vectorOfSlavs.clear();
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	for (set<Slav*>::iterator it_set=setOfSlavs.begin();
	it_set!=setOfSlavs.end();)
	{	
		mapOfSlavs[*it_set]=*(it_set=setOfSlavs.erase(it_set));
		it_set=setOfSlavs.erase(it_set);
	}
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian	
	for (map<Slav*,Slav*>::iterator it_set=mapOfSlavs.begin(); 				it_set!=mapOfSlavs.end(); it_set++)
 	{
 	cout<<(*(*it_set).first).description()<<"---";
	cout<<(*(*it_set).second).description()<<endl;
	}
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for (int i=0; i<n;i++)
	{
		queueOfSlavs.push(&slavs[i]);		
	}
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while(!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
		while(!stackOfSlavs.empty())
	{
		cout<<stackOfSlavs.top()->description()<<endl	;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
