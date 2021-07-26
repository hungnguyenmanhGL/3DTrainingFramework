attribute vec3 a_uv;//VertexPos
attribute vec3 a_posL;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
varying vec3 v_uv;

void main(void)

{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_posL, 1.0);
	v_uv = a_posL;
}

 
