precision mediump float;
varying vec3 v_color;
varying vec3 a_posL;

uniform sampler2D u_texture; 
varying vec2 v_uv;
void main()
{
	//gl_FragColor = vec4(v_color, 1.0); //task2
	gl_FragColor = texture2D(u_texture, v_uv);
}
