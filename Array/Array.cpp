#include <iostream>
#include <array>  // 静态数组头文件


// 静态数组
int main() {
    // 初始化
    std::array<int, 5> arr1;  // 声明并默认初始化一个大小为 5 的整型数组（值未定义）
    
    std::array<int, 5> arr2 = {1, 2, 3};  // 声明一个大小为 5 的整型数组，并部分初始化，剩余为 0
    
    std::array<int, 5> arr3 = {1, 2, 3, 4, 5};  // 声明一个大小为 5 的整型数组，并统一初始化
    
    std::array<int, 5> arr4 = arr2;  // 复制 arr2 给 arr4

    std::array<std::array<int, 4>, 3> arr2D = {1, 2, 3};  // 声明一个 3 行 4 列的二维数组，并部分初始化，剩余为 0 。遵循行优先原则
    
    

    // 获取数组大小
    std::cout << "数组 arr3 的大小为：" << arr3.size() << std::endl;



    // 判空
    std::cout << "数组 arr3 是否为空: " << arr3.empty() << std::endl;



    // 访问元素
    // 无边界检查访问
    int value1 = arr3[2];
    std::cout << "无边界检查访问数组 arr3 的第三个元素为：" << value1 << std::endl;  // 3
    
    int val2D1 = arr2D[0][1];
    std::cout << "无边界检查访问数组 arr2D 的第一行第二列的元素：" << val2D1 << std::endl;  // 2

    // 有边界检查访问
    int value2 = arr3.at(4);
    std::cout << "有边界检查访问数组 arr3 的第五个元素为：" << value2 << std::endl;  // 5

    // 有边界检查访问 越界 抛出std::out_of_range
    // int value3 = arr3.at(5);
    // try {
    //     std::cout << "有边界检查访问数组 arr3 的第六个元素（越界）为：" << value3 << std::endl;  // 抛出std::out_of_range
    // }
    // catch(const std::out_of_range& e) {
    //     std::cerr << "Error: " << e.what();
    // }

    int val2D2 = arr2D.at(0).at(1);
    std::cout << "有边界检查访问数组 arr2D 的第一行第二列的元素：" << val2D2 << std::endl;
    
    // 访问第一个元素
    int front = arr3.front();
    std::cout << "数组 arr3 的第一个元素为：" << front << std::endl;

    // 访问最后一个元素
    int back = arr3.back();
    std::cout << "数组 arr3 的最后一个元素为：" << back << std::endl;
    

    // 使用指针访问元素
    int* ptr = arr3.data();  // 获取底层数组指针 获取第一个元素的地址
    std::cout << "数组 arr3 的底层数组指针为: " << ptr << std::endl;

    int value4 = *(ptr + 2);  // 获取第三个元素的值
    std::cout << "指针访问数组 arr3 的第三个元素：" << value4 << std::endl;
    
    
    // 范围for循环数组
    std::cout << "数组 arr3 为：";
    for(int num : arr3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "数组 arr2D 为：" << std::endl;
    for(const auto& row : arr2D) {
        for(const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }



    // 修改元素
    // 无边界检查访问，修改数组 arr3 的第三个元素为 10
    arr3[2] = 10;
    
    // 无边界检查访问，修改数组 arr2D 的第一行第二个元素为 10
    arr2D[0][1] = 10;


    // 有边界检查访问，修改数组 arr3 的第四个元素为 20
    arr3.at(3) = 20;

    // 有边界检查访问，修改数组 arr2D 的二行第三列元素为 20
    arr2D.at(1).at(2) = 20;


    // 填充元素
    arr2.fill(2);  // 把所有元素都赋值为 2


    // 交换内容
    arr1.swap(arr2);  // 交换两个同类型数组，交换数组 arr1 和 数组 arr2 的内容



}