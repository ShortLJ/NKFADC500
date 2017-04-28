// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME usb3comrootDict

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
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3com.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3comroot.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_usb3comroot(void *p = 0);
   static void *newArray_usb3comroot(Long_t size, void *p);
   static void delete_usb3comroot(void *p);
   static void deleteArray_usb3comroot(void *p);
   static void destruct_usb3comroot(void *p);
   static void streamer_usb3comroot(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::usb3comroot*)
   {
      ::usb3comroot *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::usb3comroot >(0);
      static ::ROOT::TGenericClassInfo 
         instance("usb3comroot", ::usb3comroot::Class_Version(), "usb3comroot.h", 14,
                  typeid(::usb3comroot), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::usb3comroot::Dictionary, isa_proxy, 18,
                  sizeof(::usb3comroot) );
      instance.SetNew(&new_usb3comroot);
      instance.SetNewArray(&newArray_usb3comroot);
      instance.SetDelete(&delete_usb3comroot);
      instance.SetDeleteArray(&deleteArray_usb3comroot);
      instance.SetDestructor(&destruct_usb3comroot);
      instance.SetStreamerFunc(&streamer_usb3comroot);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::usb3comroot*)
   {
      return GenerateInitInstanceLocal((::usb3comroot*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::usb3comroot*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr usb3comroot::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *usb3comroot::Class_Name()
{
   return "usb3comroot";
}

//______________________________________________________________________________
const char *usb3comroot::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::usb3comroot*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int usb3comroot::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::usb3comroot*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *usb3comroot::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::usb3comroot*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *usb3comroot::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::usb3comroot*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void usb3comroot::Streamer(TBuffer &R__b)
{
   // Stream an object of class usb3comroot.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_usb3comroot(void *p) {
      return  p ? new(p) ::usb3comroot : new ::usb3comroot;
   }
   static void *newArray_usb3comroot(Long_t nElements, void *p) {
      return p ? new(p) ::usb3comroot[nElements] : new ::usb3comroot[nElements];
   }
   // Wrapper around operator delete
   static void delete_usb3comroot(void *p) {
      delete ((::usb3comroot*)p);
   }
   static void deleteArray_usb3comroot(void *p) {
      delete [] ((::usb3comroot*)p);
   }
   static void destruct_usb3comroot(void *p) {
      typedef ::usb3comroot current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_usb3comroot(TBuffer &buf, void *obj) {
      ((::usb3comroot*)obj)->::usb3comroot::Streamer(buf);
   }
} // end of namespace ROOT for class ::usb3comroot

namespace {
  void TriggerDictionaryInitialization_libusb3comrootDict_Impl() {
    static const char* headers[] = {
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3com.h",
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3comroot.h",
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
#line 1 "libusb3comrootDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(USB3COM wrapper class for root)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3comroot.h")))  usb3comroot;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libusb3comrootDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3com.h"
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/usb3comroot.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"usb3comroot", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libusb3comrootDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libusb3comrootDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libusb3comrootDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libusb3comrootDict() {
  TriggerDictionaryInitialization_libusb3comrootDict_Impl();
}
