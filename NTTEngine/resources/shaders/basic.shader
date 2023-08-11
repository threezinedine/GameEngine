#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

out vec4 m_VertexColor;

void main()
{
   gl_Position = position;
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