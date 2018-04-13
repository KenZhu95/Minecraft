R"zzz(#version 330 core
in vec4 vertex_position;
in vec4 translation;
in float division;
in float type;
uniform mat4 view;
uniform vec4 light_position;
out vec4 vs_light_direction;
out vec3 v_position;
out vec4 color;
out float divis;

void main()
{
	//gl_Position = vertex_position;
	mat4 trans_mat = mat4(1.0);
	trans_mat[3][0] = translation.x;
	trans_mat[3][1] = translation.y;
	trans_mat[3][2] = translation.z;
	vec4 vertex_p = trans_mat * vertex_position;
	gl_Position = vertex_p;
	vs_light_direction = light_position - view * vertex_p;
	v_position = vertex_p.xyz;
	color = vec4(0.5, 0.5, 0.5, 1.0);
	if (type <= 0.5) {
		color = vec4(229.0, 160.0, 25.0, 0.0) / 255.0;
	} else if (type <= 1.5) {
		color = vec4(119.0, 136.0, 153.0, 0.0) / 255.0;
	} else {
		color = vec4(76.0, 153.0, 0.0, 0.0) / 255.0;
	}
	divis = division;
}
)zzz";