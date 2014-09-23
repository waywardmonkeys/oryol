//------------------------------------------------------------------------------
//  Synth.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "Synth.h"
#include "Core/Trace.h"

namespace Oryol {

Synth::_state* Synth::state = nullptr;

//------------------------------------------------------------------------------
void
Synth::Setup(const SynthSetup& setupAttrs) {
    ORYOL_TRACE_CONTEXT("Synth::Setup");
    o_assert(!IsValid());
    state = new _state();
    ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(state, "Synth::_state");
    state->soundManager.Setup(setupAttrs);
}

//------------------------------------------------------------------------------
void
Synth::Discard() {
    ORYOL_TRACE_CONTEXT("Synth::Discard");
    o_assert(IsValid());
    state->soundManager.Discard();
    delete state;
    state = nullptr;
}

//------------------------------------------------------------------------------
bool
Synth::IsValid() {
    return nullptr != state;
}

//------------------------------------------------------------------------------
void
Synth::Update() {
    ORYOL_TRACE_CONTEXT("Synth::Update");
    o_assert_dbg(IsValid());
    state->soundManager.Update();
}

//------------------------------------------------------------------------------
void
Synth::AddOp(int32 voice, int32 track, const SynthOp& op, int32 timeOffset) {
    o_assert_dbg(IsValid());
    state->soundManager.AddOp(voice, track, op, timeOffset);
}

} // namespace Oryol
