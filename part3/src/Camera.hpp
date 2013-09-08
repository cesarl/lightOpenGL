#ifndef					__CAMERA_HPP__
# define				__CAMERA_HPP__

#include				<glm/glm.hpp>
#include				<glm/gtc/type_ptr.hpp>
#include				<glm/gtc/matrix_transform.hpp>
#include                                <allegro5/allegro.h>
#include				<GL/glu.h>
#include				<cmath>

class					Camera
{
private:
  glm::mat4				projection_;
  glm::mat4				view_;
  glm::vec3				position_;
  float					horizontalAngle_;
  float					verticalAngle_;
  float					fov_;
  float					speed_;
  glm::mat4				mvp_;
public:
  Camera()
  {
    position_ = glm::vec3(0,0,5);
    horizontalAngle_ = 3.14f;
    verticalAngle_ = 0.0f;
    fov_ = 45.0f;
    speed_ = 0.01f;
  }

  ~Camera()
  {}

  void					update(float time, const ALLEGRO_EVENT &ev)
  {
    glm::vec2				pos;
    static glm::vec2			last = glm::vec2(0,0);
    ALLEGRO_MOUSE_STATE			state;

    al_get_mouse_state(&state);
    pos = glm::vec2(state.x, state.y);
    last -= pos;
    horizontalAngle_ = speed_ * pos.x;
    verticalAngle_ = speed_ * pos.y;
    glm::vec3 direction(cos(verticalAngle_) * sin(horizontalAngle_),
			sin(verticalAngle_),
			cos(verticalAngle_) * cos(horizontalAngle_));
    glm::vec3 right = glm::vec3(sin(horizontalAngle_ - 3.14f / 2.0f),
				0,
				cos(horizontalAngle_ - 3.14f / 2.0f));

    glm::vec3 up = glm::cross(right, direction);

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_W)
      {
	position_ += direction * time * speed_;
      }
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_S)
      {
	position_ -= direction * time * speed_;
      }
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D)
      {
	position_ += right * time * speed_;
      }
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_A)
      {
	position_ -= right * time * speed_;
      }

    projection_ = glm::perspective(fov_, 4.0f / 3.0f, 0.1f, 100.0f);
    view_ = glm::lookAt(position_, position_ + direction, -up);
    mvp_ = projection_ * view_;
    last = pos;
  }

  glm::mat4				&getMvp()
  {
    return mvp_;
  }

  
};

// class					FlatCamera
// {
// public:
//   explicit				FlatCamera() throw() :
//     position_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     rotation_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     speed_(30.0f)
//   {}

//   virtual ~FlatCamera()
//   {}

//   inline bool				initBehavior() throw()
//   {
//     return true;
//   }

//   inline void				updateBehavior(float, const ALLEGRO_EVENT &) throw()
//   {
//     glRotatef(this->rotation_.x, 1.0f, 0.0f, 0.0f);
//     glRotatef(this->rotation_.y, 0.0f, 1.0f, 0.0f);
//     glRotatef(this->rotation_.z, 0.0f, 0.0f, 1.0f);
//     glTranslatef(-this->position_.x, -this->position_.y, -this->position_.z);
//   }

//   inline void				inputBehavior(float time, const ALLEGRO_EVENT &ev) throw()
//   {
//     // static float			lastTime = -1;
//     // ALLEGRO_KEYBOARD_STATE		k;
//     // float				speed;
//     // glm::vec3				direction;
//     // glm::vec3				angle;

//     // al_get_keyboard_state(&k);

//     // if (lastTime == -1)
//     //   lastTime = al_get_time();
//     // speed = (time - lastTime) * this->speed_;

//     // direction = glm::vec3(0,0,0);
//     // angle = glm::vec3(0,0,0);

//     // if (al_key_down(&k, ALLEGRO_KEY_W))
//     //   {
//     // 	direction += glm::vec3(0, 1, 0);// * glm::vec3(speed, speed, speed);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_S))
//     //   {
//     // 	direction -= glm::vec3(0, 1, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_A))
//     //   {
//     // 	direction += glm::vec3(1, 0, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_D))
//     //   {
//     // 	direction -= glm::vec3(1, 0, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_Q))
//     //   {
//     // 	angle -= glm::vec3(0, 1, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_E))
//     //   {
//     // 	angle += glm::vec3(0, 1, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_Z))
//     //   {
//     // 	angle -= glm::vec3(1, 0, 0);
//     //   }
//     // if (al_key_down(&k, ALLEGRO_KEY_X))
//     //   {
//     // 	angle += glm::vec3(1, 0, 0);
//     //   }

//     // angle *= speed;
//     // direction *= speed;
//     // this->rotation_ += angle;
//     // this->position_ += direction;

//     // lastTime = time;
//     (void)ev;
//     (void)time;
//   }

//   inline const glm::vec3			&getPosition() const throw()
//   {
//     return this->position_;
//   }

//   inline const glm::vec3			&getRotation() const throw()
//   {
//     return this->rotation_;
//   }
// private:
//   glm::vec3				position_;
//   glm::vec3				rotation_;
//   float					speed_;
// };

// class					FreeFly
// {
// public:
//   explicit				FreeFly() throw() :
//     position_(glm::vec3(0.0f, 0.0f, 200.0f)),
//     forward_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     focus_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     theta_(0.0f),
//     phi_(0.0f),
//     sensitivity_(1.0f),
//     speed_(80.0f)
//   {}

//   virtual ~FreeFly()
//   {}

//   inline bool				initBehavior() throw()
//   {
//     ALLEGRO_DISPLAY			*d;
//     glm::vec3				pos;
//     glm::vec3				center;

//     d = al_get_current_display();
//     if (!d)
//       return false;
//     center = glm::vec3(al_get_display_width(d) / 2.0f, al_get_display_height(d) / 2.0f, 0.0f);
//     // al_set_mouse_xy(d, center.x, center.y);
//     // al_grab_mouse(d);

//     this->focus_ = center;

//     this->theta_ = 0.0f;
//     this->phi_ = 0.0f;
//     this->updateVectors();
//     return true;
//   }

//   inline void				updateBehavior(float, const ALLEGRO_EVENT &) throw()

//   {
//     ALLEGRO_MOUSE_STATE			state;
//     glm::vec3				pos;

//     al_get_mouse_state(&state);
//     pos = glm::vec3(state.x, state.y, 0.0f);
//     this->focus_ -= pos;

//     this->theta_ -= (float)this->focus_.x * this->sensitivity_;
//     this->phi_ -= (float)this->focus_.y * this->sensitivity_;

//     this->focus_ = pos;

//     this->updateVectors();

//     glRotatef(this->phi_, 1.0f, 0.0f, 0.0f);
//     glRotatef(this->theta_, 0.0f, 1.0f, 0.0f);
//     glTranslatef(-this->position_.x, -this->position_.y, -this->position_.z);
//     this->rotation_ = glm::vec3(this->phi_, this->theta_, 0.0f);
//   }

//   inline glm::mat4			&getMvp()
//   {
//     static glm::mat4			map;
//     float				m[16];

//     glGetFloatv(GL_MODELVIEW_MATRIX, m);
//     map = glm::make_mat4(m);
//     glGetFloatv(GL_PROJECTION_MATRIX, m);
//     map *= glm::make_mat4(m);
//     return map;
//   }

//   inline void				inputBehavior(float time, const ALLEGRO_EVENT &ev)
//   {
//     static float			lastTime = -1;
//     ALLEGRO_KEYBOARD_STATE		k;

//     al_get_keyboard_state(&k);

//     if (lastTime == -1)
//       lastTime = al_get_time();
//     float speed = (time - lastTime) * this->speed_;

//     if (al_key_down(&k, ALLEGRO_KEY_W))
//       {
// 	this->position_ += this->forward_ * glm::vec3(speed, speed, speed);
//       }
//     if (al_key_down(&k, ALLEGRO_KEY_S))
//       {
// 	this->position_ -= this->forward_ * glm::vec3(speed, speed, speed);
//       }
//     if (al_key_down(&k, ALLEGRO_KEY_A))
//       {
// 	glm::vec3 up(0.0f, 1.0f, 0.0f);
// 	glm::vec3 left = glm::cross(up, forward_);
// 	this->position_ += glm::normalize(left);
//       }
//     if (al_key_down(&k, ALLEGRO_KEY_D))
//       {
// 	glm::vec3 up(0.0f, 1.0f, 0.0f);
// 	glm::vec3 left = glm::cross(up, forward_);
// 	this->position_ -= glm::normalize(left);
//       }
//     if (al_key_down(&k, ALLEGRO_KEY_Q))
//       {
// 	this->position_ += glm::vec3(0.0f, speed / 20.0f, 0.0f);
//       }
//     if (al_key_down(&k, ALLEGRO_KEY_E))
//       {
// 	this->position_ -= glm::vec3(0.0f, speed / 20.0f, 0.0f);
//       }

//     lastTime = time;
//     (void)ev;
//     (void)time;
//   }

//   inline const glm::vec3			&getPosition() const throw()
//   {
//     return this->position_;
//   }

//   inline const glm::vec3			&getRotation() const throw()
//   {
//     return this->rotation_;
//   }


// private:
//   void					updateVectors()
//   {
//     if (this->phi_ > 89.0)
//       {
// 	this->phi_ = 89.0;
//       }
//     else if (this->phi_ < -89.0)
//       {
// 	this->phi_ = -89.0;
//       }

//     if (this->theta_ > 360.0)
//       {
// 	this->theta_ = 0.0;
//       }
//     else if (this->theta_ < 0.0)
//       {
// 	this->theta_ = 360.0;
//       }

//     double				r;

//     r = cos(this->phi_ * M_PI / 180.0f);
//     this->forward_.x = r * sin(this->theta_ * M_PI / 180.0f);
//     this->forward_.y = sin(this->phi_ * M_PI / 180.0f * -1.0f);
//     this->forward_.z = r * cos(this->theta_ * M_PI / 180.0f) * -1.0f * cos(this->phi_ * M_PI / 180.0f);
//   }
// private:
//   glm::vec3				position_;
//   glm::vec3				forward_;
//   glm::vec3				focus_;
//   double				theta_;
//   double				phi_;
//   float					sensitivity_;
//   float					speed_;
//   glm::vec3				rotation_;
// };

// class					Perspective
// {
// public:
//   explicit Perspective() throw() :
//     center_(glm::vec3(0.0f, 0.0f, 0.0f))
//   {}

//   virtual ~Perspective()
//   {}

//   inline bool				initRender() throw()
//   {
//     ALLEGRO_DISPLAY			*d;
//     glm::vec3				pos;

//     d = al_get_current_display();
//     if (!d)
//       return false;
//     this->center_ = glm::vec3(al_get_display_width(d) / 2.0f, al_get_display_height(d) / 2.0f, 0.0f);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(60.0, (double)((this->center_.x * 2.0f) / (this->center_.y * 2.0f)), 1.0, 1000.0);
//     return true;
//   }

//   inline void				updateRender(float, const ALLEGRO_EVENT &) throw()
//   {
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//   }

//   inline void				inputRender(float, const ALLEGRO_EVENT &) throw()
//   {}

// private:
//   glm::vec3				center_;
// };

// class					Orthographic
// {
// public:
//   explicit Orthographic() throw() :
//     min_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     max_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     size_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     center_(glm::vec3(0.0f, 0.0f, 0.0f)),
//     zoom_(1.0f)
//   {}

//   virtual ~Orthographic()
//   {}

//   inline bool				initRender() throw()
//   {
//     ALLEGRO_DISPLAY			*d;
//     glm::vec3				pos;

//     d = al_get_current_display();
//     if (!d)
//       return false;
//     this->size_ = glm::vec3(al_get_display_width(d), al_get_display_height(d), 0.0f);
//     this->center_ = glm::vec3(this->size_.x / 2.0f, this->size_.y / 2.0f, 0.0f);
//     this->max_ = this->min_;
//     this->max_ += this->size_;

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glViewport(0, 0, this->size_.x * this->zoom_, this->size_.y * this->zoom_);
//     glOrtho(0 * this->zoom_,
// 	    this->size_.x,
// 	    0 *this->zoom_,
// 	    this->size_.y,
// 	    -10000,
// 	    10000);
//     glMatrixMode(GL_MODELVIEW);
//     return true;
//   }

//   inline void				updateRender(float, const ALLEGRO_EVENT &) throw()
//   {
//     glMatrixMode(GL_PROJECTION);
//     glViewport(0, 0, this->size_.x * this->zoom_, this->size_.y * this->zoom_);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//   }

//   inline void				inputRender(float, const ALLEGRO_EVENT &) throw()
//   {
//     // this->zoom_ += 0.003f;
//     // std::cout << this->zoom_ << std::endl;
//   }

// private:
//   glm::vec3				min_;
//   glm::vec3				max_;
//   glm::vec3				size_;
//   glm::vec3				center_;
//   float					zoom_;
// };


// template				<class CameraRender, class CameraBehavior>
// class					Camera : public CameraRender, public CameraBehavior
// {
// public:
//   Camera()
//   {
//   }

//   virtual ~Camera()
//   {}

//   bool					init()
//   {
//     if (!this->initRender())
//       return false;
//     return this->initBehavior();
//   }

//   void					update(float time, const ALLEGRO_EVENT &ev)
//   {
//     this->updateRender(time, ev);
//     this->updateBehavior(time, ev);
//   }

//   void					updateEnd()
//   {
//   }

//   void					input(float time, const ALLEGRO_EVENT &ev)
//   {
//     this->inputRender(time, ev);
//     this->inputBehavior(time, ev);
//     (void)ev;
//     (void)time;
//   }
// };

#endif					// __CAMMERA_HPP__



