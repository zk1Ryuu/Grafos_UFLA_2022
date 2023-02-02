/*  - Trabalho Pratico de grafos - semestre letivo 2022/2

    - Universidade Federal de Lavras - UFLA
    - Departamento de Ciencia da Computacao - DCC
    - Algoritmos em Grafos
    - Docente Mayron
    - Discente e feito por: Guilherme Fabricio Brito da Rosa
    - Turma: 10A


 */

#include "classes.h"

void noh::precedencia(destiny *linhas){
	
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

			if(p[i] == 0 and d[i] != 0){
				
				if(d[i] != d01){
					
					cout << "id igual:  " << id[i]
					    << "chegada: " << d01;
				}
			}
		}
		
		if(dem[i] < 0){
			
			d01 = 0;

			p01 = id[i] - ((linhas->size - 1) / 2);
			
			if(p[i] != 0 and d[i] == 0){
				
				if(p[i] != p01){
					
					cout << "id igual a " << id[i] << " possui um erro de prioridade!" << endl
                    <<  "esperado: " << p01 << endl
					<< "encontrado: " << p[i];
				}
			}
		}
	}
}

void noh::distancia_dos_nohs(ifstream& arquivo_instancia, destiny *linhas){
	
	for(int i = 0; i < linhas->size; i++){
		for(int j = 0; j < linhas->size; j++){
			arquivo_instancia >> dist[i][j];
        }
    }
}

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

int main(){
	
	string n1;
    char choice;
	
	cout << "Digite o nome da instancia (tem que estar na mesma raiz do programa): ";

	cin >> n1;
	
	ifstream arquivo_instancia( n1 + ".txt");
	
	if(arquivo_instancia){
		

		destiny *linhas = new destiny;
		int numero_vertices = linhas->ler_5(arquivo_instancia);

		string texto;
		arquivo_instancia >> texto;
		

		noh *nohs = new noh(linhas);
		
		nohs->leitura(linhas, arquivo_instancia);
		nohs->precedencia(linhas);
		

			arquivo_instancia >> texto;
			
			nohs->distancia_dos_nohs(arquivo_instancia, linhas);
			
			cout << "Leitura SUCEDIDO !!!" << endl;
			
		
		arquivo_instancia.close();
	}
	
	else
		cout << "ARQUIVO NAO ENCONTRADO, FECHANDO APLICACAO";
		
	return 0;
}
