#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Cliente;
class Itinerario;
class Viagem;
class Troco;
class Alojamento;
class Pacote;

class Cliente {
protected:
	string nome;
	vector<Viagem* > viagens;
public:
	Cliente(string n){
		nome=n;
	}
	virtual ~Cliente(){}
	string getNome() const {return nome;}
	virtual float calcDesconto() = 0;
	virtual void adicionarViagem(Viagem* viagem, int n);
	void mostrarHistorico();
	virtual string infoString() = 0;
	int contarNomes(string nome);
};

class ClienteParticular: public Cliente {
public:
	ClienteParticular(string nm):Cliente(nm){}
	float calcDesconto();
	string infoString();
};

class ClienteComercial: public Cliente {
	float mediaParticipantes; //numero medio de participantes
	int totalParticipantes;
public:
	ClienteComercial(string nm):Cliente(nm){ mediaParticipantes = 0; totalParticipantes = 0; }
	float calcDesconto();
	string infoString();
	void setMediaParticipantes(float med) { mediaParticipantes = med; }
	void setTotalParticipantes(int tot) { totalParticipantes = tot; }
	void adicionarViagem(Viagem* viagem, int n);
};

struct eqCliente {
	bool operator()(const Cliente *cli1, const Cliente *cli2) const {
		return cli1->getNome() == cli2->getNome();
	}
};

struct hashCliente {

	int operator()(const Cliente *cli) const {
	   int seed = 31;
	   unsigned long hash = 0;
	   for(int i = 0; i < cli->getNome().length(); i++)
	   {
		  hash = (hash * seed) + cli->getNome()[i];
	   }
	   return hash;
	}

};

typedef unordered_map<Cliente*, hashCliente, eqCliente> HashTableClientes;

class Itinerario {
private:
	vector<Troco> trocos;
	float preco;
public:
	Itinerario();
	~Itinerario(){}
	vector<Troco> getTrocos();
	void addTroco(Troco troco);
	string getOrigem();
	string getDestino();
	float getPreco();
	void mostrar();
};

class Troco{
private:
	string origem;
	string destino;
	string transporte;
	float preco;
public:
	Troco(string origem, string destino, string transporte, float preco);
	~Troco(){}
	string getOrigem();
	string getDestino();
	string getTransporte();
	float getPreco();
};

class Alojamento{
private:
	string nome;
	string local;
	float preco;
public:
	Alojamento(){};
	Alojamento(string nome, string local, float preco);
	string getNome();
	string getLocal();
	float getPreco();
};

class Viagem {
protected:
	Itinerario itinerario;
	Alojamento alojamento;
	float preco;
public:
	Viagem(Itinerario itinerario);
	~Viagem(){}
	virtual string getOrigem();
	virtual string getDestino();
	Itinerario getItinerario();
	virtual void mostrar();
	float getPreco();
	void setPreco(float preco);
	void adicionarAlojamento(Alojamento alojamento);
	Alojamento getAlojamento();
};

class Pacote: public Viagem
{
public:
	Pacote(Itinerario itinerario,float preco);
	Pacote(Itinerario itinerario, float preco, Alojamento &alojamento);
	void mostrar();
	string infoString();
};

class Agencia {
private:
	struct node {
		string valor;
		int parente;
	};
	vector<vector<node> > caminhos;
	vector<Cliente*> clientes;
	vector<Pacote> pacotes;
	vector<Troco> trocos;
	vector<Alojamento> alojamentos;
	HashTableClientes clientesAntigos;
	int limAntigos = 2; //Número de anos a partir do qual se é considerado cliente antigo
public:
	Agencia();
	~Agencia(){}
	int numViagens() const;
	int numClientes() const;
	void adicionaCliente(Cliente* cli);
	bool apagaCliente(string nomeCli);
	void adicionarPacote(Pacote pacote);
	void venderPacote(string nomeCliente, string origem, string destino, int n = 1);
	int getHashSize(){return clientesAntigos.size();}
	// Modificar os vectores!!
	vector<Cliente*> getClientes();

	vector<int> getAdjacentes(int indice);
	vector< vector<node> > getCaminhos();
	void adicionarTroco(Troco troco);
	vector<string> encontrarCaminho(string origem, string destino);
	Itinerario criarItinerario(vector<string> caminho);
	void venderViagem(string nomeCliente, string origem, string destino, string alojamento = "NULO", int n = 1);
	void mostrarHistorico(string nomeCliente);

	void mostrarClientes();
	void mostrarTrocos();
	void mostrarPacotes();
	void mostrarAlojamentos();

	bool gravarAgencia(string filepath);
	bool carregarAgencia(string filepath);

	void adicionarAlojamento(Alojamento alojamento);

	/***************/

	class ExcecaoClienteNaoExistente{};
	class ExcecaoPacoteNaoExistente{};
	class ExcecaoOrigemNaoExistente{};
	class ExcecaoDestinoNaoExistente{};
	class ExcecaoCaminhoNaoExistente{};
	class ExcecaoAlojamentoNaoDisponivel{};
};
