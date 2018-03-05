#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <atomic>
#include <memory>
#include <chrono>
#include <mos/gfx/vertex.hpp>

namespace mos {
namespace gfx {
class Mesh;
using SharedMesh = std::shared_ptr<Mesh>;
/**
 * Describes the geometric data to be rendered. Contains vertices
 * and indices, for vertex order.
 */
class Mesh {
public:
  using Positions = std::vector<glm::vec3>;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

  /**
   * @brief Vertices container.
   */
  using Vertices = std::vector<Vertex>;

  /**
   * @brief Elements/indices container.
   */
  using Indices = std::vector<int>;

  template<class Tv, class Te>
  /**
   * @brief Mesh constructor.
   * @param vertices_begin Iterator to first vertex.
   * @param vertices_end Iterator to last vertex.
   * @param elements_begin Iterator to first element.
   * @param elements_end Iterator to last element.
   *
   * Mesh constructor that takes Vertices and elements (vertex order for
   *rendering).
   */
  Mesh(const Tv vertices_begin, const Tv vertices_end,
       Te elements_begin, Te elements_end)
      : vertices(vertices_begin, vertices_end),
        indices(elements_begin, elements_end), id_(current_id_++) {
    invalidate();
  }

  /**
   * @brief Mesh constructor
   * @param vertices
   * @param elements
   */
  Mesh(const std::initializer_list<Vertex> &vertices,
       const std::initializer_list<int> &elements);

  /**
   * @brief Mesh constructor from file.
   * @param path
   */
  Mesh(const std::string &path);

  /**
   * @brief Mesh
   */
  Mesh();

  /**
   * @brief Mesh copy constructor.
   * @param mesh
   */
  Mesh(const Mesh &mesh);

  /**
   * @brief ~Mesh destructor.
   */
  ~Mesh();

  static SharedMesh load(const std::string &path);

  /**
   * @return A unique identifier.
   */
  unsigned int id() const;

  /**
   * @return Time when modified.
   */
  TimePoint modified() const;

  /**
   * @brief invalidates the mesh, hence the data is updated.
   *
   */
  //TODO: Automatic when moodified
  void invalidate();

  /**
   * @brief Clear the whole mesh.
   */
  void clear();

  /**
   * @brief Get a copy of positions.
   * @return
   */
  Positions positions() const;
  /**
   * @brief mix
   * @param mesh1
   * @param mesh2
   * @param amount
   */
  void mix(const Mesh &mesh1, const Mesh &mesh2, const float amount);

  void apply_transform(const glm::mat4 &transform);

  void calculate_normals();
  void calculate_flat_normals();
  void calculate_tangents();

  Vertices vertices;
  Indices indices;
private:
  TimePoint modified_;
  void calculate_tangents(Vertex &v0, Vertex &v1, Vertex &v2);
  static std::atomic_uint current_id_;
  unsigned int id_;
};
}
}