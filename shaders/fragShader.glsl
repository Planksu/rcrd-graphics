#version 400 core

// light model
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform float u_shininess;
uniform vec3 u_ambient_color;
uniform vec3 u_light_dir;

// data coming from the vertex shader
in vec3 v_vertex;
in vec3 v_color;
in vec3 v_normal;
in vec3 v_camera_pos;

out vec4 color_out;

void main()
{
	vec3 color;
	float light_power = 500.0f;
	
	vec3 ambient_color = u_ambient_color * v_color;
	vec3 diffuse_color = v_color;
	vec3 specular_color = vec3(0.3, 0.3, 0.3);
	
	// Distance to light
	float distance = distance(u_light_position, v_vertex);
	
	vec3 eyedir = vec3(0, 0, 0) - v_vertex;
	vec3 lightdir = u_light_position + eyedir;
	
	vec3 n = normalize(v_normal);
	vec3 l = normalize(lightdir);
	float cosTheta = clamp(dot(n,l),0,1);
	
	vec3 e = normalize(eyedir);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e,r),0,1);

	color = ambient_color + diffuse_color * u_light_color * light_power * cosTheta / (distance*distance) + specular_color * u_light_color * light_power * pow(cosAlpha, 100)  / (distance*distance);
	color_out = vec4(color, 1.0);
} 
