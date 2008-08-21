#ifndef GRAAL_LEVEL_EDITOR_TILE_OBJECTS_DISPLAY_HPP_
#define GRAAL_LEVEL_EDITOR_TILE_OBJECTS_DISPLAY_HPP_

#include <gtkmm.h>
#include "preferences.hpp"
#include "tiles_display.hpp"

namespace Graal {
  namespace level_editor {
    class tile_objects_display: public Gtk::VBox {
    public:
      tile_objects_display(level_editor::preferences& preferences);

      void set();
      void get();

      // Small wrapper around tiles_display
      void set_tile_size(int tile_width, int tile_height);
      void set_tileset_surface(const Cairo::RefPtr<Cairo::Surface>& surface);

      typedef sigc::signal<void, tile_buf&, int, int> signal_tiles_selected_type;
      signal_tiles_selected_type& signal_tiles_selected();
      
      void on_mouse_pressed(GdkEventButton* event);
    protected:
      Gtk::ComboBoxEntryText m_groups;
      Gtk::ComboBoxEntryText m_objects;

      tiles_display m_display;

      preferences& m_preferences;

      void on_group_changed();
      void on_object_changed();

      signal_tiles_selected_type m_signal_tiles_selected;
    };
  }
}

#endif