#pragma once
//------------------------------------------------------------------------------
/**
    @file Core/Class.h
    @brief Oryol class annotation macros
*/
#include "Core/Types.h"
#include "Core/Trace.h"

/// declare an Oryol class with pool allocator (located inside class declaration)
#define OryolClassPoolAllocDecl(TYPE) \
private:\
static Oryol::_priv::poolAllocator<TYPE> allocator;\
protected:\
virtual void destroy() {\
    TYPE::allocator.Destroy(this);\
};\
public:\
template<typename... ARGS> static Oryol::Ptr<TYPE> Create(ARGS&&... args) {\
    auto p = TYPE::allocator.Create(std::forward<ARGS>(args)...);\
    ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(p, #TYPE);\
    return Oryol::Ptr<TYPE>(p);\
};\

/// implementation-side macro for Oryol class with pool allocator (located in .cc source file)
#define OryolClassPoolAllocImpl(TYPE) \
Oryol::_priv::poolAllocator<TYPE> TYPE::allocator;

/// implementation-side macro for template classes with pool allocator (located in .cc source file)
#define OryolTemplClassPoolAllocImpl(TEMPLATE_TYPE, CLASS_TYPE) \
template<class TEMPLATE_TYPE> Oryol::_priv::poolAllocator<CLASS_TYPE<TEMPLATE_TYPE>> CLASS_TYPE<TEMPLATE_TYPE>::allocator;

/// declare an Oryol class without pool allocator (located inside class declaration)
#define OryolClassDecl(TYPE) \
protected:\
virtual void destroy() {\
    delete(this);\
};\
public:\
template<typename... ARGS> static Oryol::Ptr<TYPE> Create(ARGS&&... args) {\
    auto p = new TYPE(std::forward<ARGS>(args)...);\
    ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(p, #TYPE);\
    return Oryol::Ptr<TYPE>(p);\
};

/// implementation-side macro for Oryol class without pool allocator (located in .cc source file)
#define OryolClassImpl(TYPE)


