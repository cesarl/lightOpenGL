#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				"OptionManager.hpp"
#include				"Singleton.hpp"
#include				"Camera.hpp"

//static Camera<Orthographic, FlatCamera> camera;
static Camera<Perspective, FreeFly> camera;

class					EventManager : public Singleton<EventManager>
{
public:
  ~EventManager();

  void					draw(float time, const ALLEGRO_EVENT &ev)
  {
    static double			fps = 0;
    static int				frames_done = 0;
    static double			old_time = al_get_time();

    camera.update(time, ev);

    if(time - old_time >= 1.0)
      {
	fps = frames_done / (time - old_time);
	frames_done = 0;
	old_time = time;
	std::cout << "FPS : " << fps << " || TIME : " << old_time << std::endl;
      }
    frames_done++;
  }


  bool					init()
  {
    if (!al_install_keyboard())
      return false;
    if (!al_install_mouse())
      return false;
    this->event_queue_ = al_create_event_queue();
    if (!this->event_queue_)
      return false;
    this->timer_ = al_create_timer(1.0f / 120.0f);
    if (!this->timer_)
      return false;
    if (!al_install_joystick())
      return false;
    if (!camera.init())
      return false;
    al_register_event_source(this->event_queue_, al_get_keyboard_event_source());
    // al_register_event_source(this->event_queue_, al_get_joystick_event_source());
    al_register_event_source(this->event_queue_, al_get_mouse_event_source());
    al_register_event_source(this->event_queue_, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(this->event_queue_, al_get_timer_event_source(this->timer_));
    al_start_timer(this->timer_);

    return true;
  }

  void					uninit()
  {
    if (this->event_queue_)
      al_destroy_event_queue(this->event_queue_);
    if (this->timer_)
      al_destroy_timer(this->timer_);
    al_uninstall_keyboard();
    al_uninstall_mouse();
  }

  void					play()
  {
    bool				canDraw;
    ALLEGRO_EVENT			ev;
    float				time;

    this->run_->setValue(true);
    canDraw = false;
    while (this->run_->getValue())
      {
	time = al_get_time();
	al_wait_for_event(this->event_queue_, &ev);
	if (ev.type == ALLEGRO_EVENT_TIMER)
	  {
	    canDraw = true;
	  }
	if (upt_)
	  {
	    this->upt_(time, ev);
	  }
	else
	  {
	    camera.input(time, ev);
	  }
	if (canDraw && al_is_event_queue_empty(this->event_queue_))
	  {
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    if (draw_)
	      {
		this->draw_(time, ev);
	      }
	    else
	      {
		draw(time, ev);
	      }
	    al_flip_display();
	    canDraw = false;
	  }
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	  {
	    this->stop();
	  }
      }
  }
  void					stop()
  {
    this->run_->setValue(false);
  }
  void					setUpdateLoop(void (fun)(float, const ALLEGRO_EVENT &))
  {
    this->upt_ = fun;
  }

  void					setDrawLoop(void (fun)(float, const ALLEGRO_EVENT &))
  {
    this->draw_ = fun;
  }

private:
  void					(*upt_)(float, const ALLEGRO_EVENT &ev);
  void					(*draw_)(float, const ALLEGRO_EVENT &ev);
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  OptionValue<bool>			*run_;
  EventManager() :
    upt_(NULL),
    draw_(NULL),
    event_queue_(NULL),
    timer_(NULL),
    run_(NULL)
  {
    OptionManager::getInstance()->setOption<bool>("run", true);
    this->run_ = OptionManager::getInstance()->getOption<bool>("run");
  }
  friend class Singleton<EventManager>;
};

#endif					// __EVENT_MANAGER_HH__

