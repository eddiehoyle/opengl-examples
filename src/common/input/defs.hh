//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_DEFS_HH
#define OPENGL_EXAMPLES_DEFS_HH


namespace common {

enum class KeyState {
    kUnknown,
    kPress,
    kRepeat,
    kRelease
};

enum class KeyEvent {
    kUnknown,
    kForward,
    kBackward,
    kTurnLeft,
    kTurnRight,
    kCancel
};

}

#endif //OPENGL_EXAMPLES_DEFS_HH
