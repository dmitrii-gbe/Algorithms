template <typename It>
void QuickSortInPlace(It first, It last){
    if (last - first < 2){
        return;
    }
    else {
        typename std::iterator_traits<It>::value_type pivot = *(first + GetRandomIndex(last - first - 1));
        It left = first;
        It right = std::prev(last);
        while (right >= left){
            if (*left >= pivot && *right <= pivot){
                std::swap(*left, *right);
                ++left;
                --right;
            }
            else if (*left < pivot && *right <= pivot){
                ++left;
            }
            else if (*left >= pivot && *right > pivot){
                --right;
            }
            else {
                ++left;
                --right;
            }
        }
        QuickSortInPlace(first, left);
        QuickSortInPlace(left, last);
    }
}
