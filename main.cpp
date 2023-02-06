/*  - Trabalho Pratico de grafos - semestre letivo 2022/2

    - Universidade Federal de Lavras - UFLA
    - Departamento de Ciencia da Computacao - DCC
    - Algoritmos em Grafos
    - Docente Mayron
    - Discente e feito por: Guilherme Fabricio Brito da Rosa
    - Turma: 10A


 */

#include "classes.h"

//Foi feito para integrar os dominios de p e d
void noh::priodade(destiny *linhas){
	
	int d01 = 0;
	int p01 = 0;
	
	for(int i = 0; i < linhas->size; i++){
		
		if(dem[i] == 0){
				
				cout << "Erro !"
                    << "p e d encontrados: " << p[i] << " " << d[i];
		}
		
		if(dem[i] > 0){
			
			d01 = id[i] + ((linhas->size - 1) / 2);
			p01 = 0;

			if(p[i] == 0 and d[i] != 0)
				if(d[i] != d01)
					cout << "id igual:  " << id[i] << "chegada: " << d01;
		}
		
		if(dem[i] < 0){
			
			d01 = 0;

			p01 = id[i] - ((linhas->size - 1) / 2);
			
			if(p[i] != 0 and d[i] == 0)
				if(p[i] != p01)
					cout << "ID possui um erro de prioridade!" << endl << "foi encontrado: " << p[i];
		}
	}
}

void noh::distancia_dos_nohs(ifstream& arquivo_instancia, destiny *linhas){
	
	for(int i = 0; i < linhas->size; i++)
		for(int j = 0; j < linhas->size; j++)
			arquivo_instancia >> dist[i][j];
}

//
int destiny::ler_5(ifstream& arquivo_instancia){
	
	string texto;

    int k = 0;
	
	while (k < 10) {
    
		getline(arquivo_instancia, texto, ' ');
		
		switch(k){
			
			case 0:
				getline(arquivo_instancia, name);
				break;
				
			case 1:
				getline(arquivo_instancia, location);
				break;
				
			case 2:
				getline(arquivo_instancia, comment);
				break;
				
			case 3:
				getline(arquivo_instancia, type);
				break;
				
			case 4:
				getline(arquivo_instancia, texto);
				size = stoi(texto);
				break;
				
			case 5:
				getline(arquivo_instancia, distribuition);
				break;
				
			case 6:
				getline(arquivo_instancia, depot);
				break;
				
			case 7:
				getline(arquivo_instancia, texto);
				route_time = stoi(texto);
				break;
				
			case 8:
				getline(arquivo_instancia, texto);
				time_widow = stoi(texto);
				break;
				
			case 9:
				getline(arquivo_instancia, texto);
				capacity = stoi(texto);
				break;

            k++;
		}
	}
	
	return size;
}

//Feito algumas das restricoes solicitada no enunciado do macro01
void automovel::restricao(ifstream& arquivo_instancia, destiny *linhas, noh *nohs){
	
	//restricao 01
	cout << "Restricoes: " << endl << endl;
	
	int numero_atual, posicao, tempo_total = 0;
	
	
	for(int i = 0; i < qtd_veiculos; i++){
		
		posicao = 0;
		
		for(auto aux = rota[i].begin(); aux != rota[i].end(); aux++){
			
			numero_atual = *aux;
			
			if(nohs->dem[numero_atual] < 0){
				
				int aux_p = numero_atual - ((linhas->size - 1) / 2);
				
				int k = 0;
				while(k < posicao){
					
					if(rota[i][k] == aux_p)
						break;
						
					k++;
				}
				
				if(k == posicao){
					
					cout << "Restricao 01 feito !!!" << endl;
					cout << endl;
				}
			}
			posicao++;
		}

		numero_atual = 0;
		int num_prox;
		
		//restricao 02
		for(auto aux = rota[i].begin(); aux != rota[i].end(); aux++){
				
				numero_atual = *aux;
				num_prox = *(aux + 1);
				tempo_total += nohs->dist[numero_atual][num_prox];
			
			
			if(tempo_total < nohs->etw[num_prox])
				tempo_total = nohs->etw[num_prox] + nohs->dur[num_prox];
				
			else
				tempo_total += nohs->dur[num_prox];
				
		}

		if(tempo_total >= linhas->route_time)
			cout << "Restricao 02 ultrapassada !!!!";

		else
			cout << "restricao 02 sucedida !!!";
			
		cout << endl;
		
		//restricao 03

		posicao = 0;
		int acumulador = 0;
		
		for(auto aux = rota[i].begin(); aux != rota[i].end(); aux++){
			
			numero_atual = *aux;
			
			if(numero_atual == 0)
				continue;
			
			for(int k; k < posicao; k++)
				if(rota[i][k] == numero_atual)
				acumulador = k;
					break;
			

			if(acumulador == posicao)
				cout << "A rota de um veiculo tem um ponto visitado 1 vez";
			else
				cout << "A rota do veiculo foi visitado 2 vezes";
		}
		posicao++;
	}
}

//Classe principal do programa
int main(){
	
	string n1, texto;
	//Inicia com o nome da isntancia (MESMA RAIZ DO ARQUIVO main.cpp)
	cout << "Nome da instancia ";

	cin >> n1;
	
	ifstream arquivo_instancia( n1 + ".txt");
	
	if(arquivo_instancia){
		
		destiny *linhas = new destiny;

		arquivo_instancia >> texto;

		noh *nohs = new noh(linhas);
		
		nohs->leitura(linhas, arquivo_instancia);
		nohs->priodade(linhas);

			arquivo_instancia >> texto;
			
			nohs->distancia_dos_nohs(arquivo_instancia, linhas);
			
			cout << "Leitura SUCEDIDO !!!" << endl;
			
			automovel *veiculos = new automovel(arquivo_instancia);
					
			veiculos->restricao(arquivo_instancia, linhas, nohs);
		
		arquivo_instancia.close();
	}
	
	else
		cout << "ARQUIVO NAO ENCONTRADO/DIGITADO ERRADO, FECHANDO APLICACAO";
		
	return 0;
}
