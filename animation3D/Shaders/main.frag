#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

//luz ambiente
uniform vec3 ambientColor;
//intensidade da luz ambiente
uniform float ambientIntensity;

void main() {
	vec3 finalColor = vec3(.0, .0, .0);
	//iluminaçao ambiente
	finalColor += (ambientColor * ambientIntensity);

	finalColor *= colorOut;
	fragColor = vec4(finalColor, 1.0);
}