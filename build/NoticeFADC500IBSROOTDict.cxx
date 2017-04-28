// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME NoticeFADC500IBSROOTDict

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
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBS.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBSROOT.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_NKFADC500IBS(void *p = 0);
   static void *newArray_NKFADC500IBS(Long_t size, void *p);
   static void delete_NKFADC500IBS(void *p);
   static void deleteArray_NKFADC500IBS(void *p);
   static void destruct_NKFADC500IBS(void *p);
   static void streamer_NKFADC500IBS(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NKFADC500IBS*)
   {
      ::NKFADC500IBS *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NKFADC500IBS >(0);
      static ::ROOT::TGenericClassInfo 
         instance("NKFADC500IBS", ::NKFADC500IBS::Class_Version(), "NoticeFADC500IBSROOT.h", 8,
                  typeid(::NKFADC500IBS), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NKFADC500IBS::Dictionary, isa_proxy, 18,
                  sizeof(::NKFADC500IBS) );
      instance.SetNew(&new_NKFADC500IBS);
      instance.SetNewArray(&newArray_NKFADC500IBS);
      instance.SetDelete(&delete_NKFADC500IBS);
      instance.SetDeleteArray(&deleteArray_NKFADC500IBS);
      instance.SetDestructor(&destruct_NKFADC500IBS);
      instance.SetStreamerFunc(&streamer_NKFADC500IBS);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NKFADC500IBS*)
   {
      return GenerateInitInstanceLocal((::NKFADC500IBS*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::NKFADC500IBS*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr NKFADC500IBS::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *NKFADC500IBS::Class_Name()
{
   return "NKFADC500IBS";
}

//______________________________________________________________________________
const char *NKFADC500IBS::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NKFADC500IBS*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int NKFADC500IBS::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NKFADC500IBS*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NKFADC500IBS::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NKFADC500IBS*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NKFADC500IBS::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NKFADC500IBS*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void NKFADC500IBS::Streamer(TBuffer &R__b)
{
   // Stream an object of class NKFADC500IBS.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_NKFADC500IBS(void *p) {
      return  p ? new(p) ::NKFADC500IBS : new ::NKFADC500IBS;
   }
   static void *newArray_NKFADC500IBS(Long_t nElements, void *p) {
      return p ? new(p) ::NKFADC500IBS[nElements] : new ::NKFADC500IBS[nElements];
   }
   // Wrapper around operator delete
   static void delete_NKFADC500IBS(void *p) {
      delete ((::NKFADC500IBS*)p);
   }
   static void deleteArray_NKFADC500IBS(void *p) {
      delete [] ((::NKFADC500IBS*)p);
   }
   static void destruct_NKFADC500IBS(void *p) {
      typedef ::NKFADC500IBS current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_NKFADC500IBS(TBuffer &buf, void *obj) {
      ((::NKFADC500IBS*)obj)->::NKFADC500IBS::Streamer(buf);
   }
} // end of namespace ROOT for class ::NKFADC500IBS

namespace {
  void TriggerDictionaryInitialization_libNoticeFADC500IBSROOTDict_Impl() {
    static const char* headers[] = {
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBS.h",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBSROOT.h",
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
#line 1 "libNoticeFADC500IBSROOTDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(NKFADC500IBS wrapper class for root)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBSROOT.h")))  NKFADC500IBS;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libNoticeFADC500IBSROOTDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBS.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/NoticeFADC500IBSROOT.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"NKFADC500IBS", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libNoticeFADC500IBSROOTDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libNoticeFADC500IBSROOTDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libNoticeFADC500IBSROOTDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libNoticeFADC500IBSROOTDict() {
  TriggerDictionaryInitialization_libNoticeFADC500IBSROOTDict_Impl();
}
