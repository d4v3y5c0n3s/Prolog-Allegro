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

allegro_key(a,1).
allegro_key(b,2).
allegro_key(c,3).
allegro_key(d,4).
allegro_key(e,5).
allegro_key(f,6).
allegro_key(g,7).
allegro_key(h,8).
allegro_key(i,9).
allegro_key(j,10).
allegro_key(k,11).
allegro_key(l,12).
allegro_key(m,13).
allegro_key(n,14).
allegro_key(o,15).
allegro_key(p,16).
allegro_key(q,17).
allegro_key(r,18).
allegro_key(s,19).
allegro_key(t,20).
allegro_key(u,21).
allegro_key(v,22).
allegro_key(w,23).
allegro_key(x,24).
allegro_key(y,25).
allegro_key(z,26).

allegro_key(0,27).
allegro_key(1,28).
allegro_key(2,29).
allegro_key(3,30).
allegro_key(4,31).
allegro_key(5,32).
allegro_key(6,33).
allegro_key(7,34).
allegro_key(8,35).
allegro_key(9,36).

allegro_key(pad_0,37).
allegro_key(pad_1,38).
allegro_key(pad_2,39).
allegro_key(pad_3,40).
allegro_key(pad_4,41).
allegro_key(pad_5,42).
allegro_key(pad_6,43).
allegro_key(pad_7,44).
allegro_key(pad_8,45).
allegro_key(pad_9,46).

allegro_key(f1,47).
allegro_key(f2,48).
allegro_key(f3,49).
allegro_key(f4,50).
allegro_key(f5,51).
allegro_key(f6,52).
allegro_key(f7,53).
allegro_key(f8,54).
allegro_key(f9,55).
allegro_key(f10,56).
allegro_key(f11,57).
allegro_key(f12,58).

allegro_key(escape,59).
allegro_key(tilde,60).
allegro_key(minus,61).
allegro_key(equals,62).
allegro_key(backspace,63).
allegro_key(tab,64).
allegro_key(openbrace,65).
allegro_key(closebrace,66).
allegro_key(enter,67).
allegro_key(semicolon,68).
allegro_key(quote,69).
allegro_key(backslash,70).
allegro_key(backslash2,71).%uk/germany keyboards
allegro_key(comma,72).
allegro_key(fullstop,73).
allegro_key(slash,74).
allegro_key(space,75).

allegro_key(insert,76).
allegro_key(delete,77).
allegro_key(home,78).
allegro_key(end,79).
allegro_key(pgup,80).
allegro_key(pgdn,81).
allegro_key(left,82).
allegro_key(right,83).
allegro_key(up,84).
allegro_key(down,85).

allegro_key(pad_slash,86).
allegro_key(pad_asterisk,87).
allegro_key(pad_minus,88).
allegro_key(pad_plus,89).
allegro_key(pad_delete,90).
allegro_key(pad_enter,91).

allegro_key(printscreen,92).
allegro_key(pause,93).

allegro_key(abnt_c1,94).
allegro_key(yen,95).
allegro_key(kana,96).
allegro_key(convert,97).
allegro_key(noconvert,98).
allegro_key(at,99).
allegro_key(circumflex,100).
allegro_key(colon2,101).
allegro_key(kanji,102).

allegro_key(pad_equals,103).%macosx
allegro_key(backquote,104).%macosx
allegro_key(semicolon2,105).%macosx
allegro_key(command,106).%macosx

allegro_key(back,107).%androidbackkey
allegro_key(volume_up,108).
allegro_key(volume_down,109).

%androidgamekeys
allegro_key(search,110).
allegro_key(dpad_center,111).
allegro_key(button_x,112).
allegro_key(button_y,113).
allegro_key(dpad_up,114).
allegro_key(dpad_down,115).
allegro_key(dpad_left,116).
allegro_key(dpad_right,117).
allegro_key(select,118).
allegro_key(start,119).
allegro_key(button_l1,120).
allegro_key(button_r1,121).
allegro_key(button_l2,122).
allegro_key(button_r2,123).
allegro_key(button_a,124).
allegro_key(button_b,125).
allegro_key(thumbl,126).
allegro_key(thumbr,127).

allegro_key(unknown,128).

allegro_key(modifiers,215).

allegro_key(lshift,215).
allegro_key(rshift,216).
allegro_key(lctrl,217).
allegro_key(rctrl,218).
allegro_key(alt,219).
allegro_key(altgr,220).
allegro_key(lwin,221).
allegro_key(rwin,222).
allegro_key(menu,223).
allegro_key(scrolllock,224).
allegro_key(numlock,225).
allegro_key(capslock,226).
