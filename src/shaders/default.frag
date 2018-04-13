R"zzz(#version 330 core
flat in vec4 normal;
in vec4 light_direction;
in vec3 bary_color;
flat in float type;
flat in vec4 color_r;
flat in float divi;
out vec4 fragment_color;


int size = 256;
int mask = size-1;
int perm[256];
float grads_x[256], grads_y[256];
float pi = acos(-1.0);

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float f_function(float t) {
	if (t < 0) {
		t = -t;
	}
	return t >= 1.0 ? 0.0 : 1.0 - (3.0 - 2.0 * t) * t * t;
}

float surflet(float x, float y, float grad_x, float grad_y) {
	return f_function(x) * f_function(y) * (grad_x * x + grad_y * y);
}

float noise(float x, float y) {
	float result = 0.0f;
	int cell_x = int(floor(x));
	int cell_y = int(floor(y));
	for (int grid_y = cell_y; grid_y <= cell_y + 1; ++grid_y) {
		for (int grid_x = cell_x; grid_x <= cell_x + 1; ++grid_x) {
			int hash = perm[(perm[grid_x & mask] + grid_y) & mask];
			result += surflet(x - grid_x, y - grid_y, grads_x[hash], grads_y[hash]);
		}
	}
	return result;
	
}


void main()
{

	for (int index = 0; index < size; ++index) {
		int other = int(rand(vec2(index, index - 1.0)) * 10000) % (index+1);
		if (index > other) {
			perm[index] = perm[other];
		}
		perm[other] = index;
		grads_x[index] = cos(2.0f * pi * index / size);
		grads_y[index] = sin(2.0f * pi * index / size);
	}

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
	float bb = noise(uv_cor.x, uv_cor.y);
	if (type <= 0.5) {
		color1 = vec4(0.5, 0.5, 0.0, 0.0);
	} else if (type <= 1.5) {
		color1 = vec4(0.0, 1.0, 0.0, 0.0);
	} else {
		color1 = vec4(0.0, 0.0, 1.0, 0.0);
	}
	fragment_color = color_r * (bb +0.5);
}
)zzz";
