#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projView;
uniform mat4 transform;

void main()
{
   gl_Position = projView * transform * position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 m_Color;

void main()
{
   color = vec4(m_Color.xyz, 1.0);
};


#shader vertextriangle
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projView;
uniform mat4 transform;

void main()
{
   gl_Position = projView * transform * position;
};

#shader fragmenttriangle
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
   color = vec4(1, 1, 1, 1);
};