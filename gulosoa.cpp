#include<iostream>
#include <list>
#include <queue>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int obj[3][3]={{1,2,3},
                     {4,5,6},
                     {7,8,0}};

struct Node {
    int prioridade;
    int arr[3][3];
    list<Node> antecessores;
    void printnode(int arr[3][3]);
    bool operator<(const Node& rhs) const
    {
        return prioridade > rhs.prioridade;
    }
};

struct NodeVisitado {
    int visitado[3][3];
};


void Node::printnode(int arr[3][3]){
    for (int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            cout << arr[i][j]<< " ";
        }
        cout << "\n";
    }
}

void print_antecessores(list<Node> &lista){

	list<Node> :: iterator it;

    for(it = lista.begin(); it != lista.end(); ++it){
		it->printnode(it->arr);
		cout<<"\n";
    }
}

int funcao (Node node){
    int cont=0;

    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            if (obj[i][j]!=node.arr[i][j]){
                cont++;
            }
        }
    }
    return cont;
}

bool checa_objetivo(Node node){

    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(obj[i][j]!=node.arr[i][j])
                return false;
        }
    }
    return true;
}

bool checa_visitado(Node node, list<NodeVisitado> &lista){

    list<NodeVisitado> :: iterator it;

    for(it = lista.begin(); it != lista.end(); ++it){
        int i=0, j=0;
        for(i=0; i<3; ++i){
            for(j=0; j<3; ++j){
                if(it->visitado[i][j]!=node.arr[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
}


void swap (Node node, int i, int j, int si, int sj, priority_queue<Node> &fila, list<NodeVisitado> &lista, NodeVisitado visit){

    int aux;
    int x=0, y=0;
    bool check;

    x=i+(si);
    y=j+(sj);

    node.antecessores.push_back(node);

    aux = node.arr[i][j];
    node.arr[i][j]=node.arr[x][y];
    node.arr[x][y]=aux;

    check=checa_visitado(node, lista);

    if(check==false){
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                visit.visitado[i][j]=node.arr[i][j];
            }
        }
        node.prioridade=funcao(node);
        fila.push(node);
        lista.push_back(visit);

        node.printnode(node.arr);
        cout << "\n" << node.prioridade;
        cout << "\n\n";
    }
    else
        cout << "ja visitado\n";

}

void expande (Node node, priority_queue<Node> &fila, list<NodeVisitado> &lista, NodeVisitado visit){

int vi, vj;

    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(node.arr[i][j]==0){
                vi=i;
                vj=j;
            }
        }
    }


    if(vi+1<=2){
        swap(node, vi, vj, 1, 0, fila, lista, visit);
    }
    if(vj+1<=2){
        swap(node, vi, vj, 0, 1, fila, lista, visit);
    }
    if(vi-1>=0){
        swap(node, vi, vj, -1, 0, fila, lista, visit);
    }
    if(vj-1>=0){
        swap(node, vi, vj, 0, -1, fila, lista, visit);
    }
}

void printprio (priority_queue<Node> &fila){

}



int main()
{
    Node node, teste;
    NodeVisitado visit;
    int i=0, j=0, cont=0;
    priority_queue<Node> fila;
    list<NodeVisitado> lista;
    bool fim;


    printf("Digite 0 para indicar o espaço vazio\n");

    for(i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            cin >> node.arr[i][j];
            visit.visitado[i][j]=node.arr[i][j];
        }
    }
    node.prioridade=funcao(node);
    fila.push(node);
    lista.push_back(visit);

    while(!fila.empty()){
        cont++;
        teste=fila.top();
        fila.pop();
        fim=checa_objetivo(teste);
        if(fim==true){
            cout << "resultado encontrado depois de " << cont << " iteracoes\n";
            cout<<"o caminho para chegar nessa solução foi: \n";
            print_antecessores(teste.antecessores);
            teste.printnode(teste.arr);
            return 0;
        }
        else{
            expande(teste, fila, lista, visit);
        }
    }
    return 0;
}
