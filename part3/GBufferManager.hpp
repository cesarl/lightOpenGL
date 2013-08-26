#ifndef				__GBUFFER_MANAGER_HPP__
# define			__GBUFFER_MANAGER_HPP__

#include			<allegro5/allegro.h>
#include			<allegro5/allegro_opengl.h>
#include			"Singleton.hpp"

class				GBufferManager : public Singleton<GBufferManager>
{
public:
  enum				GB_TEXTURE_TYPE
    {
      GB_TEXTURE_TYPE_POSITION = 0,
      GB_TEXTURE_TYPE_DIFFUSE = 1,
      GB_TEXTURE_TYPE_NORMAL = 2,
      GB_TEXTURE_TYPE_TEXCOORD = 3,
      GB_TEXTURE_TYPE_NUMBER = 4
    };

  virtual ~GBufferManager()
  {
    uninit();
  }

  void				uninit()
  {
    if (fbo_ != 0)
      glDeleteFramebuffers(1, &fbo_);
    if (textures_[0] != 0)
      glDeleteTextures(GB_TEXTURE_TYPE_NUMBER, textures_);
    if (depthTexture_ != 0)
      glDeleteTextures(1, &depthTexture_);
  }

  bool				init(unsigned int width, unsigned int height)
  {
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);

    glGenTextures(GB_TEXTURE_TYPE_NUMBER, textures_);
    glGenTextures(1, &depthTexture_);

    for (unsigned int i = 0; i < GB_TEXTURE_TYPE_NUMBER; ++i)
      {
	glBindTexture(GL_TEXTURE_2D, textures_[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures_[i], 0);
      }

    glBindTexture(GL_TEXTURE_2D, depthTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture_, 0);
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, drawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
      {
	std::cerr << "Framebuffer error : " << status << std::endl;
	// todo : TROW AN EXCEPTION
	return false;
      }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    return true;
  }

  void				bindForWriting()
  {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
  }

  void				bindForReading()
  {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_);
  }

  void				setReadBuffer(GB_TEXTURE_TYPE type)
  {
    glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
  }

private:
  GLuint			fbo_;
  GLuint			textures_[GB_TEXTURE_TYPE_NUMBER];
  GLuint			depthTexture_;
};

#endif				// __GBUFFER_MANAGER_HPP__
