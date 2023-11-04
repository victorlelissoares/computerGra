# Documentação do Código OpenGL 3D

Este documento fornece uma breve documentação do código em C++ que 
utiliza a biblioteca OpenGL para criar uma aplicação 3D simples. O código é 
dividido em várias partes, incluindo a inicialização do OpenGL, a criação de 
um cubo 3D, a compilação e ligação de shaders, bem como a renderização dos objetos.

## Autores: 

####  Victor Lelis

#### Matheus Vieira

#### Victor Ramires

## Requisitos

Para executar o código, você precisará ter as seguintes bibliotecas instaladas:

- GLFW: Uma biblioteca para criar janelas com contexto OpenGL.
- GLEW: Uma biblioteca para gerenciar extensões OpenGL.
- GLM: Uma biblioteca para matemática para OpengGL.
- Um compilador C++ compatível com C++11.


## Variáveis Globais

- `programId`: Um identificador para o programa OpenGL.
- `cubeVAO`: Um identificador para o Vertex Array Object (VAO) do cubo.
- `indexOffSet`: Um deslocamento de índice para o buffer.
- `matrixId`: O identificador para a matriz no shader.
- `projection`: Uma matriz de projeção.

## Funções

### `ReadProgramSource(const std::string filePath)`

Esta função lê o código-fonte do shader de um arquivo e retorna uma string 
contendo o código.

### `CompileAndLinkShaders()`

Essa função cria, compila e vincula shaders (vertex e fragment shaders) para 
criar um programa OpenGL. Ele usa os shaders localizados em "./shaders/Main.vert" e 
"./shaders/Main.frag". Os shaders são vinculados ao `programId`.

### `CreateCube()`

A função CreateCube() é responsável por criar um cubo 3D para ser renderizado no 
contexto OpenGL. Esta função define os vértices, cores e índices do cubo e configura 
os buffers e o Vertex Array Object (VAO) necessários para renderização. Vamos examinar o 
funcionamento detalhado dessa função:

Definição de Vértices, Cores e Índices:

Dentro da função, são definidos os vértices do cubo, as cores para cada face do cubo e os índices que determinam a ordem dos vértices para formar os triângulos que compõem o cubo. Os vértices são armazenados em um array vertices, as cores em um array colors, e os índices em um array indices. Cada vértice possui uma posição tridimensional (x, y, z), e as cores são definidas como valores RGB.

Geração de Buffers:

A função chama glGenVertexArrays() e glGenBuffers() para gerar identificadores para o VAO e um buffer. Esses identificadores são armazenados em cubeVAO e BufferId, respectivamente.

Configuração do Buffer:

A função chama glBindBuffer(GL_ARRAY_BUFFER, BufferId) para fazer com que o buffer BufferId seja o buffer atual. No entanto, neste momento, o buffer ainda não foi preenchido com dados.

Preenchimento do Buffer:

Os dados (vértices, cores e índices) são inseridos no buffer usando a função glBufferSubData(). Isso é feito em três etapas consecutivas:

Os vértices são copiados para o buffer na posição currentOffSet do buffer.
As cores são copiadas para o buffer na posição currentOffSet após os vértices.
Os índices são copiados para o buffer na posição currentOffSet após as cores.
O deslocamento currentOffSet é atualizado a cada etapa para garantir que os dados sejam colocados nas posições corretas do buffer.

Definição do indexOffSet:

Após a cópia dos índices no buffer, o valor de indexOffSet é definido como o valor atual de currentOffSet, indicando onde começam os índices no buffer.

Configuração do VAO:

O VAO é vinculado usando glBindVertexArray(cubeVAO). Dentro deste bloco, as seguintes 
operações são realizadas:

O buffer de elementos (índices) é vinculado ao VAO usando glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId).
O buffer com os dados dos vértices é vinculado ao VAO usando glBindBuffer(GL_ARRAY_BUFFER, BufferId).
Configuração de Atributos de Vértice:

Nesta etapa, são configurados os atributos de vértice para o VAO. Isso inclui a posição dos vértices e as cores. Os seguintes passos são executados:

O atributo de posição (0) é ativado usando glEnableVertexAttribArray(0), e sua configuração é definida com glVertexAttribPointer(), indicando que os dados de posição são compostos por 3 valores de ponto flutuante.
O atributo de cor (1) é ativado usando glEnableVertexAttribArray(1), e sua configuração é definida com glVertexAttribPointer(), indicando que os dados de cor são compostos por 3 valores de ponto flutuante sem normalização.
Desvinculação do VAO:

Após a configuração dos atributos de vértice, o VAO é desvinculado com glBindVertexArray(0).

### `initOpenGL()`

Inicializa o OpenGL, chama `CreateCube()` para criar o cubo, chama `CompileAndLinkShaders()` para compilar e vincular os shaders, configura a matriz de projeção e obtém o identificador da matriz no shader.

### `desenha(float dt)`

Esta função é responsável por desenhar o cubo na tela. Ela aplica transformações matriciais aos cubos e, em seguida, desenha-os usando os shaders vinculados. O `dt` é usado para animar os cubos.

### `main()`

A função `main()` inicia o GLFW, cria uma janela, inicializa o OpenGL, inicia um loop de renderização e, finalmente, libera os recursos após o término do programa.

###  Projeção
A projeção utilizada foi a projeção perspectiva (Frustrum), a função utilizada foi retirada da biblioteca `glm`, a função `glm::perspective(glm::radians(45.f), 800.f / 680.f, 0.1f, 10.f)` cria um frustrum
com o plano de recorte de frente á `0.1` unidades da câmera e o plano de recorte de fundo á `10.0` unidades da posição da câmera. Os parâmetros passados a função são, respectivamente, o `fovy` que é o 
ângulo de abertura da câmera, que é definido pelos `projetores` do frustrum. O segundo parâmetro, `aspect`, é a razão de aspecto do frustrum, que é definido pela, largura/altura. e por fim, os dois ultimas parâmetros
são a distânca da câmera ao plano de frente, e ao plano de fundo.

#### Visão do Frustrum
<img src="ImagensReadme/A-viewing-frustum-defined-in-OpenGL-to-emulate-the-real-camera.png">

## Shader de Vértices
O shader de vértices recebe duas váriaveis de entrada, 
`in layout (location=0) vec3 vertexIn` e 
`in layout (location=1) vec3 colorIn`, que são, respectivamente, 
os vértices que vem do programa principal e as cores que serão usadas na etapa do shader de fragmentos, a variável `out vec3 colorOut` tem o propóstio
de repassar a cor de entrada, `colorIn` para o próximo passo do pipeline. Para determinar o `gl_Position`, os vértices, `vertexIn` são multiplicados 
por uma variável uniforme, `uniform mat4 Matrix`, que é a matriz que, transforma de cordenadas locais, para globais e coordenadas globais para de projeção.

## Shader de Fragmento
Ele pega a cor de entrada `colorOut` e a define como a cor de saída 
`fragColor`, tornando o fragmento de pixel completamente opaco.

## Execução

Para executar, entre na pasta `animation3D`.

Execute:
`g++ *.cpp  Error/*.cpp Utils/*.cpp -o app -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor && ./app`.

Contém uma versão executável dentro da pasta `animation3D`.

## Resultado


<img src="ImagensReadme/gif-animacao-3d.gif">

## Fontes

As fontes consultadas para fazer esse trabalho foram:

http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_05

https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

https://glm.g-truc.net/0.9.4/api/a00133.html

http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

https://learnopengl.com/Getting-started/Hello-Window
