:- load_foreign_library(allegro_binding).
:- al_init.
:- al_install_keyboard.
:- al_init_image_addon.
:- al_init_primitives_addon.

allegro_event_type('ALLEGRO_EVENT_JOYSTICK_AXIS', 1).
allegro_event_type('ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN', 2).
allegro_event_type('ALLEGRO_EVENT_JOYSTICK_BUTTON_UP', 3).
allegro_event_type('ALLEGRO_EVENT_JOYSTICK_CONFIGURATION', 4).

allegro_event_type('ALLEGRO_EVENT_KEY_DOWN', 10).
allegro_event_type('ALLEGRO_EVENT_KEY_CHAR', 11).
allegro_event_type('ALLEGRO_EVENT_KEY_UP', 12).

allegro_event_type('ALLEGRO_EVENT_MOUSE_AXES', 20).
allegro_event_type('ALLEGRO_EVENT_MOUSE_BUTTON_DOWN', 21).
allegro_event_type('ALLEGRO_EVENT_MOUSE_BUTTON_UP', 22).
allegro_event_type('ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY', 23).
allegro_event_type('ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY', 24).
allegro_event_type('ALLEGRO_EVENT_MOUSE_WARPED', 25).

allegro_event_type('ALLEGRO_EVENT_TIMER', 30).

allegro_event_type('ALLEGRO_EVENT_DISPLAY_EXPOSE', 40).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_RESIZE', 41).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_CLOSE', 42).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_LOST', 43).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_FOUND', 44).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_SWITCH_IN', 45).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_SWITCH_OUT', 46).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_ORIENTATION', 47).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_HALT_DRAWING', 48).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING', 49).

allegro_event_type('ALLEGRO_EVENT_TOUCH_BEGIN', 50).
allegro_event_type('ALLEGRO_EVENT_TOUCH_END', 51).
allegro_event_type('ALLEGRO_EVENT_TOUCH_MOVE', 52).
allegro_event_type('ALLEGRO_EVENT_TOUCH_CANCEL', 53).

allegro_event_type('ALLEGRO_EVENT_DISPLAY_CONNECTED', 60).
allegro_event_type('ALLEGRO_EVENT_DISPLAY_DISCONNECTED', 61).
