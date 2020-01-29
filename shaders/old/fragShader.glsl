#version 400 core

// light model
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform float u_shininess;
uniform vec3 u_ambient_color;
uniform vec3 u_light_dir;
uniform vec3 diffuse_model;
uniform vec3 specular_model;

// data coming from the vertex shader
in vec3 v_vertex;
in vec3 v_color;
in vec3 v_ambient;
in vec3 v_specular;
in vec3 v_normal;
in vec3 v_fragpos;
in vec3 v_camera_pos;

out vec4 color_out;

void main()
{	
	vec3 ambient_color = v_color * 0.2;
	vec3 diffuse_color = v_color;
	vec3 specular_color = v_specular;
	
	// Distance to light
	float distance = distance(u_light_position, v_vertex);
	
	vec3 eyedir = v_camera_pos - v_fragpos;
	vec3 lightdir = u_light_position - v_fragpos;
	vec3 halfdir = lightdir + eyedir;
	
	vec3 n = normalize(v_normal);
	vec3 l = normalize(lightdir);
	vec3 h = normalize(halfdir);
	float lambertian = max(dot(n,l), 0.0);
	vec3 specular = vec3(0.0, 0.0, 0.0);
	if(lambertian > 0.0)
	{
		vec3 v = normalize(eyedir);
		vec3 r = reflect(-l, n);
		float specAngle = max(dot(n,h), 0.0);
		specular = pow(specAngle, u_shininess) * u_light_color;
	}
	
	vec3 color = v_ambient * u_ambient_color + v_color * lambertian * diffuse_model + specular_color * specular * specular_model;
	color_out = vec4(color, 1.0);
} 
