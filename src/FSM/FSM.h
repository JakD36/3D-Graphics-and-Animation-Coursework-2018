//
// Created by Jack Davidson on 12/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FSM_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FSM_H

#include <stack>
#include <queue>
#include <gsl/pointers>

class Flowstate;

struct FSMCommands
{
    public:
    enum class Type
    {
        PUSH,
        POP
    };
    Type m_type;
    Flowstate* m_flowstate;
};

class FSM {
private:
    std::stack<gsl::owner<Flowstate*>> m_stack;
    std::queue<FSMCommands> m_fsmCommands;
public:
    void PushState(Flowstate* fs) noexcept;
    void PopState() noexcept;

    void Update(double deltaTime);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FSM_H
