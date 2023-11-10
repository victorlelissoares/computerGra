#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

//cor ambiente
uniform vec3 ambientColor;

void main() {
	vec3 finalColor = colorOut * ambientColor; // objectColor é a cor do objeto
	fragColor = vec4(finalColor, 1.0);
}