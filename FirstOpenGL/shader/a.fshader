#version 330

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;


void main()
{
	vec4 picColor1 = texture(texture2, vec2(texCoord.x, 1-texCoord.y));
	FragColor = mix(texture( texture1, texCoord), picColor1, blend) * vec4(ourColor, 1.f);
}