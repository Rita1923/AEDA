#include "AgenciaViagens.h"
#include <iostream>
#include <fstream>


Itinerario::Itinerario()
{
	preco = 0.0;
}

void Itinerario::addTroco(Troco troco)
{
	trocos.push_back(troco);
	preco += troco.getPreco();
}

vector<Troco> Itinerario::getTrocos() {
	return trocos;
}

string Itinerario::getOrigem()
{
	return trocos[0].getOrigem();
}

string Itinerario::getDestino()
{
	return trocos[trocos.size()-1].getDestino();
}

float Itinerario::getPreco() {
	return preco;
}

void Itinerario::mostrar() {
	for (size_t i = 0; i < trocos.size(); i++) {
		cout << trocos[i].getOrigem() << " " << trocos[i].getDestino() << " " << trocos[i].getTransporte() << " " << trocos[i].getPreco() << endl;
	}
}
