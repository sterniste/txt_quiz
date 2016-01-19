#ifndef QUIZ_TXT_H
#define QUIZ_TXT_H

#include <memory>
#include <string>
#include <vector>

namespace txt_quiz {
using uwchar = char16_t;
using uwstring = std::u16string;

class guess_text_var : public uwstring {
  using seq_off = unsigned short int;
  std::vector<seq_off> seq_offs;
  unsigned int seq_pos;
  bool front_solved;

 public:
  guess_text_var(const uwstring& text) : uwstring{text}, seq_offs{0}, seq_pos{}, front_solved{} {}

  uwstring get_seq_str(unsigned int seq) const;
  bool get_seq_solved(unsigned int seq) const;
  unsigned int get_pos() const { return seq_pos; }
  void solve(unsigned int pos, unsigned int len);
#ifndef NDEBUG  
  void validate();
#endif  
};

struct guess_text_vars : public std::vector<guess_text_var> {
  guess_text_vars(const std::vector<uwstring>& answer_vars);
#ifndef NDEBUG  
  void validate();
#endif  
};

struct guess_text_shuffle {
  virtual ~guess_text_shuffle() {}

  virtual std::unique_ptr<const guess_text_vars> shuffle_guess_text(const guess_text_vars& text_vars) = 0;
};

class quiz_question {
  std::unique_ptr<const guess_text_vars> text_vars;
  int pos_var;

 public:
  quiz_question(const std::vector<uwstring>& answer_vars);

  bool shuffle_guess_text(guess_text_shuffle& text_shuffle);
  uwstring get_guess_text() const;
  bool move_guess_text_pos(bool move_right, bool wrap = false);
  int get_guess_text_pos() const;
  bool accept_guess_char(uwchar uwc);
#ifndef NDEBUG  
  void validate();
#endif  
};
}

#endif
