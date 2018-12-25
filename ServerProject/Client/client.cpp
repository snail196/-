#define WIN32_LEAN_AND_MEAN

#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	//����Windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//------------
	//-- ��Socket API��������TCP�ͻ���
	// 1 ����һ��socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("���󣬽���Socketʧ��...\n");
	}
	else {
		printf("����Socket�ɹ�...\n");
	}
	// 2 ���ӷ����� connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret  = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("�������ӷ�����ʧ��...\n");
	}
	else {
		printf("���ӷ������ɹ�...\n");
	}

	
	while (true)
	{
		//3������������
		char cmdBuf[128] = {};
		scanf("%s",cmdBuf);
		//4 ������������
		if (0 == strcmp(cmdBuf, "exit"))
		{
			printf("�յ�exit������������");
			break;
		}else{
			//5 �������������������
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}

		// 6 ���շ�������Ϣ recv
		char recvBuf[128] = {};
		int nlen = recv(_sock, recvBuf, 128, 0);
		if (nlen > 0)
		{
			printf("���յ����ݣ�%s \n", recvBuf);
		}
	}
	// 7 �ر��׽���closesocket
	closesocket(_sock);
	//���Windows socket����
	WSACleanup();
	printf("���˳���");
	getchar();
	return 0;
}