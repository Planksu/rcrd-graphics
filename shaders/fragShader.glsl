#version 400 core

// light model
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform float u_shininess;
uniform vec3 u_ambient_color;

// data coming from the vertex shader
in vec3 v_vertex;
in vec3 v_color;
in vec3 v_normal;

out vec4 color_out;

void main()
{
	vec3 to_light;
	vec3 vertex_normal;
	vec3 reflection;
	vec3 to_camera;
	float cos_angle;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 ambient_color;
	vec3 color;
	
	ambient_color = u_ambient_color * v_color;
	to_light = u_light_position - v_vertex;
	to_light = normalize(to_light);
	vertex_normal = normalize(v_normal);
	cos_angle = dot(vertex_normal, to_light);
	cos_angle = clamp(cos_angle, 0.0, 1.0);
	diffuse_color = vec3(v_color) * cos_angle;
	reflection = 2.0 * dot(vertex_normal, to_light) * vertex_normal - to_light;
	to_camera = -1.0 * v_vertex;
	reflection = normalize(reflection);
	to_camera = normalize(to_camera);
	cos_angle = dot(reflection, to_camera);
	cos_angle = clamp(cos_angle, 0.0, 1.0);
	cos_angle = pow(cos_angle, u_shininess);

	if(cos_angle > 0.0)
	{
		specular_color = u_light_color * cos_angle;
		diffuse_color = diffuse_color * (1.0 - cos_angle);
	}
	else
	{
		specular_color = vec3(0.0, 0.0, 0.0);
	}

	color = ambient_color + diffuse_color + specular_color;
	color_out = vec4(color, 1.0);
} 
