#include <gtest/gtest.h>

#include "s21_containers.h"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ARRAY______________________________________________________________________________________________________
TEST(Create_Array, EX_1) {
  s21::array<int, 5> a;
  s21::array<int, 5> need = {0, 0, 0, 0, 0};
  EXPECT_EQ((a == need), 1);
}

TEST(Create_Array, EX_2) {
  s21::array<int, 5> a;
  s21::array<int, 5> need(a);
  EXPECT_EQ((a == need), 1);
}

TEST(Array_item, EX_1) {
  s21::array<int, 5> a = {1, 2, 3};
  int need = 1;
  EXPECT_EQ((a.front() == need), 1);
}

TEST(Array_item, EX_2) {
  s21::array<int, 3> a = {1, 2, 3};
  int need = 3;
  EXPECT_EQ((a.back() == need), 1);
}

TEST(Array_item, EX_3) {
  s21::array<int, 5> a = {1, 2, 3};
  int need = 0;
  EXPECT_EQ((a.back() == need), 1);
}

TEST(Array_item, EX_4) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ((*a.begin() == a[0]), 1);
}

TEST(Array_item, EX_5) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ((*a.data() + 1 == a[1]), 1);
}

TEST(Array_item, EX_6) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ((a.end() == nullptr), 1);
}

TEST(Array_empty, EX_1) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ((a.empty() == 0), 1);
}

TEST(Array_size, EX_1) {
  s21::array<int, 3> a = {1, 2, 3};
  EXPECT_EQ((a.max_size() == 4611686018427387903), 1);
}

TEST(Array_swap, EX_1) {
  s21::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = {1, 1, 1};
  s21::array<int, 3> need = {1, 1, 1};
  s21::array<int, 3> need_1 = {1, 2, 3};
  a.swap(b);

  EXPECT_EQ((a == need), 1);
  EXPECT_EQ((b == need_1), 1);
}

TEST(Array_fill, EX_1) {
  s21::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> need = {1, 1, 1};
  a.fill(1);

  EXPECT_EQ((a == need), 1);
}

// LIST______________________________________________________________________________________________________
TEST(Create_List, EX_1) {
  s21::list<int> a;
  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_List, EX_2) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b(a);

  EXPECT_EQ((a == b), 1);
}

TEST(List_pop_back, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {1, 2};

  a.pop_back();

  EXPECT_EQ((a == need), 1);
}

TEST(List_pop_back, EX_2) {
  s21::list<int> a;
  EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST(List_pop_front, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {2, 3};

  a.pop_front();

  EXPECT_EQ((a == need), 1);
}

TEST(List_push_back, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {1, 2, 3, 3};

  a.push_back(3);

  EXPECT_EQ((a == need), 1);
}

TEST(List_push_back, EX_2) {
  s21::list<int> a;
  a.push_back(1);
  EXPECT_EQ((a.front() == 1), 1);
}

TEST(List_push_front, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {3, 1, 2, 3};

  a.push_front(3);

  EXPECT_EQ((a == need), 1);
}

TEST(List_push_front, EX_2) {
  s21::list<int> a;
  a.push_front(1);
  EXPECT_EQ((a.front() == 1), 1);
}

TEST(List_size, EX_1) {
  s21::list<int> a = {1, 2, 3};
  EXPECT_EQ((a.max_size() == 4611686018427387903), 1);
}

TEST(List_swap, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 1, 1};
  s21::list<int> need = {1, 1, 1};
  s21::list<int> need_1 = {1, 2, 3};
  a.swap(b);

  EXPECT_EQ((a == need), 1);
  EXPECT_EQ((b == need_1), 1);
}

TEST(List_insert, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {1, 1, 2, 3};

  a.insert(a.begin(), 1);

  EXPECT_EQ((a == need), 1);
}

TEST(List_insert, EX_2) {
  s21::list<int> a;
  s21::list<int> need = {1};

  a.insert(a.begin(), 1);

  EXPECT_EQ((a == need), 1);
}

TEST(List_insert, EX_3) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {1, 9, 2, 3};

  a.insert(++a.begin(), 9);

  EXPECT_EQ((a == need), 1);
}

TEST(List_unique, EX_1) {
  s21::list<int> a = {1, 2, 2, 3};
  s21::list<int> need = {1, 2, 3};

  a.unique();

  EXPECT_EQ((a == need), 1);
}

TEST(List_reverse, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {3, 2, 1};

  a.reverse();

  EXPECT_EQ((a == need), 1);
}

TEST(List_reverse, EX_2) {
  s21::list<int> a;

  EXPECT_THROW(a.reverse(), std::out_of_range);
}

TEST(List_merge, EX_1) {
  s21::list<int> a;
  s21::list<int> b;

  EXPECT_THROW(a.merge(b), std::out_of_range);
}

TEST(List_merge, EX_2) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 0, 4};
  a.merge(b);

  s21::list<int> need = {0, 1, 1, 2, 3, 4};

  EXPECT_EQ((a == need), 1);
}

TEST(List_merge, EX_3) {
  s21::list<int> a;
  s21::list<int> b = {1, 0, 4};
  a.merge(b);

  s21::list<int> need = {0, 1, 4};

  EXPECT_EQ((a == need), 1);
}

TEST(List_erase, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {2, 3};
  a.erase(a.begin());

  EXPECT_EQ((a == need), 1);
}

TEST(List_erase, EX_2) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> need = {1, 3};
  a.erase(++a.begin());

  EXPECT_EQ((a == need), 1);
}

TEST(List_splice, EX_1) {
  s21::list<int> a = {1, 2, 3};
  s21::list<int> b = {9, 9, 9};
  s21::list<int> need = {1, 9, 9, 9, 2, 3};

  a.splice(++a.begin(), b);

  EXPECT_EQ((a == need), 1);
}

TEST(List_insert_many, EX_1) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many(++a.begin(), 9, 9, 9);
  s21::list<int> need = {1, 9, 9, 9, 2, 3};

  EXPECT_EQ((a == need), 1);
}

TEST(List_insert_front, EX_1) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_front(9, 9, 9);
  s21::list<int> need = {9, 9, 9, 1, 2, 3};

  EXPECT_EQ((a == need), 1);
}

TEST(List_insert_back, EX_1) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_back(9, 9, 9);
  s21::list<int> need = {1, 2, 3, 9, 9, 9};

  EXPECT_EQ((a == need), 1);
}

// VECTOR______________________________________________________________________________________________________
TEST(Create_Vector, EX_1) {
  s21::vector<int> a;
  s21::vector<int> need;
  EXPECT_EQ((a == need), 1);
}

TEST(Create_Vector, EX_2) {
  s21::vector<int> a;
  s21::vector<int> need(a);
  EXPECT_EQ((a == need), 1);
}

TEST(Vector_item, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  int need = 1;
  EXPECT_EQ((a.front() == need), 1);
}

TEST(Vector_item, EX_2) {
  s21::vector<int> a = {1, 2, 3};
  int need = 3;
  EXPECT_EQ((a.back() == need), 1);
}

TEST(Vector_item, EX_3) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ((*a.begin() == a[0]), 1);
}

TEST(Vector_item, EX_4) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ((*a.data() + 1 == a[1]), 1);
}

TEST(Vector_empty, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ((a.empty() == 0), 1);
}

TEST(Vector_size, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  EXPECT_EQ((a.max_size() == 4611686018427387903), 1);
}

TEST(Vector_swap, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> b = {1, 1, 1};
  s21::vector<int> need = {1, 1, 1};
  s21::vector<int> need_1 = {1, 2, 3};
  a.swap(b);

  EXPECT_EQ((a == need), 1);
  EXPECT_EQ((b == need_1), 1);
}

TEST(Vector_fit, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> need = {2, 2, 2};
  need.reserve(5);
  need.shrink_to_fit();
  a.reserve(5);
  a.shrink_to_fit();

  EXPECT_EQ((a.capacity() == need.capacity()), 1);
}

TEST(Vector_insert, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> need = {4, 1, 2, 3};
  a.insert(a.data(), 4);

  EXPECT_EQ((a == need), 1);
}

TEST(Vector_erase, EX_1) {
  s21::vector<int> a = {1, 2, 3};
  s21::vector<int> need = {1, 3};
  a.erase(a.data() + 1);

  EXPECT_EQ((a == need), 1);
}

TEST(Vector_pop, EX_1) {
  s21::vector<int> a;

  EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST(Vector_insert_many, EX_1) {
  s21::vector<int> a;
  s21::vector<int> need = {1, 2, 3};
  a.insert_many(a.begin(), 1, 2, 3);
  EXPECT_EQ((a == need), 1);
}

TEST(Vector_insert_many_b, EX_1) {
  s21::vector<int> a = {2, 3};
  s21::vector<int> need = {2, 3, 1, 2, 3};
  a.insert_many_back(1, 2, 3);
  EXPECT_EQ((a == need), 1);
}
// MAP______________________________________________________________________________________________________

TEST(Create_Map, EX_1) {
  s21::map<std::string, int> a;

  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_Map, EX_2) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 2}};
  s21::map<std::string, int> b(a);

  EXPECT_EQ((a == b), 1);
}

TEST(Map_max_size, EX_1) {
  s21::map<std::string, int> a;

  EXPECT_EQ((a.max_size() == 5380300354831952553), 1);
}

TEST(Map_insert, EX_1) {
  s21::map<std::string, int> a;
  s21::map<std::string, int> need = {{"m", 3}};
  a.insert({"m", 3});

  EXPECT_EQ((a == need), 1);
}

TEST(Map_insert, EX_2) {
  s21::map<std::string, int> a;
  s21::map<std::string, int> need = {{"m", 3}};
  a.insert("m", 3);

  EXPECT_EQ((a == need), 1);
}

TEST(Map_insert, EX_3) {
  s21::map<std::string, int> a;
  s21::map<std::string, int> need = {{"m", 3}};
  a["m"] = 3;

  EXPECT_EQ((a == need), 1);
}

TEST(Map_insert, EX_4) {
  s21::map<std::string, int> a = {{"m", 1}};
  s21::map<std::string, int> need = {{"m", 4}};
  a.insert_or_assign("m", 4);

  EXPECT_EQ((a == need), 1);
}

TEST(Map_insert, EX_5) {
  s21::map<std::string, int> a = {{"a", 1}};
  s21::map<std::string, int> need = {{"a", 1}, {"m", 4}};
  a.insert_or_assign("m", 4);

  EXPECT_EQ((a == need), 1);
}

TEST(Map_swap, EX_1) {
  s21::map<std::string, int> a = {{"a", 1}};
  s21::map<std::string, int> b = {{"b", 1}};
  a.swap(b);
  s21::map<std::string, int> need = {{"a", 1}};
  s21::map<std::string, int> need_1 = {{"b", 1}};

  EXPECT_EQ((a == need_1), 1);
  EXPECT_EQ((b == need), 1);
}

TEST(Map_erase, EX_1) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 3}};
  s21::map<std::string, int> need = {{"a", 1}};
  a.erase(a.last());

  EXPECT_EQ((a == need), 1);
}

TEST(Map_merge, EX_1) {
  s21::map<std::string, int> a = {{"a", 1}, {"j", 3}};
  s21::map<std::string, int> b = {{"b", 1}};
  a.merge(b);
  s21::map<std::string, int> need = {{"a", 1}, {"b", 1}, {"j", 3}};

  EXPECT_EQ((a == need), 1);
}

TEST(Map_contains, EX_1) {
  s21::map<std::string, int> a = {{"a", 1}, {"b", 3}};

  EXPECT_EQ(a.contains("a"), 1);
}

TEST(Map_insert_many, EX_1) {
  s21::map<std::string, int> a = {{"m", 1}};
  s21::map<std::string, int> need = {{"m", 1}, {"a", 2}, {"b", 2}};
  a.insert_many(std::make_pair("m", 1), std::make_pair("a", 2),
                std::make_pair("b", 2));

  EXPECT_EQ((a == need), 1);
}

// SET______________________________________________________________________________________________________

TEST(Create_Set, EX_1) {
  s21::set<int> a;
  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_Set, EX_2) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b(a);

  EXPECT_EQ((a == b), 1);
}

TEST(Set_max_size, EX_1) {
  s21::set<int> a;

  EXPECT_EQ((a.max_size() == 4611686018427387903), 1);
}

TEST(Set_insert, EX_1) {
  s21::set<int> a;
  s21::set<int> need = {1};
  a.insert(1);

  EXPECT_EQ((a == need), 1);
}

TEST(Set_insert, EX_2) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> need = {1, 2, 3, 9};
  a.insert(9);

  EXPECT_EQ((a == need), 1);
}

TEST(Set_swap, EX_1) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> b = {4, 5, 6};
  a.swap(b);
  s21::set<int> need = {1, 2, 3};
  s21::set<int> need_1 = {4, 5, 6};

  EXPECT_EQ((a == need_1), 1);
  EXPECT_EQ((b == need), 1);
}

TEST(Set_erase, EX_1) {
  s21::set<int> a = {5, 6};
  s21::set<int> need = {5};
  a.erase(a.last());

  EXPECT_EQ((a == need), 1);
}

TEST(Set_merge, EX_1) {
  s21::set<int> a = {4, 5, 6};
  s21::set<int> b = {12, 3, 4};
  a.merge(b);
  s21::set<int> need = {4, 5, 6, 12, 3, 4};

  EXPECT_EQ((a == need), 1);
}

TEST(Set_contains, EX_1) {
  s21::set<int> a = {1, 2, 55, 6};

  EXPECT_EQ(a.contains(55), 1);
}

TEST(Set_insert_many, EX_1) {
  s21::set<int> a = {1, 2, 3};
  s21::set<int> need = {1, 2, 3, 11, 22, 33};
  a.insert_many(11, 22, 33);

  EXPECT_EQ((a == need), 1);
}

// MULTISETSET______________________________________________________________________________________________________

TEST(Create_Multiset, EX_1) {
  s21::multiset<int> a;
  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_Multiset, EX_2) {
  s21::multiset<int> a = {1, 2, 3};
  s21::multiset<int> b(a);

  EXPECT_EQ((a == b), 1);
}

TEST(Multiset_max_size, EX_1) {
  s21::multiset<int> a;

  EXPECT_EQ((a.max_size() == 4611686018427387903), 1);
}

TEST(Multiset_insert, EX_1) {
  s21::multiset<int> a;
  s21::multiset<int> need = {1};
  a.insert(1);

  EXPECT_EQ((a == need), 1);
}

TEST(Multiset_insert, EX_2) {
  s21::multiset<int> a = {1, 2, 3};
  s21::multiset<int> need = {1, 2, 3, 9};
  a.insert(9);

  EXPECT_EQ((a == need), 1);
}

TEST(Multiset_swap, EX_1) {
  s21::multiset<int> a = {1, 2, 3};
  s21::multiset<int> b = {4, 5, 6};
  a.swap(b);
  s21::multiset<int> need = {1, 2, 3};
  s21::multiset<int> need_1 = {4, 5, 6};

  EXPECT_EQ((a == need_1), 1);
  EXPECT_EQ((b == need), 1);
}

TEST(Multiset_erase, EX_1) {
  s21::multiset<int> a = {5, 6};
  s21::multiset<int> need = {5};
  a.erase(a.last());

  EXPECT_EQ((a == need), 1);
}

TEST(Multiset_merge, EX_1) {
  s21::multiset<int> a = {4, 5, 6};
  s21::multiset<int> b = {12, 3, 4};
  a.merge(b);
  s21::multiset<int> need = {4, 5, 6, 12, 3, 4};

  EXPECT_EQ((a == need), 1);
}

TEST(Multiset_contains, EX_1) {
  s21::multiset<int> a = {1, 2, 55, 6};

  EXPECT_EQ(a.contains(55), 1);
}

TEST(Multiset_insert_many, EX_1) {
  s21::multiset<int> a = {1, 2, 3};
  s21::multiset<int> need = {1, 2, 3, 11, 22, 33};
  a.insert_many(11, 22, 33);

  EXPECT_EQ((a == need), 1);
}

TEST(Multiset_eq_range, EX_1) {
  s21::multiset<int> a = {1, 2, 2, 2, 6};

  EXPECT_EQ((*a.equal_range(2).first == 2), 1);
  EXPECT_EQ((*a.equal_range(2).second == 6), 1);
}

TEST(Multiset_lower_bound, EX_1) {
  s21::multiset<int> a = {1, 2, 2, 2, 6};

  EXPECT_EQ((*a.lower_bound(2) == 2), 1);
}

TEST(Multiset_lower_bound, EX_2) {
  s21::multiset<int> a = {1, 2, 2, 2, 6};

  EXPECT_EQ((*a.lower_bound(3) == 6), 1);
}

TEST(Multiset_upper_bound, EX_1) {
  s21::multiset<int> a = {1, 2, 2, 2, 6};

  EXPECT_EQ((*a.upper_bound(2) == 6), 1);
}

TEST(Multiset_upper_bound, EX_2) {
  s21::multiset<int> a = {1, 2, 2, 2, 6};

  EXPECT_EQ((*a.upper_bound(7) == 1), 1);
}

// STACK______________________________________________________________________________________________________
TEST(Create_Stack, EX_1) {
  s21::stack<int> a;

  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_Stack, EX_2) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b(a);
  s21::stack<int> need = {3, 2, 1};

  EXPECT_EQ((need == b), 1);
}

TEST(Stack_pop, EX_1) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> need = {1, 2};
  a.pop();

  EXPECT_EQ((need == a), 1);
}

TEST(Stack_pop, EX_2) {
  s21::stack<int> a;
  EXPECT_THROW(a.pop(), std::out_of_range);
}

TEST(Stack_push, EX_1) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> need = {1, 2, 3, 4};
  a.push(4);
  EXPECT_EQ((need == a), 1);
}

TEST(Stack_swap, EX_1) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> b = {4, 5, 6};

  s21::stack<int> need = {1, 2, 3};
  s21::stack<int> need_1 = {4, 5, 6};
  a.swap(b);

  EXPECT_EQ((need_1 == a), 1);
  EXPECT_EQ((need == b), 1);
}

TEST(Stack_insert_many, EX_1) {
  s21::stack<int> a = {1, 2, 3};
  s21::stack<int> need = {1, 2, 3, 4, 5, 6};

  a.insert_many_front(4, 5, 6);

  EXPECT_EQ((need == a), 1);
}

// QUEUE______________________________________________________________________________________________________
TEST(Create_Queue, EX_1) {
  s21::queue<int> a;

  EXPECT_EQ((a.size() == 0), 1);
}

TEST(Create_Queue, EX_2) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b(a);

  EXPECT_EQ((a == b), 1);
}

TEST(Queue_pop, EX_1) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> need = {2, 3};
  a.pop();

  EXPECT_EQ((need == a), 1);
}

TEST(Queue_pop, EX_2) {
  s21::queue<int> a;
  EXPECT_THROW(a.pop(), std::out_of_range);
}

TEST(Queue_push, EX_1) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> need = {1, 2, 3, 4};
  a.push(4);
  EXPECT_EQ((need == a), 1);
}

TEST(Queue_swap, EX_1) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> b = {4, 5, 6};

  s21::queue<int> need = {1, 2, 3};
  s21::queue<int> need_1 = {4, 5, 6};
  a.swap(b);

  EXPECT_EQ((need_1 == a), 1);
  EXPECT_EQ((need == b), 1);
}

TEST(Queue_insert_many, EX_1) {
  s21::queue<int> a = {1, 2, 3};
  s21::queue<int> need = {1, 2, 3, 4, 5, 6};

  a.insert_many_back(4, 5, 6);

  EXPECT_EQ((need == a), 1);
}
