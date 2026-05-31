# Plotador de Funções

Projeto desenvolvido em C++ com o framework **Qt (Widgets)** para a plotagem e visualização de funções matemáticas em um plano cartesiano interativo.

## 📋 Especificações e Funcionalidades

O aplicativo permite ao usuário visualizar o comportamento de múltiplas expressões matemáticas simultaneamente. As principais funcionalidades incluem:

- **Inclusão de Funções:** Permite digitar expressões matemáticas na variável `x` (ex: `sin(x)`, `x^2 + 2*x`, `exp(x)`).
- **Paleta de Cores:** Possibilidade de escolher a cor da curva gerada (Azul, Vermelho, Verde ou Preto) usando botões de rádio na janela de diálogo.
- **Ajuste de Limites Dinâmico:** Controles numéricos (`QSpinBox`) na interface principal para definir o Zoom do gráfico (limites Mínimo e Máximo para os eixos X e Y).
- **Tabela de Acompanhamento:** Lista todas as funções ativas sendo desenhadas na tela e sua respectiva cor em uma tabela visual (`QTableWidget`).
- **Redimensionamento Automático:** O gráfico se adapta automaticamente ao maximizar ou redimensionar a janela principal (`resizeEvent`).
- **Coordenadas ao Clique:** Ao clicar em qualquer ponto da área do gráfico, a barra de status inferior exibe as coordenadas cartesianas reais (X e Y) equivalentes àquele pixel (`mouseReleaseEvent`).
- **Limpeza:** Um botão dedicado para apagar todas as funções e zerar a visualização.

## 🧩 Estrutura do Código

O projeto foi implementado seguindo o paradigma de Orientação a Objetos, dividido nas seguintes classes principais:

1. **`MainPlotador`**: A janela principal (`QMainWindow`). Gerencia os controles numéricos (SpinBoxes), a tabela de visualização e instancializa o gráfico dinamicamente.
2. **`Grafico`**: Uma classe herdada de `QLabel`. Responsável exclusivo por toda a lógica de renderização (`QPainter`), cálculos de conversão de tela para plano cartesiano e emissão de sinais de clique do mouse.
3. **`LehFuncao`**: Uma caixa de diálogo (`QDialog`) para capturar a digitação do usuário e a escolha da cor, emitindo os dados validados de volta para a classe principal.
4. **`Evaluator`**: Uma classe responsável pelo *parsing* das Strings matemáticas e resolução ponto a ponto para gerar os valores de Y com base em X.

## 🚀 Requisitos de Sistema

- **IDE:** Qt Creator
- **Framework:** Qt 5 ou Qt 6 (com módulo Widgets)
- **Build System:** CMake (Mínimo v3.16)
- **Compilador:** Compatível com C++17 (ex: MinGW 64-bit, GCC, ou MSVC)

## 🛠️ Como Compilar e Executar

Para executar este projeto em uma máquina local através do Qt Creator, siga o passo a passo abaixo:

1. **Extração:** 
   Descompacte o arquivo `.zip` contendo o código-fonte em um diretório de sua escolha. *(Certifique-se de que a pasta extraída não contenha a pasta oculta de build gerada em outra máquina).*

2. **Abertura do Projeto:**
   Abra o **Qt Creator**. Vá em `File > Open File or Project...` (Arquivo > Abrir Arquivo ou Projeto...) e selecione o arquivo **`CMakeLists.txt`** presente na raiz da pasta extraída.

3. **Configuração do Projeto (Kits):**
   Na tela que se abrirá, o Qt Creator pedirá para configurar o Kit do projeto. Selecione um kit padrão (ex: `Desktop Qt 6.x.x MinGW 64-bit`) e clique em **Configure Project** (Configurar Projeto).

4. **Compilação e Execução:**
   - Aguarde alguns segundos enquanto o CMake lê e configura os arquivos e dependências (`.cpp`, `.h` e `.ui`).
   - Clique no botão verde de **Run** (Executar) no canto inferior esquerdo da tela, ou pressione o atalho **`Ctrl + R`**.
   - O projeto será compilado gerando um novo diretório de Build localmente e a janela principal do Plotador será aberta.

## 💡 Como Usar

1. Com o programa aberto, note os SpinBoxes na parte superior. Eles definem os limites de tela. O padrão carrega de `-10` a `10` nos dois eixos.
2. Vá no menu de topo: **Plotagem > Função...**
3. Digite uma expressão válida na caixa de texto. Exemplo: `sin(x)`.
4. Selecione uma cor e clique em **OK**.
5. O gráfico traçará a curva imediatamente. Adicione quantas desejar.
6. Clique em qualquer lugar sobre o plano de fundo do gráfico e observe a barra de status na base da janela informando a coordenada real daquele ponto!
7. Clique no botão **APAGAR** a qualquer momento para limpar.

---
*Desenvolvido como projeto acadêmico de programação.*