#ifndef					__IMAGE_LOADER_HH__
# define				__IMAGE_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"ImageMedia.hpp"

class					ImageLoader : public Loader<ImageMedia>
{
public:
  ImageLoader() : Loader<ImageMedia>()
  {
    // al_set_new_bitmap_flags(ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  }

  virtual ~ImageLoader()
  {}
  virtual ImageMedia			*load(const File &file, bool force = false)
  {
    ALLEGRO_BITMAP			*bmp;
    GLuint				tex;

    bmp = al_load_bitmap(file.getFullName().c_str());
    if (!bmp)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load image.");
    // al_convert_mask_to_alpha(bmp, al_map_rgb(255, 0, 0));
    tex = al_get_opengl_texture(bmp);
    if (tex == 0)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load texture.");
    return new ImageMedia(bmp, tex, file.getFileName(), force);
  }
  virtual void				save(const ImageMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif					// __IMAGE_LOADER_HH__
