#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

struct Interval {
    double start = 0;
    double end = 0;
};

std::ostream& operator<<(std::ostream& out, const Interval& i) {
    out << i.start << " " << i.end << '\n';
    return out;
}

std::vector<Interval> GetIntervals(size_t n) {
    std::vector<Interval> result(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> result[i].start >> result[i].end;
    }
    return result;
}

bool IfNotIntersect(const Interval& lhs, const Interval& rhs) {
    return lhs.end <= rhs.start || lhs.start == rhs.end || rhs.start == rhs.end;
}

std::vector<Interval> GetOptimalIntervals(std::vector<Interval>& intervals) {
    std::sort(intervals.begin(), intervals.end(), [](const Interval& lhs, const Interval& rhs) {
        return std::tuple(lhs.end, lhs.start) < std::tuple(rhs.end, rhs.start);
    });
    std::vector<Interval> result;
    result.reserve(intervals.size());
    result.push_back(intervals.front());
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (IfNotIntersect(result.back(), intervals[i])) {
            result.push_back(intervals[i]);
        }
    }
    return result;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    auto intervals = GetIntervals(n);
    auto result = GetOptimalIntervals(intervals);
    std::cout << result.size() << '\n';
    for (auto it = result.begin(), end = result.end(); it != end; ++it) {
        std::cout << *it;
    }

    return 0;
}
