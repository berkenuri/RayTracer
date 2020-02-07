////////////////////////////////////////////////////////////////////////////////
/// AUTHOR: Berke Nuri
/// @file
/// @brief Contains main function to create a window and run engine that
///        repeatedly generates a framebuffer and displays it.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ray.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "scene.h"

// STL
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>

// GL
#define GL_GLEXT_PROTOTYPES
#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>
#endif

// GLM
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these

// Window
int g_width{1360};
int g_height{768};
int g_window{0};
std::unique_ptr<glm::vec4[]> g_frame{nullptr}; ///< Framebuffer

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize() {
  glClearColor(0.f, 0.f, 0.0f, 0.f);

  g_frame = std::make_unique<glm::vec4[]>(g_width*g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void
resize(GLint _w, GLint _h) {
  g_width = _w;
  g_height = _h;

  // Viewport
  glViewport(0, 0, g_width, g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Timer function to fix framerate in a GLUT application
/// @param _v Value (not used here)
///
/// Note, this is rudametary and fragile.
void
timer(int _v) {
  if(g_window != 0) {
    glutPostRedisplay();

    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    glutTimerFunc((unsigned int)(1000.f*g_delay), timer, 0);
  }
  else
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw() {
  using namespace std::chrono;

  //////////////////////////////////////////////////////////////////////////////
  // Clear
  for(int i = 0; i < g_width*g_height; ++i) {
    g_frame[i] = glm::vec4(0.f, 0.f, 0.f, 0.f);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  float theta = (float) M_PI / 4.0f;

  Material mat = Material("mat");
  Material shiny = Material("shiny");

  Scene scene = Scene();

  std::ifstream ifs;
  ifs.open("test1.txt");

  if (!ifs) {
        std::cout << "Unable to open file";
        exit(1);
  }

  std::string line;

  while(ifs) {

    getline(ifs, line);
    std::istringstream iss(line);

    std::string tag;
    iss >> tag;

    if (tag.compare("Camera:") == 0) {

      std::string view;
      glm::vec3 pos;
      float focal_length;

      iss >> view >> pos.x >> pos.y >> pos.z >> focal_length;

      Camera camera = Camera(view, pos, focal_length, theta, g_width, g_height);
      scene.addCamera(camera);

    } else if (tag.compare("Light:") == 0) {

      glm::vec3 pos;

      iss >> pos.x >> pos.y >> pos.z;

      std::shared_ptr<Light> ptr_light(new Light(pos));
      scene.addLight(ptr_light);

    } else if (tag.compare("Sphere:") == 0) {

      glm::vec3 pos;
      float r;
      glm::vec4 c;
      Material m = Material();

      iss >> pos.x >> pos.y >> pos.z >> r >> c[0] >> c[1] >> c[2] >> c[3];

      std::string materialType;
      iss >> materialType;

      if (materialType.compare("shiny") == 0) {
        m = shiny;
      } else {
        m = mat;
      }

      std::shared_ptr<Sphere> ptr_sphere(new Sphere(pos, r, c, m));
      scene.addObject(ptr_sphere);

    } else if (tag.compare("Plane:") == 0) {

      glm::vec3 pos;
      glm::vec3 n;
      glm::vec4 c;
      Material m = Material();

      iss >> pos.x >> pos.y >> pos.z >> n.x >> n.y >> n.z
      >> c[0] >> c[1] >> c[2] >> c[3];

      std::string materialType;
      iss >> materialType;

      if (materialType.compare("shiny") == 0) {
        m = shiny;
      } else {
        m = mat;
      }

      std::shared_ptr<Plane> ptr_plane(new Plane(pos, n, c, m));
      scene.addObject(ptr_plane);

    } else {}

  }

  ifs.close();

  scene.rayTracer(g_frame, g_width, g_height);

  // Simple static :P
  //for(int i = 0; i < g_width*g_height; ++i)
  //  g_frame[i] = glm::vec4(1, 0, 0, 1.f);

  glDrawPixels(g_width, g_height, GL_RGBA, GL_FLOAT, g_frame.get());

  //////////////////////////////////////////////////////////////////////////////
  // Show
  glutSwapBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Record frame time
  high_resolution_clock::time_point time = high_resolution_clock::now();
  g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
  g_frameTime = time;
  g_framesPerSecond = 1.f/(g_delay + g_frameRate);
  printf("FPS: %6.2f\n", g_framesPerSecond);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
void
keyPressed(GLubyte _key, GLint _x, GLint _y) {
  switch(_key) {
    // Escape key : quit application
    case 27:
      std::cout << "Destroying window: " << g_window << std::endl;
      glutDestroyWindow(g_window);
      g_window = 0;
      break;
    // Unhandled
    default:
      std::cout << "Unhandled key: " << (int)(_key) << std::endl;
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses of special keys
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
void
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
  switch(_key) {
    // Arrow keys
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
      break;
    // Unhandled
    default:
      std::cout << "Unhandled special key: " << _key << std::endl;
      break;
  }
}

void clamp255(glm::vec3& col) {
  col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
  col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
  col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {

  //////////////////////////////////////////////////////////////////////////////
  // Initialize GLUT Window
  std::cout << "Initializing GLUTWindow" << std::endl;
  // GLUT
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(g_width, g_height); // HD size
  g_window = glutCreateWindow("Spiderling: A Rudamentary Game Engine");

  // GL
  initialize();

  //////////////////////////////////////////////////////////////////////////////
  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glutReshapeFunc(resize);
  glutDisplayFunc(draw);
  glutKeyboardFunc(keyPressed);
  glutSpecialFunc(specialKeyPressed);
  glutTimerFunc(1000/FPS, timer, 0);

  // Start application
  std::cout << "Starting Application" << std::endl;
  glutMainLoop();

  return 0;

}

#if   defined(OSX)
#pragma clang diagnostic pop
#endif
