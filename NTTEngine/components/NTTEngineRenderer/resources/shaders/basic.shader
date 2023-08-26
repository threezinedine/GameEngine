#shader vertex
#version 330 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec2 v_TextCoord;
layout(location = 3) in float v_TextureId;

uniform mat4 projView;
uniform mat4 transform;

out vec2 m_TextCoord;
out float m_TextureId;
out vec4 m_Color;

void main()
{
   gl_Position = projView * transform * v_Position;
   m_TextCoord = v_TextCoord;
   m_TextureId = v_TextureId;
   m_Color = v_Color;
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

uniform sampler2D m_TextureArray[32];

in vec2 m_TextCoord;
in int m_TextureId;
in vec4 m_Color;

void main()
{
   color = texture(m_TextureArray[], m_TextCoord);
};


#shader all-fragment
#version 330 core

layout(location = 0) out vec4 color;


uniform sampler2D m_TextureArray[32];
uniform float m_TilingFactor;

in vec2 m_TextCoord;
in float m_TextureId;
in vec4 m_Color;

void main()
{
   color = texture(m_TextureArray[int(m_TextureId)], m_TextCoord * m_TilingFactor) * m_Color;
   // color = texture(m_TextureArray[int(m_TextureId)], m_TextCoord * m_TilingFactor);
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