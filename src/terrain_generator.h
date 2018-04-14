#ifndef TERRAINDENERATOR_H
#define TERRAINGENERATOR_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>
#include <unordered_map>
#include <map>

class TerrainGenerator {
public:
	TerrainGenerator();
	~TerrainGenerator();
	glm::vec3 center_position;
	int start_x;
	int start_z;
	float side_length;
	float max_height = 15.0f;
	void getCenterFromEye(glm::vec3 eye_center) {
		center_position = glm::vec3(eye_center);
	}
	std::vector<glm::vec3> heights;
	int height_buffer[101][101];
	int append_buffer[101][101];
	//void generateHeights();
	void generatePerlinHeights();
	void setSideLength(float length) {
		side_length = length;
	}
	float center_height_lb = 0;
	float center_height_rb = 0;
	float center_height_lt = 0;
	float center_height_rt = 0;
	void initialize();

};

#endif