#include <bits/stdc++.h>

int main(){
    // vertice: par de rótulo e cor (v, c)
    // aresta: par de vertices (v1, v2)
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
        

        // V = V - J
        // Condensar v com todos os vértices J:
            // Para todo vértice i, i \in V/{v}, faça:
                // Se i adjacente a j, para algum j \in J:
                    // Tornar i adjacente a v; remover j da lista de adjacência de i
        // v.cor() = j.cor()
    return 0;
}