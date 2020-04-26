//
// Created by Jack Davidson on 12/04/2020.
//

#include "FSM.h"
#include "Flowstate.h"

void FSM::PushState(Flowstate *fs) noexcept
{
    if(!m_stack.empty())
    {
        m_stack.top()->m_state = FSM_State::INACTIVE;
    }
    m_stack.push(fs);
    fs->m_state = FSM_State::PRESENTING;
    fs->StartPresenting();
}

void FSM::PopState() noexcept
{
    if(!m_stack.empty())
    {
        Flowstate* topState = m_stack.top();
        if(topState->m_state == FSM_State::ACTIVE)
        {
            topState->m_state = FSM_State::DISMISSING;
            topState->StartDismissing();
        }
        // TODO: Report not ready to be popped
    }
    // TODO: Might be worth to report here
}

void FSM::Update(double deltaTime)
{
    if(!m_stack.empty())
    {
        Flowstate *topState = m_stack.top();
        if (topState != nullptr)
        {
            switch (topState->m_state)
            {
                case FSM_State::INACTIVE:
                    break;
                case FSM_State::PRESENTING:
                    if(topState->UpdatePresenting() == FSM_Status::COMPLETE)
                    {
                        topState->StartActive();
                        topState->m_state =  FSM_State::ACTIVE;
                    }
                    break;
                case FSM_State::ACTIVE:
                    topState->UpdateActive();
                    break;
                case FSM_State::DISMISSING:
                    if (topState->UpdateDismissing() == FSM_Status::COMPLETE)
                    {
                        m_stack.pop();
                        if (!m_stack.empty())
                        {
                            topState = m_stack.top();
                            topState->m_state = FSM_State::ACTIVE;
                        }
                    }
                    break;
            }
        }
    }
}