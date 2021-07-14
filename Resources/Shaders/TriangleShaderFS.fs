precision mediump float;
varying vec3 v_color;
varying vec3 a_posL;
void main()
{
	gl_FragColor = vec4(v_color, 1.0);
}
