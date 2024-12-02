#version 330 core
in vec2 vUv0;
uniform sampler2D texturaC;
uniform sampler2D texturaB;
uniform sampler2D texturaD;
uniform float intLuzAmb;
out vec4 fFragColor;
uniform float flipping;


void main() { 

    bool frontFacing = (flipping >-1)? gl_FrontFacing : !gl_FrontFacing;

    vec3 colorC = vec3(texture(texturaC, vUv0));
    vec3 colorB = vec3(texture(texturaB, vUv0));
    vec3 colorD = vec3(texture(texturaD, vUv0));

    vec3 colorCorrosion = colorC;
    vec3 color;

    if(colorCorrosion.r > 0.6){
        discard;
    }
    
    if(frontFacing){
        color = colorB;
    }
    else color = colorD;
    fFragColor = vec4(color, 1.0);
}