#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

void main() {
	//cor RGBA
	fragColor = vec4(colorOut, 1.f);
}