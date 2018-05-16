#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#define infinity 9999999999
using namespace std;

double Euclidiandistance(long xA, long yA, long xB, long yB);
class Node {

public:
	string name;
	Node* prox;
	long** rot;
	unsigned int size;
	vector<Node*> candidates;

	Node() {

		size = 0;
		name = "";
		prox = NULL;

	}//Construtor

	Node(string s) {

		size = 0;
		name = s;
		prox = NULL;

	}//constructor

	void setRotSize(unsigned int size);
};

void Node::setRotSize(unsigned int size) {
	this->size = size;
	rot = new long*[size];
	for (unsigned int i = 0; i < size; i++) {
		rot[i] = new long[2];	// Allocate memory for adjacency matrix
	}

	for (unsigned int i = 0; i < size; i++) {
		for (int j = 0; j < 2; j++) {
			rot[i][j] = 0;	// Initialize the vertices to 0
		}
	}
}//setRot

double dist(string pai, Node* city, int x, int y) {
	double retorno = 0;
	for (unsigned int i = 0; i < city->candidates.size(); i++) {
		if (city->candidates.at(i)->name != pai) {
			double shortest = (infinity);
			for (unsigned int j = 0; j < city->candidates.at(i)->size; j++) {
				double d = Euclidiandistance(x ,y, city->candidates.at(i)->rot[j][0], city->candidates.at(i)->rot[j][1]) + dist(city->name, city->candidates.at(i), city->candidates.at(i)->rot[j][0], city->candidates.at(i)->rot[j][1]);
				if (d < shortest) shortest = d;
			}
			if (shortest != (infinity)) {
				retorno += shortest;
			}
		}
	}
	return retorno;
}

double dist(Node* city) {
	double shortest = infinity;
	int x, y;
	for (unsigned int i = 0; i < city->size; i++) {
		x = city->rot[i][0];
		y = city->rot[i][1];
		double d = dist("", city, city->rot[i][0], city->rot[i][1]);
		if (d < shortest) shortest = d;
	}
	return shortest;
}

Node* getcitiestring(string nome, vector<Node*> cities) {
	Node* city = NULL;
	for (unsigned int i = 0; i < cities.size(); i++) {
		if (cities.at(i)->name == nome) {
			city = cities.at(i);
			break;
		}
	}
	return city;
}// getcitiestring

double Euclidiandistance(long xA, long yA, long xB, long yB) {
	return sqrt(pow((xA-xB), 2) + pow((yA-yB), 2));
}// Euclidiandistance

int main(){
	vector<Node*> cities;
	int city, qtdRot, i;
	long x, y;
	string nome, s1, s2;
	do {
		cin >> city;
		if (city > 0) {
			for (i = 0; i < city; i++) {
				cin >> nome;
				cin >> qtdRot;
				cities.push_back(new Node(nome));
				cities.at(i)->setRotSize(qtdRot);
				for (int j = 0; j < qtdRot; j++) {
					cin >> x >> y;
					cities.at(i)->rot[j][0] = x;
					cities.at(i)->rot[j][1] = y;
				}
			}
			for (int j = 0; j < city - 1; j++) {
				cin >> s1 >> s2;
				Node* c1 = getcitiestring(s1, cities);
				Node* c2 = getcitiestring(s2, cities);
				c1->candidates.push_back(c2);
				c2->candidates.push_back(c1);
			}
			cout << round(dist(cities.back()) * 10) / 10 << endl;
			cities.clear();
		}
	}while (city > 0);
	return 0;
}
