//
// Created by Eddie Hoyle on 17/11/17.
//

#ifndef OPENGL_EXAMPLES_COMMAND_HH
#define OPENGL_EXAMPLES_COMMAND_HH

namespace common {

class Camera;

class AbstractCommand {
public:
    virtual ~AbstractCommand() {}
    virtual void execute() = 0;
};

class MoveCommand {
public:

};


}

#endif //OPENGL_EXAMPLES_COMMAND_HH
