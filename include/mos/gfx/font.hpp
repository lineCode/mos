#pragma once
#include <map>
#include <memory>
#include <mos/gfx/character.hpp>
#include <mos/gfx/texture_2d.hpp>

namespace mos {
namespace gfx {

/** Bitmap font. */
class Font final {
public:
  using CharMap = std::map<char, Character>;
  /** @param characters Chars supported.
   * @param texture Image with glyphs. */
  Font(const CharMap &characters,
       const SharedTexture2D &texture,
       const float height,
       const float ascender,
       const float descender);
  Font(const std::string &path);
  ~Font();
  float height() const;
  float base() const;
  /** Texture with characters. */
  SharedTexture2D texture;

  /** Characters supported. */
  CharMap characters;
private:
  float base_;
  float height_;
};
}
}

