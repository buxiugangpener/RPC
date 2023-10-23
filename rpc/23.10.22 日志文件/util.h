#ifndef ROCKET_COMMON_UTIL
#define ROCKET_COMMON_UTIL
#include <sys/types.h>
#include <unistd.h>


namespace Rocket {
	//获取进程号和线程号

	//定义接口
	pid_t getPid();
	pid_t getThreadId();

}
#endif