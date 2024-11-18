#version 330
out vec4 frag_colour;
uniform sampler2D textureUnitID;
in vec2 uvc;
void main () {
     //frag_colour = vec4(uvc,1.0,1.0); //test na funkcnost uv souøadnic
     frag_colour = texture(textureUnitID, uvc);
}