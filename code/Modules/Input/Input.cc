//------------------------------------------------------------------------------
//  Input.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "Input.h"
#include "Core/Trace.h"

namespace Oryol {

struct Input::_state* Input::state = nullptr;
    
//------------------------------------------------------------------------------
void
Input::Setup(const InputSetup& setup) {
    ORYOL_TRACE_CONTEXT("Input::Setup");
    o_assert(!IsValid());
    state = new _state();
    ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(state, "Input::_state");
    state->inputManager.setup(setup);
}

//------------------------------------------------------------------------------
void
Input::Discard() {
    ORYOL_TRACE_CONTEXT("Input::Discard");
    o_assert(IsValid());
    state->inputManager.discard();
    delete state;
    state = nullptr;
}

//------------------------------------------------------------------------------
bool
Input::IsValid() {
    return nullptr != state;
}

//------------------------------------------------------------------------------
void
Input::SetCursorMode(CursorMode::Code mode) {
    o_assert_dbg(IsValid());
    state->inputManager.setCursorMode(mode);
}

//------------------------------------------------------------------------------
CursorMode::Code
Input::GetCursorMode() {
    o_assert_dbg(IsValid());
    return state->inputManager.getCursorMode();
}

//------------------------------------------------------------------------------
void
Input::BeginCaptureText() {
    o_assert_dbg(IsValid());
    state->inputManager.beginCaptureText();
}

//------------------------------------------------------------------------------
void
Input::EndCaptureText() {
    o_assert_dbg(IsValid());
    return state->inputManager.endCaptureText();
}

//------------------------------------------------------------------------------
const class Keyboard&
Input::Keyboard() {
    o_assert_dbg(IsValid());
    return state->inputManager.Keyboard();
}

//------------------------------------------------------------------------------
const class Mouse&
Input::Mouse() {
    o_assert_dbg(IsValid());
    return state->inputManager.Mouse();
}

//------------------------------------------------------------------------------
const class Gamepad&
Input::Gamepad(int32 index) {
    o_assert_dbg(IsValid());
    return state->inputManager.Gamepad(index);
}

//------------------------------------------------------------------------------
const class Touchpad&
Input::Touchpad() {
    o_assert_dbg(IsValid());
    return state->inputManager.Touchpad();
}

//------------------------------------------------------------------------------
const class Sensors&
Input::Sensors() {
    o_assert_dbg(IsValid());
    return state->inputManager.Sensors();
}

} // namespace Input
