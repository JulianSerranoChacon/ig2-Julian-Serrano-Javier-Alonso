#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
uniform float sintime;
out float zf;

void main() {
    vUv0 = uv0;

    float ZF = sintime*0.25 + 1;
    vUv0 = vUv0 * ZF;

    vUv0.s = vUv0.s + 0.5;
    vUv0.t = vUv0.t + 0.5;
    zf = ZF;
    
    gl_Position = modelViewProjMat * vertex;
}