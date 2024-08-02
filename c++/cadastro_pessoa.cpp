#include <iostream>
#include <cstdlib>
#include <string>

#define MAX_PEOPLE 2

using namespace std;

typedef struct{
  std::string nome;
  int idade;
  float altura;
}Pessoa;

// Função para ler os dados de uma pessoa
void sign_players(Pessoa* pessoa);
void print_signed_list(Pessoa* pessoa);

int main() {
  
  Pessoa pessoa[MAX_PEOPLE];
  sign_players(pessoa);
  print_signed_list(pessoa);
  
  return 0;
}

void sign_players(Pessoa* pessoa){
  for(int i = 0; i < MAX_PEOPLE; i++){
    cout << "Cadastre a " << i+1 << " pessoa: " << endl;
    cout << "Nome: ";
    cin >> pessoa[i].nome;
    cout << "Idade: ";
    cin >> pessoa[i].idade;
    cout << "Altura em cm: ";
    cin >> pessoa[i].altura;
    cout << "---------------------------------------" << endl;
  }
}

void print_signed_list(Pessoa* pessoa){
  cout << "\nPessoas cadastradas: " << endl;

  for(int i = 0; i < MAX_PEOPLE; i++){
    cout << "Pessoa " << i+1 << " Nome: " << pessoa[i].nome << endl;
    cout << "Pessoa " << i+1 << " Idade: " << pessoa[i].idade << endl;
    cout << "Pessoa " << i+1 << " Altura em metros: " << (float)pessoa[i].altura/100 << "m"<< endl;
    cout << "---------------------------------------" << endl;
  }

}
