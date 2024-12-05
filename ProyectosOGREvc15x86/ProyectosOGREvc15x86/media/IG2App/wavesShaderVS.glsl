#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
uniform float sintime;

void main() {
    vUv0 = uv0;

    vec4 center = vec4(0,0,0,0);
    float a = 5;
    float b = 3;
    vec4 vertexCoord = vertex;
    float distanceCenter = distance(vertex, center);

    vertexCoord.y += sin(vertexCoord.x + (sintime*a)) * b + sin(vertexCoord.z + (distanceCenter) + (sintime*a)) * b; 


    gl_Position = modelViewProjMat * vertexCoord;
}