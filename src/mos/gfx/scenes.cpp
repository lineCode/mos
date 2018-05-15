#include <mos/gfx/scenes.hpp>

namespace mos{
namespace gfx{

Scenes::Scenes(const std::initializer_list<Scene> & scenes): scenes_(scenes){
}

void Scenes::push_back(const Scene &scene) {
  scenes_.push_back(scene);
}

Scenes::Scenes() {}

Scenes::Container::const_iterator Scenes::begin() const {
  return scenes_.begin();
}

Scenes::Container::const_iterator Scenes::end() const {
  return scenes_.end();
}

}
}