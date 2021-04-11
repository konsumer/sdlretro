#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>

extern "C" {
struct retro_hw_render_callback;
}

namespace drivers {

class video_base {
public:
    virtual ~video_base() = default;

    virtual int get_renderer_type() { return 0; }
    virtual bool init_hw_renderer(retro_hw_render_callback*) { return false; }
    virtual void inited_hw_renderer() {}
    virtual void deinit_hw_renderer() {}

    virtual void window_resized(int width, int height, bool fullscreen) = 0;

    /* pixel_format follows libretro: RGB1555=0 XRGB8888=1 RGB565=2 */
    virtual bool game_resolution_changed(int width, int height, int max_width, int max_height, uint32_t pixel_format) = 0;
    virtual void render(const void *data, int width, int height, size_t pitch) = 0;
    virtual void frame_render() = 0;

    virtual void gui_popup() {}
    virtual void gui_leave() {}
    virtual void gui_predraw() {}
    virtual void config_changed() {}

    virtual void *get_framebuffer(uint32_t *width, uint32_t *height, size_t *pitch, int *format)
    { return nullptr; }
    virtual bool frame_drawn() = 0;
    virtual void get_resolution(int &width, int &height) {}

    virtual int get_font_size() const { return 0; }
    virtual void set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { }
    virtual void draw_rectangle(int x, int y, int w, int h) {}
    virtual void fill_rectangle(int x, int y, int w, int h) {}
    /* width: 0=fullscreen -1=fullscreen allow wrap
     *        others: negative = allow wrap */
    virtual void draw_text(int x, int y, const char *text, int width, bool shadow) {}
    virtual void get_text_width_and_height(const char *text, int &w, int &t, int &b) const { }

    virtual void clear() {}
    virtual void flip() {}

    void add_message(const char *text, uint32_t frames);
    void message_frame_pass();
    inline void set_skip_frame() { skip_frame = true; }
    inline void set_aspect_ratio(float ratio) { aspect_ratio = ratio; }

protected:
    bool skip_frame = false;
    std::vector<std::pair<std::string, uint32_t>> messages;
    float aspect_ratio = 0.f;
};

}
