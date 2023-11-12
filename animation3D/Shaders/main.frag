#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

//luz ambiente
uniform vec3 ambientColor;
//intensidade da luz ambiente
uniform float ambientIntensity;

vec3 lightPos = vec3(0, 1, 0);

void main() {
	vec3 finalColor = vec3(.0, .0, .0);
	//iluminaçao ambiente
	finalColor += (ambientColor * ambientIntensity);

	//iluminação difusa
	vec3 norm = normalize(normalOut);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ambientColor;
	finalColor += diffuse;

	finalColor *= colorOut;
	fragColor = vec4(finalColor, 1.0);
}