uniform sampler2D texture;
uniform vec2 resolution;
uniform vec2 click_pos;
uniform vec4 color;
uniform float threshold_sq;

void main() {
    vec2 this_uv = gl_TexCoord[0].xy;
    this_uv.y = 1.0 - this_uv.y;

    vec2 click_uv = click_pos / resolution;
    click_uv.y = 1.0 - click_uv.y;

    vec4 this_color = texture2D(texture, this_uv);
    vec4 click_color = texture2D(texture, click_uv);
    vec4 diff = this_color - click_color;

    gl_FragColor = this_color;
    if(dot(diff, diff) < threshold_sq) {
        gl_FragColor = color;
    }
}