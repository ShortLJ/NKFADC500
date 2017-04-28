// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME nkusbDict

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
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/nkusb.hh"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_libnkusbDict_Impl() {
    static const char* headers[] = {
"/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/nkusb.hh",
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
#line 1 "libnkusbDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libnkusbDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/MoonByul/Moon_root/NFADC500/CMAKE/include/nkusb.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libnkusbDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libnkusbDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libnkusbDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libnkusbDict() {
  TriggerDictionaryInitialization_libnkusbDict_Impl();
}
