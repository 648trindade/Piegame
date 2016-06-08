# Piegame

Piegame é uma biblioteca desenvolvida para a criação facilitada de jogos 2D em C++.

É inspirada na biblioteca Pygame, de Python (a qual sempre gostamos muito de escrever nossos jogos).

Você encontrará diversas semelhanças com Pygame - infelizmente não em tudo - e essa é justamente a idéia: 
trazer a facilidade do Pygame para C++.

Vamos buscar implementar todas as coisas úteis e simples de Pygame sem pecar muito com o desempenho devido o nível de
abstração (pra que dividir quando se pode usar shift? :D ).

A biblioteca em si é composta de classes que abrigam funções wrapper da biblioteca SDL2 (Pygame foi originalmente
criado com base na SDL 1.2).

Está em pleno processo de desenvolvimento: Estamos tentando portar a API do Pygame, reaproveitando inclusive códigos
dele (com devidas referências, é claro) como por exemplo pra conversão de cores.

## O que está pronto:
| Classe/Estrutura Piegame | Classe Pygame | Status          | Definição |
| :----------------------- | :------------ | :-------------- | :-------- |
| Point                    | -             | Pronta          | Representa um ponto em coordenadas 2D (x,y) |
| Dimension                | -             | Pronta          | Representa um tamanho/dimensão (altura, largura) |
| Color                    | Color         | Pronta          | Representa uma cor RGBA |
| Rect                     | Rect          | Pronta          | Representa um retângulo |
| display                  | display       | Desenvolvimento | Controles de janela |
| Texture                  | Surface       | -               | Representa algo imprimível na tela (imagem, mapa de cores, etc) |
| (A adicionar) ...        | ...           | ...             | ... |

#### Autor: Rafael Gauna Trindade
#### Email: rtrindade@inf.ufsm.br