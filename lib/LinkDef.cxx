// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME libdILinkDef

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "interface/WFViewer.h"
#include "interface/MCPAnalyzer.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_InterpolatorFunc(void *p);
   static void deleteArray_InterpolatorFunc(void *p);
   static void destruct_InterpolatorFunc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::InterpolatorFunc*)
   {
      ::InterpolatorFunc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::InterpolatorFunc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("InterpolatorFunc", ::InterpolatorFunc::Class_Version(), "interface/WFViewer.h", 22,
                  typeid(::InterpolatorFunc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::InterpolatorFunc::Dictionary, isa_proxy, 4,
                  sizeof(::InterpolatorFunc) );
      instance.SetDelete(&delete_InterpolatorFunc);
      instance.SetDeleteArray(&deleteArray_InterpolatorFunc);
      instance.SetDestructor(&destruct_InterpolatorFunc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::InterpolatorFunc*)
   {
      return GenerateInitInstanceLocal((::InterpolatorFunc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::InterpolatorFunc*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WFViewer(void *p = 0);
   static void *newArray_WFViewer(Long_t size, void *p);
   static void delete_WFViewer(void *p);
   static void deleteArray_WFViewer(void *p);
   static void destruct_WFViewer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WFViewer*)
   {
      ::WFViewer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WFViewer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("WFViewer", ::WFViewer::Class_Version(), "interface/WFViewer.h", 41,
                  typeid(::WFViewer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WFViewer::Dictionary, isa_proxy, 4,
                  sizeof(::WFViewer) );
      instance.SetNew(&new_WFViewer);
      instance.SetNewArray(&newArray_WFViewer);
      instance.SetDelete(&delete_WFViewer);
      instance.SetDeleteArray(&deleteArray_WFViewer);
      instance.SetDestructor(&destruct_WFViewer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WFViewer*)
   {
      return GenerateInitInstanceLocal((::WFViewer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::WFViewer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MCPAnalyzer(void *p = 0);
   static void *newArray_MCPAnalyzer(Long_t size, void *p);
   static void delete_MCPAnalyzer(void *p);
   static void deleteArray_MCPAnalyzer(void *p);
   static void destruct_MCPAnalyzer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MCPAnalyzer*)
   {
      ::MCPAnalyzer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MCPAnalyzer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MCPAnalyzer", ::MCPAnalyzer::Class_Version(), "interface/MCPAnalyzer.h", 19,
                  typeid(::MCPAnalyzer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MCPAnalyzer::Dictionary, isa_proxy, 4,
                  sizeof(::MCPAnalyzer) );
      instance.SetNew(&new_MCPAnalyzer);
      instance.SetNewArray(&newArray_MCPAnalyzer);
      instance.SetDelete(&delete_MCPAnalyzer);
      instance.SetDeleteArray(&deleteArray_MCPAnalyzer);
      instance.SetDestructor(&destruct_MCPAnalyzer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MCPAnalyzer*)
   {
      return GenerateInitInstanceLocal((::MCPAnalyzer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MCPAnalyzer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr InterpolatorFunc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *InterpolatorFunc::Class_Name()
{
   return "InterpolatorFunc";
}

//______________________________________________________________________________
const char *InterpolatorFunc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::InterpolatorFunc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int InterpolatorFunc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::InterpolatorFunc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *InterpolatorFunc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::InterpolatorFunc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *InterpolatorFunc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::InterpolatorFunc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WFViewer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *WFViewer::Class_Name()
{
   return "WFViewer";
}

//______________________________________________________________________________
const char *WFViewer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFViewer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int WFViewer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WFViewer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WFViewer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFViewer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WFViewer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WFViewer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MCPAnalyzer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MCPAnalyzer::Class_Name()
{
   return "MCPAnalyzer";
}

//______________________________________________________________________________
const char *MCPAnalyzer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MCPAnalyzer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MCPAnalyzer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MCPAnalyzer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MCPAnalyzer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MCPAnalyzer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MCPAnalyzer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MCPAnalyzer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void InterpolatorFunc::Streamer(TBuffer &R__b)
{
   // Stream an object of class InterpolatorFunc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(InterpolatorFunc::Class(),this);
   } else {
      R__b.WriteClassBuffer(InterpolatorFunc::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_InterpolatorFunc(void *p) {
      delete ((::InterpolatorFunc*)p);
   }
   static void deleteArray_InterpolatorFunc(void *p) {
      delete [] ((::InterpolatorFunc*)p);
   }
   static void destruct_InterpolatorFunc(void *p) {
      typedef ::InterpolatorFunc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::InterpolatorFunc

//______________________________________________________________________________
void WFViewer::Streamer(TBuffer &R__b)
{
   // Stream an object of class WFViewer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WFViewer::Class(),this);
   } else {
      R__b.WriteClassBuffer(WFViewer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WFViewer(void *p) {
      return  p ? new(p) ::WFViewer : new ::WFViewer;
   }
   static void *newArray_WFViewer(Long_t nElements, void *p) {
      return p ? new(p) ::WFViewer[nElements] : new ::WFViewer[nElements];
   }
   // Wrapper around operator delete
   static void delete_WFViewer(void *p) {
      delete ((::WFViewer*)p);
   }
   static void deleteArray_WFViewer(void *p) {
      delete [] ((::WFViewer*)p);
   }
   static void destruct_WFViewer(void *p) {
      typedef ::WFViewer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WFViewer

//______________________________________________________________________________
void MCPAnalyzer::Streamer(TBuffer &R__b)
{
   // Stream an object of class MCPAnalyzer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MCPAnalyzer::Class(),this);
   } else {
      R__b.WriteClassBuffer(MCPAnalyzer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MCPAnalyzer(void *p) {
      return  p ? new(p) ::MCPAnalyzer : new ::MCPAnalyzer;
   }
   static void *newArray_MCPAnalyzer(Long_t nElements, void *p) {
      return p ? new(p) ::MCPAnalyzer[nElements] : new ::MCPAnalyzer[nElements];
   }
   // Wrapper around operator delete
   static void delete_MCPAnalyzer(void *p) {
      delete ((::MCPAnalyzer*)p);
   }
   static void deleteArray_MCPAnalyzer(void *p) {
      delete [] ((::MCPAnalyzer*)p);
   }
   static void destruct_MCPAnalyzer(void *p) {
      typedef ::MCPAnalyzer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MCPAnalyzer

namespace {
  void TriggerDictionaryInitialization_LinkDef_Impl() {
    static const char* headers[] = {
"interface/WFViewer.h",
"interface/MCPAnalyzer.h",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/sw/lcg/app/releases/ROOT/6.05.02/x86_64-slc6-gcc49-opt/root/include",
"/afs/cern.ch/user/a/ajofrehe/cern-summer-2016/testbeam-June/H4Analysis/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$interface/LinkDef.h")))  InterpolatorFunc;
class __attribute__((annotate("$clingAutoload$interface/LinkDef.h")))  WFViewer;
class __attribute__((annotate("$clingAutoload$interface/LinkDef.h")))  MCPAnalyzer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "interface/WFViewer.h"
#include "interface/MCPAnalyzer.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"InterpolatorFunc", payloadCode, "@",
"MCPAnalyzer", payloadCode, "@",
"WFViewer", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("LinkDef",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_LinkDef_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_LinkDef_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_LinkDef() {
  TriggerDictionaryInitialization_LinkDef_Impl();
}
