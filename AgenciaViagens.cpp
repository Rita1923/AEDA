#include "AgenciaViagens.h"
#include "sequentialSearch.h"
#include <iostream>
#include <fstream>

using namespace std;

Agencia::Agencia(){}

int Agencia::numViagens() const
{
	return pacotes.size();
}

int Agencia::numClientes() const
{
	return clientes.size();
}

void Agencia::adicionarPacote(Pacote pacote)
{
	pacotes.push_back(pacote);
}

void Agencia::venderPacote(string nomeCliente, string origem, string destino, int n)
{
	vector<string> nomes;

	for(size_t i=0; i<clientes.size(); i++) {
		nomes.push_back(clientes[i]->getNome());
	}
	int index = sequentialSearch(nomes, nomeCliente);

	if(index == -1)
		throw ExcecaoClienteNaoExistente();

	for(size_t i=0; i<pacotes.size(); i++) {
		if(pacotes[i].getOrigem() == origem) {
			if(pacotes[i].getDestino() == destino) {
				clientes[index]->adicionarViagem(&pacotes[i], n);
				return;
			}
		}
	}

	throw ExcecaoPacoteNaoExistente();
}


void Agencia::adicionaCliente(Cliente* cli){
	clientes.push_back(cli);
}

bool Agencia::apagaCliente(string nomeCli){
	for(int i=0; i<clientes.size(); i++){
		if(clientes[i]->getNome() == nomeCli){
			clientes.erase(clientes.begin()+i);
			return true;
		}
	}

	return false;
}

vector<Cliente*> Agencia::getClientes(){
	return clientes;
}

vector<int> Agencia::getAdjacentes(int indice) {
	vector<int> indices;
	for (size_t i = 1; i < caminhos[indice].size(); i++) {
		for (size_t j = 0; j < caminhos.size(); j++) {
			if (caminhos[indice][i].valor == caminhos[j][0].valor) {
				indices.push_back(j);
			}
		}
	}
	return indices;
}

vector< vector<Agencia::node> > Agencia::getCaminhos() {
	return caminhos;
}

void Agencia::adicionarTroco(Troco troco) {
	trocos.push_back(troco);

	/* Adiciona a origem a lista de adjacencias, se ainda nao existir */
	int origemEncontrada = 1;
	for (size_t i = 0; i < caminhos.size(); i++) {
		if (caminhos[i][0].valor == troco.getOrigem()) {
			node n1 = { troco.getDestino(), -1 };
			caminhos[i].push_back(n1);
			origemEncontrada = 0;
		}
	}

	if (origemEncontrada == 1) {
		node n1 = { troco.getOrigem(), -1 };
		node n2 = { troco.getDestino(), -1 };
		vector<node> temp;
		temp.push_back(n1);
		temp.push_back(n2);
		caminhos.push_back(temp);
	}

	/* Adiciona o destino a lista de adjacencias, se ainda nao existir */
	int destinoEncontrado = 1;
	for (size_t i = 0; i < caminhos.size(); i++) {
		if (caminhos[i][0].valor == troco.getDestino()) {
			destinoEncontrado = 0;
		}
	}

	if (destinoEncontrado == 1) {
		node n1 = { troco.getDestino(), -1 };
		vector<node> temp;
		temp.push_back(n1);
		caminhos.push_back(temp);
	}
}

vector<string> Agencia::encontrarCaminho(string origem, string destino) {
	for (size_t i = 0; i < caminhos.size(); i++) {
		for (size_t j = 0; j < caminhos[i].size(); j++) {
			caminhos[i][j].parente = -1;
		}
	}


	int indice = -1;
	for (size_t i = 0; i < caminhos.size(); i++) {
		if (caminhos[i][0].valor == origem) {
			indice = i;
		}
	}

	queue<int> q;
	q.push(indice);

	vector<string> visitados;
	visitados.push_back(caminhos[indice][0].valor);

	bool done = false;
	int indiceDestino = -1;

	while (!q.empty() && !done) {
		int temp = q.front();
		q.pop();

		vector<int> adj = getAdjacentes(temp);
		for (size_t i = 0; i < adj.size(); i++) {
			int visitado = 0;
			for (size_t j = 0; j < visitados.size(); j++) {
				if (visitados[j] == caminhos[adj[i]][0].valor)
					visitado = 1;
			}

			if (visitado == 0) {
				visitados.push_back(caminhos[adj[i]][0].valor);
				caminhos[adj[i]][0].parente = temp;
				q.push(adj[i]);
				if (caminhos[adj[i]][0].valor == destino) {
					indiceDestino = adj[i];
					done = true;
				}
			}
		}
	}

	vector<string> res;

	if (indiceDestino != -1) {
		int x = indiceDestino;
		while (caminhos[x][0].parente != -1) {
			res.push_back(caminhos[x][0].valor);
			x = caminhos[x][0].parente;
		}
		res.push_back(origem);
		reverse(res.begin(), res.end());
	}

	return res;
}

Itinerario Agencia::criarItinerario(vector<string> caminho) {
	Itinerario i1;

	for (size_t i = 0; i < caminho.size() - 1; i++) {
		for (size_t j = 0; j < trocos.size(); j++) {
			if (trocos[j].getOrigem() == caminho[i] && trocos[j].getDestino() == caminho[i + 1])
				i1.addTroco(trocos[j]);
		}
	}

	return i1;
}

void Agencia::venderViagem(string nomeCliente, string origem, string destino, string alojamento, int n) {
	vector<string> nomes;
	for (size_t i = 0; i < clientes.size(); i++) {
		nomes.push_back(clientes[i]->getNome());
	}
	int indice = sequentialSearch(nomes, nomeCliente);
	if (indice == -1)
		throw ExcecaoClienteNaoExistente();

	vector<string> origens;
	for (size_t i = 0; i < trocos.size(); i++) {
		origens.push_back(trocos[i].getOrigem());
	}
	if (sequentialSearch(origens, origem) == -1)
		throw ExcecaoOrigemNaoExistente();

	vector<string> destinos;
	for (size_t i = 0; i < trocos.size(); i++) {
		destinos.push_back(trocos[i].getDestino());
	}
	if (sequentialSearch(destinos, destino) == -1)
		throw ExcecaoDestinoNaoExistente();

	int encontrouAlojamento = -1;
	if (alojamento != "NULO") {
		for (size_t i = 0; i < alojamentos.size(); i++) {
			if (alojamentos[i].getNome() == alojamento && alojamentos[i].getLocal() == destino)
				encontrouAlojamento = i;
		}
		if (encontrouAlojamento == -1)
			throw ExcecaoAlojamentoNaoDisponivel();
	}

	vector<string> caminho;
	caminho = encontrarCaminho(origem, destino);

	if (caminho.size() == 0)
		throw ExcecaoCaminhoNaoExistente();

	Viagem *v1 = new Viagem(criarItinerario(caminho));
	v1->setPreco(v1->getPreco() - v1->getPreco() * clientes[indice]->calcDesconto());
	if (alojamento != "NULO") { v1->adicionarAlojamento(alojamentos[encontrouAlojamento]); }
	clientes[indice]->adicionarViagem(v1, n);
}

void Agencia::mostrarHistorico(string nomeCliente) {
	vector<string> nomes;
	for (size_t i = 0; i < clientes.size(); i++) {
		nomes.push_back(clientes[i]->getNome());
	}
	int indice = sequentialSearch(nomes, nomeCliente);
	if (indice == -1)
		throw ExcecaoClienteNaoExistente();

	clientes[indice]->mostrarHistorico();
}

void Agencia::mostrarClientes() {
	cout << "Clientes da Agencia: " << endl;
	for (size_t i = 0; i < clientes.size(); i++) {
		cout << clientes[i]->getNome() << endl;
	}
	cout << endl;
}

void Agencia::mostrarTrocos() {
	cout << "Trocos disponiveis: " << endl;
	for (size_t i = 0; i < trocos.size(); i++) {
		cout << trocos[i].getOrigem() << " " << trocos[i].getDestino() << " " << trocos[i].getTransporte() << " " << trocos[i].getPreco() << endl;
	}
	cout << endl;
}

void Agencia::mostrarPacotes() {
	cout << "Pacotes disponiveis: \n";
	for (size_t i = 0; i < pacotes.size(); i++) {
		pacotes[i].mostrar();
	}
	cout << endl;
}

void Agencia::mostrarAlojamentos() {
	cout << "Alojamentos disponiveis: \n";
	for (size_t i = 0; i < alojamentos.size(); i++) {
		cout << alojamentos[i].getNome() << " " << alojamentos[i].getLocal() << " " << alojamentos[i].getPreco() << endl;
	}
	cout << endl;
}

bool Agencia::gravarAgencia(string filepath) {
	ofstream outfile;
	outfile.open(filepath.c_str());

	if (outfile.is_open()) {
		for (size_t i = 0; i < clientes.size(); i++) {
			outfile << clientes[i]->infoString();
		}
		outfile << "\n";
		for (size_t i = 0; i < pacotes.size(); i++) {
			outfile << pacotes[i].infoString();
		}
		outfile << "\n";
		for (size_t i = 0; i < trocos.size(); i++) {
			outfile << trocos[i].getOrigem() << " " << trocos[i].getDestino() << " " << trocos[i].getTransporte() << " " << trocos[i].getPreco() << " ";
		}
		outfile << "\n";
		for (size_t i = 0; i < alojamentos.size(); i++) {
			outfile << alojamentos[i].getNome() << " " << alojamentos[i].getLocal() << " " << alojamentos[i].getPreco() << " ";
		}
		outfile.close();
	} else {
		return false;
	}

	return true;
}

bool Agencia::carregarAgencia(string filepath) {
	string sclientes = "", spacotes = "", strocos = "", salojamentos = "";
	ifstream infile;
	infile.open(filepath.c_str());

	if (infile.is_open()) {
		getline(infile, sclientes);
		getline(infile, spacotes);
		getline(infile, strocos);
		getline(infile, salojamentos);
		infile.close();
	} else {
		return false;
	}

	/* Carregar informacao relativa a trocos */
	if (strocos.length() != 0) {
		istringstream iss(strocos);
		string origem = "", destino = "", transporte = "";
		float preco;

		while (iss >> origem >> destino >> transporte >> preco) {
			Troco t1(origem, destino, transporte, preco);
			adicionarTroco(t1);
		}
	}

	//cout << "trocos carregados!\n";

	/* Carregar informacao relativa a alojamentos */
	if (salojamentos.length() != 0) {
		istringstream iss(salojamentos);
		string alojamento = "", local ="";
		float preco;

		while(iss >> alojamento >> local >> preco) {
			Alojamento al1(alojamento, local, preco);
			adicionarAlojamento(al1);
		}
	}

	//cout << "alojamentos carregados\n";

	/* Carregar informacao relativa a pacotes */
	if (spacotes.length() != 0) {
		istringstream iss(spacotes);
		int numTrocos;
		string origem = "", destino = "", transporte = "", alojamento = "";
		float preco, precoTotal;

		while (iss >> precoTotal >> alojamento >> numTrocos) {
			Itinerario i1;
			for (int i = 0; i < numTrocos; i++) {
				iss >> origem >> destino >> transporte >> preco;
				i1.addTroco(Troco(origem, destino, transporte, preco));
			}
			Pacote p1(i1, precoTotal);

			int indice1;
			if (alojamento != "NULO") {
				for (size_t i = 0; i < alojamentos.size(); i++) {
					if (alojamentos[i].getNome() == alojamento && alojamentos[i].getLocal() == i1.getDestino())
						indice1 = i;
				}
				p1.adicionarAlojamento(alojamentos[indice1]);
			}

			adicionarPacote(p1);
		}
	}

	//cout << "pacotes carregados\n";

	/* Carregar informacao relativa a clientes */
	if (sclientes.length() != 0) {
		istringstream iss(sclientes);
		int numNomes, numViagens, numMedio, numTotal, numTrocos;
		vector<string> nomes;
		float preco, precoTotal;
		string tipo = "", alojamento = "", origem = "", destino = "", transporte = "", nome = "", tmp = "";
		ostringstream oss;
		while (iss >> numNomes) {
			oss.str("");
			nomes.clear();
			for (int i = 0; i < numNomes; i++) {
				iss >> tmp;
				nomes.push_back(tmp);
			}

			iss >> tipo;
			if (tipo == "Particular") {
				for (int i = 0; i < nomes.size() - 1; i++) {
					oss << nomes[i] << " ";
				}
				oss << nomes[nomes.size() - 1];

				ClienteParticular *c1 = new ClienteParticular(oss.str());
				adicionaCliente(c1);

				iss >> numViagens;
				for (int i = 0; i < numViagens; i++) {
					float precoTrocos = 0;
					Itinerario i1;
					iss >> precoTotal >> alojamento >> numTrocos;
					for (int j = 0; j < numTrocos; j++) {
						iss >> origem >> destino >> transporte >> preco;
						precoTrocos += preco;
						i1.addTroco(Troco(origem, destino, transporte, preco));
					}

					if (alojamento != "NULO") {
						for (size_t j = 0; j < alojamentos.size(); j++) {
							if (alojamentos[j].getNome() == alojamento && alojamentos[j].getLocal() == destino)
								precoTrocos += alojamentos[j].getPreco();
						}
					}

					if (precoTotal != precoTrocos) {
						//cout << i1.getOrigem() << i1.getDestino();
						venderPacote(oss.str(), i1.getOrigem(), i1.getDestino());
					} else {
						if (alojamento == "NULO") {
							venderViagem(oss.str(), i1.getOrigem(), i1.getDestino());
						} else {
							venderViagem(oss.str(), i1.getOrigem(), i1.getDestino(), alojamento);
						}
					}
				}
			} else {
				for (int i = 0; i < nomes.size() - 1; i++) {
					oss << nomes[i] << " ";
				}
				oss << nomes[nomes.size() - 1];

				iss >> numMedio >> numTotal;
				ClienteComercial *c1 = new ClienteComercial(oss.str());
				c1->setMediaParticipantes(numMedio);
				c1->setTotalParticipantes(numTotal);

				adicionaCliente(c1);

				iss >> numViagens;
				for (int i = 0; i < numViagens; i++) {

					float precoTrocos = 0;
					Itinerario i1;
					iss >> precoTotal >> alojamento >> numTrocos;
					for (int j = 0; j < numTrocos; j++) {
						iss >> origem >> destino >> transporte >> preco;
						precoTrocos += preco;
						i1.addTroco(Troco(origem, destino, transporte, preco));
					}

					if (alojamento != "NULO") {
						for (size_t j = 0; j < alojamentos.size(); j++) {
							if (alojamentos[j].getNome() == alojamento && alojamentos[j].getLocal() == destino)
								precoTrocos += alojamentos[j].getPreco();
						}
					}

					if (precoTotal != precoTrocos - precoTrocos * c1->calcDesconto()) {
						//cout << precoTotal << precoTrocos;
						//cout << i1.getOrigem() << i1.getDestino() << endl;
						venderPacote(oss.str(), i1.getOrigem(), i1.getDestino(), 0);
					} else {
						if (alojamento == "NULO") {
							venderViagem(oss.str(), i1.getOrigem(), i1.getDestino(), "NULO");
						} else {
							venderViagem(oss.str(), i1.getOrigem(), i1.getDestino(), alojamento, 0);
						}
					}

					//cout << "CC viagem adicionada" << i1.getOrigem() << i1.getDestino() << endl;
				}
			}
		}
	}

	return true;
}


void Agencia::adicionarAlojamento(Alojamento alojamento) {
	alojamentos.push_back(alojamento);
}
