uniform sampler2D texture;
uniform vec2 resolution;
uniform int radius;
uniform float tight_coef;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    float total_alpha = 0.0;
    float total_weight = 0.0;

    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            float dist = length(vec2(float(x), float(y)));
            float weight = exp(-dist * dist * 2.0);
            vec2 offset = vec2(float(x), float(y)) / resolution;
            total_alpha += texture2D(texture, uv + offset).a * weight;
            total_weight += weight;
        }
    }
    float alpha = pow(total_alpha / total_weight, tight_coef);
    gl_FragColor = vec4(gl_Color.rgb, gl_Color.a * alpha);
}