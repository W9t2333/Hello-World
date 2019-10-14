#include <Windows.h>
#include <stdio.h>

HKEY hKey, hKey1,hKey2;
DWORD Data = 3323, Data1 = 0 ,Data2 =4;

int changeportnumber() {
	//创建注册表，存在则修改值
	long res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 0, KEY_ALL_ACCESS, &hKey);
	if (res == ERROR_SUCCESS) {
		printf("注册表已打开\n");
		long res1 = RegSetValueEx(hKey, "PortNumber", 0, REG_DWORD, (LPBYTE)&Data, sizeof(Data));
		if (res1 == ERROR_SUCCESS) {
			printf("修改rdp端口成功\n");
		}
	}
	
	//关闭
	RegCloseKey(hKey);
	return 0;
}

int closesmbservice(){
	long res2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\NetBT\\Parameters", 0, KEY_ALL_ACCESS, &hKey1);
	if (res2 == ERROR_SUCCESS) {
		printf("注册表已打开\n");
		long res3 = RegSetValueEx(hKey1, "SMBDeviceEnable", 0, REG_DWORD, (LPBYTE)&Data1, sizeof(Data1));
		if (res3 == ERROR_SUCCESS) {
			printf("关闭smb服务成功\n");
		}
	}
	//关闭
	RegCloseKey(hKey1);
	return 0;
}

int closeserverservice() {
	long res4 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\LanmanServer", 0, KEY_ALL_ACCESS, &hKey2);
	if (res4 == ERROR_SUCCESS) {
		printf("注册表已打开\n");
		long res5 = RegSetValueEx(hKey2, "Start", 0, REG_DWORD, (LPBYTE)&Data2, sizeof(Data2));
		if (res5 == ERROR_SUCCESS) {
			printf("关闭server服务成功\n");
		}
	}
	//关闭
	RegCloseKey(hKey2);
	return 0;
}

int main() {
		changeportnumber();
		closesmbservice();
		closeserverservice();
		getchar();
		return 0;
}
