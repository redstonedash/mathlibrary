#version 330
 
out vec4 finalColor;
layout (std140) uniform Materials {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};
 
in Data {
    vec3 normal;
    vec3 eye;
   
} DataIn;
 
uniform vec3 lightDir;
void main() {
 
    vec4 spec = vec4(0.0);
 
    vec3 n = normalize(DataIn.normal);
    vec3 l = normalize(DataIn.lightDir);
    vec3 e = normalize(DataIn.eye);
 
    float intensity = max(dot(n,l), 0.0);
    if (intensity > 0.0) {
        vec3 h = normalize(l + e);
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }
 
    finalColor = max(intensity * diffuse + spec, ambient);
}