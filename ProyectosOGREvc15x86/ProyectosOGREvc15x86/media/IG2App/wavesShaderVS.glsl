#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
uniform float sintime;

void main() {

    vec4 center = vec4(750,1500,0,0);
    float a = 1.5;
    float b = 2.6;
    vec4 vertexCoord = vertex;
    //float distanceCenter = distance(center, vertex);

    vertexCoord.y += sin(vertexCoord.x + (sintime*a)) * b + sin(vertexCoord.z + (1) + (sintime*a)) * b; 

    vUv0 = uv0;

    gl_Position = modelViewProjMat * vertexCoord;
}