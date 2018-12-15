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
uniform vec3 lightPos[9*18] = {
vec3(0,15,0),
vec3(50,15,0),
vec3(-50,15,0),
vec3(0,15,50),
vec3(0,15,-50),
vec3(50,15,50),
vec3(50,15,-50),
vec3(-50,15,50),
vec3(-50,15,-50),
vec3(100,15,0),
vec3(150,15,0),
vec3(50,15,0),
vec3(100,15,50),
vec3(100,15,-50),
vec3(150,15,50),
vec3(150,15,-50),
vec3(50,15,50),
vec3(50,15,-50),
vec3(200,15,0),
vec3(250,15,0),
vec3(150,15,0),
vec3(200,15,50),
vec3(200,15,-50),
vec3(250,15,50),
vec3(250,15,-50),
vec3(150,15,50),
vec3(150,15,-50),
vec3(300,15,0),
vec3(350,15,0),
vec3(250,15,0),
vec3(300,15,50),
vec3(300,15,-50),
vec3(350,15,50),
vec3(350,15,-50),
vec3(250,15,50),
vec3(250,15,-50),
vec3(400,15,0),
vec3(450,15,0),
vec3(350,15,0),
vec3(400,15,50),
vec3(400,15,-50),
vec3(450,15,50),
vec3(450,15,-50),
vec3(350,15,50),
vec3(350,15,-50),
vec3(500,15,0),
vec3(550,15,0),
vec3(450,15,0),
vec3(500,15,50),
vec3(500,15,-50),
vec3(550,15,50),
vec3(550,15,-50),
vec3(450,15,50),
vec3(450,15,-50),
vec3(600,15,0),
vec3(650,15,0),
vec3(550,15,0),
vec3(600,15,50),
vec3(600,15,-50),
vec3(650,15,50),
vec3(650,15,-50),
vec3(550,15,50),
vec3(550,15,-50),
vec3(700,15,0),
vec3(750,15,0),
vec3(650,15,0),
vec3(700,15,50),
vec3(700,15,-50),
vec3(750,15,50),
vec3(750,15,-50),
vec3(650,15,50),
vec3(650,15,-50),
vec3(800,15,0),
vec3(850,15,0),
vec3(750,15,0),
vec3(800,15,50),
vec3(800,15,-50),
vec3(850,15,50),
vec3(850,15,-50),
vec3(750,15,50),
vec3(750,15,-50),
vec3(900,15,0),
vec3(950,15,0),
vec3(850,15,0),
vec3(900,15,50),
vec3(900,15,-50),
vec3(950,15,50),
vec3(950,15,-50),
vec3(850,15,50),
vec3(850,15,-50),
vec3(1000,15,0),
vec3(1050,15,0),
vec3(950,15,0),
vec3(1000,15,50),
vec3(1000,15,-50),
vec3(1050,15,50),
vec3(1050,15,-50),
vec3(950,15,50),
vec3(950,15,-50),
vec3(1100,15,0),
vec3(1150,15,0),
vec3(1050,15,0),
vec3(1100,15,50),
vec3(1100,15,-50),
vec3(1150,15,50),
vec3(1150,15,-50),
vec3(1050,15,50),
vec3(1050,15,-50),
vec3(1200,15,0),
vec3(1250,15,0),
vec3(1150,15,0),
vec3(1200,15,50),
vec3(1200,15,-50),
vec3(1250,15,50),
vec3(1250,15,-50),
vec3(1150,15,50),
vec3(1150,15,-50),
vec3(1300,15,0),
vec3(1350,15,0),
vec3(1250,15,0),
vec3(1300,15,50),
vec3(1300,15,-50),
vec3(1350,15,50),
vec3(1350,15,-50),
vec3(1250,15,50),
vec3(1250,15,-50),
vec3(1400,15,0),
vec3(1450,15,0),
vec3(1350,15,0),
vec3(1400,15,50),
vec3(1400,15,-50),
vec3(1450,15,50),
vec3(1450,15,-50),
vec3(1350,15,50),
vec3(1350,15,-50),
vec3(1500,15,0),
vec3(1550,15,0),
vec3(1450,15,0),
vec3(1500,15,50),
vec3(1500,15,-50),
vec3(1550,15,50),
vec3(1550,15,-50),
vec3(1450,15,50),
vec3(1450,15,-50),
vec3(1600,15,0),
vec3(1650,15,0),
vec3(1550,15,0),
vec3(1600,15,50),
vec3(1600,15,-50),
vec3(1650,15,50),
vec3(1650,15,-50),
vec3(1550,15,50),
vec3(1550,15,-50),
vec3(1700,15,0),
vec3(1750,15,0),
vec3(1650,15,0),
vec3(1700,15,50),
vec3(1700,15,-50),
vec3(1750,15,50),
vec3(1750,15,-50),
vec3(1650,15,50),
vec3(1650,15,-50)
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
    float modX = mod(position.x,10);
    if(modX >= 9.5f){
    	modX = sin(((modX-9.5f)/0.5f) * 3.14159265359);
    } else {
    	modX = 0;
    }
    float modZ = mod(position.z,10);
    if(modZ >= 9.5f){
    	modZ = sin(((modZ-9.5f)/0.5f) * 3.14159265359);
    } else {
    	modZ = 0;
    }
    vec3 normalNoise;
    normalNoise = vec3(sin(noiser(position.xz/4)*3.1415)/6,cos(noiser(position.xz/4)*3.1415)/6,cos(noiser(position.xz/4)*3.1415)/6);
    vec3 reflectedNormal = normalize(reflect(position - cameraPos, normalize(fragNormal + normalNoise - vec3(modX,modZ,0) + (normalNoise/3))));
    float noise = noiser(position.xz/5);
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
    vec3 outColor = vec3(0,0,0);
    position.y += noise * 2.5;
    vec3 surfaceDir = reflectedNormal;
    for(int i = 0; i < lightPos.length(); i++)
    {
        float lighDistance = distance(lightPos[i],position);
        if(lighDistance < 150) //for performance
        {
            float fadeWithDist = 1- (lighDistance-100)/50;
            float lightDirectness = dot(normalize(lightPos[i] - position),surfaceDir);
            float lightFinalBrightness = lightDirectness/(distance(lightPos[i],position)/0.5);
            float reflectiveColor = pow(1/(distance(lightPos[i], position+(normalize(surfaceDir)*(lighDistance)))*0.5),2);
            //finalColor = vec4(position,1);
            //finalColor = vec4(reflectiveColor,reflectiveColor,reflectiveColor,1);//lightFinalBrightness,lightFinalBrightness,lightFinalBrightness,1);
            float finalBrightness = ((lightFinalBrightness*(cos(noiser(position.xz/3)*3.1415)))+(reflectiveColor*(1-cos(noiser(position.xz/3)*3.1415))));
            outColor += vec3(finalBrightness*0.98,finalBrightness*1.2,finalBrightness*1.4)*fadeWithDist;
        }
    }
    finalColor = vec4(outColor,1+(fragPosition.y/5));
}