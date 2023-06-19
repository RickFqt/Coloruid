#include <bits/stdc++.h>


std::vector<std::string> tokenize(std::string s){
    std::vector<std::string> tokens;
    int n = s.length();
    int count = 0;
    int start = 0;
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
        toCheck = theOnes;
    }
    else{        
        toCheck = Vertices;
    }
    int v_max_colors = -1;
    int c_max_colors = -1;
    int max_colors = -1;

    int v_all_max_colors = -1;
    int c_all_max_colors = -1;
    int all_max_colors = -1;
    int current_all_max_colors = -1;
    
    
    int number;
    for(int i : toCheck){
        current_all_max_colors = 0;
        for(int j = 0; j < nc; ++j){
            number = allInOne(i, mat_adj, n_colors[j]);
            // Se houver vértice v ligado a todos os vértices J de uma cor:
            if(number == n_colors[j].size() && number != 0){
                current_all_max_colors++;
                if(current_all_max_colors > all_max_colors){
                    all_max_colors = current_all_max_colors;
                    v_all_max_colors = i;
                    c_all_max_colors = j;
                }
            }
            // Senão:
            // Achar o vértice v ligado a maior quantidade de vértices J de mesma cor
            if(number > max_colors){
                max_colors = number;
                v_max_colors = i;
                c_max_colors = j;
            }
        }
    }
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

    // Remover adj de current_nodes
    std::list<int>::iterator it = current_nodes.begin();
    
    std::vector<int>::iterator it_adj = adj.begin();
    
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
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " <caminho_para_arquivo>" << std::endl;
        return 1;
    }
    const std::string filePath = argv[1];
    std::ifstream file(filePath);
    if (!file) {
        std::cout << "Não foi possível abrir o arquivo: " << filePath << std::endl;
        return 1;
    }
    // Leitura do numero de vertices do grafo
    int Nv = 0; // numero de vertices
    int nc = 0; // numero de cores
    
    // Mapeamento das cores
    std::unordered_map<int, int> map_colors;
    
    // matriz de adjacência
    std::vector<std::vector<int>> mat_adj;
    
    //variaveis para auxiliar a leitura
    bool first = true;
    int colorcount = 0;
    int edgecount = 0;
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
            if(colorcount < Nv){
                colorcount++;
                map_colors[std::stoi(tokenLine[0])] = std::stoi(tokenLine[1]);
            }else{
                if(mat_adj[std::stoi(tokenLine[0])][std::stoi(tokenLine[1])] == 0)edgecount++;
                mat_adj[std::stoi(tokenLine[0])][std::stoi(tokenLine[1])] = 1;
                mat_adj[std::stoi(tokenLine[1])][std::stoi(tokenLine[0])] = 1;
            }
        }
    }
    file.close();
    std::cout << "Número de arestas: " << edgecount << std::endl;
    // lista de vértices
    std::list<int> Vertices;
    for(int i = Nv - 1; i >= 0; --i){
        Vertices.push_front(i);
    }


    /// --------PRINT DA MATRIZ-------------
    std::cout << "----- Matriz Inicial ----- ";
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

    int actcount = 0;
    while(Vertices.size() != 1){
        std::pair<int, int> a = find(Vertices, mat_adj, map_colors, nc);
        int v = a.first;
        int idealColor = a.second;
        std::cout << "A ação será no vértice " << v << " com a cor " << idealColor << "."<< std::endl;
        actcount++;
        // Função que encontra os adjacentes com a mesma cor de um vértice
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

    return 0;
}