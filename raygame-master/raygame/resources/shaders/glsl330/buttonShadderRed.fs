#version 330

vec3 lgithDirection = normalize(vec3(1.2,1,-0.5));
// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;
uniform float pressed = 0;
// Output fragment color
out vec4 finalColor;

void main()
{
    float brightness = abs(pressed - (-dot(vec3(fragNormal.x, fragNormal.y, fragNormal.z),lgithDirection))) + 0.2;
   	finalColor = vec4(brightness*1.2,brightness*0.3, brightness*0.3,1);
}