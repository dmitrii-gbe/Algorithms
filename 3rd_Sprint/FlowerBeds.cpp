#include <vector> 
#include <iostream> 
#include <algorithm> 
#include <tuple> 
 
struct Section { 
    Section(int l, int r){ 
        left = l; 
        right = r; 
    } 
    Section() = default; 
     
 int left = 0; 
 int right = 0; 
}; 
 
bool operator<(const Section& l, const Section& r) { 
 return std::tie(l.left, l.right) < std::tie(r.left, r.right); 
} 
 
std::ostream& operator<<(std::ostream& out, const Section& sec){ 
 out << sec.left << " " << sec.right;  
 return out; 
} 
 
template <typename T> 
std::ostream& operator<<(std::ostream& out, const std::vector<T> v){ 
 bool is_first = true; 
 for (auto it = v.begin(); it != v.end(); ++it){ 
  if (is_first){ 
   std::cout << *it; 
   is_first = false; 
  } 
  else { 
   std::cout << '\n' << *it; 
  } 
 } 
 return out; 
} 
 
enum class IntersectionType { 
 PARTIAL, 
 FULL_HIGH, 
 FULL_LOW, 
 NO 
}; 
 
IntersectionType IfIntersect(const Section& l, const Section& r){ 
 if (l.left <= r.left && l.right >= r.right){ 
  return IntersectionType::FULL_LOW; 
 } 
 if (l.left == r.left && l.right < r.right){ 
     return IntersectionType::FULL_HIGH; 
 } 
 if (l.right < r.left){ 
  return IntersectionType::NO; 
 } 
 if (l.right >= r.left && l.right < r.right) { 
  return IntersectionType::PARTIAL; 
 } 
 else { 
     return IntersectionType::FULL_LOW; 
 } 
} 
 
std::vector<Section> CollapseSections(std::vector<Section>& v){ 
 std::vector<Section> tmp; 
 std::sort(v.begin(), v.end()); 
 tmp.push_back(v[0]); 
 for (size_t i = 1; i < v.size(); ++i){ 
  if (IfIntersect(tmp.back(), v[i]) == IntersectionType::NO){ 
   tmp.push_back(v[i]); 
  } 
  else if (IfIntersect(tmp.back(), v[i]) == IntersectionType::PARTIAL){ 
   Section s(tmp.back().left, v[i].right); 
   tmp.pop_back(); 
   tmp.push_back(s); 
  } 
  else if (IfIntersect(tmp.back(), v[i]) == IntersectionType::FULL_LOW) { 
  } 
  else { 
      tmp.pop_back(); 
      tmp.push_back(v[i]); 
  } 
 } 
 return tmp; 
} 
 
int main(){ 
 int counter = 0; 
 std::cin >> counter; 
 std::vector<Section> storage(counter); 
 while (counter > 0){ 
  int left, right; 
  std::cin >> left >> right; 
  storage[counter - 1] = Section(left, right); 
  --counter; 
 } 
  
 std::vector<Section> result = CollapseSections(storage); 
 std::cout << result; 
 return 0; 
}}
