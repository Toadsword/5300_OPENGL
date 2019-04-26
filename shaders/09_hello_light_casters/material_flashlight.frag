
layout(location = 0) out vec4 FragColor;

struct TextureMaterial {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
struct FlashLight {
	vec3 position;
	vec3  direction;
	float cutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
	uniform vec3 objectColor;
	uniform vec3 lightColor;
	uniform vec3 viewPos;
	uniform FlashLight light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
uniform TextureMaterial material;


void main()
{    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 lightDir = normalize(light.position - FragPos);
  	float cosTheta = dot(lightDir, normalize(-light.direction));
    
	if(cosTheta > light.cutOff) 
	{       
		// diffuse 
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        
		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
	}
	else
	{
		FragColor = vec4(ambient,1.0);
	}
}