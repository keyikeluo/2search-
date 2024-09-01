#include <iostream>
#include <vector>
#include <stack>

// 模拟栈类
class SimulatedStack {
private:
    std::stack<int> stack;
    int max_size;

public:
    SimulatedStack() : max_size(0) {}

    void push(int value) {
        stack.push(value);
        if (stack.size() > max_size) {
            max_size = stack.size();
        }
        std::cout << "Push: " << value << ", Stack size: " << stack.size() << std::endl;
    }

    int pop() {
        if (stack.empty()) {
            throw std::runtime_error("Pop from empty stack");
        }
        int value = stack.top();
        stack.pop();
        std::cout << "Pop: " << value << ", Stack size: " << stack.size() << std::endl;
        return value;
    }

    int getMaxSize() const {
        return max_size;
    }

    bool empty() const {
        return stack.empty();
    }
};

// 二分搜索递归函数
int binarySearch(std::vector<int>& arr, int left, int right, int x, SimulatedStack& simulatedStack, int& steps) {
    simulatedStack.push(left);
    simulatedStack.push(right);

    steps++;
    if (right >= left) {
        int mid = left + (right - left) / 2;
        std::cout << "Step " << steps << ": Searching in range [" << left << ", " << right << "], mid: " << mid << std::endl;

        // 如果元素刚好在中间位置
        if (arr[mid] == x) {
            simulatedStack.pop();
            simulatedStack.pop();
            return mid;
        }

        // 如果元素在中间位置的左边
        if (arr[mid] > x) {
            int result = binarySearch(arr, left, mid - 1, x, simulatedStack, steps);
            simulatedStack.pop();
            simulatedStack.pop();
            return result;
        }

        // 如果元素在中间位置的右边
        int result = binarySearch(arr, mid + 1, right, x, simulatedStack, steps);
        simulatedStack.pop();
        simulatedStack.pop();
        return result;
    }

    simulatedStack.pop();
    simulatedStack.pop();
    // 如果元素不存在于数组中
    return -1;
}

int main() {
    std::vector<int> arr = { 2, 3, 4, 10, 40 };
    int x = 1;
    int steps = 0;
    SimulatedStack simulatedStack;

    int result = binarySearch(arr, 0, arr.size() - 1, x, simulatedStack, steps);

    std::cout << "Element " << x << (result != -1 ? " found at index " : " not found, search failed at index ") << result << std::endl;
    std::cout << "Total steps: " << steps << std::endl;
    std::cout << "Maximum stack size: " << simulatedStack.getMaxSize() << std::endl;

    return 0;
}
