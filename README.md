# TODO

 * Ler .pal (1)
   * guardar tamanhos diferentes e número máximo de permutações por tamanho
     * ler número máximo de permutações por tamanho para array com indíce = tamanho, zero se não existir esse tamanho

 * Ler .dic (1)
   * Guardar número de palavras por tamanho

 * Ler .dic (2)
   * ler vertíces do mesmo tamanho (`Vertex *`) para array (`Vertex **`) com indíce = tamanho, NULL se não existir esse tamanho
     * `typedef Graph Vertex*`

 * Ler .pal (2)
   * ler linha
   * dijkstra
     * encontrar vértice de partida (destino é desnecessário?) eficientemente no array de vértices/grafo (`Vertex *` que é o mesmo que `Graph`)
   * escrever linha .stat
     * escrever vértices ao longo do caminho encontrado

### Criação de grafos
 * Para cada grafo, para cada vértice `a`:
   * testar se está ligado a outro vértice `b` com peso `p`
   * atualizar lista de adjacências de `a` e `b`
   * evitar ligar um vértice a si mesmo (número de chars em comum = 0)

### Problemas
