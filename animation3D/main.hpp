//
// Created by lelis on 11/9/23.
//
#include<iostream>
#include<string>

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "./Utils/utils.h"

//variaveis globais
const float width = 800;
const float height = 680;

int matrixId;
unsigned int programId = 0;
unsigned int cubeVAO = 0;
unsigned int indexOffSet = 0;
glm::mat4 projection(1.f);

//iluminação ambiente
glm::vec3 ambientColor(0.5, 0.1111117, 0.7222); // Cor da luz ambiente (ajuste os valores conforme necessário)
float ambientIntensity = 0.4f;

//utilizados para fazer a escala do cubo do meio da tela
float escalaMin = 0.5f; // fator de escala mínimo
float escalaMax = 1.9f; // fator de escala máximo
float escalaAtual = 1.0f; //valor inicial do fator de escala
float incremento = 0.01; //quanto a escala muda por iteração
bool aumentando = true; //direção inicial da mudança de escala

//funções
void CompileAndLinkShaders();
void criaCubo();
void inicializaOpenGL();
void desenha(float dt);
void luzAmbiente();