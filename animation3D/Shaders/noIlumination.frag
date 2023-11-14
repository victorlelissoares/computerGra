#version 450

//color que vem do passo anterior do pipeline, no caso do shader de fragmento
in vec3 colorOut;
in vec3 fragPos;
in vec3 normalOut;
//cor que vai pro proximo passo do pipeline
out vec4 fragColor;

void main() {
    vec3  finalColor = colorOut;
    fragColor = vec4(finalColor, 1.0);
}