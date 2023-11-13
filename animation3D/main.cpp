#include "main.hpp"

int main(){
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Erro ao iniciar GLFW!");
        return -1;
    }

    /* Cria uma janela de tamanho 800x600 no contexto opengl */
    window = glfwCreateWindow(width, height, "Animacao 3D - projecao perpectiva, rotacao, translacao e escala", NULL, NULL);
    if (!window){
        fprintf(stderr, "Janela GLFW não foi criada!");
        glfwTerminate();
        return -1;
    }

    /* Torna a janela o contexto atual da opengl */
    glfwMakeContextCurrent(window);

    GLenum status = glewInit();
    if (GLEW_OK != status){
        fprintf(stderr, "Erro ao Inicializar glew!");
        return -1;
    }

    // Inicialização do ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init( "#version 450" );

    inicializaOpenGL();

    float tempoInicial = glfwGetTime();

    while (!glfwWindowShouldClose(window)){

        float tempoAtual = glfwGetTime();
        float deltaTime = tempoAtual - tempoInicial;

        // Processamento de eventos do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Conteúdo da janela ImGui
        ImGui::Begin("Meu GUI");
        ImGui::SetCursorPos(ImVec2(10, 10));
        if (ImGui::Button("Clique-me")) {
            // Ação quando o botão do ImGui é clicado
            showButton = !showButton;  // Inverte o estado da variável
        }

        ImGui::End();

        // Renderização do ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //passa o tempo decorrido para realizar/aplicar variações nas matrizes de modelToWorld
        desenha(deltaTime);

        // Renderização final
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finalização do ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

//Cubo formado por triangulos, cada face é formada por dois triângulos
void criaCubo(){
    glm::vec3 points[] = {
            // frente
            glm::vec3(-0.5f, +0.5f, +0.5f),//0
            glm::vec3(-0.5f, -0.5f, +0.5f),//1
            glm::vec3(+0.5f, -0.5f, +0.5f),//2
            glm::vec3(+0.5f, +0.5f, +0.5f),//3

            //fundo
            glm::vec3(+0.5f, +0.5f, -0.5f),//4
            glm::vec3(+0.5f, -0.5f, -0.5f),//5
            glm::vec3(-0.5f, -0.5f, -0.5f),//6
            glm::vec3(-0.5f, +0.5f, -0.5f), //7

            //os demais lados do cubo são combinações dos demais vértices escritos anteriormente
    };

    glm::vec3 vertices[] = {
            //frente
            points[0],//0
            points[1],//1
            points[2],//2
            points[3],//3

            //fundo
            points[4],//4
            points[5],//5
            points[6],//6
            points[7],//7

            //direita
            points[3],//8
            points[2],//9
            points[5],//10
            points[4],//11

            //esquerda
            points[7],//12
            points[6],//13
            points[1],//14
            points[0],//15

            //cima
            points[7],//16
            points[0],//17
            points[3],//18
            points[4],//19

            //baixo
            points[1],//20
            points[6],//21
            points[5],//22
            points[2] //23
    };

    GLubyte colors[] = {
            //face da frente vermelha
            255, 0, 0,
            255, 0, 0,
            255, 0, 0,
            255, 0, 0,

            //face de trás verde
            0, 255, 0,
            0, 255, 0,
            0, 255, 0,
            0, 255, 0,

            //face da direita azul
            0, 0, 255,
            0, 0, 255,
            0, 0, 255,
            0, 0, 255,

            //face da esquerda amarela
            255, 255, 0,
            255, 255, 0,
            255, 255, 0,
            255, 255, 0,

            //face de cima magenta
            255, 0, 255,
            255, 0, 255,
            255, 0, 255,
            255, 0, 255,

            //face debaixo ciano
            125, 255, 255,
            125, 15, 255,
            125, 255, 255,
            125, 255, 25
    };

    unsigned int indices[] = {
            0,   1,  2,  0,  2,  3,// frente
            4,   5,  6,  4,  6,  7,// trás
            8,   9, 10,  8, 10, 11,// direita
            12, 13, 14, 12, 14, 15,// esquerda
            16, 17, 18, 16, 18, 19,// cima
            20, 21, 22, 20, 22, 23 // baixo
    };

    unsigned int BufferId = 0;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &BufferId);

    //Criando buffer único
    glBindBuffer(GL_ARRAY_BUFFER, BufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices) + sizeof(colors) + sizeof(indices), nullptr, GL_STATIC_DRAW);

    // Preenchendo sub buffer com vértices
    unsigned int currentOffSet = 0;
    glBufferSubData(GL_ARRAY_BUFFER, currentOffSet, sizeof(vertices), vertices);

    // Preenchendo sub buffer com cores
    currentOffSet += sizeof(vertices);
    glBufferSubData(GL_ARRAY_BUFFER, currentOffSet, sizeof(colors), colors);

    // Preenchendo sub buffer com os indices
    currentOffSet += sizeof(colors);
    glBufferSubData(GL_ARRAY_BUFFER, currentOffSet, sizeof(indices), indices);

    indexOffSet = currentOffSet;


    glBindVertexArray(cubeVAO);
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, BufferId);

        // Atributo de posição do vértice
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

        // Atributo de cor
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3 * sizeof(GLubyte), (void*)sizeof(vertices));
    }
    glBindVertexArray(0);
}

void luzAmbiente(){
    int ambientColorLocation = glGetUniformLocation(programId, "ambientColor");
    glUniform3fv(ambientColorLocation, 1, glm::value_ptr(ambientColor));

    //definindo intensidade da cor
    int ambientIntensityLocation = glGetUniformLocation(programId, "ambientIntensity");
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}

void inicializaOpenGL(){

    criaCubo();
    //compila e linka os Shaders de fragmentos e de vétices, resultando no programa (shade de vérticer+fragmento)
    CompileAndLinkShaders();

    //linka a variavel matriz do shader de vétice ao programaId
    matrixId = glGetUniformLocation(programId, "Matrix");
    glEnable(GL_DEPTH_TEST);

    projection = glm::perspective(glm::radians(45.f), width / height, 0.1f, 10.f);
    projection = projection * glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
    //cria a matriz de projeção, que será usada para posicionar os objetos nas coordenadas da cena, que é 5 unidades para dentro da tela (z=-5.f)

    luzAmbiente();
}

void desenha(float dt){
    //faz o cubo no centro da tela aumentar e diminuir
    if (aumentando) {
        escalaAtual += incremento;
        if (escalaAtual >= escalaMax)
            aumentando = false;

    } else {
        escalaAtual -= incremento;
        if (escalaAtual <= escalaMin)
            aumentando = true;

    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Define a cor de fundo para branco
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    //desenha o primeiro cubo
    //leva do modelo para o mundo
    glm::mat4 model = glm::rotate(glm::mat4(1.f), +dt, glm::vec3(0.f, 1.f, 0.f));//rotaciona no eixo y
    model = glm::scale(glm::mat4(1.0f), glm::vec3(escalaAtual/2, escalaAtual, escalaAtual/4));//aplica escala em todos os eixos
    model = glm::rotate(model, 1.75f * dt, glm::vec3(1.f, 0.f, 0.f));//rotaciona no eixo x
    model = glm::rotate(model, 0.75f * dt, glm::vec3(0.f, 0.f, 1.f));//rotaciona no eixo z
    //leva do mundo para a projeção
    glm::mat4 finalMatrix = projection * model;

    glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(finalMatrix));

    glBindVertexArray(cubeVAO);
    {
        //apenas sinaliza o cast, para suprimir o warning
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(indexOffSet));
    }


    //desenha o segundo cubo
    //as rotaçõoes são as mesmas do cubo anteior, somente alterando o sentido de rotação
    model = glm::rotate(glm::mat4(1.f), -dt, glm::vec3(0.f, 1.f, 0.f));
    //translada o cubo no eixo x e y
    model = glm::translate(model, glm::vec3(-2.0f, -0.99f, 0.f));
    model = glm::rotate(model, 1.75f * dt, glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, 0.75f * dt, glm::vec3(0.f, 0.f, 1.f));
    //leva do mundo para a projeção
    finalMatrix = projection * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(finalMatrix));
    glBindVertexArray(cubeVAO);
    {
        //apenas sinaliza o cast, para suprimir o warning
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(indexOffSet));
    }


    //desenha o 3 cubo
    //as rotaçõoes são as mesmas do cubo anteior, somente alterando o sentido de rotação
    model = glm::rotate(glm::mat4(1.f), -dt, glm::vec3(0.f, -1.f, 0.f));
    //translada o cubo no eixo x e y
    model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.f));
    model = glm::rotate(model, 1.75f * dt, glm::vec3(0.f, -1.f, 0.f));
    model = glm::rotate(model, 0.75f * dt, glm::vec3(0.f, 0.f, -1.f));
    //leva do mundo para a projeção
    finalMatrix = projection * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(finalMatrix));
    glBindVertexArray(cubeVAO);
    {
        //apenas sinaliza o cast, para suprimir o warning
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(indexOffSet));
    }
    glBindVertexArray(0);
}

void CompileAndLinkShaders(){
    // 1. Criamos os nossos Objetos:
    //    Programa = Vertex Shader + Fragment Shader
    programId = glCreateProgram();
    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // 2. Passamos as strings para com códigos GLSL
    //    para o tipo const char* = código fonte final
    std::string vsCode, fsCode;
    vsCode = ReadProgramSource("Shaders/main.vert");
    fsCode = ReadProgramSource("Shaders/main.frag");

    const char* vsFinalCode = vsCode.c_str();
    const char* fsFinalCode = fsCode.c_str();

    // 3. Copiamos o código fonte final
    //para o Shader anteriormente criado
    glShaderSource(vertexShaderId, 1, &vsFinalCode, NULL);
    glShaderSource(fragmentShaderId, 1, &fsFinalCode, NULL);

    // 4. Compilamos os Shaders
    glCompileShader(vertexShaderId);
    glCompileShader(fragmentShaderId);

    // 5. Anexamos os Shaders compilados ao Programa
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);


    //6. Link
    glLinkProgram(programId);

    //7. Delete
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);


    //8. Utilizar o programa
    glUseProgram(programId);

}