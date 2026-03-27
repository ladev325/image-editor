uniform sampler2D texture;
uniform vec2 resolution;
uniform float radius;
uniform vec2 direction;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float samples = 0.0;

    for (float i = -radius; i <= radius; i++) {
        color += texture2D(texture, uv + i * direction / resolution);
        samples++;
    }

    gl_FragColor = color / samples;
}