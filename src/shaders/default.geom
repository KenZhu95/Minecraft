R"zzz(#version 400 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
uniform mat4 projection;
uniform mat4 view;
in vec4 vs_light_direction[];
in vec4 color[];
in float divis[];
flat out float divi;
flat out vec4 color_r;
flat out vec4 normal;
out vec4 light_direction;
out vec4 world_position;
out vec3 bary_coor;
flat out vec3 heights;
void main()
{
	int n = 0;
	//normal = vec4(0.0, 0.0, 1.0f, 0.0);
	normal = vec4(normalize(cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz)),1.0);
	vec3 pos1 = gl_in[0].gl_Position.xyz;
	vec3 pos2 = gl_in[1].gl_Position.xyz;
	vec3 pos3 = gl_in[2].gl_Position.xyz;
	vec3 l_a = pos2 - pos1;
	vec3 l_b = pos3 - pos1;
	float area = length(cross(pos2-pos1,pos3-pos1));
	float length1 = area / length(pos3-pos2);
	float length2 = area / length(pos3-pos1);
	float length3 = area / length(pos2-pos1);
	heights = vec3(length1, length2, length3);

	color_r = color[0];
	divi = divis[0];

	for (n = 0; n < gl_in.length(); n++) {
		light_direction = vs_light_direction[n];
		world_position = gl_in[n].gl_Position;
		//gl_Position = projection * gl_in[n].gl_Position;
		gl_Position = projection * view * gl_in[n].gl_Position;
		if (n == 0){
			bary_coor = vec3(1.0,0.0,0.0);
		} else if (n == 1){
			bary_coor = vec3(0.0, 1.0, 0.0);
		} else {
			bary_coor = vec3(0.0, 0.0, 1.0);
		}
		EmitVertex();
	}
	EndPrimitive();
}
)zzz";