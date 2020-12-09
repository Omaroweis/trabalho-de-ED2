#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<stack>
#include<sstream>
using namespace std;
typedef pair< pair<int, int>, pair<int, int> > iiii;//vertice, peso, chegada, saida
typedef vector<pair< pair<int, int>, pair<int, int> > >T;
typedef pair<int,int>ii;
typedef vector<ii>vi;
T G[1024];

map<string, int>nome_vertice;
vector<string>n_v;
map<int, string>vertice_nome;
vector<int>pai(1024, -1);
string id, nome;
vector<int>dist(1024, __INT_MAX__/2);
stack<int>pilha;

int achaHora(string id, int p) // de chegada
{

  for(auto it : G[p])
    {
      if(vertice_nome[it.first.first] == id){return it.second.first;}
    }
}
int achaHoraSaida(string id, int p)
{
  for(auto it : G[p])
    {
      if(vertice_nome[it.first.first] == id){ return it.second.second;}
    }
}
void djistra(int s)
{
  dist[s] = 0;

  priority_queue<ii, vi, greater< ii > > pq;
  pq.push(ii(0,s));
  while (!pq.empty()) {
      int distancia = pq.top().first;
      int u = pq.top().second;
      pq.pop();
      for(auto it : G[u])
        {
          int adj = it.first.first;
          int peso = it.first.second;
          int saida = it.second.second;
          bool flag = true;
          if(pai[u] != -1)
            {
              int p = pai[u];
              int horaPaiChegou = achaHora(vertice_nome[u], p);
              if(saida - horaPaiChegou < 30) flag = false;
            }
          if(flag)
            {
              if(dist[adj] > dist[u] + peso)
                {
                  dist[adj] = dist[u]+peso;
                  pq.push(ii(dist[adj], adj));
                  pai[adj] = u;
                }
            }
        }
    }
}

void achaCaminho(int a, int b)
{
  pilha.push(b);
    while(b != a)
    {
      b = pai[b];
      pilha.push(b);
    }
  return;

}
int converteHora(string hora) // recebe a hora em string e retorna o equivalente em minutos
{
  int aux = 0;
  aux+=(int(hora[0] - 48))*10;
  aux+=(int(hora[1] - 48));
  aux*=60;
  aux+=(int(hora[3] - 48)) *10;
  aux+=(int(hora[4] - 48));
  return aux;
}
int main()
{
  string saida, chegada;
  string nomeSegundo;

  cout<<"DIGITE AS OPCOES DE VIAGENS, E QUANDO ACABAR DIGITE O #\n";
  int cont = 1;
  string str, word;
  getline(cin, str);
  while (str.compare("#")) {

      stringstream ss(str);
      ss >> id;
      map<string, int>::iterator itt;
      ss >> nome;
      //ss >> saida;

      while (ss>>saida) {
          //verifica o primeiro
          ss>>nomeSegundo;
          itt = nome_vertice.find(nome);

          if(itt == nome_vertice.end()) // nao tem ainda no grafo
            {
              nome_vertice[nome] = cont;
              vertice_nome[cont] = nome;
              cont++;
            }

         // verifica o segundo
          itt = nome_vertice.find(nomeSegundo);
          if(itt == nome_vertice.end()) // nao tem ainda no grafo
            {
              nome_vertice[nomeSegundo] = cont;
              vertice_nome[cont] = nomeSegundo;
              cont++;
            }

          ss>>chegada;
          int saidaNum, chegadaNum;
          saidaNum=converteHora(saida);
          chegadaNum = converteHora(chegada);
          int peso = chegadaNum - saidaNum;
          iiii auxi = iiii(make_pair(nome_vertice[nomeSegundo], peso), make_pair(chegadaNum, saidaNum));
          G[nome_vertice[nome]].push_back(auxi);
          nome = nomeSegundo;

        }
      getline(cin, str);
    }

    for(int i = 1; i<=cont; i++)
      {
        cout<<vertice_nome[i]<<": ";
        for(auto it : G[i])
          {
            cout<<vertice_nome[it.first.first]<<" ";
          }
        cout<<endl;
      }

    cout<<"DIGITE O NOME DO AEROPORTO DE ORIGEM\n";
    cin>>nome;
    string nome2;
    djistra(nome_vertice[nome]);
    cout<<"DIGITE O NOME DO AEROPORTO DE DESTINO\n";
    cin>>nome2;

    while (pilha.size()) {
        pilha.pop();
      }
    achaCaminho(nome_vertice[nome], nome_vertice[nome2]);


    pilha.pop();
    while (!pilha.empty()) {
        int p = pai[pilha.top()];
        cout<<vertice_nome[p]<<" "<<achaHoraSaida(vertice_nome[pilha.top()], p)/60<<":"<<achaHoraSaida(vertice_nome[pilha.top()], p)%60<<" ";
        cout<<" ";
        cout<<vertice_nome[pilha.top()]<<" "<<achaHora(vertice_nome[pilha.top()], p)/60<<":"<<achaHora(vertice_nome[pilha.top()], p)%60;
        pilha.pop();
        cout<<endl;
      }

  exit(0);
}


