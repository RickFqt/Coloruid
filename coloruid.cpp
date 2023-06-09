#include <bits/stdc++.h>

void action(int n,  std::vector<int> adj, std::vector<std::vector<int>>& mat_adj, int nodeqtt,
             std::unordered_map<int, int> &map_colors){
    map_colors[n] = map_colors[adj[0]];
    for(int y: adj){
        for(int i = 0; i < nodeqtt; i++){
            if(mat_adj[i][y]){
                mat_adj[i][y] = 0;
                mat_adj[y][i] = 0;
                mat_adj[n][i] = 1;
                mat_adj[i][n] = 1;
            }
        }
    }
}
int main(){
    // vertice: rotulados por numeros, que estará associado a uma cor por um (dicionário? é esse o nome?)
    // aresta: par de vertices (v1, v2) (representada na lista de adjacência por 1 ou 0)
    // grafo: matriz de adjacencia

    // Leitura do numero de vertices do grafo
    int Nv = 9; // numero de vertices

    std::vector<int> Vertices(9);
    for(int i = 0; i < Nv; ++i){
        Vertices[i] = i;
    }

    // Leitura das cores
    std::unordered_map<int, int> map_colors;
    map_colors[0] = 0;
    map_colors[1] = 1;
    map_colors[2] = 2;
    map_colors[3] = 1;
    map_colors[4] = 1;
    map_colors[5] = 3;
    map_colors[6] = 0;
    map_colors[7] = 0;
    map_colors[8] = 1;


    std::vector<std::vector<int>> mat_adj(Nv, std::vector<int>(Nv, 0));

    int i = 0;
    int j = 0;
    while(i < Nv){
        mat_adj[i][j] = 1;
        ++i;
        ++j;
    }

    /// --------PRINT DA MATRIZ-------------
    std::cout << "V ";
    for(int k = 0; k < Nv; ++k){
        std::cout << k << " ";
    }
    std::cout << std::endl;
    for(int k = 0; k < Nv; ++k){
        std::cout << k << " ";
        for(int l = 0; l < Nv; ++l){
            std::cout << mat_adj[k][l] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    /// -------------------------------------

    // "Leitura" das arestas do grafo (fase 4)
    std::vector<std::pair<int, int>> adj = {{std::pair<int, int>(0, 1)}, std::pair<int, int>(0, 2), std::pair<int, int>(0, 3),
                                            std::pair<int, int>(1, 2), std::pair<int, int>(1, 5),
                                            std::pair<int, int>(2, 3), std::pair<int, int>(2, 5), std::pair<int, int>(2, 6),
                                            std::pair<int, int>(4, 5), std::pair<int, int>(4, 7),
                                            std::pair<int, int>(5, 6), std::pair<int, int>(5, 7), std::pair<int, int>(5, 8),
                                            std::pair<int, int>(6, 8),
                                            std::pair<int, int>(7, 8)};
    int size_adj = adj.size();
    for(int k = 0; k < size_adj; ++k){
        mat_adj[adj[k].first][adj[k].second] = 1;
        mat_adj[adj[k].second][adj[k].first] = 1;
    }

    /// --------PRINT DA MATRIZ-------------
    std::cout << "V ";
    for(int k = 0; k < Nv; ++k){
        std::cout << k << " ";
    }
    std::cout << std::endl;
    for(int k = 0; k < Nv; ++k){
        std::cout << k << " ";
        for(int l = 0; l < Nv; ++l){
            std::cout << mat_adj[k][l] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    /// -------------------------------------


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
        
            // (1) V = V - J
            // (2) Para todo vértice i, i \in V\{v}, faça:
                // Para todo vértice k, k \in J, faça:
                    // Se adj(i, k) = 1:
                        // adj(i, k) = adj(k, i) = 0; adj(i, v) = adj(v, i) = 1;
            // (3) Para todo vertice j, j \in J, faça:
                // adj(j, v) = adj(v, j) = 0;
            // (4) Para algum vertice j \in J, faça:
                // v.cor() = j.cor()
        
        // Ideia do Condensar (primeira condensação da fase 4):
        int v = 5; // Na prática, já encontrou esse valor antes

        std::vector<int> J{1, 4, 8}; // Na prática, já encontrou esses valores antes

        // (1) V = V - J
        Vertices =  std::vector<int> {0, 2, 3, 5, 6, 7}; // Fiz isso manualmente, refazer depois

        // (2)
        for(int x : Vertices){
            if(x == v){
                continue;
            }
            else{
                for(int y : J){
                    if(mat_adj[x][y] == 1){
                        // vertices adjacentes a algum vertice condensado ...
                        mat_adj[x][y] = 0;
                        mat_adj[y][x] = 0;

                        // ... sao agora adjacentes ao representante
                        mat_adj[x][v] = 1;
                        mat_adj[v][x] = 1;
                    }
                }
            }
        }

        // (3)
        for(int y : J){
            mat_adj[y][y] = 0;
            mat_adj[y][v] = 0;
            mat_adj[v][y] = 0;
        }

        // (4)
        map_colors[v] = map_colors[J[0]];

        /// --------PRINT DA MATRIZ-------------
        std::cout << "V ";
        for(int k = 0; k < Nv; ++k){
            std::cout << k << " ";
        }
        std::cout << std::endl;
        for(int k = 0; k < Nv; ++k){
            std::cout << k << " ";
            for(int l = 0; l < Nv; ++l){
                std::cout << mat_adj[k][l] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        /// -------------------------------------
    return 0;
}