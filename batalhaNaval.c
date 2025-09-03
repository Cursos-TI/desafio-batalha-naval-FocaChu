#include <stdio.h>

// Constantes globais
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Declarando funções
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], const char* titulo);
int posicaoValida(int linha, int coluna);
int verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                         int linha_inicio, int coluna_inicio, int orientacao);
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                   int linha, int coluna, int orientacao, const char* tipo);

void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void exibirHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], const char* nome);
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                                 int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                                 int linha_centro, int coluna_centro);

int main() {
    printf("=== BATALHA NAVAL - NÍVEL MESTRE ===\n");
    
    // Tabuleiro principal para navios
    int tabuleiroNavios[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiroNavios);
    
    // Tabuleiro para habilidades especiais
    int tabuleiroHabilidades[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Posicionamento do navios
    printf("\n--- POSICIONAMENTO DE NAVIOS ---\n");
    
    // Navio horizontal
    if (posicionarNavio(tabuleiroNavios, 2, 3, 0, "horizontal")) {
        printf("✓ Navio horizontal posicionado em (2,3)\n");
    }
    
    // Navio vertical
    if (posicionarNavio(tabuleiroNavios, 5, 7, 1, "vertical")) {
        printf("✓ Navio vertical posicionado em (5,7)\n");
    }
    
    // Navio diagonal (direita-baixo)
    printf("Posicionando navio diagonal 1...\n");
    if (verificarSobreposicao(tabuleiroNavios, 1, 1, 2)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiroNavios[1 + i][1 + i] = 3;
        }
        printf("✓ Navio diagonal 1 posicionado em (1,1)\n");
    }
    
    // Navio diagonal (direita-cima)
    printf("Posicionando navio diagonal 2...\n");
    if (verificarSobreposicao(tabuleiroNavios, 7, 2, 3)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiroNavios[7 - i][2 + i] = 3;
        }
        printf("✓ Navio diagonal 2 posicionado em (7,2)\n");
    }
    
    // Exibir tabuleiro com navios
    exibirTabuleiro(tabuleiroNavios, "TABULEIRO COM NAVIOS (0 = Água, 3 = Navio)");

    // Habilidades especiais
    printf("\n--- HABILIDADES ESPECIAIS ---\n");
    
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    
    // Criar habilidades especiais
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Exibir padrões das habilidades
    printf("\nPadrões das Habilidades Especiais:\n");
    exibirHabilidade(cone, "CONE");
    exibirHabilidade(cruz, "CRUZ");
    exibirHabilidade(octaedro, "OCTAEDRO");
    
    // Aplicar habilidades no tabuleiro
    printf("\nAplicando habilidades no tabuleiro...\n");
    
    // Aplicar cone na posição (2,2)
    aplicarHabilidadeNoTabuleiro(tabuleiroHabilidades, cone, 2, 2);
    printf("✓ Habilidade CONE aplicada no centro (2,2)\n");
    
    // Aplicar cruz na posição (5,5)
    aplicarHabilidadeNoTabuleiro(tabuleiroHabilidades, cruz, 5, 5);
    printf("✓ Habilidade CRUZ aplicada no centro (5,5)\n");
    
    // Aplicar octaedro na posição (7,7)
    aplicarHabilidadeNoTabuleiro(tabuleiroHabilidades, octaedro, 7, 7);
    printf("✓ Habilidade OCTAEDRO aplicada no centro (7,7)\n");
    
    // Exibir tabuleiro com áreas afetadas pelas habilidades
    exibirTabuleiro(tabuleiroHabilidades, "TABULEIRO COM HABILIDADES (0 = Não afetado, 1 = Afetado)");

    // Montando tabuleiro
    printf("\n--- VISÃO GERAL DO JOGO ---\n");
    
    // Tabuleiro combinado (navios + habilidades)
    int tabuleiroCombinado[TAM_TABULEIRO][TAM_TABULEIRO];
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            // Se tem navio, mostra 3; se não, mostra valor da habilidade
            tabuleiroCombinado[i][j] = (tabuleiroNavios[i][j] == 3) ? 3 : tabuleiroHabilidades[i][j];
        }
    }
    
    exibirTabuleiro(tabuleiroCombinado, "TABULEIRO COMBINADO (0 = Água, 1 = Habilidade, 3 = Navio)");

    return 0;
}

// Helpers

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], const char* titulo) {
    printf("\n%s:\n", titulo);
    
    // Cabeçalho com números das colunas
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linha separadora
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO * 3; j++) {
        printf("-");
    }
    printf("\n");
    
    // Conteúdo do tabuleiro
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d|", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

int verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                         int linha_inicio, int coluna_inicio, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int linha, coluna;
        
        switch(orientacao) {
            case 0: // Horizontal
                linha = linha_inicio;
                coluna = coluna_inicio + i;
                break;
            case 1: // Vertical
                linha = linha_inicio + i;
                coluna = coluna_inicio;
                break;
            case 2: // Diagonal direita-baixo
                linha = linha_inicio + i;
                coluna = coluna_inicio + i;
                break;
            case 3: // Diagonal direita-cima
                linha = linha_inicio - i;
                coluna = coluna_inicio + i;
                break;
            default:
                return 0;
        }
        
        if (!posicaoValida(linha, coluna)) {
            printf("ERRO: Posição (%d,%d) fora do tabuleiro!\n", linha, coluna);
            return 0;
        }
        
        if (tabuleiro[linha][coluna] == 3) {
            printf("ERRO: Sobreposição em (%d,%d)!\n", linha, coluna);
            return 0;
        }
    }
    return 1;
}

int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                   int linha, int coluna, int orientacao, const char* tipo) {
    printf("Posicionando navio %s em (%d,%d)...\n", tipo, linha, coluna);
    
    if (verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            switch(orientacao) {
                case 0: // Horizontal
                    tabuleiro[linha][coluna + i] = 3;
                    break;
                case 1: // Vertical
                    tabuleiro[linha + i][coluna] = 3;
                    break;
            }
        }
        return 1;
    }
    return 0;
}

void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Padrão cone (3x5)
    int padrao[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = padrao[i][j];
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Padrão cruz (3x5)
    int padrao[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = padrao[i][j];
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Padrão octaedro (3x5)
    int padrao[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = padrao[i][j];
        }
    }
}

void exibirHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], const char* nome) {
    printf("\n%s:\n", nome);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                                 int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                                 int linha_centro, int coluna_centro) {
    int offset = TAM_HABILIDADE / 2; // 2 para centralizar
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha_tab = linha_centro - offset + i;
            int coluna_tab = coluna_centro - offset + j;
            
            if (posicaoValida(linha_tab, coluna_tab)) {
                // Usa operador OR para não sobrescrever outras habilidades
                tabuleiro[linha_tab][coluna_tab] |= habilidade[i][j];
            }
        }
    }
}