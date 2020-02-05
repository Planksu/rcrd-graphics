#version 400 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);
    
	// transform back to linear range
    lightDistance = lightDistance / far_plane;
	
	// set frag depth
    gl_FragDepth = lightDistance;
}