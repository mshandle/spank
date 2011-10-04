precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_texCoord;

void main()
{
	 //gl_FragColor = texture2D(u_texture, v_texCoord);
	 vec4 Color= texture2D(u_texture, v_texCoord);
	 float Gray =  Color.r * 0.3 + Color.g * 0.59 +  Color.b * 0.11;
	gl_FragColor = vec4(Gray, Gray, Gray, Color.a);
}
