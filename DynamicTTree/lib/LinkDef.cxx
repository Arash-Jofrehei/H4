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
#include "test/DT_SimpleExample.cpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *DynamicTTree_Dictionary();
   static void DynamicTTree_TClassManip(TClass*);
   static void *new_DynamicTTree(void *p = 0);
   static void *newArray_DynamicTTree(Long_t size, void *p);
   static void delete_DynamicTTree(void *p);
   static void deleteArray_DynamicTTree(void *p);
   static void destruct_DynamicTTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DynamicTTree*)
   {
      ::DynamicTTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DynamicTTree));
      static ::ROOT::TGenericClassInfo 
         instance("DynamicTTree", "interface/DynamicTTreeInterface.h", 11,
                  typeid(::DynamicTTree), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DynamicTTree_Dictionary, isa_proxy, 4,
                  sizeof(::DynamicTTree) );
      instance.SetNew(&new_DynamicTTree);
      instance.SetNewArray(&newArray_DynamicTTree);
      instance.SetDelete(&delete_DynamicTTree);
      instance.SetDeleteArray(&deleteArray_DynamicTTree);
      instance.SetDestructor(&destruct_DynamicTTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DynamicTTree*)
   {
      return GenerateInitInstanceLocal((::DynamicTTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DynamicTTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DynamicTTree_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DynamicTTree*)0x0)->GetClass();
      DynamicTTree_TClassManip(theClass);
   return theClass;
   }

   static void DynamicTTree_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DynamicTTree(void *p) {
      return  p ? new(p) ::DynamicTTree : new ::DynamicTTree;
   }
   static void *newArray_DynamicTTree(Long_t nElements, void *p) {
      return p ? new(p) ::DynamicTTree[nElements] : new ::DynamicTTree[nElements];
   }
   // Wrapper around operator delete
   static void delete_DynamicTTree(void *p) {
      delete ((::DynamicTTree*)p);
   }
   static void deleteArray_DynamicTTree(void *p) {
      delete [] ((::DynamicTTree*)p);
   }
   static void destruct_DynamicTTree(void *p) {
      typedef ::DynamicTTree current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DynamicTTree

namespace ROOT {
   static TClass *maplEstringcOpairlEfloatcOintgRsPgR_Dictionary();
   static void maplEstringcOpairlEfloatcOintgRsPgR_TClassManip(TClass*);
   static void *new_maplEstringcOpairlEfloatcOintgRsPgR(void *p = 0);
   static void *newArray_maplEstringcOpairlEfloatcOintgRsPgR(Long_t size, void *p);
   static void delete_maplEstringcOpairlEfloatcOintgRsPgR(void *p);
   static void deleteArray_maplEstringcOpairlEfloatcOintgRsPgR(void *p);
   static void destruct_maplEstringcOpairlEfloatcOintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,pair<float,int> >*)
   {
      map<string,pair<float,int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,pair<float,int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,pair<float,int> >", -2, "map", 96,
                  typeid(map<string,pair<float,int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOpairlEfloatcOintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(map<string,pair<float,int> >) );
      instance.SetNew(&new_maplEstringcOpairlEfloatcOintgRsPgR);
      instance.SetNewArray(&newArray_maplEstringcOpairlEfloatcOintgRsPgR);
      instance.SetDelete(&delete_maplEstringcOpairlEfloatcOintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOpairlEfloatcOintgRsPgR);
      instance.SetDestructor(&destruct_maplEstringcOpairlEfloatcOintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,pair<float,int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,pair<float,int> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOpairlEfloatcOintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,pair<float,int> >*)0x0)->GetClass();
      maplEstringcOpairlEfloatcOintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOpairlEfloatcOintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOpairlEfloatcOintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,pair<float,int> > : new map<string,pair<float,int> >;
   }
   static void *newArray_maplEstringcOpairlEfloatcOintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,pair<float,int> >[nElements] : new map<string,pair<float,int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOpairlEfloatcOintgRsPgR(void *p) {
      delete ((map<string,pair<float,int> >*)p);
   }
   static void deleteArray_maplEstringcOpairlEfloatcOintgRsPgR(void *p) {
      delete [] ((map<string,pair<float,int> >*)p);
   }
   static void destruct_maplEstringcOpairlEfloatcOintgRsPgR(void *p) {
      typedef map<string,pair<float,int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,pair<float,int> >

namespace {
  void TriggerDictionaryInitialization_LinkDef_Impl() {
    static const char* headers[] = {
"test/DT_SimpleExample.cpp",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/sw/lcg/app/releases/ROOT/6.05.02/x86_64-slc6-gcc49-opt/root/include",
"/afs/cern.ch/user/a/ajofrehe/cern-summer-2016/testbeam-June/H4Analysis/DynamicTTree/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$test/DT_SimpleExample.cpp")))  DynamicTTree;
namespace std{template <class _CharT> struct __attribute__((annotate("$clingAutoload$string")))  char_traits;
}
namespace std{template <typename > class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "test/DT_SimpleExample.cpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DynamicTTree", payloadCode, "@",
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
