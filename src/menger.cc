#include "menger.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger()
{
	// Add additional initialization if you like
}

Menger::~Menger()
{
}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = 0;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

// FIXME generate Menger sponge geometry

void Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
							   std::vector<glm::uvec3>& obj_faces,
							   std::vector<float>& obj_divis) const
{
	if (!this->nesting_level_){
		create_menger(obj_vertices, obj_faces, obj_divis, min_bound, max_bound);
		return;
	}

}

void
Menger::create_menger(std::vector<glm::vec4>& obj_vertices,
					  std::vector<glm::uvec3>& obj_faces,
					  std::vector<float>& obj_divis,
					  glm::vec3 min,
					  glm::vec3 max) const
{
	unsigned long v_num = obj_vertices.size();

	// obj_vertices.emplace_back(glm::vec4(min[0], min[1], min[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(max[0], max[1], max[2], 1.0f));
	// obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));


	// obj_faces.emplace_back(glm::uvec3(v_num, v_num + 1, v_num + 2));
 //    obj_faces.emplace_back(glm::uvec3(v_num + 3, v_num + 2, v_num + 1));

	// obj_faces.emplace_back(glm::uvec3(v_num + 1, v_num + 4, v_num + 3));
	// obj_faces.emplace_back(glm::uvec3(v_num + 6, v_num + 3, v_num + 4));

	// obj_faces.emplace_back(glm::uvec3(v_num + 5, v_num + 4, v_num + 7));
	// obj_faces.emplace_back(glm::uvec3(v_num + 6, v_num + 7, v_num + 4));

	// obj_faces.emplace_back(glm::uvec3(v_num + 0, v_num + 5, v_num + 2));
	// obj_faces.emplace_back(glm::uvec3(v_num + 7, v_num + 2, v_num + 5));

	// obj_faces.emplace_back(glm::uvec3(v_num + 0, v_num + 1, v_num + 5));
	// obj_faces.emplace_back(glm::uvec3(v_num + 4, v_num + 5, v_num + 1));

	// obj_faces.emplace_back(glm::uvec3(v_num + 2, v_num + 3, v_num + 7));
	// obj_faces.emplace_back(glm::uvec3(v_num + 6, v_num + 7, v_num + 3));


	obj_vertices.emplace_back(glm::vec4(min[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	obj_divis.emplace_back(1.0);

	obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(max[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	obj_divis.emplace_back(1.0);

	obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(max[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	obj_divis.emplace_back(1.0);

	obj_vertices.emplace_back(glm::vec4(min[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	obj_divis.emplace_back(1.0);

	obj_vertices.emplace_back(glm::vec4(min[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(max[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], min[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], min[1], min[2], 1.0f));
	obj_divis.emplace_back(1.0);

	obj_vertices.emplace_back(glm::vec4(min[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));
	obj_divis.emplace_back(0.0);

	obj_vertices.emplace_back(glm::vec4(max[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(min[0], max[1], max[2], 1.0f));
	obj_vertices.emplace_back(glm::vec4(max[0], max[1], min[2], 1.0f));
	obj_divis.emplace_back(1.0);


	obj_faces.emplace_back(glm::uvec3(v_num, v_num + 1, v_num + 2));
	obj_faces.emplace_back(glm::uvec3(v_num + 3, v_num + 4, v_num + 5));
	obj_faces.emplace_back(glm::uvec3(v_num = 6, v_num + 7, v_num + 8));
	obj_faces.emplace_back(glm::uvec3(v_num + 9, v_num + 10, v_num + 11));
	obj_faces.emplace_back(glm::uvec3(v_num + 12, v_num + 13, v_num + 14));
	obj_faces.emplace_back(glm::uvec3(v_num + 15, v_num + 16, v_num + 17));
	obj_faces.emplace_back(glm::uvec3(v_num + 18, v_num + 19, v_num + 20));
	obj_faces.emplace_back(glm::uvec3(v_num + 21, v_num + 22, v_num + 23));
	obj_faces.emplace_back(glm::uvec3(v_num + 24, v_num + 25, v_num + 26));
	obj_faces.emplace_back(glm::uvec3(v_num + 27, v_num + 28, v_num + 29));
	obj_faces.emplace_back(glm::uvec3(v_num + 30, v_num + 31, v_num + 32));
	obj_faces.emplace_back(glm::uvec3(v_num + 33, v_num + 34, v_num + 35));


}