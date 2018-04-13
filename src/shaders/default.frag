R"zzz(#version 330 core
flat in vec4 normal;
in vec4 light_direction;
in vec3 bary_color;
flat in float type;
flat in vec4 color_r;
flat in float divi;
out vec4 fragment_color;

void main()
{
	vec4 color1 = vec4(0.5, 0.5, 0.5, 1.0);
	//color = vec4(abs(normal.x), abs(normal.y), abs(normal.z), 0.0);
	//float dot_nl = dot(normalize(light_direction), normalize(normal));
	//dot_nl = clamp(dot_nl, 0.0, 1.0);
	//fragment_color = clamp(dot_nl * color, 0.0, 1.0);
	vec2 uv_cor;
	if (divi <= 0.5) {
		uv_cor = vec2(bary_color.y, bary_color.z);
	} else {
		uv_cor = vec2(1-bary_color.y, 1-bary_color.z);
	}
	if (type <= 0.5) {
		color1 = vec4(0.5, 0.5, 0.0, 0.0);
	} else if (type <= 1.5) {
		color1 = vec4(0.0, 1.0, 0.0, 0.0);
	} else {
		color1 = vec4(0.0, 0.0, 1.0, 0.0);
	}
	fragment_color = color_r;
}
)zzz";
