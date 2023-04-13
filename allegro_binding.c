// allegro_test.c
#include <SWI-Prolog.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//swipl-ld -lallegro -lallegro_main -lallegro_font -lallegro_image -lallegro_primitives -o allegro_binding -shared allegro_binding.c

static PL_blob_t event_source_ref_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "event_source_ref",
  .release = NULL,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

int destroy_timer (atom_t timer) {
  ALLEGRO_TIMER ** timer_handle = PL_blob_data(timer, NULL, NULL);
  al_destroy_timer(*timer_handle);
  return TRUE;
}
static PL_blob_t timer_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "timer",
  .release = destroy_timer,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

int destroy_event_queue(atom_t event_queue) {
  ALLEGRO_EVENT_QUEUE ** event_queue_handle = PL_blob_data(event_queue, NULL, NULL);
  al_destroy_event_queue(*event_queue_handle);
  return TRUE;
}
static PL_blob_t event_queue_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "event_queue",
  .release = destroy_event_queue,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

static PL_blob_t joystick_ref_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "joystick_reference",
  .release = NULL,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

static PL_blob_t display_ref_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "display_ref",
  .release = NULL,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

static PL_blob_t timer_ref_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "timer_ref",
  .release = NULL,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

int destroy_display(atom_t display) {
  ALLEGRO_DISPLAY ** al_disp = PL_blob_data(display, NULL, NULL);
  al_destroy_display(*al_disp);
  return TRUE;
}
static PL_blob_t display_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "display",
  .release = destroy_display,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

int destroy_font(atom_t font) {
  ALLEGRO_FONT ** al_font = PL_blob_data(font, NULL, NULL);
  al_destroy_font(*al_font);
  return TRUE;
}
static PL_blob_t font_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "font",
  .release = destroy_font,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

static PL_blob_t color_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "color",
  .release = NULL,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

int destroy_bitmap(atom_t font) {
  ALLEGRO_BITMAP ** al_bitmap = PL_blob_data(font, NULL, NULL);
  al_destroy_bitmap(*al_bitmap);
  return TRUE;
}
static PL_blob_t bitmap_blob = {
  .magic = PL_BLOB_MAGIC,
  .flags = PL_BLOB_UNIQUE,
  .name = "bitmap",
  .release = destroy_bitmap,
  .compare = NULL,
  .write = NULL,
  .acquire = NULL,
  .save = NULL,
  .load = NULL
};

bool blobterm2data (term_t term, PL_blob_t* type_we_want, void** data) {
  PL_blob_t* blob_type;
  if(PL_get_blob(term, data, NULL, &blob_type) && blob_type == type_we_want) {
    return true;
  }
  return false;
}

foreign_t al_init_wrapper () {
  if(al_install_system(ALLEGRO_VERSION_INT, NULL)){
    PL_succeed;
  } else {
    PL_fail;
  }
}

foreign_t al_install_keyboard_wrapper () {
  if(al_install_keyboard()){
    PL_succeed;
  } else {
    PL_fail;
  }
}

foreign_t al_get_keyboard_event_source_wrapper (term_t source_out){
  if(!PL_is_variable(source_out)) PL_fail;
  ALLEGRO_EVENT_SOURCE * keysource = al_get_keyboard_event_source();
  if(!PL_unify_blob(source_out, &keysource, sizeof(keysource), &event_source_ref_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_create_timer_wrapper (term_t secs_per_tick, term_t timer_out) {
  if(!PL_is_variable(timer_out)) PL_fail;
  double spt_val;
  if(!PL_get_float(secs_per_tick, &spt_val)) PL_fail;
  ALLEGRO_TIMER* timer = al_create_timer(spt_val);
  if(!PL_unify_blob(timer_out, &timer, sizeof(timer), &timer_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_start_timer_wrapper (term_t timer_in){
  ALLEGRO_TIMER** timer = NULL;
  PL_blob_t* blob_type;
  if(!(blobterm2data(timer_in, &timer_blob, (void**)&timer) || blobterm2data(timer_in, &timer_ref_blob, (void**)&timer))) PL_fail;
  al_start_timer(*timer);
  PL_succeed;
}

foreign_t al_get_timer_event_source_wrapper(term_t timer_in, term_t source_out) {
  if(!PL_is_variable(source_out)) PL_fail;
  ALLEGRO_TIMER** timer = NULL;
  if(!(blobterm2data(timer_in, &timer_blob, (void**)&timer) || blobterm2data(timer_in, &timer_ref_blob, (void**)&timer))) PL_fail;
  ALLEGRO_EVENT_SOURCE * ev_src = al_get_timer_event_source(*timer);
  if(!PL_unify_blob(source_out, &ev_src, sizeof(ev_src), &event_source_ref_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_create_event_queue_wrapper(term_t event_queue_out) {
  if(!PL_is_variable(event_queue_out)) PL_fail;
  ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
  if(!PL_unify_blob(event_queue_out, &event_queue, sizeof(event_queue), &event_queue_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_register_event_source_wrapper(term_t queue_in, term_t source_in){
  ALLEGRO_EVENT_QUEUE ** ev_q = NULL;
  ALLEGRO_EVENT_SOURCE ** ev_src = NULL;
  if(!blobterm2data(queue_in, &event_queue_blob, (void**)&ev_q)) PL_fail;
  if(!blobterm2data(source_in, &event_source_ref_blob, (void**)&ev_src)) PL_fail;
  al_register_event_source(*ev_q, *ev_src);
  PL_succeed;
}

term_t event2prologterm (ALLEGRO_EVENT * event) {
  ALLEGRO_EVENT_SOURCE * event_source = NULL;
  term_t event_out = PL_new_term_ref();
  term_t ev_t = PL_new_term_ref();
  term_t ev_src = PL_new_term_ref();
  term_t ev_ts = PL_new_term_ref();
  term_t ev_specifics = PL_new_term_ref();
  functor_t ev_functor = PL_new_functor(PL_new_atom("allegro_event"), 4);
  (void)!PL_put_uint64(ev_t, event->type);
  event_source = event->any.source;
  if(!PL_unify_blob(ev_src, &event_source, sizeof(event_source), &event_source_ref_blob)) PL_fail;
  (void)!PL_put_float(ev_ts, event->any.timestamp);
  PL_put_nil(ev_specifics);
  term_t elem = PL_new_term_ref();
  if (ALLEGRO_EVENT_TYPE_IS_USER(event->type)) {
    PL_type_error("User events are not implemented yet.", event_out);
  } else {
    switch (event->type) {
    case ALLEGRO_EVENT_JOYSTICK_AXIS :
      (void)!PL_put_float(elem, event->joystick.pos);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->joystick.axis);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->joystick.stick);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->joystick.id, sizeof(event->joystick.id), &joystick_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN :
      (void)!PL_put_int64(elem, event->joystick.button);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->joystick.id, sizeof(event->joystick.id), &joystick_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP :
      (void)!PL_put_int64(elem, event->joystick.button);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->joystick.id, sizeof(event->joystick.id), &joystick_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION :
      break;
    case ALLEGRO_EVENT_KEY_DOWN :
      (void)!PL_put_blob(elem, &event->keyboard.display, sizeof(event->keyboard.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->keyboard.keycode);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_KEY_CHAR :
      (void)!PL_put_blob(elem, &event->keyboard.display, sizeof(event->keyboard.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_bool(elem, event->keyboard.repeat);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_uint64(elem, event->keyboard.modifiers);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->keyboard.unichar);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->keyboard.keycode);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_KEY_UP :
      (void)!PL_put_blob(elem, &event->keyboard.display, sizeof(event->keyboard.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->keyboard.keycode);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_AXES :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->mouse.pressure);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dw);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dz);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->mouse.pressure);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_uint64(elem, event->mouse.button);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->mouse.pressure);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_uint64(elem, event->mouse.button);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_MOUSE_WARPED :
      (void)!PL_put_blob(elem, &event->mouse.display, sizeof(event->mouse.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->mouse.pressure);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dw);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dz);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.w);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.z);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->mouse.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_TIMER :
      (void)!PL_put_int64(elem, event->timer.count);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->timer.source, sizeof(event->timer.source), &timer_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_EXPOSE :
      (void)!PL_put_int64(elem, event->display.height);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.width);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_RESIZE :
      (void)!PL_put_int64(elem, event->display.height);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.width);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->display.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_LOST :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_FOUND :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_ORIENTATION :
      (void)!PL_put_int64(elem, event->display.orientation);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING :
      break;
    case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING :
      break;
    case ALLEGRO_EVENT_TOUCH_BEGIN :
      (void)!PL_put_bool(elem, event->touch.primary);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->touch.id);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->touch.display, sizeof(event->touch.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_TOUCH_END :
      (void)!PL_put_bool(elem, event->touch.primary);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->touch.id);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->touch.display, sizeof(event->touch.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_TOUCH_MOVE :
      (void)!PL_put_bool(elem, event->touch.primary);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->touch.id);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->touch.display, sizeof(event->touch.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_TOUCH_CANCEL :
      (void)!PL_put_bool(elem, event->touch.primary);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dy);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.dx);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.y);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_float(elem, event->touch.x);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_int64(elem, event->touch.id);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      (void)!PL_put_blob(elem, &event->touch.display, sizeof(event->touch.display), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_CONNECTED :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    case ALLEGRO_EVENT_DISPLAY_DISCONNECTED :
      (void)!PL_put_blob(elem, &event->display.source, sizeof(event->display.source), &display_ref_blob);
      (void)!PL_cons_list(ev_specifics, elem, ev_specifics);
      break;
    default :
      PL_type_error("Unrecognized event from queue: ", event_out);
    }
  }
  (void)!PL_unify_functor(event_out, ev_functor);
  (void)!PL_unify_arg(1, event_out, ev_t);
  (void)!PL_unify_arg(2, event_out, ev_src);
  (void)!PL_unify_arg(3, event_out, ev_ts);
  (void)!PL_unify_arg(4, event_out, ev_specifics);
  return event_out;
}

foreign_t al_wait_for_event_wrapper(term_t event_queue_in, term_t event_out){
  ALLEGRO_EVENT_QUEUE ** event_queue = NULL;
  ALLEGRO_EVENT event;
  if(!blobterm2data(event_queue_in, &event_queue_blob, (void**)&event_queue)) PL_fail;
  al_wait_for_event(*event_queue, &event);
  if(!PL_unify(event_out, event2prologterm(&event))) PL_fail;
  PL_succeed;
}

foreign_t al_get_next_event_wrapper(term_t queue_in, term_t event_out) {
  ALLEGRO_EVENT_QUEUE ** event_queue = NULL;
  ALLEGRO_EVENT_SOURCE * event_source = NULL;
  ALLEGRO_EVENT * event = NULL;
  if(!blobterm2data(queue_in, &event_queue_blob, (void**)&event_queue)) PL_fail;
  if(!al_get_next_event(*event_queue, event)) PL_fail;
  if(!PL_unify(event_out, event2prologterm(event))) PL_fail;
  PL_succeed;
}

foreign_t al_is_event_queue_empty_wrapper (term_t queue_in, term_t isEmpty) {
  ALLEGRO_EVENT_QUEUE ** event_queue = NULL;
  if(!blobterm2data(queue_in, &event_queue_blob, (void**)&event_queue)) PL_fail;
  if(!PL_unify_bool(isEmpty, al_is_event_queue_empty(*event_queue))) PL_fail;
  PL_succeed;
}

foreign_t al_create_display_wrapper(term_t w_in, term_t h_in, term_t display_out) {
  if(!PL_is_variable(display_out)) PL_fail;
  int w;
  if(!PL_get_integer(w_in, &w)) PL_fail;
  int h;
  if(!PL_get_integer(h_in, &h)) PL_fail;
  ALLEGRO_DISPLAY * disp = al_create_display(w, h);
  return PL_unify_blob(display_out, &disp, sizeof(disp), &display_blob);
}

foreign_t al_get_display_event_source_wrapper(term_t display_in, term_t source_out) {
  if(!PL_is_variable(source_out)) PL_fail;
  ALLEGRO_DISPLAY ** disp = NULL;
  if(!blobterm2data(display_in, &display_blob, (void**)&disp)) PL_fail;
  ALLEGRO_EVENT_SOURCE * event_source = al_get_display_event_source(*disp);
  if(!PL_unify_blob(source_out, &event_source, sizeof(event_source), &event_source_ref_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_flip_display_wrapper() {
  al_flip_display();
  PL_succeed;
}

foreign_t al_create_builtin_font_wrapper(term_t font_out) {
  if(!PL_is_variable(font_out)) PL_fail;
  ALLEGRO_FONT * font = al_create_builtin_font();
  PL_unify_blob(font_out, &font, sizeof(font), &font_blob);
  PL_succeed;
}

foreign_t al_draw_text_wrapper(term_t font_in, term_t color_in, term_t x_in, term_t y_in, term_t flags_in, term_t text_in) {
  ALLEGRO_FONT ** al_font = NULL;
  if(!blobterm2data(font_in, &font_blob, (void**)&al_font)) PL_fail;
  ALLEGRO_COLOR* al_color = NULL;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  double x;
  if(!PL_get_float(x_in, &x)) PL_fail;
  double y;
  if(!PL_get_float(y_in, &y)) PL_fail;
  int al_flags;
  if(!PL_get_integer(flags_in, &al_flags)) PL_fail;
  char * text = NULL;
  if(!PL_get_atom_chars(text_in, &text)) PL_fail;
  al_draw_text(*al_font, *al_color, x, y, al_flags, text);
  PL_succeed;
}

foreign_t al_clear_to_color_wrapper(term_t color_in) {
  ALLEGRO_COLOR* al_color;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  al_clear_to_color(*al_color);
  PL_succeed;
}

foreign_t al_map_rgb_wrapper(term_t r_in, term_t g_in, term_t b_in, term_t color_out) {
  if(!PL_is_variable(color_out)) PL_fail;
  int r;
  if(!PL_get_integer(r_in, &r)) PL_fail;
  int g;
  if(!PL_get_integer(g_in, &g)) PL_fail;
  int b;
  if(!PL_get_integer(b_in, &b)) PL_fail;
  ALLEGRO_COLOR color;
  color = al_map_rgb(r, g, b);
  if(!PL_unify_blob(color_out, &color, sizeof(color), &color_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_init_image_addon_wrapper () {
  if(!al_init_image_addon()) PL_fail;
  PL_succeed;
}

foreign_t al_load_bitmap_wrapper (term_t filename, term_t bitmap_out) {
  if(!PL_is_variable(bitmap_out)) PL_fail;
  char * text = NULL;
  if(!PL_get_atom_chars(filename, &text)) PL_fail;
  ALLEGRO_BITMAP * bitmap = al_load_bitmap(text);
  if(!PL_unify_blob(bitmap_out, &bitmap, sizeof(bitmap), &bitmap_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_draw_bitmap_wrapper(term_t bitmap_in, term_t dx_in, term_t dy_in, term_t flags_in) {
  ALLEGRO_BITMAP** bitmap = NULL;
  if(!blobterm2data(bitmap_in, &bitmap_blob, (void**)&bitmap)) PL_fail;
  double dx;
  if(!PL_get_float(dx_in, &dx)) PL_fail;
  double dy;
  if(!PL_get_float(dy_in, &dy)) PL_fail;
  int flags;
  if(!PL_get_integer(flags_in, &flags)) PL_fail;
  al_draw_bitmap(*bitmap, dx, dy, flags);
  PL_succeed;
}

foreign_t al_init_primitives_addon_wrapper () {
  if(!al_init_primitives_addon()) PL_fail;
  PL_succeed;
}

foreign_t al_draw_filled_triangle_wrapper (term_t x1_in, term_t y1_in, term_t x2_in, term_t y2_in, term_t x3_in, term_t y3_in, term_t color_in) {
  double x1;
  if(!PL_get_float(x1_in, &x1)) PL_fail;
  double y1;
  if(!PL_get_float(y1_in, &y1)) PL_fail;
  double x2;
  if(!PL_get_float(x2_in, &x2)) PL_fail;
  double y2;
  if(!PL_get_float(y2_in, &y2)) PL_fail;
  double x3;
  if(!PL_get_float(x3_in, &x3)) PL_fail;
  double y3;
  if(!PL_get_float(y3_in, &y3)) PL_fail;
  ALLEGRO_COLOR* al_color;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, *al_color);
  PL_succeed;
}

foreign_t al_draw_filled_rectangle_wrapper (term_t x1_in, term_t y1_in, term_t x2_in, term_t y2_in, term_t color_in) {
  double x1;
  if(!PL_get_float(x1_in, &x1)) PL_fail;
  double y1;
  if(!PL_get_float(y1_in, &y1)) PL_fail;
  double x2;
  if(!PL_get_float(x2_in, &x2)) PL_fail;
  double y2;
  if(!PL_get_float(y2_in, &y2)) PL_fail;
  ALLEGRO_COLOR* al_color;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  al_draw_filled_rectangle(x1, y1, x2, y2, *al_color);
  PL_succeed;
}

foreign_t al_draw_circle_wrapper (term_t cx_in, term_t cy_in, term_t r_in, term_t color_in, term_t thickness_in) {
  double cx;
  if(!PL_get_float(cx_in, &cx)) PL_fail;
  double cy;
  if(!PL_get_float(cy_in, &cy)) PL_fail;
  double r;
  if(!PL_get_float(r_in, &r)) PL_fail;
  ALLEGRO_COLOR* al_color;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  double thickness;
  if(!PL_get_float(thickness_in, &thickness)) PL_fail;
  al_draw_circle(cx, cy, r, *al_color, thickness);
  PL_succeed;
}

foreign_t al_draw_line_wrapper (term_t x1_in, term_t y1_in, term_t x2_in, term_t y2_in, term_t color_in, term_t thickness_in) {
  double x1;
  if(!PL_get_float(x1_in, &x1)) PL_fail;
  double y1;
  if(!PL_get_float(y1_in, &y1)) PL_fail;
  double x2;
  if(!PL_get_float(x2_in, &x2)) PL_fail;
  double y2;
  if(!PL_get_float(y2_in, &y2)) PL_fail;
  ALLEGRO_COLOR* al_color;
  if(!blobterm2data(color_in, &color_blob, (void**)&al_color)) PL_fail;
  double thickness;
  if(!PL_get_float(thickness_in, &thickness)) PL_fail;
  al_draw_line(x1, y1, x2, y2, *al_color, thickness);
  PL_succeed;
}

foreign_t al_map_rgb_f_wrapper (term_t r_in, term_t g_in, term_t b_in, term_t color_out) {
  double r;
  if(!PL_get_float(r_in, &r)) PL_fail;
  double g;
  if(!PL_get_float(g_in, &g)) PL_fail;
  double b;
  if(!PL_get_float(b_in, &b)) PL_fail;
  ALLEGRO_COLOR color = al_map_rgb_f(r, g, b);
  if(!PL_unify_blob(color_out, &color, sizeof(color), &color_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_map_rgba_f_wrapper (term_t r_in, term_t g_in, term_t b_in, term_t a_in, term_t color_out) {
  double r;
  if(!PL_get_float(r_in, &r)) PL_fail;
  double g;
  if(!PL_get_float(g_in, &g)) PL_fail;
  double b;
  if(!PL_get_float(b_in, &b)) PL_fail;
  double a;
  if(!PL_get_float(a_in, &a)) PL_fail;
  ALLEGRO_COLOR color = al_map_rgba_f(r, g, b, a);
  if(!PL_unify_blob(color_out, &color, sizeof(color), &color_blob)) PL_fail;
  PL_succeed;
}

foreign_t al_set_new_display_option_wrapper (term_t option_in, term_t value_in, term_t importance_in) {
  int option;
  if(!PL_get_integer(option_in, &option)) PL_fail;
  int value;
  if(!PL_get_integer(value_in, &value)) PL_fail;
  int importance;
  if(!PL_get_integer(importance_in, &importance)) PL_fail;
  al_set_new_display_option(option, value, importance);
  PL_succeed;
}

foreign_t al_set_new_bitmap_flags_wrapper (term_t flags_in) {
  int flags;
  if(!PL_get_integer(flags_in, &flags)) PL_fail;
  al_set_new_bitmap_flags(flags);
  PL_succeed;
}

foreign_t al_draw_prim_wrapper (term_t vtxs_in, term_t decl_in, term_t texture_in, term_t start_in, term_t end_in, term_t type_in) {
  PL_type_error("The 'al_draw_prim()' function is not implemented yet.", vtxs_in);
  int start;
  if(!PL_get_integer(start_in, &start)) PL_fail;
  int end;
  if(!PL_get_integer(end_in, &end)) PL_fail;
  int type;
  if(!PL_get_integer(type_in, &type)) PL_fail;
  PL_succeed;
}

foreign_t al_set_blender_wrapper (term_t op_in, term_t src_in, term_t dst_in) {
  int op;
  if(!PL_get_integer(op_in, &op)) PL_fail;
  int src;
  if(!PL_get_integer(src_in, &src)) PL_fail;
  int dst;
  if(!PL_get_integer(dst_in, &dst)) PL_fail;
  al_set_blender(op, src, dst);
  PL_succeed;
}

foreign_t al_get_mouse_event_source_wrapper (term_t source_out) {
  ALLEGRO_EVENT_SOURCE * event_source = al_get_mouse_event_source();
  if(!PL_unify_blob(source_out, &event_source, sizeof(event_source), &event_source_ref_blob)) PL_fail;
  PL_succeed;
}

install_t install_allegro_binding () {
  PL_register_foreign("al_init", 0, al_init_wrapper, 0);
  PL_register_foreign("al_install_keyboard", 0, al_install_keyboard_wrapper, 0);
  PL_register_foreign("al_get_keyboard_event_source", 1, al_get_keyboard_event_source_wrapper, 0);
  PL_register_foreign("al_create_timer", 2, al_create_timer_wrapper, 0);
  PL_register_foreign("al_start_timer", 1, al_start_timer_wrapper, 0);
  PL_register_foreign("al_get_timer_event_source", 2, al_get_timer_event_source_wrapper, 0);
  PL_register_foreign("al_create_event_queue", 1, al_create_event_queue_wrapper, 0);
  PL_register_foreign("al_register_event_source", 2, al_register_event_source_wrapper, 0);
  PL_register_foreign("al_wait_for_event", 2, al_wait_for_event_wrapper, 0);
  PL_register_foreign("al_get_next_event", 2, al_get_next_event_wrapper, 0);
  PL_register_foreign("al_is_event_queue_empty", 2, al_is_event_queue_empty_wrapper, 0);
  PL_register_foreign("al_create_display", 3, al_create_display_wrapper, 0);
  PL_register_foreign("al_get_display_event_source", 2, al_get_display_event_source_wrapper, 0);
  PL_register_foreign("al_flip_display", 0, al_flip_display_wrapper, 0);
  PL_register_foreign("al_create_builtin_font", 1, al_create_builtin_font_wrapper, 0);
  PL_register_foreign("al_draw_text", 6, al_draw_text_wrapper, 0);
  PL_register_foreign("al_clear_to_color", 1, al_clear_to_color_wrapper, 0);
  PL_register_foreign("al_map_rgb", 4, al_map_rgb_wrapper, 0);
  PL_register_foreign("al_init_image_addon", 0, al_init_image_addon_wrapper, 0);
  PL_register_foreign("al_load_bitmap", 2, al_load_bitmap_wrapper, 0);
  PL_register_foreign("al_draw_bitmap", 4, al_draw_bitmap_wrapper, 0);
  PL_register_foreign("al_init_primitives_addon", 0, al_init_primitives_addon_wrapper, 0);
  PL_register_foreign("al_draw_filled_triangle", 7, al_draw_filled_triangle_wrapper, 0);
  PL_register_foreign("al_draw_filled_rectangle", 5, al_draw_filled_rectangle_wrapper, 0);
  PL_register_foreign("al_draw_circle", 5, al_draw_circle_wrapper, 0);
  PL_register_foreign("al_draw_line", 6, al_draw_line_wrapper, 0);
  PL_register_foreign("al_map_rgb_f", 4, al_map_rgb_f_wrapper, 0);
  PL_register_foreign("al_map_rgba_f", 5, al_map_rgba_f_wrapper, 0);
  PL_register_foreign("al_set_new_display_option", 3, al_set_new_display_option_wrapper, 0);
  PL_register_foreign("al_set_new_bitmap_flags", 1, al_set_new_bitmap_flags_wrapper, 0);
  PL_register_foreign("al_draw_prim", 6, al_draw_prim_wrapper, 0);
  PL_register_foreign("al_set_blender", 3, al_set_blender_wrapper, 0);
  PL_register_foreign("al_get_mouse_event_source", 1, al_get_mouse_event_source_wrapper, 0);
}
