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

vec3 lightPos = vec3(0., 0., -0.5);
vec3 viewPos = vec3(0, 0, 0);//posição padrão

float specularStrenght = 0.5;

void main() {
	vec3 norm = normalize(normalOut);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	//iluminaçao ambiente
	vec3 ambient = (ambientColor * ambientIntensity);

	//iluminação difusa
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ambientColor;

	//especular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2048);
	vec3 specular = specularStrenght * spec * ambientColor;

	vec3 finalColor = (ambient + diffuse + specular) * colorOut;
	fragColor = vec4(finalColor, 1.0);
}