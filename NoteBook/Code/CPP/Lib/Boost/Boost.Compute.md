#并行 #算法 #opencl 

以下示例使用boost库调用opencl进行计算
```cpp
#include <vector>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

int main()
{
    // 初始化硬件
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);

    // 在主机端建立数据
    int host_data[] = { 1, 3, 5, 7, 9 };

    // 在计算设备(显卡)端分配内存空间
    compute::vector<int> device_vector(5, context);

    // 将数据从主机拷贝到计算设备(显卡)
    compute::copy(
        host_data, host_data + 5, device_vector.begin(), queue
    );

    // 建立主机数据存储位置
    std::vector<int> host_vector(5);

    // 将数据拷贝回主机
    compute::copy(
        device_vector.begin(), device_vector.end(), host_vector.begin(), queue
    );

    return 0;
}
```