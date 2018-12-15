#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 modelPos = vec3(0,0,0);
uniform vec3 lightPos[9] = {
vec3(0,15,0),
vec3(-100,15,0),
vec3(-50,15,0),
vec3(0,15,20),
vec3(0,15,-20),
vec3(-100,15,20),
vec3(-100,15,-20),
vec3(-50,15,20),
vec3(-50,15,-20)
    };
uniform vec3 cameraPos;
uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;
// Output fragment color
out vec4 finalColor;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(62.01019,12.9898)))*
        43424.5453123);
}

float hash(vec2 p)  // replace this by something better
{
    p  = 50.0*fract( p*0.3183099 + vec2(0.71,0.113));
    return -1.0+2.0*fract( p.x*p.y*(p.x+p.y) );
}

float nicerNoise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );
	
	vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( hash( i + vec2(0.0,0.0) ), 
                     hash( i + vec2(1.0,0.0) ), u.x),
                mix( hash( i + vec2(0.0,1.0) ), 
                     hash( i + vec2(1.0,1.0) ), u.x), u.y);
}

// TODO: improve readability

float noiser( vec2 coord )
{
    vec2 p = coord.xy / 25;

	vec2 uv = p*vec2(1,1.0);
	
	float f = 0.0;
	uv *= 8.0;
    mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );
	f  = 0.5000*nicerNoise( uv ); uv = m*uv;
	f += 0.2500*nicerNoise( uv ); uv = m*uv;
	f += 0.1250*nicerNoise( uv ); uv = m*uv;
	f += 0.0625*nicerNoise( uv ); uv = m*uv;

	f = 0.5 + 0.5*f;	
	
	return f;
}

void main()
{
    // Texel color fetching from texture sampler
    vec3 position = (fragPosition) + modelPos;
    float modX = mod(position.x + time,3);
    if(modX >= 3 * 0.95f){
    	modX = sin(((modX-9.5f)/1.0f) * 3.14159265359);
    } else {
    	modX = 0;
    }
    float modZ = mod(position.z,3);
    if(modZ >= 3 * 0.95f){
    	modZ = sin(((modZ-9.5f)/1.0f) * 3.14159265359);
    } else {
    	modZ = 0;
    }
    vec3 normalNoise;
    float noise = noiser(position.xz+vec2(time,0));
    normalNoise = vec3(sin(noise*3.1415)/2,cos(noise*3.1415)/2,cos(noise*3.1415)/2);
    vec3 reflectedNormal = normalize(reflect(position - cameraPos, normalize(fragNormal + normalNoise - vec3(modX,modZ,0) + (normalNoise/3))));
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
    vec3 outColor = vec3(0,0,0);
    position.y += noise * 2.5;
    vec3 surfaceDir = reflectedNormal;
    for(int i = 0; i < lightPos.length(); i++){
        float lighDistance = distance(lightPos[i],position);
        float fadeWithDist = 1- (lighDistance-100)/50;
        float lightDirectness = dot(normalize(lightPos[i] - position),surfaceDir);
        float lightFinalBrightness = lightDirectness/(distance(lightPos[i],position)/0.4);
        float reflectiveColor = pow(1/(distance(lightPos[i], position+(normalize(surfaceDir)*(lighDistance)))*0.35),4);
        //finalColor = vec4(position,1);
        //finalColor = vec4(reflectiveColor,reflectiveColor,reflectiveColor,1);//lightFinalBrightness,lightFinalBrightness,lightFinalBrightness,1);
        float finalBrightness = ((lightFinalBrightness*(cos(noiser(position.xz/3)*3.1415)))+(reflectiveColor*(1-cos(noiser(position.xz/3)*3.1415))));
        outColor += vec3(finalBrightness*0.98,finalBrightness*1.2,finalBrightness*1.4)*fadeWithDist;
    }
   	finalColor = vec4(outColor,(1+(-(fragPosition.x+95)/(20*noiser(vec2(position.z/8,time))))));
}