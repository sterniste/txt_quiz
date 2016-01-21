#include <cassert>
#include <utility>
#include <vector>
using namespace std;

#include "quiz_txt.h"

namespace txt_quiz {

#ifndef NDEBUG
void
guess_text_var::validate(bool local) const {
  assert(!empty());
}
#endif

guess_text_vars::guess_text_vars(const vector<uwstring>& answer_vars) {
  for (const auto& answer_var : answer_vars)
    push_back(guess_text_var{answer_var});
#ifndef NDEBUG
  validate();
#endif
}

#ifndef NDEBUG
void
guess_text_vars::validate(bool local) const {
  if (!local) {
    for (const auto& text_var : *this)
      text_var.validate();
  }
  assert(!empty());
}
#endif

quiz_question::quiz_question(const vector<uwstring>& answer_vars) : text_vars{new guess_text_vars{answer_vars}}, pos_var{} {
#ifndef NDEBUG
  validate(true);
#endif
}

#ifndef NDEBUG
void
quiz_question::validate(bool local) const {
  if (!local)
    text_vars->validate();
  // TODO: pos_var
}
#endif

bool
quiz_question::filter_guess_text(guess_text_filter& text_filter) {
  unique_ptr<const guess_text_vars> text_vars{text_filter.filter_guess_text(*this->text_vars)};
  if (!text_vars)
    return false;
  this->text_vars = move(text_vars);
  return true;
}

uwstring
quiz_question::get_guess_text() const {
  return uwstring{};  // TODO
}

bool
quiz_question::move_guess_text_pos(bool move_right, bool wrap) {
  return false;  // TODO
}

bool
quiz_question::accept_guess_char(uwchar uwc) {
  return false;  // TODO
}
}
