# Autores:

Matheus Augusto Correa de Oliveira, **RA:** 11201721710\
Henrique Jotten Mendonca de Souza, **RA:** 11045812

# <Projeto 3> SolarMK2

## Links:

[Código GitHub](https://github.com/Matheuzs/abcg)  
[GitHub Pages](https://matheuzs.github.io/abcg/SolarMK2/)

## Descrição do Projeto:

*SolarMK2* é um projeto 3D baseado no nosso projeto anterior(Solar System), esse programa tem como objetivo simular os planetas do sistema solar de forma individual e unica.
Entre algumas das funcionalidade está a de poder mover a camera no espaço através o mouse como trackball, alem disso, cada planeta pode ter o direcionamento da iluminação ajustado e suas informações técnicas são apresentadas em uma janela separada. No caso do planeta terra, ainda é possivel ver diferentes representações geográficas.

## Detalhes de Uso:



## Detalhamento do Código:



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
