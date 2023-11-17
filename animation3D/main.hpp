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
#include "Libs/imgui.h"
#include "Libs/imgui_impl_glfw.h"
#include "Libs/imgui_impl_opengl3.h"

//variaveis globais
const float width = 800;
const float height = 680;

int matrixId;
unsigned int programId = 0;
unsigned int cubeVAO = 0;
unsigned int indexOffSet = 0;
glm::mat4 projection(1.f);

//utilizados para fazer a escala do cubo do meio da tela
float escalaMin = 0.5f; // fator de escala mínimo
float escalaMax = 1.9f; // fator de escala máximo
float escalaAtual = 1.0f; //valor inicial do fator de escala
float incremento = 0.01; //quanto a escala muda por iteração
bool aumentando = true; //direção inicial da mudança de escala
const char *nomeShaderAtual = "Sem iluminação";

//funções
void criaCubo();
void CompileAndLinkShaders(const std::string& shaderPath);
void desenha(float dt);
void inicializaOpenGL();