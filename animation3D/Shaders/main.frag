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

float specularStrenght = 0.5;
float Kd = 0.99;   // Diffuse reflection coefficient
float Ks = 0.77;   // Specular reflection coefficient

vec3 diffuseColor = normalize(vec3(255, 52, 255));
vec3 specularColor = normalize(vec3(255, 155, 200));

vec3 lightPos = vec3(-0.5,-0.5,5);
vec3 viewPos = vec3(0, 0, 0);//posição padrão

void main() {
	vec3 norm = normalize(normalOut);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	//iluminaçao ambiente
	vec3 ambient = (ambientColor * ambientIntensity);

	//iluminação difusa
	float cosTeta = clamp(dot(norm,lightDir),0.,1.);
	vec3 difusa = diffuseColor*Kd*cosTeta;

	//especular
	vec3 reflex = 2 * norm * cosTeta - normalize(lightPos);
	float cosAlfa = clamp(dot(viewPos,reflex),0.,1.);
	vec3 specular = specularColor * Ks * pow(cosAlfa,1032);

	vec3 finalColor = (ambient + difusa + specular ) * colorOut;
	fragColor = vec4(finalColor, 1.0);
}