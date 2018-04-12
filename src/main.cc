#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// OpenGL library includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <debuggl.h>
#include "menger.h"
#include "camera.h"
#include "terrain_generator.h"

int window_width = 800, window_height = 600;

// VBO and VAO descriptors.
enum { kVertexBuffer, kIndexBuffer, kTranslationBuffer, kTypeBuffer, kNumVbos };

// These are our VAOs.
enum { kGeometryVao, kNumVaos };

GLuint g_array_objects[kNumVaos];  // This will store the VAO descriptors.
GLuint g_buffer_objects[kNumVaos][kNumVbos];  // These will store VBO descriptors.

// C++ 11 String Literal
// See http://en.cppreference.com/w/cpp/language/string_literal
const char* vertex_shader =
#include "shaders/default.vert"
;


const char* geometry_shader =
#include "shaders/default.geom"
;

const char* fragment_shader =
#include "shaders/default.frag"
;


// FIXME: Implement shader effects with an alternative shader.


void
ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << "\n";
}

std::shared_ptr<Menger> g_menger;
Camera g_camera;
bool FPSMode = true;
bool if_gravity = true;
TerrainGenerator terrain;

void
KeyCallback(GLFWwindow* window,
            int key,
            int scancode,
            int action,
            int mods)
{
	// Note:
	// This is only a list of functions to implement.
	// you may want to re-organize this piece of code.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_S && mods == GLFW_MOD_CONTROL && action == GLFW_RELEASE) {
		// FIXME: save geometry to OBJ
		
	} else if (key == GLFW_KEY_S && mods == GLFW_MOD_CONTROL && action == GLFW_RELEASE) {
		if_gravity = !if_gravity;
	} else if (key == GLFW_KEY_W && action != GLFW_RELEASE) {
		// FIXME: WASD
		g_camera.forward_back(1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_S && action != GLFW_RELEASE && mods!= GLFW_MOD_CONTROL) {
		g_camera.forward_back(-1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_A && action != GLFW_RELEASE) {
		g_camera.strafe(-1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_D && action != GLFW_RELEASE) {
		g_camera.strafe(1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_LEFT && action != GLFW_RELEASE) {
		// FIXME: Left Right Up and Down
		g_camera.roll(-1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE) {
		g_camera.roll(1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE) {
		g_camera.up_down(-1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_UP && action != GLFW_RELEASE) {
		g_camera.up_down(1.0);
		g_camera.is_move = true;
	} else if (key == GLFW_KEY_C && action != GLFW_RELEASE) {
		// FIXME: FPS mode on/off
		FPSMode = !FPSMode;
	}

}

int g_current_button;
bool g_mouse_pressed;
bool g_prev_pressed;
int INSTANCE_COUNT = 0;


void
MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y)
{
	glm::vec2 mouse(mouse_x, mouse_y);
	glm::vec2 prev(g_camera.mouse_x_, g_camera.mouse_y_);
	glm::vec2 diff = mouse - prev;
	g_prev_pressed = g_mouse_pressed;
	g_camera.mouse_x_ = mouse_x;
	g_camera.mouse_y_ = mouse_y;
	if (!g_mouse_pressed)
		return;
	if (!g_prev_pressed){
		std::cout << "not pressed previously" << std::endl;
		return;
	}
	if (g_current_button == GLFW_MOUSE_BUTTON_LEFT) {
		// FIXME: left drag
		g_camera.rotate(glm::vec2(diff.x, diff.y));
	} else if (g_current_button == GLFW_MOUSE_BUTTON_RIGHT) {
		// FIXME: right drag
		g_camera.zoom(10.0f * diff.y / window_height);
	} else if (g_current_button == GLFW_MOUSE_BUTTON_MIDDLE) {
		// FIXME: middle drag

	}

	//g_camera.mouse_x_ = mouse_x;
	//g_camera.mouse_y_ = mouse_y;
	//g_prev_pressed = g_mouse_pressed;
}

void
MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	g_mouse_pressed = (action == GLFW_PRESS);
	g_current_button = button;
}


int main(int argc, char* argv[])
{
	std::string window_title = "Menger";
	if (!glfwInit()) exit(EXIT_FAILURE);
	g_menger = std::make_shared<Menger>();
	glfwSetErrorCallback(ErrorCallback);

	// Ask an OpenGL 4.1 core profile context
	// It is required on OSX and non-NVIDIA Linux
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(window_width, window_height,
			&window_title[0], nullptr, nullptr);
	CHECK_SUCCESS(window != nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	CHECK_SUCCESS(glewInit() == GLEW_OK);
	glGetError();  // clear GLEW's error for it
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePosCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSwapInterval(1);
	const GLubyte* renderer = glGetString(GL_RENDERER);  // get renderer string
	const GLubyte* version = glGetString(GL_VERSION);    // version as a string
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL version supported:" << version << "\n";

	std::vector<glm::vec4> obj_vertices;
	std::vector<glm::uvec3> obj_faces;
	std::vector<glm::vec4> translation_vectors;
	std::vector<float> types;

	terrain.getCenterFromEye(g_camera.getEyePosition());
	//terrain.center_position = glm::vec3(1.0);
	terrain.setSideLength(100.0f);
	terrain.generateHeights();
	INSTANCE_COUNT = 0;
	for (const auto& height: terrain.heights) {
		int h = (int)(height.y);
		for (int i = 0; i <= h; i++) {
			INSTANCE_COUNT++;
			glm::vec4 translation = glm::vec4(0.0f);
			translation.x = (float)height.x;
			translation.y = (float)i;
			translation.z = (float)height.z;
			translation_vectors.emplace_back(translation);
			if (i <= 10) {
				types.emplace_back(0.0);
			} else if (i <= 20) {
				types.emplace_back(1.0);
			} else {
				types.emplace_back(2.0);
			}

		}
	}
	glm::vec3 eye_old = g_camera.getEyePosition();
	g_camera.setEyePosition(glm::vec3(eye_old.x, terrain.heights[terrain.center_index].y + 2.75 , eye_old.z));

	std::cout << translation_vectors.size() << std::endl;

    //FIXME: Create the geometry from a Menger object.

	g_menger->set_nesting_level(0);
	g_menger->generate_geometry(obj_vertices, obj_faces);
	g_menger->set_clean();


	glm::vec4 min_bounds = glm::vec4(std::numeric_limits<float>::max());
	glm::vec4 max_bounds = glm::vec4(-std::numeric_limits<float>::max());
	for (const auto& vert : obj_vertices) {
		min_bounds = glm::min(vert, min_bounds);
		max_bounds = glm::max(vert, max_bounds);
	}
	// std::cout << "min_bounds = " << glm::to_string(min_bounds) << "\n";
	// std::cout << "max_bounds = " << glm::to_string(max_bounds) << "\n";

	// Setup our VAO array.
	CHECK_GL_ERROR(glGenVertexArrays(kNumVaos, &g_array_objects[0]));

	// Switch to the VAO for Geometry.
	CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kGeometryVao]));

	// Generate buffer objects
	CHECK_GL_ERROR(glGenBuffers(kNumVbos, &g_buffer_objects[kGeometryVao][0]));

	// Setup vertex data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * obj_vertices.size() * 4, obj_vertices.data(),
				GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(0));


	// Setup translation data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kTranslationBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * translation_vectors.size() * 4, translation_vectors.data(),
				GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(1));

		// Setup translation data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kTypeBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * types.size(), types.data(),
				GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(2));

	CHECK_GL_ERROR(glVertexAttribDivisor(1,1));
	CHECK_GL_ERROR(glVertexAttribDivisor(2,1));

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(uint32_t) * obj_faces.size() * 3,
				obj_faces.data(), GL_STATIC_DRAW));

	/*
 	 * By far, the geometry is loaded into g_buffer_objects[kGeometryVao][*].
	 * These buffers are binded to g_array_objects[kGeometryVao]
	 */





	// Setup vertex shader.
	GLuint vertex_shader_id = 0;
	const char* vertex_source_pointer = vertex_shader;
	CHECK_GL_ERROR(vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
	CHECK_GL_ERROR(glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, nullptr));
	glCompileShader(vertex_shader_id);
	CHECK_GL_SHADER_ERROR(vertex_shader_id);

	// Setup geometry shader.
	GLuint geometry_shader_id = 0;
	const char* geometry_source_pointer = geometry_shader;
	CHECK_GL_ERROR(geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER));
	CHECK_GL_ERROR(glShaderSource(geometry_shader_id, 1, &geometry_source_pointer, nullptr));
	glCompileShader(geometry_shader_id);
	CHECK_GL_SHADER_ERROR(geometry_shader_id);

	// Setup fragment shader.
	GLuint fragment_shader_id = 0;
	const char* fragment_source_pointer = fragment_shader;
	CHECK_GL_ERROR(fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
	CHECK_GL_ERROR(glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr));
	glCompileShader(fragment_shader_id);
	CHECK_GL_SHADER_ERROR(fragment_shader_id);

	// Let's create our program.
	GLuint program_id = 0;
	CHECK_GL_ERROR(program_id = glCreateProgram());
	CHECK_GL_ERROR(glAttachShader(program_id, vertex_shader_id));
	CHECK_GL_ERROR(glAttachShader(program_id, fragment_shader_id));
	CHECK_GL_ERROR(glAttachShader(program_id, geometry_shader_id));

	// Bind attributes.
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 0, "vertex_position"));
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 1, "translation"));
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 2, "type"));
	CHECK_GL_ERROR(glBindFragDataLocation(program_id, 0, "fragment_color"));
	glLinkProgram(program_id);
	CHECK_GL_PROGRAM_ERROR(program_id);

	// Get the uniform locations.
	GLint projection_matrix_location = 0;
	CHECK_GL_ERROR(projection_matrix_location =
			glGetUniformLocation(program_id, "projection"));
	GLint view_matrix_location = 0;
	CHECK_GL_ERROR(view_matrix_location =
			glGetUniformLocation(program_id, "view"));
	GLint light_position_location = 0;
	CHECK_GL_ERROR(light_position_location =
			glGetUniformLocation(program_id, "light_position"));




	glm::vec4 light_position = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
	float aspect = 0.0f;
	float theta = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		// Setup some basic window stuff.
		glfwGetFramebufferSize(window, &window_width, &window_height);
		glViewport(0, 0, window_width, window_height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);


		// Switch to the Geometry VAO.
		CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kGeometryVao]));

		if (g_menger && g_menger->is_dirty()) {
			obj_vertices.clear();
			obj_faces.clear();
			g_menger->generate_geometry(obj_vertices, obj_faces);
			g_menger->set_clean();

			// FIXME: Upload your vertex data here.
			CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kVertexBuffer]));
			CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj_vertices.size() * 4, &obj_vertices[0], GL_STATIC_DRAW));
		}

		if (g_camera.is_move) {

			terrain.getCenterFromEye(g_camera.getEyePosition());
			//terrain.center_position = glm::vec3(1.0);
			terrain.generateHeights();
			INSTANCE_COUNT = 0;
			translation_vectors.clear();
			types.clear();
			for (const auto& height: terrain.heights) {
				int h = (int)(height.y);
				for (int i = 0; i <= h; i++) {
					INSTANCE_COUNT++;
					glm::vec4 translation = glm::vec4(0.0f);
					translation.x = (float)height.x;
					translation.y = (float)i;
					translation.z = (float)height.z;
					translation_vectors.emplace_back(translation);
					if (i <= 10) {
						types.emplace_back(0.0);
					} else if (i <= 20) {
						types.emplace_back(1.0);
					} else {
						types.emplace_back(2.0);
					}

				}
			}
			eye_old = g_camera.getEyePosition();
			std::cout << eye_old.x << std::endl;
			g_camera.setEyePosition(glm::vec3(eye_old.x, terrain.heights[terrain.center_index].y + 2.75 , eye_old.z));
			CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kTranslationBuffer]));
			// NOTE: We do not send anything right now, we just describe it to OpenGL.
			CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * translation_vectors.size() * 4, translation_vectors.data(),
				GL_STATIC_DRAW));
			CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kTypeBuffer]));
			// NOTE: We do not send anything right now, we just describe it to OpenGL.
			CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * types.size(), types.data(),
				GL_STATIC_DRAW));

			g_camera.is_move = false;
		}

		// Compute the projection matrix.
		aspect = static_cast<float>(window_width) / window_height;
		glm::mat4 projection_matrix =
			glm::perspective(glm::radians(45.0f), aspect, 0.0001f, 1000.0f);

		// Compute the view matrix
		// FIXME: change eye and center through mouse/keyboard events.
		glm::mat4 view_matrix = g_camera.get_view_matrix();

		// Use our program.
		CHECK_GL_ERROR(glUseProgram(program_id));

		// Pass uniforms in.
		CHECK_GL_ERROR(glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE,
					&projection_matrix[0][0]));
		CHECK_GL_ERROR(glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE,
					&view_matrix[0][0]));
		CHECK_GL_ERROR(glUniform4fv(light_position_location, 1, &light_position[0]));

		// Draw our triangles.
		//CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, obj_faces.size() * 3, GL_UNSIGNED_INT, 0));
		CHECK_GL_ERROR(glDrawElementsInstanced(GL_TRIANGLES, obj_faces.size() * 3, GL_UNSIGNED_INT, 0, INSTANCE_COUNT));

		// FIXME: Render the floor
		// Note: What you need to do is
		// 	1. Switch VAO
		// 	2. Switch Program
		// 	3. Pass Uniforms
		// 	4. Call glDrawElements, since input geometry is
		// 	indicated by VAO.

		// Poll and swap.
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}