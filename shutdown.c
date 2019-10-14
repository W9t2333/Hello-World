#include <Windows.h>
//强制关闭计算机
BOOL systemShutDown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	//获取进程标志
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return FALSE;
	}
	//获取关机特权的LUID
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//获取这个进程的关机特权
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		return FALSE;
	}
	// 强制关闭计算机
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)) {
		return FALSE;
	}
	return TRUE;
	// 强制重启计算机
	//if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))
		//return FALSE;
	//return TRUE;
}

int main() {
	systemShutDown();
	return 0;
}
