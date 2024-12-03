#version 330 core 
uniform sampler2D textura;  // Tipo sampler2D para texturas 2D 
in vec2 vUv0; // Out (del vertex shader) 
out vec4 fFragColor; // Out (del fragment shader) 
void main() 
{ 
    vec3 color = vec3(texture(textura, vUv0)); // Acceso a téxel         
    fFragColor=vec4(color,1.0);
    
}