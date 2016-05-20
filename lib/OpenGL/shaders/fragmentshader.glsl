//
// fragmentshader.glsl for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/shaders/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 17 14:52:54 2016 Alexis Guerville
// Last update Tue Mar 29 21:19:05 2016 Alexis Guerville
//

#version 130

in vec2 Texcoord;
in vec3 Color;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
}
