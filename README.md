# Autores:

Matheus Augusto Correa de Oliveira, **RA:** 11201721710\
Henrique Jotten Mendonca de Souza, **RA:** 11045812

# <Projeto 3> Space Viewer

## Links:

[Código GitHub](https://github.com/Matheuzs/abcg)  
[GitHub Pages](https://matheuzs.github.io/abcg/spaceViewer/) (Não Funcional)  
[Video Demonstração](https://drive.google.com/file/d/1LNQIVZkMwnSdyRk5K_4-yJBMCwdf_osn/view?usp=sharing)


## Descrição do Projeto:

*Space Viewer* é um projeto 3D onde implementamos uma evolução do nosso projeto anterior (Solar System) e utilizamos referencias do projeto viewer6, esse programa tem como objetivo simular os planetas e satélites do sistema solar de forma individual e única.
Entre algumas das funcionalidade está a de poder rotacionar o planeta e dar zoom in/out, alem disso, cada planeta (exceto o Sol) pode ter o direcionamento da iluminação ajustado e todos os planetas/satélites possuem um help marker com breve descrição a seu respeito. No caso do planeta terra, possue textura complementar com as nuvens rotacionando em volta e é possivel ver diferentes representações geográficas.

![alt text](https://github.com/Matheuzs/abcg/blob/master/images/spaceViewer.gif?raw=true)

## Detalhes de Uso:
* Canto inferior esquerdo - Botão para modo tela cheia.
* Canto superior esquerdo - Sliders para direcionar a direção da fonte de luz nos eixos X, Y e Z, com exceção do Sol.
* Canto superior direito - Seleção do objeto do sistema solar a ser analisado, caso seja selecionado a Terra é habilitado outro combo box onde é possível alterar entre representações geográficas. 
* Canto superior direito - Informações do corpo celeste selecionado.
* Para girar a visão do corpo celeste basta segurar o botão esquerdo do mouse e arrastar.
* Com o scroll do mouse é possível alterar o zoom do planeta.
* Lista de Planetas/Satélites disponíveis:  
{"Sol", "Mercurio", "Venus", "Terra", "Lua", "Marte", "Jupiter", "Saturno", "Urano", "Netuno", "Ceres", "Haumea", "Makemake", "Eris"}
* Mapas geográficos da Terra disponíveis:  
{"Default", "Politico", "Noturno", "NoWater"}


## Detalhamento do Código:

* **Assets/**: Pasta onde está centralizado os shaders, mapas de textura e modelos. Possuímos os shaders de mapeamento das texturas normais, shader e mapa de textura da skybox e o shader para as texturas dos planetas/satélites. O planeta terra também possui a textura de nuvens;

* **constants.hpp**: Classe auxiliar que centraliza algumas das constantes do projeto para fins de organização, principalmente as Strings utilizadas nas descrições dos planetas;

* **main.cpp:** Nela utilizamos o abcg e definimos algumas configurções como o tamanho da tela (600x600), título e exibição do botão de tela cheia;

* **model.hpp / model.cpp**: Classe auxiliar que reune as funções relativas ao carregamento de texturas, normais e modelos, aqui também está a implementação para renderização dos modelo utilizado no projeto;

* **openglwindow.hpp / openglwindow.cpp**: Classe que define todos os comportamentos da tela opengl e dos objetos renderizados na tela, algumas de suas funções são:\
\
*handleEvent:* Implementa o tracking dos botões do Mouse;\
\
*initializeSkybox:* Função responsável por carregar os shaders e textura para o skybox, através dela iniciamos o VAO e VBO da textura de fundo da aplicação;\
\
*loadModel:* Carrega a textura do planeta renderizado ao carregar a aplicação, também valoriza as propriedades utilizadas nos shaders;\
\
*renderSkybox:* Carrega o programa da skybox e renderiza na tela;\
\
*getPlanetTexture:* Função que devolve qual o nome (String) do arquivo de textura que deve ser utilizada nos planetas;\
\
*getEarthTexture:* Função que devolve qual o nome (String) do arquivo de textura que deve ser utilizada para as texturas do Planeta Terra (Variantes);\
\
*loadPlanetsTextures:* Responsável por carregar a textura do planeta escolhido quando o mesmo é alterado na combobox;\
\
*loadEarthTextures:* Responsável por carregar as texturas variantes do planeta terra quando o mesmo está selecionado no combo box;\
\
*PaintUI:* Aqui temos todos os widgets utilizados no projeto, na primeira window temos o combo box onde é possível alternar entre os planetas, e no caso da terra é habilitado um novo combo box logo abaixo onde podemos alterar os mapas geográficos da terra. Nesta mesma window também possuímos o HelpMarker com a descrição do respectivo planeta.
A segunda window (habilitada apenas se o Sol nao está selecionado) temos os sliders onde é possível direcionar a luz, e também temos outro help marker onde possuimos uma descrição de ajuda.\
\
*HelpMarker:* Função para criarmos help markers com em uma window, onde passamos por parametro descrição e label.

* **trackball.hpp / trackball.cpp**: Classe que implementa os comportamento da camera com o Mouse.

# <Projeto 2> Solar System

## Links:

[Código GitHub](https://github.com/Matheuzs/abcg)  
[GitHub Pages](https://matheuzs.github.io/abcg/solarSystem/)

## Descrição do Projeto:

*Solar System* é um projeto 3D baseado no projeto [LookAt](https://hbatagelo.github.io/abcgapps/lookat/index.html), esse programa tem como objetivo simular os planetas do sistema solar orbitando em volta do Sol. Entre algumas das funcionalidade está a de poder mover a camera no espaço através das teclas:

### Movimentos da Camera:
* <kbd>A</kbd> e <kbd>←</kbd>: Move a camera ao redor do eixo Y para a Esquerda.  
* <kbd>D</kbd> e <kbd>→</kbd>: Move a camera ao redor do eixo Y para a Direita.  
* <kbd>W</kbd> e <kbd>↑</kbd>: Move a camera no eixo Z para Frente.   
* <kbd>S</kbd> e <kbd>↓</kbd>: Move a camera no eixo Z para Trás.  
* <kbd>Q</kbd>: Move a camera no eixo X para a Esquerda.  
* <kbd>E</kbd>: Move a camera no eixo X para a Direita.  

![alt text](https://github.com/Matheuzs/abcg/blob/master/images/solarsystem.png?raw=true)

Através dos Widgets presentes no topo da tela é possivel alternar entre os planetas do sistema solar, bem como alterar as propriedades de velocidade de orbita do planeta com o slider e retornar a camera para a posição inicial do programa com o botão.  

![alt text](https://github.com/Matheuzs/abcg/blob/master/images/solarsystem-widgets.png?raw=true)

**OBS:** O projeto não segue as distancias e proporções reais do sistema solar. 

## Detalhamento do Código:

* **Assets/**: Pasta onde está centralizado os shaders, aqui também está o modelo utilizado para os planetas (sphere.obj).

* **camera.hpp / camera.cpp**: Classe que possui todos os movimentos de camera, também é aqui onde definimos a ViewMatrix e ProjectionMatrix, posição inicial da camera e para onde ela estará apontando sua visão.

* **main.cpp:** Nela utilizamos o abcg e definimos algumas configurções como o tamanho da tela (600x600) e título.

* **openglwindow.hpp / openglwindow.cpp**: Classe que define todos os comportamentos da tela opengl e dos objetos renderizados na tela, algumas de suas funções são:  
*handleEvent:* Define o comportamento da camera para o teclado.  
*loadModelFromFile:* Carrega o modelo obj de esferas que se encontra na pasta de assets.  
*initializePlanetAttrib:* Popula o array de planetas e suas propriedades de cor e escala.  


# <Projeto 1> Pac-Man Rain

## Links:

[Código GitHub](https://github.com/Matheuzs/abcg)  
[GitHub Pages](https://matheuzs.github.io/abcg/pacmanRain/)

## Descrição do Projeto:

*Pac-Man Rain* é um jogo 2D que utiliza a biblioteca abcg e é baseado no projeto [Asteroids](https://hbatagelo.github.io/abcgapps/asteroids/index.html), o objetivo do jogo é que você fuja com o Fantasma dos Pac-Mans que estão caindo do topo da tela, toda a movimentação do fantasma é feita com as teclas <kbd>A</kbd> / <kbd>D</kbd> ou <kbd>←</kbd> / <kbd>→</kbd> se movimentando apenas no eixo X da tela.\
O jogo termina em Vitória se o fantasma sobreviver sem colidir com os Pac-Mans por 60 segundos (Timer na tela) e em Game Over em caso de colisão, em ambos o jogo resetará após 5 segundos da sua conclusão.

![alt text](https://github.com/Matheuzs/abcg/blob/master/images/pacmanrain.png?raw=true)

## Detalhamento do Código:

* **gamedata.hpp**: Arquivo de cabeçalho que implementa enums e struct para os estados do jogo e para a movimentacao.\
Os estados são "Playing", "GameOver" e "Win".\
A movimentação é "Right" e "Left".

* **ghost.cpp / ghost.hpp:** Classes que implementam os comportamentos/atributos do fantasma no jogo, ele é renderizado utilizando 17 vértices com GL_TRIANGLES, as coordenadas dos vértices são normalizadas no intervalo (15.5, 15.5).\
Na função update(), fazemos o contorno para que o fantasma não saia da visão da tela.

* **main.cpp:** Nela utilizamos o abcg e definimos algumas configurções como o tamanho da tela (600x600) e título.

* **openglwindow.cpp / openglwindow.hpp:** Classe principal onde definimos todos os comportamentos da tela opengl e chamamos as classes ghost e pacmans, nesta implementamos a utilizacao do SDL na função handleEvent() que define ocomportamento das teclasna movimentacao.
Em initializeGL(), carregamos as fontes que serão usadas nos textos e os shaders que estão na pasta assets.
É tembém nesta classe que implementamos a função de colisão e os casos de WIN / LOSE.

* **pacmans.cpp / pacmans.hpp:** Implementa os comportamentos/atributos dos pacmans que caem do topo da tela, a classe gera os pacmans na posicao (aleatória, 1.5) de 3 em 3 segundos através da função generatePacmans().
A geometria dos pacmans é gerada com 10 lados e utilizando GL_TRIANGLE_FAN.
