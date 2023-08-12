#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

uniform mat4 projView;

out vec4 m_VertexColor;

void main()
{
   gl_Position = projView * position;
   m_VertexColor = vertexColor;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 m_VertexColor;

void main()
{
   color = m_VertexColor;
};


#shader vertextriangle
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projView;

void main()
{
   gl_Position = projView * position;
};

#shader fragmenttriangle
#version 330 core

layout(location = 0) out vec4 color;

in vec4 m_VertexColor;

void main()
{
   color = vec4(1, 1, 1, 1);
};