#include <mos/gfx/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mos {
namespace gfx {

Camera::Camera() {
}

Camera::Camera(const glm::vec3 &position,
                 const glm::vec3 &center,
                 const glm::mat4 &projection,
                 const glm::vec3 &up)
  : projection(projection), view(glm::lookAt(position, center, up)), up_(up),
    position_(position), center_(center){}

glm::vec3 Camera::up() const { return up_; }

void Camera::up(const glm::vec3 &up) {
  up_ = up;
  update_view();
}

glm::vec3 Camera::position() const { return position_; }

void Camera::position(const glm::vec3 &position) {
  position_ = position;
  update_view();
}

glm::vec3 Camera::center() const { return center_; }

void Camera::center(const glm::vec3 &center) {
  center_ = center;
  update_view();
}

glm::vec3 Camera::direction() const {
  return glm::normalize(center_ - position_);
}

void Camera::direction(const glm::vec3 &direction) {
  center(position_ + direction);
  update_view();
}


void Camera::update_view() { view = glm::lookAt(position_, center_, up_); }

float Camera::aspect_ratio() const {
  return projection[1][1] / projection[0][0];
}
}
}
