#include <mos/render/texture.hpp>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <map>

namespace mos {
namespace gfx {
std::atomic_uint Texture::current_id_;
Texture::Texture(const int width,
                 const int height,
                 const Texture::Format &format,
                 const Texture::Wrap &wrap,
                 const bool mipmaps) : id_(current_id_++),
                                       width_(width),
                                       height_(height),
                                       format(format),
                                       wrap(wrap),
                                       mipmaps(mipmaps),
                                       layers_{Data()} {}

Texture::Texture(const std::initializer_list<Texture::Data> &layers,
                 const int width,
                 const int height,
                 const Texture::Format &format,
                 const Texture::Wrap &wrap,
                 const bool mipmaps) : Texture(layers.begin(),
                                               layers.end(),
                                               width,
                                               height,
                                               format,
                                               wrap,
                                               mipmaps) {}

Texture::Texture(const std::initializer_list<std::string> &paths,
                 const Texture::Wrap &wrap,
                 const bool mipmaps) : id_(current_id_++), wrap(wrap), mipmaps(mipmaps) {
  for (auto &path : paths) {
    int bpp;
    unsigned char *pixels = stbi_load(path.c_str(), &width_, &height_, &bpp, 0);
    layers_.push_back(Data(pixels, pixels + (width_ * height_ * bpp)));
    std::map<int, Format> bpp_map{{1, Format::R}, {2, Format::RG}, {3, Format::SRGB}, {4, Format::SRGBA}};
    format = bpp_map[bpp];
  }
}

int Texture::id() const {
  return id_;
}
int Texture::width() const {
  return width_;
}
int Texture::height() const {
  return height_;
}
int Texture::depth() const {
  return layers_.size();
}
int Texture::size(const int layer) {
  return layers_[layer].size();
}
const unsigned char *Texture::data(const int layer) const {
  return layers_[layer].data();
}
}
}
