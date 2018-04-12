#include "terrain_generator.h"

const double pi = std::acos(-1);

TerrainGenerator::TerrainGenerator() {

}

TerrainGenerator::~TerrainGenerator() {

}

void TerrainGenerator::generateHeights() {
	heights.clear();
	int x_min = floor(center_position.x - side_length);
	int x_max = floor(center_position.x + side_length);
	int z_min = floor(center_position.z - side_length);
	int z_max = floor(center_position.z + side_length);
	for (int x = x_min; x <= x_max; x++) {
		for (int z = z_min; z <= z_max; z++) {
			double frac = (double)(x - x_min) / (side_length);
			double h = (std::sin(pi * frac)+1) * max_height;
			int top_height = floor(h);
			heights.emplace_back(glm::vec3(x, top_height, z));
			if (x == floor(center_position.x) && z == floor(center_position.z)) {
				center_index = heights.size() - 1;
			}
		}
	}

}
