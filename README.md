# CG - Geometric shapes
Projeto Da Disciplina de Computação Gráfica - UFERSA, modelagem de formas geométricas.

#### Componentes
- **Rafael Luan Do Nascimento**
- **Camila Perin De Carvalho**

#### Formas Geométricas Modeladas
- **Esfera**
- **Cilindro**
- **Cone**
- **Toroid**

### Dependências
- **freeglut**
- **make**

#### Instalação
```sh
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
#### Compilar
```sh
make
```
#### Executar
```sh
make run
```
ou
```sh
./cg-geometric-shapes
```
#### Limpar Arquivos
```sh
make clean
```
### Interação
|  Tecla |  Ação  |
| ------ | ------ |
|**F1**| Seleciona a Esfera |
|**F2**| Seleciona o Cilindro |
|**F3**| Seleciona o Cone |
|**F4**| Seleciona o Toroid |
|**t**| Alterna a Textura da Forma Geométrica selecionada |
|**w**| Passa para a Próxima Forma Geométrica |
|**q**| Aumenta a velicidade de Rotação das Formas Geométricas |
|**x**| Rotação no Eixo X |
|**y**| Rotação no Eixo Y |
|**z**| Rotação no Eixo Z |
|**b**| Ativa a Rotação no Eixo X |
|**n**| Ativa a Rotação no Eixo Y |
|**m**| Ativa a Rotação no Eixo Z |
|**R**| Aumenta as divisões Radias |
|**r**| Diminui as divisões Radias |
|**H**| Aumenta as divisões de Altura |
|**h**| Diminui as divisões de Altura |
|**ESC**| Termina a Execução |

##### Licença
MIT