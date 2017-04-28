// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME NoticeTCBIBSROOTDict

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
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBS.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBSROOT.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_NKTCBIBS(void *p = 0);
   static void *newArray_NKTCBIBS(Long_t size, void *p);
   static void delete_NKTCBIBS(void *p);
   static void deleteArray_NKTCBIBS(void *p);
   static void destruct_NKTCBIBS(void *p);
   static void streamer_NKTCBIBS(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NKTCBIBS*)
   {
      ::NKTCBIBS *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NKTCBIBS >(0);
      static ::ROOT::TGenericClassInfo 
         instance("NKTCBIBS", ::NKTCBIBS::Class_Version(), "NoticeTCBIBSROOT.h", 11,
                  typeid(::NKTCBIBS), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NKTCBIBS::Dictionary, isa_proxy, 18,
                  sizeof(::NKTCBIBS) );
      instance.SetNew(&new_NKTCBIBS);
      instance.SetNewArray(&newArray_NKTCBIBS);
      instance.SetDelete(&delete_NKTCBIBS);
      instance.SetDeleteArray(&deleteArray_NKTCBIBS);
      instance.SetDestructor(&destruct_NKTCBIBS);
      instance.SetStreamerFunc(&streamer_NKTCBIBS);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NKTCBIBS*)
   {
      return GenerateInitInstanceLocal((::NKTCBIBS*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::NKTCBIBS*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr NKTCBIBS::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *NKTCBIBS::Class_Name()
{
   return "NKTCBIBS";
}

//______________________________________________________________________________
const char *NKTCBIBS::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NKTCBIBS*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int NKTCBIBS::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NKTCBIBS*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NKTCBIBS::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NKTCBIBS*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NKTCBIBS::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NKTCBIBS*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void NKTCBIBS::Streamer(TBuffer &R__b)
{
   // Stream an object of class NKTCBIBS.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_NKTCBIBS(void *p) {
      return  p ? new(p) ::NKTCBIBS : new ::NKTCBIBS;
   }
   static void *newArray_NKTCBIBS(Long_t nElements, void *p) {
      return p ? new(p) ::NKTCBIBS[nElements] : new ::NKTCBIBS[nElements];
   }
   // Wrapper around operator delete
   static void delete_NKTCBIBS(void *p) {
      delete ((::NKTCBIBS*)p);
   }
   static void deleteArray_NKTCBIBS(void *p) {
      delete [] ((::NKTCBIBS*)p);
   }
   static void destruct_NKTCBIBS(void *p) {
      typedef ::NKTCBIBS current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_NKTCBIBS(TBuffer &buf, void *obj) {
      ((::NKTCBIBS*)obj)->::NKTCBIBS::Streamer(buf);
   }
} // end of namespace ROOT for class ::NKTCBIBS

namespace {
  void TriggerDictionaryInitialization_libNoticeTCBIBSROOTDict_Impl() {
    static const char* headers[] = {
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBS.h",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBSROOT.h",
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
#line 1 "libNoticeTCBIBSROOTDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(NKTCBIBS wrapper class for root)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBSROOT.h")))  NKTCBIBS;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libNoticeTCBIBSROOTDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBS.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeTCBIBSROOT.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"NKTCBIBS", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libNoticeTCBIBSROOTDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libNoticeTCBIBSROOTDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libNoticeTCBIBSROOTDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libNoticeTCBIBSROOTDict() {
  TriggerDictionaryInitialization_libNoticeTCBIBSROOTDict_Impl();
}
