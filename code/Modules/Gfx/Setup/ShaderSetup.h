#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::ShaderSetup
    @ingroup Gfx
    @brief setup class for shaders
*/
#include "Core/Types.h"
#include "Core/String/String.h"
#include "Core/String/StringAtom.h"
#include "Core/Containers/StaticArray.h"
#include "Resource/Locator.h"
#include "Resource/Id.h"
#include "Gfx/Core/Enums.h"
#include "Gfx/Core/UniformLayout.h"
#include "Gfx/Core/VertexLayout.h"
#include "Gfx/Core/GfxConfig.h"

namespace Oryol {
    
class ShaderSetup {
public:
    /// default constructor
    ShaderSetup();
    /// construct with resource locator
    ShaderSetup(const Locator& loc);

    /// the resource locator
    class Locator Locator;

    /// add shader program from vertex- and fragment-shader sources
    void AddProgramFromSources(uint32 mask, ShaderLang::Code slang, const VertexLayout& vsInputLayout, const String& vsSource, const String& fsSource);
    /// add shader program from precompiled shader byte code
    void AddProgramFromByteCode(uint32 mask, ShaderLang::Code slang, const VertexLayout& vsInputLayout, const uint8* vsByteCode, uint32 vsNumBytes, const uint8* fsByteCode, uint32 fsNumBytes);
    /// add shader program from a metal-style shader library
    void AddProgramFromLibrary(uint32 mask, ShaderLang::Code slang, const VertexLayout& vsInputLayout, const char* vsFunc, const char* fsFunc);
    /// bind a shader uniform block name to a variable slot
    void AddUniformBlock(const StringAtom& name, const UniformLayout& layout, ShaderType::Code shaderStage, int32 slotIndex);

    /// set metal-style library byte code
    void SetLibraryByteCode(ShaderLang::Code slang, const uint8* byteCode, uint32 numBytes);
    /// get metal-style library byte code
    void LibraryByteCode(ShaderLang::Code slang, const void*& outPtr, uint32& outSize) const;

    /// get number of programs
    int32 NumPrograms() const;
    /// get program mask by index
    uint32 Mask(int32 progIndex) const;
    /// get the vertex shader input layout
    const VertexLayout& VertexShaderInputLayout(int32 progIndex) const;
    /// get program vertex shader source (only valid if setup from sources)
    const String& VertexShaderSource(int32 progIndex, ShaderLang::Code slang) const;
    /// get program fragment shader source (only valid if setup from sources)
    const String& FragmentShaderSource(int32 progIndex, ShaderLang::Code slang) const;
    /// get program vertex shader byte code, returns nullptr if no byte code exists
    void VertexShaderByteCode(int32 progIndex, ShaderLang::Code slang, const void*& outPtr, uint32& outSize) const;    
    /// get program fragment shader byte code, returns nullptr if no byte code exists
    void FragmentShaderByteCode(int32 progIndex, ShaderLang::Code slang, const void*& outPtr, uint32& outSize) const;
    /// get vertex shader name (if using metal-style shader library
    const String& VertexShaderFunc(int32 progIndex, ShaderLang::Code slang) const;
    /// get fragment shader name (if using metal-style shader library
    const String& FragmentShaderFunc(int32 progIndex, ShaderLang::Code slang) const;

    /// get number of uniform blocks
    int32 NumUniformBlocks() const;
    /// get uniform block name at index
    const StringAtom& UniformBlockName(int32 uniformBlockIndex) const;
    /// get uniform block layout at index
    const UniformLayout& UniformBlockLayout(int32 uniformBlockIndex) const;
    /// get uniform block shader stage
    ShaderType::Code UniformBlockShaderStage(int32 uniformBlockIndex) const;
    /// get uniform block slot index
    int32 UniformBlockSlot(int32 uniformBlockIndex) const;
    
private:
    struct programEntry {
        uint32 mask = 0;
        StaticArray<String, ShaderLang::NumShaderLangs> vsSources;
        StaticArray<String, ShaderLang::NumShaderLangs> fsSources;
        StaticArray<String, ShaderLang::NumShaderLangs> vsFuncs;
        StaticArray<String, ShaderLang::NumShaderLangs> fsFuncs;
        struct byteCodeEntry {
            const void* ptr = nullptr;
            uint32 size = 0;
        };
        StaticArray<byteCodeEntry, ShaderLang::NumShaderLangs> vsByteCode;
        StaticArray<byteCodeEntry, ShaderLang::NumShaderLangs> fsByteCode;
        VertexLayout vsInputLayout;
    };
    struct uniformBlockEntry {
        StringAtom name;
        UniformLayout layout;
        ShaderType::Code shaderStage;
        int32 slotIndex = InvalidIndex;
    };

    /// obtain an existing entry with matching mask or new entry
    programEntry& obtainEntry(uint32 mask);

    int32 libraryByteCodeSize;
    const void* libraryByteCode;
    int32 numProgramEntries;
    int32 numUniformBlockEntries;
    StaticArray<programEntry, GfxConfig::MaxNumBundlePrograms> programEntries;
    StaticArray<uniformBlockEntry, GfxConfig::MaxNumUniformBlocks> uniformBlockEntries;
};
    
} // namespace Oryol
