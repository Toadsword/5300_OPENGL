layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT vs_out;
out vec3 TangentLightPos;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
	
    vs_out.ViewPos  =  viewPos;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    vs_out.invTBN  = mat3(T, B, N);
        
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
