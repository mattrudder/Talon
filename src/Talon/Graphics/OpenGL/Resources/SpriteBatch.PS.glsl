
varying vec4 color;
varying vec2 texCoord;

sampler2D textureSampler;

void main()
{
	gl_FragColor = texture2D(textureSampler, texCoord) * color;
}