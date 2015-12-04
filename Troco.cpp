#include "AgenciaViagens.h"
#include "sequentialSearch.h"

Troco::Troco(string origem, string destino, string transporte, float preco)
{
	this->origem=origem;
	this->destino=destino;
	this->transporte=transporte;
	this->preco=preco;
}

string Troco::getOrigem()
{
	return origem;
}

string Troco::getDestino()
{
	return destino;
}

string Troco::getTransporte()
{
	return transporte;
}

float Troco::getPreco()
{
	return preco;
}
