#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//CLasse do destino do automovel
class destiny{
	
	private:
		int time_widow;
		int capacity;
		int size;
		int route_time;

		string type;
		string distribuition;
		string depot;
		string name;
		string location;
		string comment;

		
	public:
		destiny();
		int ler_5(ifstream& arquivo_instancia);
		
	friend class noh;
	friend class automovel;
};

#define flag -1

destiny::destiny(){
	
	route_time = flag;
	size = flag;
	capacity = flag;
	time_widow = flag;
	
}

//Classe do nó do grafo
class noh{
	
	friend class automovel;
	
	private:
		int *id;
		double *lat;
		double *longit;
		int *dem;
		int *etw;
		int *ltw;
		int *dur;
		int *p;
		int *d;
		int **dist;
		
	public:
		noh(destiny *linhas);
		void leitura(destiny *linhas, ifstream& arquivo_instancia);
		void priodade(destiny *linhas);
		void destrutor(destiny *linhas);
		void distancia_dos_nohs(ifstream& arquivo_instancia, destiny *linhas);
		void verificar_restricoes_solucao_aleatoria(ifstream& arquivo_instancia, destiny *linhas);
};

// Construtor de "noh"
noh::noh(destiny *linhas){

	int i = 0;

	while (i < linhas->size){
		dist[i] = new int[linhas->size];
		i++;
	}
	
	lat = new double[linhas->size];
	longit = new double[linhas->size];
	ltw = new int[linhas->size];
	dem = new int[linhas->size];
	etw = new int[linhas->size];
	dur = new int[linhas->size];

	id = new int[linhas->size];
	d = new int[linhas->size];
	p = new int[linhas->size];

	dist = new int*[linhas->size];

}

//Leitura das variaveis pedidos no enunciado
void noh::leitura( destiny *linhas, ifstream& arquivo_instancia){
	
	for(int i = 0; i < linhas->size; i++){
		
		int j = 0;
		while(j < 9){
			
			// leitura dos dados
			switch(j){
				
				case 0:
					arquivo_instancia >> id[i];
					break;
					
				case 1:
					arquivo_instancia >> lat[i];
					break;
					
				case 2:
					arquivo_instancia >> longit[i];
					break;
					
				case 3:
					arquivo_instancia >> dem[i];
					if(dem[i] > linhas->capacity){
						
						cout << "idd igual a " << id << "maxima esperada: " << linhas->capacity << endl;

						cout << "Capacidade do vertice encontrada: " << dem << endl;
					}
					break;
					
				case 4:
					arquivo_instancia >> etw[i];
					break;
					
				case 5:
					arquivo_instancia >> ltw[i];
					if(ltw[i] > linhas->route_time){
						
						cout << "id igual a " << id << endl << 
					 "maxima do vertice encontrada: " << ltw << endl;
					}

					break;
					
				case 6:
					arquivo_instancia >> dur[i];
					break;
					
				case 7:
					arquivo_instancia >> p[i];
					break;
					
				case 8:
					arquivo_instancia >> d[i];
					break;
			}
			j++;
		}
	}
}

//Classe do automovel
class automovel{
	
	private:
		int *id;
		vector<int> *rota;
		int qtd_veiculos;
		
	public:
		void leitura_rota(ifstream& arquivo_instancia, destiny *linhas);
		automovel(ifstream& arquivo_instancia);
		void restricao(ifstream& arquivo_instancia, destiny *linhas, noh *nohs);

};

//Leitura da rota que o automovel fará
void automovel::leitura_rota(ifstream& arquivo_instancia, destiny *linhas){
	
	int atual;

	for(int i = 0; i < qtd_veiculos; i++){
		
		for(int j = 0; j < linhas->size + 1; j++){
			
			arquivo_instancia >> atual;
			rota[i].push_back(atual);
		}
	}
}

automovel::automovel(ifstream& arquivo_instancia){
	

	string texto;
	arquivo_instancia >> texto;
	
	id = new int[qtd_veiculos];
	rota = new vector<int>[qtd_veiculos];
	arquivo_instancia >> qtd_veiculos;
	
	arquivo_instancia >> texto;
	
}
