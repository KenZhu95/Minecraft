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

class TerrainGenerator {
public:
	TerrainGenerator();
	~TerrainGenerator();
	glm::vec3 center_position;
	float side_length;
	float max_height = 20.0f;
	void getCenterFromEye(glm::vec3 eye_center) {
		center_position = glm::vec3(eye_center);
	}
	std::vector<glm::vec3> heights;
	void generateHeights();
	void setSideLength(float length) {
		side_length = length;
	}
	int center_index = 0;

};

#endif