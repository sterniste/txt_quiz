#ifdef __ANDROID__
extern "C" {
#include <jni.h>
}
#endif

#include <string>

using namespace std;

#include "cc_init.h"

// external storage directory
string esd_path;

const string&
get_esd_path() {
  return esd_path;
}

void
set_esd_path(const char* utf8) {
  esd_path = utf8;
}

#ifdef __ANDROID__
extern "C" void
Java_sstern_kbd_1quiz_QuizActivity_cc_1init(JNIEnv* env, jobject thiz, jstring j_esd_path) {
  const char* utf8 = env->GetStringUTFChars(j_esd_path, nullptr);
  set_esd_path(utf8);
  env->ReleaseStringUTFChars(j_esd_path, utf8);
}
#else
#include <cassert>
#include <cstring>
#include <string>
using namespace std;

#include "utf8_u16string.h"
using namespace utf8_u16string;

int
main() {
  set_esd_path("/esd/path");

  {
    const char* utf8_cs = "a\xff";
    const auto widened = widen(string{utf8_cs});
    assert(widened.first.size() == 1 && widened.second == 1);
  }
  {
    const u16string u16s{'a', 0xd800};
    const auto narrowed = narrow(u16s);
    assert(narrowed.first.size() == 1 && narrowed.second == 1);
  }
  {
    const char* utf8_cs = "14.95€";
    const auto widened = widen(string{utf8_cs});
    assert(widened.first.size() == 6 && widened.second > 6);
    const auto narrowed = narrow(widened.first);
    assert(narrowed.first.size() == strlen(utf8_cs) && narrowed.second == 6);
    assert(narrowed.first == string{utf8_cs});
  }
}
#endif
