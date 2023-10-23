#include <sys/types.h>
#include <unistd.h>
#include<sys/syscall.h>
#include"Rocket/common/util.h"

//实现 进程号获取和线程号获取
namespace Rocket
{

    static int g_pid = 0;
    static thread_local int  g_thread_id = 0;

    pid_t getPid() {
        if (g_pid != 0) {
            return g_pid;
        }
        return getpid();
    }

    pid_t getThreadId() {
        if (g_thread_id != 0) {
            return g_thread_id;
        }
        return syscall(SYS_gettid); //这段代码中使用了syscall(SYS_gettid)来获取线程ID，这是Linux特有的系统调用。
    }

}
