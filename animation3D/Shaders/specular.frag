#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

float Ks = 2.0;   // Coeficiente de reflexão especular

vec3 specularColor = vec3(1.0, 1.0, 1.0);  // Cor da reflexão especular

vec3 lightPos = vec3(-0.5, -0.5, 5.0);  // Posição da fonte de luz
vec3 viewPos = vec3(0.0, 0.0, 1.0);  // Posição do observador

void main() {
    float n = 0.01;
    vec3 norm = normalize(normalOut);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float cosTeta = clamp(dot(norm,lightDir),0.,1.);

    //especular
    vec3 reflex = 2 * norm * cosTeta - normalize(lightPos);
    float cosAlfa = clamp(dot(viewPos,reflex),0.,1.);
    vec3 specular = specularColor * Ks * pow(cosAlfa, n);

    //Atenuação
    float dist = length(lightPos - fragPos);
    float atenuacao = 1.0/(1+0.09*dist+0.032*dist*dist);

    vec3 finalColor = (specular) * colorOut * atenuacao;
    fragColor = vec4(finalColor, 1.0);
}