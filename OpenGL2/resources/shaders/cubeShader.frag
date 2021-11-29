#version 330 core

out vec4 color;

in vec4 vertexColors;
in vec4 FragPos;
in vec4 normal;

uniform vec4 lightColor;
uniform vec4 lightPos;

void main() {
	float ambientStrength = 0.15f;
	vec4 ambient = ambientStrength * lightColor;
	
	vec4 finalNormal = normalize(normal);
	vec4 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(finalNormal, lightDir), 0.0f);
	vec4 diffuse = diff * lightColor;
	color = (ambient + diffuse) * vertexColors;
}