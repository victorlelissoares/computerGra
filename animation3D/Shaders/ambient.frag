#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

float Ka = 0.5;
vec3 ambientColor = normalize(vec3(1, 1, 1));

vec3 lightPos = vec3(-0.5,-0.5,5);
vec3 viewPos = vec3(0, 0, 0);//posição padrão

void main() {

    //iluminaçao ambiente
    vec3 ambient = (ambientColor * Ka);

    //Atenuação
    float dist = length(lightPos - fragPos);
    float atenuacao = 1.0/(1+0.09*dist+0.032*dist*dist);

    vec3 finalColor = (ambient) * colorOut * atenuacao;
    fragColor = vec4(finalColor, 1.0);
}