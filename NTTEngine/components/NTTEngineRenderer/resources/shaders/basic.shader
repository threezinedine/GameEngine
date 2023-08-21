#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 m_TextCoord;

uniform mat4 projView;
uniform mat4 transform;

out vec2 v_TextCoord;

void main()
{
   gl_Position = projView * transform * position;
   v_TextCoord = m_TextCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 m_Color;

void main()
{
   color = vec4(m_Color.xyz, 1.0);
};


#shader image-fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D m_Texture;
in vec2 v_TextCoord;

void main()
{
   color = texture(m_Texture, v_TextCoord);
};


#shader all-fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;
uniform sampler2D m_Texture;
uniform vec3 m_Color;

void main()
{
   color = texture(m_Texture, v_TextCoord) * vec4(m_Color.xyz, 1.0f);
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