# 瑞萨RA4M2单片机LED项目完整开发指南

本项目使用RASC（瑞萨高级配置器）生成，支持RA4M2 (R7FA4M2AD) ARM Cortex-M33微控制器。

## 环境要求和软件安装

### 必需软件

#### 1. ARM交叉编译工具链
```bash
# Ubuntu/Debian安装命令
sudo apt update
sudo apt install gcc-arm-none-eabi

# 验证安装
arm-none-eabi-gcc --version
```
- **版本要求**: GCC 9.0+ (推荐14.2.0)
- **作用**: 编译ARM单片机代码
- **验证**: `arm-none-eabi-gcc --version` 显示版本信息

#### 2. CMake构建系统
```bash
# Ubuntu/Debian安装命令
sudo apt install cmake

# 验证版本 (需要3.16.4+)
cmake --version
```
- **版本要求**: 3.16.4或更高
- **作用**: 生成本地构建文件
- **验证**: `cmake --version`

#### 3. Ninja构建工具
```bash
# Ubuntu/Debian安装命令
sudo apt install ninja-build

# 验证安装
ninja --version
```
- **作用**: 快速构建工具，替代Make
- **验证**: `ninja --version`

#### 4. Renesas Flash Programmer (RFP)
```bash
# 下载地址
https://www.renesas.com/software-tool/renesas-flash-programmer-programming-gui

# 安装命令行工具
# 从下载的包中安装rfp-cli

# 验证安装
rfp-cli --help
```
- **版本**: V3.21.00.000 (推荐最新)
- **作用**: 烧录固件到RA单片机
- **验证**: `rfp-cli --help` 显示帮助信息

#### 5. Renesas Advanced Software Configurator (RASC)
```bash
# 下载地址
https://www.renesas.com/software-tool/ras-advanced-software-configurator

# 安装后验证
rasc --version
```
- **作用**: 配置MCU引脚、时钟、外设
- **GUI界面**: 可视化配置RA系列参数

### 环境变量配置

#### 临时设置 (每次启动终端)
```bash
# 设置ARM工具链路径
export ARM_TOOLCHAIN_PATH="/usr/sbin"

# 验证设置
echo $ARM_TOOLCHAIN_PATH
```

#### 永久设置 (~/.bashrc)
```bash
# 编辑bashrc文件
echo 'export ARM_TOOLCHAIN_PATH="/usr/sbin"' >> ~/.bashrc

# 重新加载配置
source ~/.bashrc

# 验证
echo $ARM_TOOLCHAIN_PATH
```

## 项目构建流程

### 1. 配置项目 (首次或修改CMakeLists.txt时)

#### Debug版本配置
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/gcc.cmake \
      -DCMAKE_BUILD_TYPE=Debug \
      -G Ninja \
      -B build/debug
```

#### Release版本配置
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/gcc.cmake \
      -DCMAKE_BUILD_TYPE=Release \
      -G Ninja \
      -B build/release
```

**配置参数说明**:
- `DCMAKE_TOOLCHAIN_FILE`: 指定RASC生成的工具链配置
- `DCMAKE_BUILD_TYPE`: 构建类型 (Debug/Release)
- `-G Ninja`: 使用Ninja构建系统
- `-B build/debug`: 指定构建输出目录

### 2. 编译项目 (每次修改代码后)

#### Debug编译
```bash
cmake --build build/debug
```

#### Release编译
```bash
cmake --build build/release
```

**输出文件位置**: `build/debug/` 或 `build/release/`
- `LED.elf`: 可执行文件 (ARM格式)
- `LED.map`: 内存映射文件
- `LED.srec`: Motorola S-record格式 (瑞萨原生支持)
- `LED.hex`: Intel HEX格式 (如需要转换)

## 文件格式转换

### ELF转Intel HEX (如需要)
```bash
# 基本转换
arm-none-eabi-objcopy -O ihex build/debug/LED.elf build/debug/LED.hex

# 验证转换结果
ls -la build/debug/LED.hex
```

### ELF转S-record (瑞萨推荐)
```bash
# 生成S-record格式
arm-none-eabi-objcopy -O srec build/debug/LED.elf build/debug/LED.srec

# 验证转换结果
ls -la build/debug/LED.srec
```

### 转换高级选项
```bash
# 带填充的转换 (填充空白区域为0xFF)
arm-none-eabi-objcopy -O ihex \
    --gap-fill=0xFF \
    build/debug/LED.elf \
    build/debug/LED.hex
```

## 固件烧录流程

### 1. 硬件连接
- **USB连接**: 使用Type-C连接开发板到PC
- **调试模式**: 确保开发板处于烧录模式
- **串口识别**: 通常识别为`/dev/ttyUSB0`

### 2. 检查连接状态
```bash
# 检查可用设备
rfp-cli -device RA -lt

# 检查串口
rfp-cli -device RA -lp

# 检查设备签名 (验证连接)
rfp-cli -device RA -port /dev/ttyUSB0 -sig
```

### 3. 烧录固件

#### 使用S-record格式 (推荐)
```bash
rfp-cli -device RA \
        -port /dev/ttyUSB0 \
        -auto \
        -file build/debug/LED.srec \
        -run
```

#### 使用Intel HEX格式
```bash
rfp-cli -device RA \
        -port /dev/ttyUSB0 \
        -auto \
        -file build/debug/LED.hex \
        -run
```

#### 完整烧录命令 (带验证)
```bash
rfp-cli -device RA \
        -port /dev/ttyUSB0 \
        -erase \
        -program \
        -verify \
        -file build/debug/LED.srec \
        -run
```

**参数说明**:
- `-device RA`: 指定RA系列设备
- `-port /dev/ttyUSB0`: 指定串口
- `-auto`: 自动执行擦除、编程、验证
- `-file`: 指定固件文件
- `-run`: 烧录完成后运行设备

## 开发调试流程

### 1. LED控制代码配置

#### RASC配置步骤
1. **启动RASC**: 运行`cmake --build build/debug --target open_rasc_LED`
2. **选择引脚**: 在Pin Configuration中找到P1_11
3. **配置GPIO**: 设置为Output模式
4. **设置初始电平**: 根据LED极性设置High/Low
5. **生成代码**: 点击"Generate Project Content"

#### 代码示例 (hal_entry.c)
```c
#include "hal_data.h"

void hal_entry(void)
{
    // 初始化IOPORT
    g_common_init();
    
    // LED闪烁循环
    while(1)
    {
        // 熄灭LED (根据实际极性调整)
        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_LOW);
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
        
        // 点亮LED
        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_HIGH);
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
    }
}
```

### 2. 常见问题排查

#### LED不亮
1. **检查引脚配置**: 确认P111在RASC中配置为GPIO输出
2. **检查硬件连接**: 用万用表测量P111引脚电平变化
3. **检查LED极性**: 确认高电平点亮还是低电平点亮
4. **检查限流电阻**: 通常需要220Ω-1kΩ电阻

#### 烧录失败
1. **检查串口权限**: 确保用户有访问`/dev/ttyUSB0`权限
2. **检查设备连接**: 确认开发板正确连接并进入烧录模式
3. **检查文件格式**: 使用S-record格式更稳定

#### 编译错误
1. **检查工具链路径**: 确认`ARM_TOOLCHAIN_PATH`环境变量正确设置
2. **清理重建**: 删除build目录后重新配置
3. **检查RASC配置**: 确认外设配置无冲突

## VS Code集成

### 配置步骤
1. **安装扩展**: C/C++, CMake Tools, Cortex-Debug
2. **设置工具链**: 在settings.json中配置ARM_GCC_TOOLCHAIN_PATH
3. **选择Kit**: 选择"ARM GCC kit with toolchainFile"
4. **配置构建**: 设置build目录为`build/${buildType}`

### 调试配置 (launch.json)
```json
{
    "type": "renesas-hardware",
    "request": "launch", 
    "target": {
        "device": "R7FA4M2AD",
        "deviceFamily": "RA",
        "debuggerType": "SEGGERJLINKARM"
    },
    "cwd": "${command:renesas.debug.supportFolder}"
}
```

## 项目结构说明

```
LED/
├── src/                    # 用户源代码
│   ├── hal_entry.c         # 用户入口函数
│   └── hal_warmstart.c    # 热启动代码
├── ra_gen/                # RASC生成文件 (不可编辑)
│   ├── main.c            # 主函数入口
│   ├── hal_data.c/.h     # HAL数据结构
│   ├── common_data.c/.h   # 通用数据结构
│   ├── pin_data.c        # 引脚配置数据
│   └── vector_data.c/.h  # 中断向量表
├── ra_cfg/               # RASC配置文件 (不可编辑)
│   └── fsp_cfg/         # FSP配置头文件
├── cmake/               # CMake配置
│   ├── gcc.cmake         # 工具链配置
│   ├── GeneratedCfg.cmake # RASC生成配置
│   └── GeneratedSrc.cmake # 源文件配置
├── build/               # 构建输出目录
│   └── debug/           # Debug版本输出
└── configuration.xml     # RASC项目配置文件
```

## 版本信息

- **MCU**: R7FA4M2AD (Cortex-M33, 100MHz)
- **FSP版本**: V6.2.0+
- **工具链**: ARM GCC 14.2.0
- **构建系统**: CMake 3.16.4 + Ninja
- **烧录工具**: Renesas Flash Programmer V3.21+

## 联系和支持

- **Renesas官网**: https://www.renesas.com
- **FSP文档**: https://renesas.github.io/fsp/
- **社区支持**: https://community.renesas.com/
- **问题反馈**: 通过GitHub Issues或Renesas社区