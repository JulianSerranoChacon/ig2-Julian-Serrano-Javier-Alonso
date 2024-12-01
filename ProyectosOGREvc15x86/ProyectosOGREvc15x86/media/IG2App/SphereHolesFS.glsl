#version 330 core
in vec2 vUv0;
uniform sampler2D texturaL;
uniform sampler2D texturaM;
uniform sampler2D texturaN;
uniform float BF;
uniform float intLuzAmb;
out vec4 fFragColor;
uniform float flipping;


void main() { 

    bool frontFacing = (flipping >-1)? gl_FrontFacing : !gl_FrontFacing;

    vec3 colorL = vec3(texture(texturaL, vUv0));
    vec3 colorM = vec3(texture(texturaM, vUv0));
    vec3 colorN = vec3(texture(texturaN, vUv0));

    vec3 colorCorrosion = colorN;
    vec3 color;

    if(colorCorrosion.r > 0.6){
        discard;
    }else{
        if(frontFacing){
            color = color colorL;
        }
        else color = colorN;
    }
    fFragColor = vec4(color, 1.0);




}