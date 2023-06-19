/*!
 * @file main.cpp
 * Benchmarking suit to compare sorting algorithms under verios situations.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <random>
#include <iterator>
#include <bits/stdc++.h>
using std::function;

//=== ALIASES

/// Sorting algorithms data type
template< typename RandomIt, typename Compare >
using alg_type = void (*) (RandomIt first, RandomIt last, Compare cmp);
/// Data type we are working with.
using value_type = unsigned int;
/// Size type.
using size_type = size_t;
/// Alias for duration measure.
using duration_t = std::chrono::duration<double>;


//=== FUNCTION IMPLEMENTATION.

/// Print time different in an humam readable form.
void print_diff( const std::chrono::time_point<std::chrono::steady_clock> &start,
                 const std::chrono::time_point<std::chrono::steady_clock> &end,
                std::ofstream out_file ){
    auto diff = end - start;
    // Milliseconds (10^-3)
    out_file << "\t\t>>> " << std::chrono::duration <double, std::milli> (diff).count() << std::endl;
    // Nanoseconds (10^-9)
    //out_file << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count() << std::endl;
    // Seconds
    //auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    //out_file << "\t\t>>> " << diff_sec.count() << " s" << std::endl;
}


std::vector<std::string> tokenize(std::string s){
    std::vector<std::string> tokens;
    int n = s.length();
    int count = 0;
    int start = 0;
    //add $3 $2 $1
    for(int i = 0; i < n; i++){
        if(s[i] == ' '){
            std::string t = s.substr(start,count);
            tokens.push_back(t);
            count = 0;
            start = i+1;
        }else{
            count++;
        }
    }
    std::string t = s.substr(start, n - start);
    tokens.push_back(t);
    return tokens;
}


int allInOne(int n, std::vector<std::vector<int>>& mat_adj, std::vector<int>& onecvertices){
    int retorno = 0;
    for(int i: onecvertices){
        if(i != n && mat_adj[n][i])retorno++;
    }
    return retorno;
}
std::pair<int, int> find(std::list<int>& Vertices, std::vector<std::vector<int>>& mat_adj, std::unordered_map<int, int> &map_colors, int nc){
    std::vector<std::vector<int>> n_colors(nc);

    std::list<int> theOnes;
    for(int i : Vertices){
        n_colors[map_colors[i]].push_back(i);
    }
    for(int i = 0; i < nc; i++){
        if(n_colors[i].size() == 1){
            theOnes.push_front(n_colors[i][0]);
        }
    }
    std::list<int> toCheck;
    
    // Se houver vértices de cor única no grafo:
    if(!theOnes.empty()){
        // std::cout << "theOnes" << std::endl;
        toCheck = theOnes;
    }
    else{
        // std::cout << "Vertices" << std::endl;
        toCheck = Vertices;
    }

    // for(int i = 0; i < n_colors.size(); ++i){
    //     for (int j : n_colors[i]){
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }
    int v_max_colors = -1;
    int c_max_colors = -1;
    int max_colors = -1;

    int v_all_max_colors = -1;
    int c_all_max_colors = -1;
    int all_max_colors = -1;
    int current_all_max_colors = -1;
    
    // std::vector<int> all_colors_count = (Vertices.size(),-1);
    
    int number;
    for(int i : toCheck){
        //std::cout << "vértice " << i<< std::endl;
        current_all_max_colors = 0;
        for(int j = 0; j < nc; ++j){
            number = allInOne(i, mat_adj, n_colors[j]);
            //std::cout << "number da cor " << j <<": " << number << std::endl;
            // Se houver vértice v ligado a todos os vértices J de uma cor:
                // std::cout<< "nó " << i << std::endl;
                // std::cout<< "cor " << j << std::endl;
                // std::cout<< "number " << number << std::endl;
                // std::cout<< "size " << n_colors[j].size() << std::endl;
            if(number == n_colors[j].size() && number != 0){
                current_all_max_colors++;
                if(current_all_max_colors > all_max_colors){
                    all_max_colors = current_all_max_colors;
                    v_all_max_colors = i;
                    c_all_max_colors = j;
                }
                // return {i, j};
            }
            if(number > max_colors){
                //std::cout <<"cor " << j << std::endl;
                max_colors = number;
                v_max_colors = i;
                c_max_colors = j;
            }
        }
    }
    // Senão:
    // Achar o vértice v ligado a maior quantidade de vértices J de mesma cor
    // std::cout << "nós verdes: " << std::endl;
    // for(int i : n_colors[1]){
    //     std::cout << i << std::endl;
    // }
    // std::cout << std::endl;
    if(all_max_colors > 0){
        return {v_all_max_colors, c_all_max_colors};    
    }else{
        return {v_max_colors, c_max_colors};
    }

}

std::vector<int> findAdj(int v, int c, std::vector<std::vector<int>>& mat_adj, 
                        std::unordered_map<int, int> &map_colors){

    int size = mat_adj[v].size();    
    std::vector<int> retorno;
    for(int i = 0; i < size; i++){
        if(map_colors[i] == c && mat_adj[v][i])
            retorno.push_back(i);
    }
    return retorno;
}

void action(int n,  std::vector<int> adj, std::vector<std::vector<int>>& mat_adj,
             std::list<int>& current_nodes, std::unordered_map<int, int> &map_colors){
    map_colors[n] = map_colors[adj[0]];

    // std::cout << "vc buga aqui" << std::endl;

    // Remover adj de current_nodes
    std::list<int>::iterator it = current_nodes.begin();
    
    std::vector<int>::iterator it_adj = adj.begin();
    
    //std::cout << "pre while" << std::endl;
    while (it_adj != adj.end())
    {
        if(*it == *it_adj){
            it = current_nodes.erase(it);
            ++it_adj;
        }
        else{
            ++it;
        }
        
    }
    // std::cout << "não" << std::endl;
    //std::cout << "pos while" << std::endl;
    for(int y: adj){
        for(int i: current_nodes){

            if(mat_adj[i][y]){
                // vertices adjacentes a algum vertice condensado ...
                mat_adj[i][y] = 0;
                mat_adj[y][i] = 0;

                // ... sao agora adjacentes ao representante
                mat_adj[n][i] = 1;
                mat_adj[i][n] = 1;
            }
        }
        mat_adj[y][y] = 0;
    }
    //std::cout << "pos for" << std::endl;
}


//=== CONSTANT DEFINITIONS.

//=== The main function, entry point.
int main( int argc, char * argv[] ){


    std::string testCases[20] = {
        "./a.txt",
        "./b.txt",
        "./c.txt",
        "./d.txt",
        "./e.txt",
        "./f.txt",
        "./g.txt",
        "./h.txt",
        "./i.txt",
        "./j.txt",
        "./k.txt",
        "./l.txt",
        "./m.txt",
        "./n.txt",
        "./o.txt",
        "./p.txt",
        "./q.txt",
        "./r.txt",
        "./s.txt",
        "./t.txt"
    };

    std::ofstream out_file;
    out_file.open ("outputTime.txt");
    for(int times = 0; times < 20; ++times){
        double elapsed_time_mean = 0;

        std::ifstream file(testCases[times]);
        if (!file) {
            std::cout << "Não foi possível abrir o arquivo: " << testCases[times] << std::endl;
            return 1;
        }
        // vertice: rotulados por numeros, que estará associado a uma cor por um (dicionário? é esse o nome?)
        // aresta: par de vertices (v1, v2) (representada na lista de adjacência por 1 ou 0)
        // grafo: matriz de adjacencia

        // Leitura do numero de vertices do grafo
        int Nv = 0; // numero de vertices
        int nc = 0; // numero de cores
        
        // Leitura das cores
        std::unordered_map<int, int> map_colors;
        
        // matriz de adjacência
        std::vector<std::vector<int>> mat_adj;
        
        //variaveis para auxiliar a leitura
        bool first = true;
        int colorcount = 0;
        std::string line;
        std::vector<std::string> tokenLine;
        while (std::getline(file, line)) {
            tokenLine = tokenize(line);
            if(first){
                first = false;
                nc = std::stoi(tokenLine[0]);
                Nv = std::stoi(tokenLine[1]);
                mat_adj.assign(Nv, std::vector<int>(Nv, 0));
                int i = 0;
                int j = 0;
                while(i < Nv){
                    mat_adj[i][j] = 1;
                    ++i;
                    ++j;
                }
            }else{
                // std::cout << "chega aqui?" << std::endl;
                if(colorcount < Nv){
                    colorcount++;
                    // std::cout << "buga aqui?" << std::endl;
                    map_colors[std::stoi(tokenLine[0])] = std::stoi(tokenLine[1]);
                }else{
                    mat_adj[std::stoi(tokenLine[0])][std::stoi(tokenLine[1])] = 1;
                    mat_adj[std::stoi(tokenLine[1])][std::stoi(tokenLine[0])] = 1;
                }
            }
        }
        file.close();

        /// ============================== TIMER COMEÇA =================================================
        auto start = std::chrono::steady_clock::now();
        // lista de vértices
        std::list<int> Vertices;
        for(int i = Nv - 1; i >= 0; --i){
            Vertices.push_front(i);
        }

        /// --------PRINT DA MATRIZ-------------
        std::cout << "Cor de cada vértice (vertice, cor): ";
        for(int k = 0; k < Nv; ++k){
            std::cout << "(" << k << ", " << map_colors[k] <<");";
        }std::cout << std::endl;
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
        int actcount = 0;
        while(Vertices.size() != 1){
            // std::cout << "AAAAA1" << std::endl;
            std::pair<int, int> a = find(Vertices, mat_adj, map_colors, nc);
            //std::cout << "AAAAA2" << std::endl;
            int v = a.first; // Na prática, já encontrou esse valor antes
            int idealColor = a.second;
            std::cout << "A ação será no vértice " << v << " com a cor " << idealColor << "."<< std::endl;
            actcount++;
            // vou fazer uma função que encontra os adjacentes em função do ponto e da cor
            std::vector<int> J = findAdj(v, idealColor, mat_adj, map_colors);

            action(v, J, mat_adj, Vertices, map_colors);


            /// --------PRINT DA MATRIZ-------------
            std::cout << "Cor de cada vértice (vertice, cor): ";
            for(int k : Vertices){
                std::cout << "(" << k << ", " << map_colors[k] <<");";
            }std::cout << std::endl;
            std::cout << "V ";
            for(int k : Vertices){
                std::cout << k << " ";
            }
            std::cout << std::endl;
            for(int k : Vertices){
                std::cout << k << " ";
                for(int l : Vertices){
                    std::cout << mat_adj[k][l] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            /// -------------------------------------
        }
        std::cout << "Foram necessárias " << actcount << " ações para chegar no grafo trivial" << std::endl;
        auto end = std::chrono::steady_clock::now();
        /// ============================== TIMER TERMINA =================================================
        auto diff( end - start );

        elapsed_time_mean = ( std::chrono::duration <double, std::milli> (diff).count() );

        out_file << "# Medição do tempo do teste "<< times << ": " << std::to_string(elapsed_time_mean) << "\n";
    }

    out_file.close();


    return EXIT_SUCCESS;
}