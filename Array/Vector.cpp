#include <iostream>
#include <vector>


// 动态数组
int main() {
    // 初始化
    std::vector<int> vec1;  // 声明一个空 vector

    std::vector<int> vec2(5, 3);  // 声明一个动态数组，并初始化大小为 5 ，且都为 3

    std::vector<int> vec3(vec2);  // 把 vec2 复制给 vec3

    // 声明并初始化一个二维动态数组
    std::vector<std::vector<int>> vec2D = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 声明一个三行四列的数组
    std::vector<std::vector<int>> matrix(3, std::vector<int>(4));



    // 获取当前元素数量
    std::cout << "vec2 的元素数量为：" << vec2.size() << std::endl;



    // 获取当前数组容量
    std::cout << "vec2 的数组容量为：" << vec2.capacity() << std::endl;



    // 判空
    std::cout << "vec2 是否为空：" << vec2.empty() << std::endl;


    
    // 访问元素
    // 无边界检查访问
    std::cout << "无边界检查访问数组 vec2 的第一个元素: " << vec2[0] << std::endl;
    
    std::cout << "无边界检查访问数组 vec2D 的第一行第二列元素：" << vec2D[0][1] << std::endl;


    // 有边界检查访问
    std::cout << "有边界检查访问数组 vec2 的第2个元素: " << vec2.at(1) << std::endl;
    
    std::cout << "有边界检查访问数组 vec2D 的第一行第二列元素：" << vec2D.at(0).at(1) << std::endl;

    // try {  // 越界访问
    //     std::cout << "越界访问 vec2 的第 10 个元素：" << vec2.at(9) << std::endl;

    //     std::cout << "越界访问 vec2D 的第六行第七列的元素：" << vec2D.at(5).at(6) << std::endl;
    // }
    // catch(const std::out_of_range& e) {
    //     std::cerr << "错误：" << e.what();
    // }

    // 指针访问
    int* ptr = vec2.data();  // 获取 vec2 的底层数组指针
    std::cout << "vec2 的底层数组指针为：" << ptr << std::endl;
    std::cout << "用指针访问 vec2 的第三个元素：" << *(ptr + 2) << std::endl;

    // 范围for循环数组
    std::cout << "输出 vec2 数组：";
    for(int num : vec2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "输出 vec2D 数组：" << std::endl;
    for(const auto& row : vec2D) {
        for(const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }



    // 修改元素
    // 无边界检查，修改数组 vec2 的第三个元素为 10
    vec2[2] = 10;

    // 无边界检查，修改数组 vec2D 的第一行第三列元素为 10
    vec2D[0][2] = 10;

    // 有边界检查，修改数组 vec2 的第一个元素为 9
    vec2.at(0) = 9;

    // 有边界检查，修改数组 vec2D 的第一行第一列元素为 11
    vec2D.at(0).at(0) = 11;



    // 添加元素
    vec2.push_back(4);  // 尾部添加
    vec2.emplace_back(5);  // 尾部添加（更高效）
    vec2.insert(vec2.begin() + 1, 10);  // 在第二个位置插入 10



    // 删除元素
    vec2.pop_back();  // 删除尾部元素
    vec2.erase(vec2.begin() + 2);  // 删除第三个元素
    vec2.erase(vec2.begin(), vec2.begin() + 2);  // 删除第一个到第三个元素
    vec2.clear();  // 清空所有元素



    // 交换内容
    vec2.swap(vec1);  // 把 vec2 和 vec1 的内容交换
}