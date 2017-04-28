// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME NKFADC500GUIDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500setting.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500run.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500gui.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *FADC500setting_Dictionary();
   static void FADC500setting_TClassManip(TClass*);
   static void *new_FADC500setting(void *p = 0);
   static void *newArray_FADC500setting(Long_t size, void *p);
   static void delete_FADC500setting(void *p);
   static void deleteArray_FADC500setting(void *p);
   static void destruct_FADC500setting(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FADC500setting*)
   {
      ::FADC500setting *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FADC500setting));
      static ::ROOT::TGenericClassInfo 
         instance("FADC500setting", "FADC500setting.h", 9,
                  typeid(::FADC500setting), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FADC500setting_Dictionary, isa_proxy, 0,
                  sizeof(::FADC500setting) );
      instance.SetNew(&new_FADC500setting);
      instance.SetNewArray(&newArray_FADC500setting);
      instance.SetDelete(&delete_FADC500setting);
      instance.SetDeleteArray(&deleteArray_FADC500setting);
      instance.SetDestructor(&destruct_FADC500setting);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FADC500setting*)
   {
      return GenerateInitInstanceLocal((::FADC500setting*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FADC500setting*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FADC500setting_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FADC500setting*)0x0)->GetClass();
      FADC500setting_TClassManip(theClass);
   return theClass;
   }

   static void FADC500setting_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FADC500run_Dictionary();
   static void FADC500run_TClassManip(TClass*);
   static void *new_FADC500run(void *p = 0);
   static void *newArray_FADC500run(Long_t size, void *p);
   static void delete_FADC500run(void *p);
   static void deleteArray_FADC500run(void *p);
   static void destruct_FADC500run(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FADC500run*)
   {
      ::FADC500run *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FADC500run));
      static ::ROOT::TGenericClassInfo 
         instance("FADC500run", "FADC500run.h", 14,
                  typeid(::FADC500run), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FADC500run_Dictionary, isa_proxy, 0,
                  sizeof(::FADC500run) );
      instance.SetNew(&new_FADC500run);
      instance.SetNewArray(&newArray_FADC500run);
      instance.SetDelete(&delete_FADC500run);
      instance.SetDeleteArray(&deleteArray_FADC500run);
      instance.SetDestructor(&destruct_FADC500run);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FADC500run*)
   {
      return GenerateInitInstanceLocal((::FADC500run*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FADC500run*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FADC500run_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FADC500run*)0x0)->GetClass();
      FADC500run_TClassManip(theClass);
   return theClass;
   }

   static void FADC500run_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FADC500gui_Dictionary();
   static void FADC500gui_TClassManip(TClass*);
   static void *new_FADC500gui(void *p = 0);
   static void *newArray_FADC500gui(Long_t size, void *p);
   static void delete_FADC500gui(void *p);
   static void deleteArray_FADC500gui(void *p);
   static void destruct_FADC500gui(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FADC500gui*)
   {
      ::FADC500gui *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FADC500gui));
      static ::ROOT::TGenericClassInfo 
         instance("FADC500gui", "FADC500gui.h", 55,
                  typeid(::FADC500gui), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FADC500gui_Dictionary, isa_proxy, 0,
                  sizeof(::FADC500gui) );
      instance.SetNew(&new_FADC500gui);
      instance.SetNewArray(&newArray_FADC500gui);
      instance.SetDelete(&delete_FADC500gui);
      instance.SetDeleteArray(&deleteArray_FADC500gui);
      instance.SetDestructor(&destruct_FADC500gui);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FADC500gui*)
   {
      return GenerateInitInstanceLocal((::FADC500gui*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FADC500gui*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FADC500gui_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FADC500gui*)0x0)->GetClass();
      FADC500gui_TClassManip(theClass);
   return theClass;
   }

   static void FADC500gui_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_FADC500setting(void *p) {
      return  p ? new(p) ::FADC500setting : new ::FADC500setting;
   }
   static void *newArray_FADC500setting(Long_t nElements, void *p) {
      return p ? new(p) ::FADC500setting[nElements] : new ::FADC500setting[nElements];
   }
   // Wrapper around operator delete
   static void delete_FADC500setting(void *p) {
      delete ((::FADC500setting*)p);
   }
   static void deleteArray_FADC500setting(void *p) {
      delete [] ((::FADC500setting*)p);
   }
   static void destruct_FADC500setting(void *p) {
      typedef ::FADC500setting current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FADC500setting

namespace ROOT {
   // Wrappers around operator new
   static void *new_FADC500run(void *p) {
      return  p ? new(p) ::FADC500run : new ::FADC500run;
   }
   static void *newArray_FADC500run(Long_t nElements, void *p) {
      return p ? new(p) ::FADC500run[nElements] : new ::FADC500run[nElements];
   }
   // Wrapper around operator delete
   static void delete_FADC500run(void *p) {
      delete ((::FADC500run*)p);
   }
   static void deleteArray_FADC500run(void *p) {
      delete [] ((::FADC500run*)p);
   }
   static void destruct_FADC500run(void *p) {
      typedef ::FADC500run current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FADC500run

namespace ROOT {
   // Wrappers around operator new
   static void *new_FADC500gui(void *p) {
      return  p ? new(p) ::FADC500gui : new ::FADC500gui;
   }
   static void *newArray_FADC500gui(Long_t nElements, void *p) {
      return p ? new(p) ::FADC500gui[nElements] : new ::FADC500gui[nElements];
   }
   // Wrapper around operator delete
   static void delete_FADC500gui(void *p) {
      delete ((::FADC500gui*)p);
   }
   static void deleteArray_FADC500gui(void *p) {
      delete [] ((::FADC500gui*)p);
   }
   static void destruct_FADC500gui(void *p) {
      typedef ::FADC500gui current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FADC500gui

namespace {
  void TriggerDictionaryInitialization_libNKFADC500GUIDict_Impl() {
    static const char* headers[] = {
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500setting.h",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500run.h",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500gui.h",
0
    };
    static const char* includePaths[] = {
"/Users/MoonByul/root/include",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/src",
"/Users/MoonByul/root/include",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libNKFADC500GUIDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500setting.h")))  FADC500setting;
class __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500run.h")))  FADC500run;
class __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500gui.h")))  FADC500gui;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libNKFADC500GUIDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500setting.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500run.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/FADC500gui.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FADC500gui", payloadCode, "@",
"FADC500run", payloadCode, "@",
"FADC500setting", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libNKFADC500GUIDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libNKFADC500GUIDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libNKFADC500GUIDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libNKFADC500GUIDict() {
  TriggerDictionaryInitialization_libNKFADC500GUIDict_Impl();
}
