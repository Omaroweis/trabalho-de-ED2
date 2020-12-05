#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<stack>
using namespace std;
typedef pair< pair<int, int>, pair<int, int> > iiii;//vertice, peso, chegada, saida
typedef vector<pair< pair<int, int>, pair<int, int> > >T;
typedef pair<int,int>ii;
typedef vector<ii>vi;
T G[1024];
map<string, string>id_nome;
map<string,string>nome_id;
map<string, int>id_vertice;
map<int, string>vertice_id;
vector<int>pai(1024, -1);
string id, nome;
vector<int>dist(1024, __INT_MAX__/2);
stack<int>pilha;

int achaHora(string id, int p) // de chegada
{
  for(auto it : G[p])
    {
      if(vertice_id[it.first.first] == id) return it.second.first;
    }
}
int achaHoraSaida(string id, int p)
{
  for(auto it : G[p])
    {
      if(vertice_id[it.first.first] == id) return it.second.second;
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
              int horaPaiChegou = achaHora(vertice_id[u], p);
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
int converteHora(string hora)
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
  cout<<"DIGITE A IDENTIFICACAO E O NOME DE TODOS OS AEROPORTOS, E QUANDO TERMINAR DIGITE #\n";
  cin>>id;
  int v = 1;

  while (id.compare("#")) {
      cin>>nome;
      id_nome[id] = nome;
      nome_id[nome] = id;
      vertice_id[v] = id;
      id_vertice[id] = v;
      v++;
      cin>>id;
    }
  string saida, chegada;
  string nomeSegundo;
  cout<<"DIGITE AS OPCOES DE VIAGENS, E QUANDO ACABAR DIGITE O #\n";
  cin>>id;
  while (id.compare("#")) {
      cin>>nome;
      cin>>saida;

      cin>>nomeSegundo>>chegada;
      int saidaNum, chegadaNum;
      saidaNum=converteHora(saida);
      chegadaNum = converteHora(chegada);
      int peso = chegadaNum - saidaNum;
      iiii auxi = iiii(make_pair(id_vertice[nome_id[nomeSegundo]], peso), make_pair(chegadaNum, saidaNum));
      G[id_vertice[id]].push_back(auxi);
      cin>>id;
    }

    cout<<"DIGITE O NOME DO AEROPORTO DE ORIGEM\n";
    cin>>nome;
    string nome2;
    djistra(id_vertice[nome_id[nome]]);
    cout<<"DIGITE O NOME DO AEROPORTO DE DESTINO\n";
    cin>>nome2;


    cout<<"vc ira gastar, na melhor hipotese: "<<dist[(id_vertice[nome_id[nome2]])]/60<<":"<<dist[(id_vertice[nome_id[nome2]])]%60<<"hrs"<<endl;

    while (pilha.size()) {
        pilha.pop();
      }
    achaCaminho(id_vertice[nome_id[nome]], id_vertice[nome_id[nome2]]);


    pilha.pop();
    while (!pilha.empty()) {
        int p = pai[pilha.top()];
        cout<<vertice_id[p]<<" "<<id_nome[vertice_id[p]]<<" "<<achaHoraSaida(vertice_id[pilha.top()], p)/60<<":"<<achaHoraSaida(vertice_id[pilha.top()], p)%60<<" ";
        cout<<" ";
        cout<<vertice_id[pilha.top()]<<" "<<id_nome[vertice_id[pilha.top()]]<<" "<<achaHora(vertice_id[pilha.top()], p)/60<<":"<<achaHora(vertice_id[pilha.top()], p)%60;
        pilha.pop();
        cout<<endl;
      }

  exit(0);
}


