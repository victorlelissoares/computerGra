#version 450

//variavel uniforme que será aplicada a todos os vértices para transforma-los
uniform mat4 Matrix;
//variaveis cujos valores vieram do programa principal
//sendo, respectivamente, as coordenadas dos vértices e as cores
in layout (location=0) vec3 vertexIn;
in layout (location=1) vec3 colorIn;
in layout (location=2) vec3 normalIn;
//cor de saida, que é a de entrada, que será repassada a próxima etapa do pipeline
out vec3 colorOut;
//normais das faces que vem do programa principal
out vec3 normalOut;
out vec3 fragPos;

void main() {
	//glPosition recebe a matrix que veio do programa
	//e multiplica pelos vértices
	gl_Position =  Matrix * vec4(vertexIn, 1.0);
	//posição do fragmento
	fragPos = vec3(Matrix * vec4(vertexIn, 1.0));
	//repassa a cor que veio do programa pra próxima etapa do pipeline(shader de fragmento)
	colorOut = colorIn;
	//repassa as normais pra proxima etapa do pipeline
	normalOut = mat3(transpose(inverse(Matrix))) * normalIn;// Transforma a normal para o espaço da câmera
}