//
// vertexshader.glsl for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/shaders/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 17 14:52:45 2016 Alexis Guerville
// Last update Thu Mar 31 00:20:24 2016 Alexis Guerville
//

#version 130

in vec2 texcoord;
in vec3 position;
in vec3 color;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	Texcoord = texcoord;
	Color = color;
	gl_Position = proj * view * model * vec4(position, 1.0);
}
