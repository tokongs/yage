/*
#pragma once
#include <string>
#include "Logger.h"

namespace yage{
static void print(const std::string& s){
    YAGE_TRACE(s);
}

static void print(int i){
    YAGE_TRACE(i);
}

static void print(long long l){
    YAGE_TRACE(l);
}

static void print(unsigned int u){
    YAGE_TRACE(u);
}

static void print(unsigned long long ul){
    YAGE_TRACE(ul);
}
static void print(float f){
    YAGE_TRACE(f);
}

static void print(bool b){
    YAGE_TRACE(b);
}

static void registerPrintFunctions(asIScriptEngine *engine){
    engine->RegisterGlobalFunction("void print(const string&in)", asFUNCTIONPR(print, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(int)", asFUNCTIONPR(print, (int), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(int64)", asFUNCTIONPR(print, (long long), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(uint)", asFUNCTIONPR(print, (unsigned int), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(uint64)", asFUNCTIONPR(print, (unsigned long long), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(float)", asFUNCTIONPR(print, (float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(bool)", asFUNCTIONPR(print, (bool), void), asCALL_CDECL);
}

}
 */