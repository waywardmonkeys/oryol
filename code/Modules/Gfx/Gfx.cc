//------------------------------------------------------------------------------
//  Gfx.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "Gfx.h"
#include "Core/Core.h"
#include "Core/Trace.h"

namespace Oryol {

using namespace _priv;

Gfx::_state* Gfx::state = nullptr;

//------------------------------------------------------------------------------
void
Gfx::Setup(const class GfxSetup& setup) {
    ORYOL_TRACE_CONTEXT("Gfx::Setup");
    o_assert_dbg(!IsValid());
    state = new _state();
    ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(state, "Gfx::_state");
    state->gfxSetup = setup;
    state->displayManager.SetupDisplay(setup);
    state->renderer.setup();
    state->resourceManager.Setup(setup, &state->renderer, &state->displayManager);
    state->runLoopId = Core::PreRunLoop()->Add([] {
        state->displayManager.ProcessSystemEvents();
    });
}

//------------------------------------------------------------------------------
void
Gfx::Discard() {
    ORYOL_TRACE_CONTEXT("Gfx::Discard");
    o_assert_dbg(IsValid());
    Core::PreRunLoop()->Remove(state->runLoopId);
    state->renderer.discard();
    state->resourceManager.Discard();
    state->displayManager.DiscardDisplay();
    delete state;
    state = nullptr;
}

//------------------------------------------------------------------------------
bool
Gfx::QuitRequested() {
    o_assert_dbg(IsValid());
    return state->displayManager.QuitRequested();
}

//------------------------------------------------------------------------------
void
Gfx::AttachEventHandler(const Ptr<Port>& handler) {
    o_assert_dbg(IsValid());
    o_assert_dbg(handler.isValid());
    state->displayManager.AttachDisplayEventHandler(handler);
}

//------------------------------------------------------------------------------
void
Gfx::DetachEventHandler(const Ptr<Port>& handler) {
    o_assert_dbg(IsValid());
    o_assert_dbg(handler.isValid());
    state->displayManager.DetachDisplayEventHandler(handler);
}

//------------------------------------------------------------------------------
const GfxSetup&
Gfx::GfxSetup() {
    o_assert_dbg(IsValid());
    return state->gfxSetup;
}

//------------------------------------------------------------------------------
const DisplayAttrs&
Gfx::DisplayAttrs() {
    o_assert_dbg(IsValid());
    return state->displayManager.GetDisplayAttrs();
}

//------------------------------------------------------------------------------
const DisplayAttrs&
Gfx::RenderTargetAttrs() {
    o_assert_dbg(IsValid());
    return state->renderer.renderTargetAttrs();
}

//------------------------------------------------------------------------------
/**
 NOTE: the LookupResource() method will bump the use-count of looked up
 resource, so make sure to call DiscardResource() when you're done with it!
*/
GfxId
Gfx::LookupResource(const Locator& loc) {
    o_assert_dbg(IsValid());
    return GfxId(state->resourceManager.LookupResource(loc));
}

//------------------------------------------------------------------------------
ResourceState::Code
Gfx::QueryResourceState(const GfxId& gfxId) {
    o_assert_dbg(IsValid());
    return state->resourceManager.QueryResourceState(gfxId.Id());
}

//------------------------------------------------------------------------------
void
Gfx::ApplyDefaultRenderTarget() {
    ORYOL_TRACE_CONTEXT("Gfx::ApplyDefaultRenderTarget");
    o_assert_dbg(IsValid());
    state->renderer.applyRenderTarget(&state->displayManager, nullptr);
}

//------------------------------------------------------------------------------
void
Gfx::ApplyOffscreenRenderTarget(const GfxId& gfxId) {
    ORYOL_TRACE_CONTEXT("Gfx::ApplyOffscreenRenderTarget");
    o_assert_dbg(IsValid());
    o_assert_dbg(gfxId.IsValid());

    texture* renderTarget = state->resourceManager.LookupTexture(gfxId.Id());
    o_assert_dbg(nullptr != renderTarget);
    state->renderer.applyRenderTarget(&state->displayManager, renderTarget);
}

//------------------------------------------------------------------------------
void
Gfx::ApplyDrawState(const GfxId& gfxId) {
    ORYOL_TRACE_CONTEXT("Gfx::ApplyDrawState");
    o_assert_dbg(IsValid());
    state->renderer.applyDrawState(state->resourceManager.LookupDrawState(gfxId.Id()));
}

//------------------------------------------------------------------------------
void
Gfx::CommitFrame() {
    ORYOL_TRACE_CONTEXT("Gfx::CommitFrame");
    o_assert_dbg(IsValid());
    state->renderer.commitFrame();
    state->displayManager.Present();
}

//------------------------------------------------------------------------------
void
Gfx::ResetStateCache() {
    ORYOL_TRACE_CONTEXT("Gfx::ResetStateCache");
    o_assert_dbg(IsValid());
    state->renderer.resetStateCache();
}

//------------------------------------------------------------------------------
void
Gfx::UpdateVertices(const GfxId& gfxId, int32 numBytes, const void* data) {
    ORYOL_TRACE_CONTEXT("Gfx::UpdateVertices");
    o_assert_dbg(IsValid());
    mesh* msh = state->resourceManager.LookupMesh(gfxId.Id());
    state->renderer.updateVertices(msh, numBytes, data);
}

//------------------------------------------------------------------------------
void
Gfx::ReadPixels(void* buf, int32 bufNumBytes) {
    ORYOL_TRACE_CONTEXT("Gfx::ReadPixels");
    o_assert_dbg(IsValid());
    state->renderer.readPixels(&state->displayManager, buf, bufNumBytes);
}

//------------------------------------------------------------------------------
void
Gfx::Clear(PixelChannel::Mask channels, const glm::vec4& color, float32 depth, uint8 stencil) {
    ORYOL_TRACE_CONTEXT("Gfx::Clear");
    o_assert_dbg(IsValid());
    state->renderer.clear(channels, color, depth, stencil);
}

//------------------------------------------------------------------------------
void
Gfx::Draw(int32 primGroupIndex) {
    ORYOL_TRACE_CONTEXT("Gfx::Draw");
    o_assert_dbg(IsValid());
    state->renderer.draw(primGroupIndex);
}

//------------------------------------------------------------------------------
void
Gfx::Draw(const PrimitiveGroup& primGroup) {
    ORYOL_TRACE_CONTEXT("Gfx::Draw");
    o_assert_dbg(IsValid());
    state->renderer.draw(primGroup);
}

//------------------------------------------------------------------------------
void
Gfx::DrawInstanced(int32 primGroupIndex, int32 numInstances) {
    ORYOL_TRACE_CONTEXT("Gfx::DrawInstanced");
    o_assert_dbg(IsValid());
    state->renderer.drawInstanced(primGroupIndex, numInstances);
}

//------------------------------------------------------------------------------
void
Gfx::DrawInstanced(const PrimitiveGroup& primGroup, int32 numInstances) {
    ORYOL_TRACE_CONTEXT("Gfx::DrawInstanced");
    o_assert_dbg(IsValid());
    state->renderer.drawInstanced(primGroup, numInstances);
}

} // namespace Oryol
