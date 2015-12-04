/*
 * Alojamento.cpp
 *
 *  Created on: 07/11/2015
 *      Author: up201404375
 */
#include "AgenciaViagens.h"
#include "sequentialSearch.h"

Alojamento::Alojamento(string nome, string local, float preco)
{
	this->nome=nome;
	this->local=local;
	this->preco=preco;
}

string Alojamento::getNome()
{
	return nome;
}

string Alojamento::getLocal()
{
	return local;
}

float Alojamento::getPreco()
{
	return preco;
}






