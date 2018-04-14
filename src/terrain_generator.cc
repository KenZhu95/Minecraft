#include "terrain_generator.h"

const double pi = std::acos(-1);

TerrainGenerator::TerrainGenerator() {

}

TerrainGenerator::~TerrainGenerator() {

}

static int const size = 256;
static int const mask = size-1;
int perm[size];
float grads_x[size], grads_y[size];
void TerrainGenerator::initialize() {
	for (int index = 0; index < size; ++index) {
		int other = rand() % (index+1);
		if (index > other) {
			perm[index] = perm[other];
		}
		perm[other] = index;
		grads_x[index] = cosf(2.0f * pi * index / size);
		grads_y[index] = sinf(2.0f * pi * index / size);
	}
}

float f_function(float t) {
	t = fabsf(t);
	return t >= 1.0f ? 0.0f : 1.0f - (3.0f - 2.0f * t) * t * t;
}

float surflet(float x, float y, float grad_x, float grad_y) {
	return f_function(x) * f_function(y) * (grad_x * x + grad_y * y);
}

float noise(float x, float y) {
	float result = 0.0f;
	int cell_x = floorf(x);
	int cell_y = floorf(y);
	for (int grid_y = cell_y; grid_y <= cell_y + 1; ++grid_y) {
		for (int grid_x = cell_x; grid_x <= cell_x + 1; ++grid_x) {
			int hash = perm[(perm[grid_x & mask] + grid_y) & mask];
			result += surflet(x - grid_x, y - grid_y, grads_x[hash], grads_y[hash]);
		}
	}
	return result;
	
}

float rand1(glm::vec2 co){
    float a =  (sin(glm::dot(glm::vec2(co.x,co.y) ,glm::vec2(12.9898,78.233))) * 43758.5453);
    return a - (float)floor(a);
}



void TerrainGenerator::generatePerlinHeights() {
	heights.clear();
	int x_min = floor(center_position.x - side_length);
	int x_max = floor(center_position.x - side_length) + 2 * side_length;
	int z_min = floor(center_position.z - side_length);
	int z_max = floor(center_position.z - side_length) + 2 * side_length;
	start_x = x_min;
	start_z = z_min;
	for (int i=0; i < 101; i++) {
		for (int j=0; j < 101; j++) {
			append_buffer[i][j] = 0;
		}
	}
	for (int x = x_min; x <= x_max; x++) {
		for (int z = z_min; z <= z_max; z++) {
			double h = glm::max((noise(((float)x/10.0), ((float)z/10.0)) + 0.5),0.0) * max_height;
			int top_height = floor(h);
			if (top_height < 2) {
				top_height = 2;
			}
			if (top_height > 9) {
				float r = rand1(glm::vec2((float)x, (float)z));
				if (r > 0.95) {
					top_height  += 2;
					append_buffer[x-x_min][z-z_min] = 1;
				}
			}
			heights.emplace_back(glm::vec3(x, top_height, z));
			height_buffer[x-x_min][z-z_min] = top_height;
			
		}
	}
}
