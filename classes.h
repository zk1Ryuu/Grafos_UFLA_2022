#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class destiny{
	
	private:
		int size;
		int route_time;
		int time_widow;
		int capacity;

		string name;
		string location;
		string comment;
		string type;
		string distribuition;
		string depot;

		
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
		void precedencia(destiny *linhas);
		void destrutor(destiny *linhas);
		void distancia_dos_nohs(ifstream& arquivo_instancia, destiny *linhas);
		void verificar_restricoes_solucao_aleatoria(ifstream& arq_solucao, destiny *linhas);
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
						
						cout << "O vertice de id igual a " << id << " possui capacidade superior ao esperado!" << endl;
						cout << "Capacidade maxima esperada: " << linhas->capacity << endl;
						cout << "Capacidade do vertice encontrada: " << dem << endl;
					}
					break;
					
				case 4:
					arquivo_instancia >> etw[i];
					break;
					
				case 5:
					arquivo_instancia >> ltw[i];
					if(ltw[i] > linhas->route_time){
						
						cout << "O vertice de id igual a " << id << " possui a janela de tempo superior ao esperado!" << endl;
						cout << "Janela de tempo maxima esperada: " << linhas->route_time << endl;
						cout << "Janela de tempo maxima do vertice encontrada: " << ltw << endl;
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

class automovel{
	
	private:
		int *id;
		vector<int> *rota;
		int qtd_veiculos;
		
	public:
		automovel(ifstream& arq_solucao);
		void leitura_rota(ifstream& arq_solucao, destiny *linhas);

		void restringimento01(ifstream& arq_solucao, destiny *linhas, noh *nohs);
};

// Construtor de "automovel"
automovel::automovel(ifstream& arq_solucao){
	
	// leitura da linhas VEICULOS
	string texto;
	arq_solucao >> texto;
	
	// leitura da quantidade de veiculos
	arq_solucao >> qtd_veiculos;
	
	// leitura da linhas ROTAS
	arq_solucao >> texto;
	
	id = new int[qtd_veiculos];
	rota = new vector<int>[qtd_veiculos];
}


// Funcao para leitura da rota de um veiculo
void automovel::leitura_rota(ifstream& arq_solucao, destiny *linhas){
	
	int num_atual;
	
	// leitura da rota do veiculo atual
	for(int i = 0; i < qtd_veiculos; i++){
		
		for(int j = 0; j < linhas->size + 1; j++){
			
			arq_solucao >> num_atual;
			rota[i].push_back(num_atual);
		}
	}
}

void automovel::restringimento01(ifstream& arq_solucao, destiny *linhas, noh *nohs){
	
	int num_atual;
	
	for(int i = 0; i < qtd_veiculos; i++){
		
		int pos = 0;
		
		for(auto it = rota[i].begin(); it != rota[i].end(); it++, pos++){
			
			num_atual = *it;
			
			// num_atual eh ponto de entrega
			if(nohs->dem[num_atual] < 0){
				
				// ponto de coleta esperado
				int aux_p = num_atual - ((linhas->size - 1) / 2);
				
				// caso o ponto i seja encontrado antes de j, o while é quebrado
				int k = 0;
				while(k < pos){
					
					if(rota[i][k] == aux_p)
						break;
						
					k++;
				}
				
				// caso k percorra ate pos, quer dizer que o ponto j apareceu depois de i
				if(k == pos)
					cout << "A rota do veiculo " << i + 1 << " possui o vertice de entrega " << num_atual << " que foi visitado antes do seu vertice de coleta!" << endl;
				
			}
		}
	}
}