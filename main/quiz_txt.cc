#include <cassert>
#include <utility>
#include <vector>
using namespace std;

#include "quiz_txt.h"

namespace txt_quiz {

guess_text_vars::guess_text_vars(const vector<uwstring>& answer_vars) {
  for (const auto& answer_var : answer_vars)
    push_back(guess_text_var{answer_var});
}
  
quiz_question::quiz_question(const vector<uwstring>& answer_vars) : text_vars{new guess_text_vars{answer_vars}}, pos_var{-1} {
  assert(!answer_vars.empty());
#ifndef NDEBUG  
  for (const auto& answer_var : answer_vars)
    assert(!answer_var.empty());
#endif
}

bool
quiz_question::shuffle_guess_text(guess_text_shuffle& text_shuffle) {
  unique_ptr<const guess_text_vars> text_vars{text_shuffle.shuffle_guess_text(*this->text_vars)};
  if (!text_vars)
    return false;
  this->text_vars = move(text_vars);
  return true;
}

uwstring
quiz_question::get_guess_text() const {
  return uwstring{}; // TODO
}

bool
quiz_question::move_guess_text_pos(bool move_right, bool wrap) {
  return false; // TODO
}
  
bool
quiz_question::accept_guess_char(uwchar uwc) {
  return false; // TODO
}

}
