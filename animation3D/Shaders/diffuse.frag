#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

float Ka = 0.5;
float Kd = 0.99;   // Diffuse reflection coefficient
float Ks = 0.77;   // Specular reflection coefficient

vec3 diffuseColor = normalize(vec3(255, 52, 255));
vec3 specularColor = normalize(vec3(255, 155, 200));
vec3 ambientColor = normalize(vec3(1, 1, 1));

vec3 lightPos = vec3(-0.5,-0.5,5);
vec3 viewPos = vec3(0, 0, 0);//posição padrão

void main() {
    vec3 norm = normalize(normalOut);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);


    //iluminação difusa
    float cosTeta = clamp(dot(norm,lightDir),0.,1.);
    vec3 difusa = diffuseColor*Kd*cosTeta;


    //Atenuação
    float dist = length(lightPos - fragPos);
    float atenuacao = 1.0/(1+0.09*dist+0.032*dist*dist);

    vec3 finalColor = (difusa) * colorOut * atenuacao;
    fragColor = vec4(finalColor, 1.0);
}