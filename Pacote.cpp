/*
 * Pacote.cpp
 *
 *  Created on: 07/11/2015
 *      Author: up201404375
 */

#include "AgenciaViagens.h"
#include "sequentialSearch.h"


Pacote::Pacote(Itinerario itinerario, float preco):Viagem(itinerario)
{
	this->preco=preco;
	//alojamento = 0;
}

Pacote::Pacote(Itinerario itinerario, float preco, Alojamento &alojamento):Viagem(itinerario)
{
	this->preco=preco;
	//this->alojamento = alojamento;
}

void Pacote::mostrar() {
	cout << "Pacote Promocional: \n";
	cout << "Origem: " << getOrigem() << " Destino: " << getDestino() << " Preco: " << getPreco() << endl;
	if (alojamento.getNome() != "NULO") {
		cout << "Alojamento: " << alojamento.getNome() << endl;
	} else {
		cout << "Alojamento: Sem Alojamento" << endl;
	}
	itinerario.mostrar();
	cout << endl;
}

string Pacote::infoString() {
	string s = "";
	ostringstream oss(s);
	oss << preco << " " << alojamento.getNome() << " " << itinerario.getTrocos().size() << " ";
	for (size_t i = 0; i < itinerario.getTrocos().size(); i++) {
		oss << itinerario.getTrocos()[i].getOrigem() << " " << itinerario.getTrocos()[i].getDestino() << " " << itinerario.getTrocos()[i].getTransporte() << " " << itinerario.getTrocos()[i].getPreco() << " ";
	}

	return oss.str();
}
