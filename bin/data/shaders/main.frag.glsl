#version 400


uniform sampler2D tex0;
uniform float alpha;
uniform vec3 color;
uniform bool useTexture;

in vec2 v_TexCoords;

out vec4 out_Color;

void main() {
    if(useTexture) {
        vec4 c = texture(tex0, v_TexCoords);
        out_Color = vec4(c.rgb * color, c.a * alpha);
    } else {
        out_Color = vec4(color, alpha);
    }
}