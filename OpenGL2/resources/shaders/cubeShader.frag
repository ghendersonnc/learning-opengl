#version 330 core

out vec4 color;

in vec4 vertexColors;
in vec4 FragPos;
in vec4 normal;

uniform vec3 lightColor;
uniform vec4 lightPos;

void main() {
	float ambientStrength = .15f;
	vec4 ambient = vec4(ambientStrength * lightColor, 1.0f);
	
	vec4 finalNormal = normalize(normal);
	vec4 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(finalNormal, lightDir), 0.0f);
	vec4 diffuse = vec4(diff * lightColor, 1.0f);
	color = (ambient + diffuse) * vertexColors;

	
}	