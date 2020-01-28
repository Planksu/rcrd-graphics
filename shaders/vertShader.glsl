#version 400 core

// model information
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


uniform vec3 camera_position;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;


// scene transformations
uniform mat4 m;
uniform mat4 mv;
uniform mat4 mvp;

// output data
out vec3 v_vertex;
out vec3 v_color;
out vec3 v_ambient;
out vec3 v_specular;
out vec3 v_normal;
out vec3 v_camera_pos;
out vec3 v_fragpos;

void main()
{
    v_vertex = vec3(mv * vec4(position, 1.0));

    v_normal = vec3(mv * vec4(normal, 0.0));

    // pass the vertex color to the fragment shader
    v_color = diffuse;
	v_ambient = ambient;
	v_specular = specular;
	
	v_fragpos = vec3(m * vec4(position, 1.0));

	v_camera_pos = camera_position;

    // transform the location of the vertex
    gl_Position = mvp * vec4(position, 1.0);
}
