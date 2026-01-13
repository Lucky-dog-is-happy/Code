#include <stdio.h>

// # 字符化
// ## 连接符
#define LOG_INFO(x, ...) printf("%s:%s:%d:"x"", \
	__FILE__, \
	__FUNCTION__, \
	__LINE__, \
	##__VA_ARGS__)
#define DAY_DECLARE(x) int day##x
#define DAY(x) day##x

int main(int argc, char **argv)
{
	int a=10;

	DAY_DECLARE(1) = 100;
	DAY_DECLARE(10) = 200;
	LOG_INFO("DAY1 = %d \n", DAY(1));
	LOG_INFO("DAY10 = %d \n", DAY(10));
	LOG_INFO("%s is %d \n", "a", a);

	return 0;
}
