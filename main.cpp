//============================================================================
// Name        : ProjectoAEDA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "AgenciaViagens.h"

using namespace std;

int main() {
	enum {
		MAIN,
		CLIENTES,
		VIAGENS,
		GRAVAR,
		CARREGAR,
		SAIR
	};

	Agencia a1;

	bool done = false;

	while (!done) {
		cout << "1 - Clientes\n2 - Viagens\n3 - Gravar\n4 - Carregar\n5 - Sair\n";
		cout << "Escolha uma opcao: ";

		int x;
		cin >> x;
		cin.ignore(); cin.clear();

		if (x == CLIENTES) {
			cout << endl << endl;
			cout << "1 - Ver Lista de Clientes\n2 - Adicionar Cliente Particular\n3 - Adicionar Cliente Comercial\n4 - Remover Cliente\n5 - Ver Historico de Cliente\n";
			cout << "Escolha uma opcao: ";

			int y;
			cin >> y;
			cin.ignore(); cin.clear();

			if (y == 1) {
				cout << endl << endl;
				a1.mostrarClientes();
			} else if (y == 2) {
				cout << endl << endl;
				cout << "Nome do Cliente a Adicionar: ";
				string s;
				getline(cin, s);
				ClienteParticular *c1 = new ClienteParticular(s);
				a1.adicionaCliente(c1);
			} else if (y == 3) {
				cout << endl << endl;
				cout << "Nome do Cliente a Adicionar: ";
				string s;
				getline(cin, s);
				ClienteComercial *c1 = new ClienteComercial(s);
				a1.adicionaCliente(c1);
			} else if (y == 4) {
				cout << endl << endl;
				cout << "Nome do Cliente a Remover: ";
				string s;
				getline(cin, s);
				a1.apagaCliente(s);
			} else if (y == 5) {
				cout << endl << endl;
				cout << "Nome do Cliente: ";
				string s;
				getline(cin, s);
				try {
					a1.mostrarHistorico(s);
				}
				catch (Agencia::ExcecaoClienteNaoExistente &e){
					cout << "Nao existe o cliente " << s << endl;
				}
			} else {
				cout << "Opcao nao existente\n";
			}
		} else if (x == VIAGENS) {
			cout << endl << endl;
			cout << "1 - Ver Trocos\n2 - Adicionar Troco\n3 - Ver Pacotes\n4 - Vender Viagem\n5 - Vender Pacote\n6 - Adicionar Alojamento\n";
			cout << "Escolha uma opcao: ";

			int y;
			cin >> y;
			cin.ignore(); cin.clear();

			if (y == 1) {
				cout << endl << endl;
				a1.mostrarTrocos();
			} else if (y == 2) {
				cout << endl << endl;
				string origem, destino, transporte;
				float preco;

				cout << "Origem? ";
				cin >> origem;
				cin.ignore(); cin.clear();

				cout << "Destino? ";
				cin >> destino;
				cin.ignore(); cin.clear();

				cout << "Transporte? ";
				cin >> transporte;
				cin.ignore(); cin.clear();

				cout << "Preco? ";
				cin >> preco;
				cin.ignore(); cin.clear();

				Troco t1(origem, destino, transporte, preco);
				a1.adicionarTroco(t1);
			} else if (y == 3) {
				cout << endl << endl;
				a1.mostrarPacotes();
			} else if (y == 4) {
				cout << endl << endl;
				string origem, destino, nomeCliente, alojamento;
				int numParticipantes;

				cout << "Origem? ";
				cin >> origem;
				cin.ignore(); cin.clear();

				cout << "Destino? ";
				cin >> destino;
				cin.ignore(); cin.clear();

				cout << "Nome do Cliente? ";
				getline(cin, nomeCliente);

				cout << "Alojamento? (NULO se nao quiser aloamento) ";
				cin >> alojamento;
				cin.ignore(); cin.clear();

				cout << "Numero de Participantes? ";
				cin >> numParticipantes;
				cin.ignore(); cin.clear();

				try {
					a1.venderViagem(nomeCliente, origem, destino, alojamento, numParticipantes);
				}
				catch (Agencia::ExcecaoClienteNaoExistente& e) {
					cout << "Cliente nao existente\n";
				}
				catch (Agencia::ExcecaoOrigemNaoExistente& e) {
					cout << "Origem nao existente\n";
				}
				catch (Agencia::ExcecaoDestinoNaoExistente& e) {
					cout << "Destino nao existente\n";
				}
				catch (Agencia::ExcecaoAlojamentoNaoDisponivel& e) {
					cout << "Alojamento nao disponivel no destino selecionado\n";
				}
				catch (Agencia::ExcecaoCaminhoNaoExistente& e) {
					cout << "Caminho inexistente entre a origem e o destino selecionados\n";
				}

			} else if (y == 5) {
				cout << endl << endl;
				string origem, destino, nomeCliente;
				int numParticipantes;

				cout << "Origem? ";
				cin >> origem;
				cin.ignore(); cin.clear();

				cout << "Destino? ";
				cin >> destino;
				cin.ignore(); cin.clear();

				cout << "Nome do Cliente? ";
				getline(cin, nomeCliente);

				cout << "Numero de Participantes? ";
				cin >> numParticipantes;
				cin.ignore(); cin.clear();

				try {
					a1.venderPacote(nomeCliente, origem, destino, numParticipantes);
				}
				catch (Agencia::ExcecaoClienteNaoExistente& e) {
					cout << "Cliente nao existente\n";
				}
				catch (Agencia::ExcecaoOrigemNaoExistente& e) {
					cout << "Origem nao existente\n";
				}
				catch (Agencia::ExcecaoDestinoNaoExistente& e) {
					cout << "Destino nao existente\n";
				}
				catch (Agencia::ExcecaoAlojamentoNaoDisponivel& e) {
					cout << "Alojamento nao disponivel no destino selecionado\n";
				}
				catch (Agencia::ExcecaoCaminhoNaoExistente& e) {
					cout << "Caminho inexistente entre a origem e o destino selecionados\n";
				}
			} else if (y == 6) {
				cout << endl << endl;
				string tipo, local;
				float preco;

				cout << "Tipo? ";
				cin >> tipo;
				cin.ignore(); cin.clear();

				cout << "Local? ";
				cin >> local;
				cin.ignore(); cin.clear();

				cout << "Preco? ";
				cin >> preco;
				cin.ignore(); cin.clear();

				Alojamento al1(tipo, local, preco);
				a1.adicionarAlojamento(al1);
			} else {
				cout << "Opcao nao existente\n";
			}
		} else if (x == GRAVAR) {
			cout << endl << endl;
			string fp = "";
			cout << "Nome do ficheiro: ";
			getline(cin, fp);
			a1.gravarAgencia(fp);
		} else if (x == CARREGAR) {
			cout << endl << endl;
			string fp = "";
			cout << "Nome do ficheiro: ";
			getline(cin, fp);
			a1.carregarAgencia(fp);
		} else if (x == SAIR) {
			done = true;
		} else {
			cout << "Opcao nao existente\n\n\n";
		}
	}
}
