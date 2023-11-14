#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

float Ka = 0.5;
float Kd = 0.99;   // Diffuse reflection coefficient
float Ks = 2.0;   // Coeficiente de reflexão especular

vec3 diffuseColor = normalize(vec3(255, 52, 255));
vec3 specularColor = vec3(1.0, 1.0, 1.0);  // Cor da reflexão especular
vec3 ambientColor = normalize(vec3(1, 1, 1));

vec3 lightPos = vec3(-0.5,-0.5,5);
vec3 viewPos = vec3(0, 0, 0);//posição padrão

void main() {
	float n = 0.01;
	vec3 norm = normalize(normalOut);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	//iluminaçao ambiente
	vec3 ambient = (ambientColor * Ka);

	//iluminação difusa
	float cosTeta = clamp(dot(norm,lightDir),0.,1.);
	vec3 difusa = diffuseColor*Kd*cosTeta;

	//especular
	vec3 reflex = 2 * norm * cosTeta - normalize(lightPos);
	float cosAlfa = clamp(dot(viewPos,reflex),0.,1.);
	vec3 specular = specularColor * Ks * pow(cosAlfa, n);

	//Atenuação
	float dist = length(lightPos - fragPos);
	float atenuacao = 1.0/(1+0.09*dist+0.032*dist*dist);

	vec3 finalColor = (ambient + difusa + specular ) * colorOut * atenuacao;
	finalColor = pow(finalColor, vec3(1.0 / 2.2) );// gamma correcao
	fragColor = vec4(finalColor, 1.0);
}