attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;

attribute vec2 a_uv;
varying vec2 v_uv;

attribute vec2 atexCoord;
attribute vec4 a_CubeVertexPos;
uniform mat4 transform;
varying vec2 texCoord;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = posL*transform;
	//texCoord = vec2(atexCoord.x, atexCoord.y);
	//gl_Position = u_CubeMVPMatrix * a_CubeVertexPos;
	//v_pos = a_CubeVertexPos;
	v_color = a_color;
	v_uv = a_uv;
}
 
