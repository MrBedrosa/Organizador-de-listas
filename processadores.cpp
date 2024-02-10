#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct processador{
	int identificador;
	string nome;
	string marca;
	int anoLancamento;
	string serie;
	string socket;
};
//**********************************************************************************************************
//||||||||||||||||||||||||||||||||||||||||||||||||||FUNÇÕES|||||||||||||||||||||||||||||||||||||||||||||||||
//**********************************************************************************************************

//__________________________________________________________________________________________________________
//ORDENAÇÃO MÉTODO EFICIENTE

int particiona(processador vet[], int c, int f){
	string pivo = vet[c].nome;
	int i = c+1, j=f;
	while(i<=j){
		if(vet[i].nome <= pivo){
			i++;
		}else if(vet[j].nome >= pivo){
			j--;
		}else{
			swap(vet[i],vet[j]);
			i++;
			j--;
		}
	}
	swap(vet[c],vet[j]);
	
	return j;
}

void quicksort(processador vet[], int pivo, int fim){
	int novo_pivo;
	if(pivo < fim){
		novo_pivo = particiona(vet, pivo, fim);
		quicksort(vet, novo_pivo +1, fim);
		quicksort(vet, pivo, novo_pivo-1);
	}
}
//__________________________________________________________________________________________________________
//LEITURA TXT

void leitura(ifstream &arquivo_txt, processador Registros[], int numRegistros){
	
	char lixo;
	
	for(int i = 0; i < numRegistros; i++){
			arquivo_txt >> Registros[i].identificador;
			arquivo_txt >> lixo;
			getline(arquivo_txt,Registros[i].nome,',');
			getline(arquivo_txt,Registros[i].marca,',');
			arquivo_txt >> Registros[i].anoLancamento;
			arquivo_txt >> lixo;
			getline(arquivo_txt,Registros[i].serie,',');
			getline(arquivo_txt,Registros[i].socket,'"');
			arquivo_txt.ignore();
		}
}
//__________________________________________________________________________________________________________
//BINÁRIO

void binario(processador registro[], int r){
	ofstream bin("arq.bin");
	bin.write((const char*)registro, sizeof(processador)*r);
	bin.close();
}

void leitura2(ifstream &bin, processador Registros[], int numRegistros){
	
	char lixo;
	
	for(int i = 0; i < numRegistros; i++){
			bin >> Registros[i].identificador;
			bin >> lixo;
			getline(bin,Registros[i].nome,',');
			getline(bin,Registros[i].marca,',');
			bin >> Registros[i].anoLancamento;
			bin >> lixo;
			getline(bin,Registros[i].serie,',');
			getline(bin,Registros[i].socket,'"');
			bin.ignore();
		}
}

void atualiza_binario(processador registro[], int n){
	remove("arq.bin");
	binario(registro, n);
	ifstream bin("arq.bin");
	leitura2(bin, registro, n);
}
//__________________________________________________________________________________________________________
//CASO 1 (PESQUISAR)

void pesquisar(processador Registros[], int numRegistros, string cpu){
	int pos = -1;
	
	for(int i = 0; i < numRegistros; i++){
		if(Registros[i].nome == cpu){
			pos = i;
			i = numRegistros;
		}
	}
	if(pos != -1){
	cout << "Dados do processador: " 
	     << endl << " " << endl
		 << Registros[pos].identificador << endl
		 << Registros[pos].nome << endl
		 << Registros[pos].marca << endl
		 << Registros[pos].anoLancamento << endl
		 << Registros[pos].serie << endl
		 << Registros[pos].socket << endl
		 << " " << endl << "________________________________________________________________________________" << endl;
	}else{
		cout << "Processador nao encontrado";
	}
}
//__________________________________________________________________________________________________________
//CASE 2 (ALTERAR E ATUALIZAR)

void alterar(ifstream &bin, processador Registros[], int iden, int numRegistros){

	string nNome;
	string nMarca;
	int nAnoLancamento;
	string nSerie;
	string nSocket;

	cout << "Digite o novo nome: " << endl;
	cin.ignore();
	getline(cin, nNome);
	cout << "Digite a nova marca: " << endl;
	cin >> nMarca;
	cout << "Digite o ano de lancamento: " << endl;
	cin >> nAnoLancamento;
	cout << "Digite a serie: " << endl;
	cin >> nSerie;
	cout << "Digite o socket: " << endl;
	cin >> nSocket;

    int pos;
	
    for(int i = 0; i<numRegistros;i++){
        if(Registros[i].identificador == iden){
            pos = i;
        }
    }
	
	Registros[pos].nome = nNome;
	Registros[pos].marca = nMarca;
	Registros[pos].anoLancamento = nAnoLancamento;
	Registros[pos].serie = nSerie;
	Registros[pos].socket = nSocket;
	
	leitura2(bin, Registros, numRegistros);
}

void atualizar(processador registro[], int n){
	remove("processadores.txt");
	
	ofstream file("processadores.txt");
	
	file << "#identificador,nome,marca,anoLancamento,serie,socket" << endl;
	file << n << endl;

	file.seekp(0, ios::end);
	for (int i = 0; i < n; ++i) {
		file << registro[i].identificador << ","
			 << registro[i].nome << ","
			 << registro[i].marca << ","
			 << registro[i].anoLancamento << ","
			 << registro[i].serie << ","
			 << registro[i].socket << '"' << endl;
	}
	file.close();
	ifstream arq("processadores.txt");
	leitura(arq, registro, n);
	atualiza_binario(registro, n);
	
}

//__________________________________________________________________________________________________________
//CASE 3 (REDIMENSIONA E INSERIR)

void redimensiona(processador Registros[], int numRegistros){
	int NovoNumRegistros = numRegistros + 1;
	processador *nvetor2 = new processador[NovoNumRegistros];
	for(int i = 0; i < NovoNumRegistros; i++){
		nvetor2[i] = Registros[i];
	}
	
	//delete[]Registros;
    Registros = nvetor2;
    numRegistros = NovoNumRegistros;
	
    cout << "redimensiona concluido" << endl;
	cout << numRegistros << endl;
	inserir(Registros, numRegistros);
	atualizar(Registros, numRegistros);
}

void inserir(processador Registros[], int numRegistros){
	int p = numRegistros-1;
	Registros[p].identificador = p;
	
	cout << "________________________________________________________________________________" << endl;
	cout << "                            *Novo Processador*                                  " << endl;
	cout << "________________________________________________________________________________" << endl;
	cout << "Nome: ";
	getline(cin, Registros[p].nome);
	cout << "Marca: ";
	cin >> Registros[p].marca;
	cout << "Ano de Lançamento: ";
	cin >> Registros[p].anoLancamento;
	cout << "Série: ";
	cin >> Registros[p].serie;
	cout << "Socket: ";
	cin >> Registros[p].socket;
	cout << endl;
	cout << "________________________________________________________________________________" << endl;
}



//__________________________________________________________________________________________________________
//CASO 4 (MOSTRAR)

void mostrar(processador Registros[], int numRegistros){
	for(int i = 0; i < numRegistros; i++){
		cout << endl << " " << endl
			<< Registros[i].identificador << endl
			<< Registros[i].nome << endl
			<< Registros[i].marca << endl
			<< Registros[i].anoLancamento << endl
			<< Registros[i].serie << endl
			<< Registros[i].socket << endl
			<< " " << endl << "________________________________________________________________________________" << endl;
		}
}

//**********************************************************************************************************
//|||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||
//**********************************************************************************************************

int main(){	
	string nomeCpu;
	string linha;
	int numRegistros;
	
	ifstream arquivo_txt("processadores.txt");
	processador *Registros = new processador[numRegistros];
	
	getline(arquivo_txt,linha);
	arquivo_txt >> numRegistros;
	arquivo_txt.ignore();
	
	leitura(arquivo_txt, Registros, numRegistros);
	arquivo_txt.close();

	binario(Registros, numRegistros);
	ifstream bin("arq.bin");
	
	if(not(bin)){
		cout << "Erro: nao foi possivel abrir o arquivo de dados!" << endl;
		return 404; 
	}else{
	
		leitura2(bin, Registros, numRegistros);
	
		cout << "________________________________________________________________________________" << endl;
		cout << "                            *Processadores*                                     " << endl;
		cout << "________________________________________________________________________________" << endl;
	
		int opcao;
	
	
		do{
        	cout << "Escolha uma opcao:" << endl
		 	<< "0 - Sair" << endl
		 	<< "1 - Buscar" << endl
		 	<< "2 - Alterar" << endl
		 	<< "3 - Inserir Novo" << endl
		 	<< "4 - Ver lista" << endl;
	    	cout << "________________________________________________________________________________" << endl;

			cin >> opcao;
			cin.ignore();
		
        	switch(opcao){
				case 1:
					quicksort(Registros, 0, numRegistros-1);
					cout << "Escreva o nome do processador de interesse: ";
					getline(cin,nomeCpu);
					cout << endl;
					pesquisar(Registros, numRegistros, nomeCpu);
					cout << endl;
					break;
			
				case 2:
					int id;
					cout << "Qual item voce deseja alterar? Digite seu numero de identificacao:";
					cin >> id;
					alterar(bin, Registros, id, numRegistros);
					quicksort(Registros, 0, numRegistros-1);
					atualizar(Registros, numRegistros);
				break;
			
				case 3:
					redimensiona(Registros, numRegistros);
					break;
			
				case 4:
					quicksort(Registros, 0, numRegistros-1);
					atualizar(Registros, numRegistros);
					mostrar(Registros, numRegistros);
				break;
			}
		}while(opcao != 0);
	}
	return 0;
}
