attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;
varying vec3 v_pos;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = posL;
	v_color = a_color;
}
   