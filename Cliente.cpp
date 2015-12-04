#include "AgenciaViagens.h"
#include <iostream>
#include <string>

//Cliente Comercial

int Cliente::contarNomes(string nome) {
	istringstream iss(nome);
	string n;
	int count = 0;
	while (iss >> n) { count++; };
	return count;
}

void Cliente::adicionarViagem(Viagem* viagem, int n) {
	viagens.push_back(viagem);
}

float ClienteParticular::calcDesconto(){
	return 0;
}

float ClienteComercial::calcDesconto(){
	if(viagens.size() > 5 && mediaParticipantes > 10)
		return 0.05;
	else if(viagens.size() > 5 && mediaParticipantes > 15)
		return 0.10;
	else
		return 0;
}

void ClienteComercial::adicionarViagem(Viagem* viagem, int n) {
	viagens.push_back(viagem);
	totalParticipantes += n;
	mediaParticipantes = totalParticipantes / viagens.size();
}

string ClienteComercial::infoString() {
	string s = "";
	ostringstream oss(s);
	oss << contarNomes(nome) << " " << nome << " Comercial " << mediaParticipantes << " " << totalParticipantes << " " << viagens.size() << " ";
	for (size_t i = 0; i < viagens.size(); i++) {
		vector<Troco> t = viagens[i]->getItinerario().getTrocos();
		oss << viagens[i]->getPreco() << " " << viagens[i]->getAlojamento().getNome() << " ";
		oss << t.size() << " ";
		for (size_t j = 0; j < t.size(); j++) {
			oss << t[j].getOrigem() << " " << t[j].getDestino() << " " << t[j].getTransporte() << " " << t[j].getPreco() << " ";
		}
	}

	return oss.str();
}

string ClienteParticular::infoString() {
	string s = "";
	ostringstream oss(s);
	oss << contarNomes(nome) << " " << nome << " Particular " << viagens.size() << " ";
	for (size_t i = 0; i < viagens.size(); i++) {
		vector<Troco> t = viagens[i]->getItinerario().getTrocos();
		oss << viagens[i]->getPreco() << " " << viagens[i]->getAlojamento().getNome() << " ";
		oss << t.size() << " ";
		for (size_t j = 0; j < t.size(); j++) {
			oss << t[j].getOrigem() << " " << t[j].getDestino() << " " << t[j].getTransporte() << " " << t[j].getPreco() << " ";
		}
	}

	return oss.str();
}

void Cliente::mostrarHistorico() {
	cout << nome << endl << endl;
	for (size_t i = 0; i < viagens.size(); i++) {
		viagens[i]->mostrar();
	}
}
