R"zzz(#version 330 core
in vec4 light_direction;
in vec3 bary_coor;
flat in float type;
flat in vec4 color_r;
flat in float divi;
flat in vec4 tran;
out vec4 fragment_color;


float pi = acos(-1.0);

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float rand_xyz(vec3 co) {
	float res1 = fract(sin(dot(co.xy ,vec2(27.5785,567.655))) * 78687.3678);
	float res2 = fract(sin(dot(co.xz ,vec2(78.789,9.3783))) * 6896.332);
	float res3 = fract(sin(dot(co.yz ,vec2(39.376,709.37733))) * 54534.578523);
	return (res1 + res2 + res3);
}


vec2 generate_gradient(float t) {
	float gra_x = cos(t * 2 * pi);
	float gra_y = sin(t * 2 * pi);
	return vec2(gra_x, gra_y);
}

float f_function(float t) {
	if (t < 0) {
		t = -t;
	}
	return t >= 1.0 ? 0.0 : 1.0 - (3.0 - 2.0 * t) * t * t;
}

float surflet(float x, float y, vec2 gradient) {
	return f_function(x) * f_function(y) * (gradient.x * x + gradient.y * y);
}

float noise(float x, float y, vec3 coor) {
	float result = 0.0f;
	float cell_x = floor(x);
	float cell_y = floor(y);
	result += surflet( x- cell_x, y - cell_y, generate_gradient(fract(rand(vec2(cell_x, cell_y)) + rand_xyz(coor))));
	result += surflet( x- cell_x - 1.0, y - cell_y, generate_gradient(fract(rand(vec2(cell_x + 1.0, cell_y)) + rand_xyz(coor))));
	result += surflet( x- cell_x, y - cell_y - 1.0, generate_gradient(fract(rand(vec2(cell_x, cell_y + 1.0)) + rand_xyz(coor))));
	result += surflet( x- cell_x - 1.0, y - cell_y - 1.0, generate_gradient(fract(rand(vec2(cell_x + 1.0, cell_y + 1.0)) + rand_xyz(coor))));
	return result;
	
}


void main()
{

	vec2 uv_cor;

	if (divi <= 0.5) {
		uv_cor = vec2(bary_coor.y, bary_coor.z);
	} else {
		uv_cor = vec2(1-bary_coor.y, 1-bary_coor.z);
	}
	float bb = noise(uv_cor.x * 10.0, uv_cor.y * 10.0, tran.xyz);

	fragment_color = color_r * min((bb +0.3),1.0);
}
)zzz";
