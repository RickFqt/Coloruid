#include <bits/stdc++.h>

int main(){
    // vertice: rotulados por numeros, que estará associado a uma cor por um (dicionário? é esse o nome?)
    // aresta: par de vertices (v1, v2) (representada na lista de adjacência por 1 ou 0)
    // grafo: lista de arestas


    // Ler grafo G = (V, A):
        // Ler vértices, e suas cores respectivas
        // Ler arestas (criar matriz de adjacência n por n)

    // Enquanto houver mais de um vértice em V, faça:
        // Se houver vértices de cor única no grafo:
            // Se houver vértice v ligado a todos os vértices J de uma cor:
                // Continue
            // Senão:
                // Achar o vértice v de cor única ligado a maior quantidade de vértices J de mesma cor
                // Continue
        // Senão:
            // Se houver vértice v ligado a todos os vértices J de uma cor:
                // Continue
            // Senão:
                // Achar o vértice v ligado a maior quantidade de vértices J de mesma cor
                // Continue
        

        // Condensar v com todos os vértices J:
        
            // V = V - J
            // Para todo vértice i, i \in V\{v}, faça:
                // Para todo vértice k, k \in J, faça:
                    // Se adj(i, k) = 1:
                        // adj(i, k) = adj(k, i) = 0; adj(i, v) = adj(v, i) = 1;
            // Para todo vertice j, j \in J, faça:
                // adj(j, v) = adj(v, j) = 0;
            // Para algum vertice j \in J, faça:
                // v.cor() = j.cor()
    return 0;
}