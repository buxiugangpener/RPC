#ifndef ROCKET_COMMON_UTIL
#define ROCKET_COMMON_UTIL
#include <sys/types.h>
#include <unistd.h>


namespace Rocket {
	//��ȡ���̺ź��̺߳�

	//����ӿ�
	pid_t getPid();
	pid_t getThreadId();

}
#endif