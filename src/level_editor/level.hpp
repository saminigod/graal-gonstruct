#ifndef GRAAL_LEVEL_HPP_
#define GRAAL_LEVEL_HPP_

#include "tileset.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <deque>
#include <list>
#include <string>

namespace Graal {
  static const std::string NW_LEVEL_VERSION = "GLEVNW01";
  class tile {
  public:
    int index;

    tile(): index(0) {}
    explicit tile(int index_): index(index_) {}
  };

  class tile_buf {
  public:
    tile_buf() : width(0), height(0) {}

    int get_width() const { return width; }
    int get_height() const { return height; }

          tile& get_tile(int x, int y)       { return tiles[x + y * width]; }
    const tile& get_tile(int x, int y) const { return tiles[x + y * width]; }

    void swap(tile_buf& other) {
      tiles.swap(other.tiles);
      std::swap(width, other.width);
      std::swap(height, other.height);
    }

    void resize(int w, int h) {
      tiles.resize(w*h);
      width = w;
      height = h;
    }

    void clear() {
      tiles.clear();
      height = width = 0;
    }

    bool empty() {
      return tiles.empty();
    }
  private:
    int width;
    int height;

    std::vector<tile> tiles;
  };

  class link {
  public:
    int x, y;
    int width, height;
    // can contain playerx, playery for example
    std::string new_x, new_y;

    std::string destination;

    link(): x(0), y(0), width(0), height(0) {}
  };

  class sign {
  public:
    int x, y;
    std::string text;
  };

  class npc {
  public:
    int id;
    int x, y;
    std::string image;
    std::string script;

    bool operator==(const Graal::npc& o) const {
      return id == o.id && x == o.x && y == o.y && image == o.image && script == o.script;
    }
    
    bool operator!=(const Graal::npc& o) const {
      return !operator==(o);
    }
  };

  class level {
  public:
    level(int fill_tile = 0);
    typedef std::list<link> link_list_type;
    typedef std::list<sign> sign_list_type;
    typedef std::list<npc> npc_list_type;

    int get_width() const;
    int get_height() const;

    Graal::npc& add_npc();
    Graal::npc& add_npc(Graal::npc& npc);
    level::npc_list_type::iterator get_npc(int id);
    void delete_npc(int id);

    tile_buf tiles;
    link_list_type links;
    sign_list_type signs;
    npc_list_type npcs;
  protected:
    int m_unique_npc_id_counter;
  };

  level* load_nw_level(const boost::filesystem::path& path);
  void save_nw_level(const level* _level, const boost::filesystem::path& path);
}

#endif
