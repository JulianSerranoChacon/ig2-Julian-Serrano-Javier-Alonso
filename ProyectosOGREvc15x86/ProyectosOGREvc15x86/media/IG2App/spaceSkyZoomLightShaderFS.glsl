#version 330 core 
uniform sampler2D texturaL;  // Tipo sampler2D para texturas 2D 
uniform sampler2D texturaM;  // -> unidades de textura (int) 
uniform float BF;  // Blending factor 
uniform float intLuzAmb; // Luz ambiente blanca 
float sintime_0_2pi;
in vec2 vUv0; // Out (del vertex shader) 
out vec4 fFragColor; // Out (del fragment shader) 
void main() 
{ 
    //vec3 colorL = vec3(texture(texturaL, vUv0)); // Acceso a téxel 
    //vec3 colorM = vec3(texture(texturaM, vUv0)); // Configuración! 
    float ZF = sintime_0_2pi * 0.3 + 1.0;
    vUv0.s = (vUv0.s- 0.5) * (ZF) + 0.5; 
    vUv0.t = (vUv0.t- 0.5) * (ZF) + 0.5;
    colorL = vec3(texture(texturaL, vUv0)); // Acceso a téxel 
    colorM = vec3(texture(texturaM, vUv0)); // Configuración! 
    vec3 color = mix(colorL, colorM, BF) * intLuzAmb; //Mix-> (1-BF).colorL + BF.colorM fFragColor = vec4(color, 1.0); 
    fFragColor=vec4(color,1.0);
    
}