#include "AgenciaViagens.h"
#include "sequentialSearch.h"

Viagem::Viagem(Itinerario itinerario)
{
	this->itinerario = itinerario;
	preco = itinerario.getPreco();
	alojamento = Alojamento("NULO", "NULO", 0);
}

string Viagem::getOrigem()
{
	return itinerario.getOrigem();
}

string Viagem::getDestino()
{
	return itinerario.getDestino();
}

Itinerario Viagem::getItinerario() {
	return itinerario;
}

float Viagem::getPreco() {
	return preco;
}

void Viagem::setPreco(float preco) {
	this->preco = preco;
}

void Viagem::mostrar() {
	cout << "Viagem Normal: \n";
	cout << "Origem: " << getOrigem() << " Destino: " << getDestino() << " Preco: " << preco << endl;
	if (alojamento.getNome() != "NULO") {
		cout << "Alojamento: " << alojamento.getNome() << endl;
	} else {
		cout << "Alojamento: Sem Alojamento" << endl;
	}
	itinerario.mostrar();
	cout << endl;
}

void Viagem::adicionarAlojamento(Alojamento alojamento) {
	this->alojamento = alojamento;
	preco += alojamento.getPreco();
}

Alojamento Viagem::getAlojamento() {
	return alojamento;
}
