#version 400 core

// model information
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


uniform vec3 camera_position;
uniform vec3 color;


// scene transformations
uniform mat4 mv;
uniform mat4 mvp;

// output data
out vec3 v_vertex;
out vec3 v_color;
out vec3 v_normal;
out vec3 v_camera_pos;

void main()
{
    v_vertex = vec3(mv * vec4(position, 1.0));

    v_normal = vec3(mv * vec4(normal, 0.0));

    // pass the vertex color to the fragment shader
    v_color = color;

	v_camera_pos = camera_position;

    // transform the location of the vertex
    gl_Position = mvp * vec4(position, 1.0);
}
