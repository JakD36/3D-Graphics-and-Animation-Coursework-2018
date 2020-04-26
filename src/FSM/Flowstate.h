//
// Created by Jack Davidson on 12/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FLOWSTATE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FLOWSTATE_H

class FSM;

enum class FSM_Status
{
    IN_PROGRESS,
    COMPLETE
};

enum class FSM_State
{
    INACTIVE,
    PRESENTING,
    ACTIVE,
    DISMISSING
};

class Flowstate {
protected:
    FSM* m_parentFSM;
public:
    FSM_State m_state;

    virtual void Init() noexcept;
    virtual void StartPresenting() noexcept;
    virtual FSM_Status UpdatePresenting() noexcept;

    virtual void StartActive() noexcept;
    virtual void UpdateActive() noexcept;

    virtual void StartDismissing() noexcept;
    virtual FSM_Status UpdateDismissing() noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FLOWSTATE_H
