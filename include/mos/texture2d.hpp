/* 
 * File:   Texture.h
 * Author: morgan
 *
 * Created on February 25, 2014, 7:26 PM
 */

#ifndef MO_TEXTURE2D_H
#define	MO_TEXTURE2D_H

#include <vector>
#include <glm/glm.hpp>

namespace mo {

/*!
 * @brief The Texture2D class
 *
 * Describes a texture in two dimension. Contains iterable chars as data.
 */
class Texture2D {
public:
    using Texels = std::vector<unsigned char>;
    static unsigned int current_id;
    template<class It>
    /*!
     * @brief Texture2D
     * @param begin
     * @param end
     * @param width
     * @param height
     * @param mipmaps should be used for rendering
     *
     * Constructor for a texture, that takes char valus from a container as input. Along with width and height.
     */
    Texture2D(It begin, It end, 
              unsigned int width, unsigned int height, 
              const bool mipmaps = true) :
              mipmaps(mipmaps),
              width_(width),
              height_(height) {
        id_ = current_id++;
        texels_.assign(begin, end);
    }

    Texture2D(const unsigned int width,
              const unsigned int height,
              const bool mipmaps = true):
        mipmaps(mipmaps),
        width_(width),
        height_(height) {
        id_ = current_id++;
    }

    virtual ~Texture2D();
    
    /*!
     * @brief begin iterator
     * @return constand begin iterator
     */
    Texels::const_iterator begin() const;

    /*!
     * @brief end iterator
     * @return constant end iterator
     */
    Texels::const_iterator end() const;
    
    /*!
     * @brief unique id
     * @return id
     */
    unsigned int id() const;
    
    /*!
     * @brief width in pixels
     * @return
     */
    unsigned int width() const;

    /*!
     * @brief height in pixels
     * @return
     */
    unsigned int height() const;

    /*!
     * @brief sample the texture
     * @param x less than width
     * @param y less than height
     * @return
     */
    glm::vec4 sample(const unsigned int x, const unsigned int y);
    
    const unsigned char * data() const;

    /*!
     * @brief if mipmaps should be used
     */
    bool mipmaps;
private:
    unsigned int id_;
    unsigned int width_;
    unsigned int height_;
    Texels texels_;
};

}

#endif	/* MO_TEXTURE_H */
